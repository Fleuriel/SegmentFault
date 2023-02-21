#pragma once
#include <vector>
#include "AEEngine.h"
#include "Main.h"
#include <queue>
#include <set>
#include <algorithm>



#define MAX_ENEMIES				100
#define GAME_OBJ_NUM_MAX		64
#define GAME_OBJ_INST_NUM_MAX	2048
#define GameObjInstances_LIFE	3	//FOR NOW

#define FLAG_ACTIVE				1

f32 const PLAYER_SIZE  = 80.0f; //Player Size...
f32 const AUG_GUN_SIZE = 40.0f; //Augment Gun Size
f32 const BOSS_SIZE	= 30.0f;    //Boss Size
f32 const BULLET_SIZE = 20.0f;  //Bullet Size
f32 const ENEMY_SIZE = 25.0f;   //Enemy Size
f32 const BULLET_SPEED = 100.0f; //Bullet Speed
u32 const  MAX_BULLETS = 3; // Maximum number of bullets allowed
s32 bulletCount = 0; // Number of bullets fired
u32 enemyCount = 0;
f32 const BOUNDING_RECT_SIZE = 1.0f;

enum ObjectType {

	TYPE_PLAYER = 0,
	TYPE_BOSS,
	TYPE_AUGMENT1,
	TYPE_BOSS_BULLETHELL_BULLET_1,
	TYPE_BULLET,
	TYPE_ENEMY,
	TYPE_PLAYER_HITBOX_INDICATOR,
	TYPE_BOSS_SPAWNER,


};


enum BossPhase {
	TYPE_BHELL1,
	TYPE_BHELL2,
	TYPE_BHELL3,
	TYPE_BHELL4,
	TYPE_BOWAP
};



class GameObjects {
private:

public:
	unsigned long type;
	AEGfxVertexList* pMesh;
};

class GameObjInstances 
{
private:

public:
	GameObjects*	pObject;
	u64				flag;
	f32				scaleX;
	f32				scaleY;
	AEVec2			position;
	AEVec2			velocity;
	f32				direction;
	AABB			boundingBox;
	AEMtx33			transform;
	bool			isAlive;
	s32				health;
};

//struct CompareDist
//{
//	bool operator()(const std::pair<float, GameObjInstances*>& p1, const std::pair<float, GameObjInstances*>& p2) const
//	{
//		return p1.first > p2.first;
//	}
//};

class Projectile {
public:
	f64 x, y;
	f64 angle;
	f64 speed;

	Projectile(f64 x = 0, f64 y = 0, f64 angle = 0, f64 speed = 0)
		: x(x), y(y), angle(angle), speed(speed) {}

	void updatePosition() {
		x += speed * cos(angle);
		y += speed * sin(angle);
	}
};

class Enemy {
private:
	f64 x, y, distanceX, distanceY;
	f64 angle;
	f64 speed;
	
public:
	//Enemy Constructor with x,y ,angle and speed of enemy.
	Enemy(f64 x = 0, f64 y = 0, f64 angle = 0, f64 speed = 0)
		: x(x), y(y), angle(angle), speed(speed) {}

	//Copy Constructor
//	Enemy (Enemy const& e){ }
	//Destructor..
//	~Enemy(){}

	void updatePosition() {
		x += speed * cos(angle);
		y += speed * sin(angle);
	}

	//void updatePosition(double x, double y) {
	//	distanceX = this->x - x;
	//	distanceY = this->y - y;

	//	double magnitude = sqrt(pow(distanceX, 2) + pow(distanceY, 2));
	//	distanceX /= magnitude;
	//	distanceY /= magnitude;

	//	this->x -= distanceX * speed;
	//	this->y -= distanceY * speed;
	//}
	f64 getX() { return x; }
	f64 getY() { return y; }
	f64 getAngle()  { return angle; }
};





//Parameters: Testing
//Player
s16 _playerScale = -1;
u8  bossPhase = 0;


//Augments
f64 _rotation_Aug = 0.0f;

s16 _enemyScale = 1; //1 is follow right, -1 is turn left,


//Parameters: Original Objects
static GameObjects						sGameObjList[GAME_OBJ_NUM_MAX];
static unsigned long					sGameObjNum;								

