#pragma once
#include <vector>
#include "AEEngine.h"
#include "Main.h"


#define MAX_ENEMIES				100
#define GAME_OBJ_NUM_MAX		64
#define GAME_OBJ_INST_NUM_MAX	2048
#define GameObjInstances_LIFE	3	//FOR NOW

#define FLAG_ACTIVE				1

float const PLAYER_SIZE  = 80.0f;
float const AUG_GUN_SIZE = 40.0f;
float const BOSS_SIZE	= 30.0f;
float const BULLET_SIZE = 20.0f;

enum ObjectType {

	TYPE_PLAYER = 0,
	TYPE_BOSS,
	TYPE_AUGMENT1,
	TYPE_BOSS_BULLETHELL_BULLET_1,
	TYPE_BULLET,
	TYPE_ENEMY

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
};

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


//Augments
f64 _rotation_Aug = 0.0f;

//Enemy (Now)
f64 enemyX[MAX_ENEMIES] = { 200.0f , 900.0f, 800.0f, 850.0f, 754.0f, 723.0f, 237.0f, 937.0f, 823.0f, 236.0f };
f64 enemyY[MAX_ENEMIES] = { 200.0f , 100.0f, 200.0f, 350.0f, 664.0f, 423.0f, 537.0f, 737.0f, 423.0f, 736.0f };
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





//Function to create/destroy a game object instance...

//GameObjInstances*						gameObjInstCreate(unsigned long type, f32 scale, AEVec2* pPos, AEVec2* pVel, f32 dir);
//
//void									gameObjInstDestroy(GameObjInstances* pInst);


f64		enemySpeed		=	1.0f;
f64		enemySize		=	10.0f;

//parameters for constructor to fufil..
const f64 GameObjInstancesSpeed = 1.0f;
const f32 projectileSpeed = 75.0f;
const f64 GameObjInstances_SIZE = 10.0f;




//Parameters GameObjInstances Mouse:
s32* mouseX = new s32, * mouseY = new s32;



//Creating the objects for enemy and Projectile.
Enemy enemy(enemyX[0], enemyY[0], 0 , GameObjInstancesSpeed);
f64 angle = atan2(enemy.getY() - 0, enemy.getX());
f64 rotationAngle = 3600;// number of rotations/360.
//Projectile projectile(0, 0, angle, projectileSpeed);



//Creating Vector(List) for instances..
std::vector<GameObjInstances> _bullet;



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
	
	//std::cout << "Destroyed" << pInst->pObject->type << '\n';
	// if instance is destroyed before, just return
	if (pInst->flag == 0)
		return;

	// zero out the flag
	pInst->flag = 0;

}
