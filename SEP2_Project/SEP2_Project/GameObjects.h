#pragma once


#include "AEEngine.h"
#include "Main.h"


#include <queue>
#include <set>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>



#define MAX_ENEMIES				100
#define GAME_OBJ_NUM_MAX		16
#define GAME_OBJ_INST_NUM_MAX	128

#define FLAG_ACTIVE				1


//FILE DIRECTORY...

std::ifstream inputFileStream{ "..\\..\\Assets\\SaveFiles\\save.txt" };


f32 const PLAYER_SIZE = 60.0f; //Player Size...
f32 const AUG_GUN_SIZE = 40.0f; //Augment Gun Size
f32 const BOSS_SIZE = 30.0f;    //Boss Size
f32 const BULLET_SIZE = 20.0f;  //Bullet Size
f32 const ENEMY_SIZE = 25.0f;   //Enemy Size
f32 const BULLET_SPEED = 100.0f; //Bullet Speed
u32 const  MAX_BULLETS = 3; // Maximum number of bullets allowed
s32 bulletCount = 0; // Number of bullets fired
u32 enemyCount = 0;
f32 const BOUNDING_RECT_SIZE = 1.0f;
f64 enemyHealth = 1;
bool upgradeToggle = 0;



enum ObjectType {

	TYPE_PLAYER = 0,
	TYPE_BOSS,
	TYPE_BOSS_BULLETHELL_BULLET_1,
	TYPE_BULLET,
	TYPE_ENEMY,
	TYPE_PLAYER_HITBOX_INDICATOR,
	TYPE_EXPERIENCE,
	TYPE_AUGMENT1,
	TYPE_AUGMENT2,
	TYPE_AUGMENT3,
	TYPE_AUGMENT4,
	TYPE_AUGMENT5,

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
	AEVec2			scale;
	AEVec2			position;
	AEVec2			velocity;
	f32				direction;
	AABB			boundingBox;
	AEMtx33			transform;
	s32				health;
	bool			showTexture;
	bool            isInvincible;
	f64				iFrame;

};

//struct CompareDist
//{
//	bool operator()(const std::pair<float, GameObjInstances*>& p1, const std::pair<float, GameObjInstances*>& p2) const
//	{
//		return p1.first > p2.first;
//	}
//};




//Parameters: Original Objects
static GameObjects						sGameObjList[GAME_OBJ_NUM_MAX];
static unsigned long					sGameObjNum;

//Object Instances
static GameObjInstances					sGameObjInstList[GAME_OBJ_INST_NUM_MAX];
static unsigned long					sGameObjInstNum;

//Pointer to Objects...
static GameObjInstances* _Player;
static GameObjInstances* _Bullet;
static GameObjInstances* _Boss;
static GameObjInstances* _BossBullet;
static GameObjInstances* _Enemy;
static GameObjInstances* _PlayerHitbox;
static GameObjInstances* _ExpOrbs;
static GameObjInstances* _Augment_One;
static GameObjInstances* _Augment_Two;
static GameObjInstances* _Augment_Three;
static GameObjInstances* _Augment_Four;
static GameObjInstances* _Augment_Five;



bool				UIToggle = false;

u32					minutes = 0;
f64					enemySpeed = 1.0f;
f64					enemySize = 10.0f;
f64					_deltaTimeEnemySpawner;
f64					_deltaTime;
f64					_deltaTime_Shooting = 0.0f;
f64					_deltaTime_State = 0.0f;
bool				toggleHitBox = false;
AEVec2				velocity;
AEVec2				velocity2;
AEVec2				velocity3;
int					numBulletsBHell;
double				DelayMovement;
bool				hasDelayTimePassed = false;
double				DelayShoot;

float enemySpawnX = 0, enemySpawnY = 0;
double _delayTimeBullets;


float xRange = 683.0f;
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
f64 angle;
f64 angle2 = 0;
f64 rotationAngle = 3600;// number of rotations/360.
//Projectile projectile(0, 0, angle, projectileSpeed);



//Creating Vector(List) for instances..
std::vector<GameObjInstances> _bullet;
std::vector<GameObjInstances*> _enemyList;
std::vector<GameObjInstances*> remainingTargets;


//Variables for TYPES...

//Parameters: Testing
//Player
s16 _playerScale = -1;
u8  bossPhase = 0;


//Augments
f64 _rotation_Aug = 0.0f;

s16 _enemyScale = 1; //1 is follow right, -1 is turn left,

AEVec2 ENEMY_DIRECTION;
AEVec2 ENEMY_VELOCITY;


f64 AUGMENT_1_FIRE_TIMER      = 0;
f64 AUGMENT_1_FIRE_INTERVAL   = 2.0f;
AEVec2 AUGMENT_1_MOUSE_POSITION;
AEVec2 AUGMENT_1_DIRECTION;

//NOT REQUIRED AS IT IS JUST A ROLLING ROCK
//f64 AUGMENT_2_FIRE_TIMER      = 0;
//f64 AUGMENT_2_FIRE_INTERVAL   = 2.0f;
AEVec2 AUGMENT_2_DIRECTION;

f64 AUGMENT_3_FIRE_TIMER	  = 0.0f;
f64 AUGMENT_3_FIRE_INTERVAL   = 10.0f;
f64 AUGMENT_3_CLOSEST_DISTANCE = 2147483647.0f; 
f64 AUGMENT_3_CLOSEST_ENEMY = 0.0f;

f64 AUGMENT_4_FIRE_TIMER;
f64 AUGMENT_4_FIRE_INTERVAL;

f64 AUGMENT_5_FIRE_TIMER;
f64 AUGMENT_5_FIRE_INTERVAL;

s32 _Player_Experience = 0;
s32 _Player_Level = 1;

int experienceCurve(int level, int& playerExperience)
{
	int baseExp = 15;
	int increment = 2 * ((level - 1) / 5);
	int requiredExp = baseExp + (level - 1) * increment;

	if (playerExperience >= requiredExp) {
		// Increment the player's level and subtract the required experience from their total
		playerExperience -= requiredExp;
		level++;
	}

	return level;
}


GameObjInstances* FindNearestEnemy(GameObjInstances* player)
{
	float minDistance = FLT_MAX;
	GameObjInstances* nearestEnemy = nullptr;
	for (int i = 0; i < GAME_OBJ_INST_NUM_MAX; ++i)
	{
		GameObjInstances* pInst = sGameObjInstList + i;
		if (pInst != player && pInst->pObject->type == TYPE_ENEMY &&
			pInst->position.x > player->position.x + 200 || pInst->position.x < player->position.x - 200 ||
			pInst->position.y > player->position.y + 200 || pInst->position.y < player->position.y - 200)
		{
			float distance = AEVec2Distance(&pInst->position, &player->position);
			if (distance < minDistance)
			{
				minDistance = distance;
				nearestEnemy = pInst;
			}
		}
	}
	return nearestEnemy;
}


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
			pInst->scale.x = scale;
			pInst->scale.y = scale;
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