//Object Instances
static GameObjInstances					sGameObjInstList[GAME_OBJ_INST_NUM_MAX];
static unsigned long					sGameObjInstNum;

//Pointer to Objects...
static GameObjInstances*				_Player;
static GameObjInstances*				_Bullet;
static GameObjInstances*				_Augment_Gun;
static GameObjInstances*				_Boss;
static GameObjInstances*				_BossBullet;
static GameObjInstances*				_Enemy;
static GameObjInstances*				_PlayerHitbox;
static GameObjInstances*				_BulletSpawner;





f64					enemySpeed				=	1.0f;
f64					enemySize				=	10.0f;
f64					_deltaTime;
f64					_deltaTime_Shooting		=   0.0f;
bool				toggleHitBox			= false;
AEVec2				velocity;
AEVec2				velocity2;
AEVec2				velocity3;
int					numBulletsBHell;
double				DelayMovement;
bool				hasDelayTimePassed		= false;
double				DelayShoot;

double _delayTimeBullets;


float xRange  = 683.0f;
float yRange = 50.0f;
float ySpeed = 4.0f;
float yPosition;

float xSpeed = 2.0f;
float frequency;
float times;
float displacementX;
float displacementY;

// Define the x spacing between bullets
int xSpacing = 10;

// Define the number of bullets to create
int numBullets = 10;

// Define the y position range for the bullet spawn location
int minY = -200;
int maxY = 200;

// Define the movement parameters
const float totalDuration = 15.0f; // Total duration of movement in seconds
const float slowDuration = 3.0f; // Duration of slow movement at the beginning
const float halfScreenWidth = AEGetWindowWidth() / 2.0f; // Half of the screen width
				// Update the position of pInst
static float timer = 0.0f; // Timer to keep track of the elapsed time

float rotationA = 0.0f;
static bool spawnBulletSpawner = true;


//parameters for constructor to fufil..
const f64 GameObjInstancesSpeed = 1.0f;
const f32 projectileSpeed = 90.0f;
const f64 GameObjInstances_SIZE = 10.0f;




//Parameters GameObjInstances Mouse:
//s32* mouseX = new s32, * mouseY = new s32

s32 mouseX, mouseY;


//Creating the objects for enemy and Projectile.
Enemy enemy(enemyX[0], enemyY[0], 0 , GameObjInstancesSpeed);
f64 angle = atan2(enemy.getY() - 0, enemy.getX());
f64 angle2 = 0;
f64 rotationAngle = 3600;// number of rotations/360.
//Projectile projectile(0, 0, angle, projectileSpeed);



//Creating Vector(List) for instances..
std::vector<GameObjInstances> _bullet;
std::vector<GameObjInstances*> _enemyList;
std::vector<GameObjInstances*> remainingTargets;


//Assets (Images)




//Assets Mesh





//Assets (Sound)




GameObjInstances* gameObjInstCreate(unsigned long type,
	float scale,
	AEVec2* pPos,
	AEVec2* pVel,
	float dir)
{
	AEVec2 zero;
	AEVec2Zero(&zero);
	AE_ASSERT_PARM(type < sGameObjNum);

	// loop through the object instance list to find a non-used object instance
	for (unsigned long i = 0; i < GAME_OBJ_INST_NUM_MAX; i++)
	{
		GameObjInstances* pInst = sGameObjInstList + i;

		// check if current instance is not used
		if (pInst->flag == 0)
		{
			// it is not used => use it to create the new instance
			pInst->pObject = sGameObjList + type;
			pInst->flag = FLAG_ACTIVE;
			pInst->scaleX = scale;
			pInst->scaleY = scale;
			pInst->position = pPos ? *pPos : zero;
			pInst->velocity = pVel ? *pVel : zero;
			pInst->direction = dir;
			
			// return the newly created instance
			return pInst;
		}
	}

	// cannot find empty slot => return 0
	return 0;
}

void gameObjInstDestroy(GameObjInstances* pInst)
{
	
	// if instance is destroyed before, just return
	if (pInst->flag == 0)
		return;
//	std::cout << "Destroyed" << pInst->pObject->type << '\n';

	// zero out the flag
	pInst->flag = 0;

}
