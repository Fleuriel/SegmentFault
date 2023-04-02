#pragma once


#include "AEEngine.h"
#include "Main.h"


#include <set>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>



#define MAX_ENEMIES				100
#define GAME_OBJ_NUM_MAX		16
#define GAME_OBJ_INST_NUM_MAX	1024

#define FLAG_ACTIVE				1


//FILE DIRECTORY...

std::ifstream inputFileStream { "Assets\\SaveFiles\\Currency.txt" };
std::ifstream inputFileStream1{ "Assets\\SaveFiles\\PlayerShipModel.txt" };
std::ifstream inputFileStream2{ "Assets\\SaveFiles\\HighScore.txt" };
std::ifstream inputFileStream3{ "Assets\\SaveFiles\\PlayerStats.txt" };

bool pause = false;



f32 const PLAYER_SIZE = 60.0f; //Player Size...
f32 const AUG_GUN_SIZE = 40.0f; //Augment Gun Size
f32 const BOSS_SIZE = 30.0f;    //Boss Size
f32 const BULLET_SIZE = 20.0f;  //Bullet Size
f32 const ENEMY_SIZE = 25.0f;   //Enemy Size

u32 const  MAX_BULLETS = 3; // Maximum number of bullets allowed
s32 bulletCount = 0; // Number of bullets fired
int enemyCount = 0;
f32 const BOUNDING_RECT_SIZE = 1.0f;
f32 enemyHealth = 1;
bool upgradeToggle = 0;
extern int SkillPoint = 0;
// Initialize cursor coordinates
s32 cursorX;
s32 cursorY;



namespace boss {
	AEVec2 velocity;
	AEVec2 velocity2;
	int numBulletsBHell;
	double DelayMovement;
	bool hasDelayTimePassed = false;
	double DelayShoot;
}



enum ObjectType {

	TYPE_PLAYER = 0,
	TYPE_BOSS,
	TYPE_BOSS_BULLETHELL_BULLET_1,
	TYPE_BULLET,
	TYPE_ENEMY,
	TYPE_PLAYER_HITBOX_INDICATOR,
	TYPE_CURRENCY,
	TYPE_AUGMENT1,
	TYPE_AUGMENT2,
	TYPE_AUGMENT3,
	TYPE_AUGMENT4,
	TYPE_AUGMENT4_PROJECTILE,
	TYPE_AUGMENT4_EXPLOSION,
	TYPE_AUGMENT5,

};


enum BossPhase {
	TYPE_BHELL1,
	TYPE_BHELL2,
	TYPE_BHELL3,
	TYPE_BHELL4,
	TYPE_BHELL5
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
	f32				iFrame;

};

//struct CompareDist
//{
//	bool operator()(const std::pair<float, GameObjInstances*>& p1, const std::pair<float, GameObjInstances*>& p2) const
//	{
//		return p1.first > p2.first;
//	}
//};




//Parameters: Original Objects
static GameObjects						*sGameObjList;
static unsigned long					sGameObjNum;

//Object Instances
static GameObjInstances					*sGameObjInstList;
static unsigned long					sGameObjInstNum;

//Pointer to Objects...
static GameObjInstances					*_Player;
static GameObjInstances					*_Bullet;
static GameObjInstances					*_Boss;
static GameObjInstances					*_BossBullet;
static GameObjInstances					*_Enemy;
static GameObjInstances					*_PlayerHitbox;
static GameObjInstances					*_ExpOrbs;
static GameObjInstances					*_Augment_One;
static GameObjInstances					*_Augment_Two;
static GameObjInstances					*_Augment_Three;
static GameObjInstances					*_Augment_Four;
static GameObjInstances					*_Augment_Five;



bool				UIToggle = false;

u32					minutes = 0;
f32					enemySpeed = 1.0f;
f32					enemySize = 10.0f;
f32					_deltaTimeEnemySpawner;
f32					_deltaTime;
f32					_deltaTime_Shooting = 0.0f;
f32					_deltaTime_State = 0.0f;
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
const f32 GameObjInstancesSpeed = 1.0f;
const f32 projectileSpeed = 90.0f;
const f32 GameObjInstances_SIZE = 10.0f;




//Parameters GameObjInstances Mouse:
//s32* mouseX = new s32, * mouseY = new s32

s32 mouseX, mouseY;


//Creating the objects for enemy and Projectile.
f32 angle;
f32 angle2 = 0;
f32 rotationAngle = 3600;// number of rotations/360.
//Projectile projectile(0, 0, angle, projectileSpeed);



//Variables for TYPES...

//Parameters: Testing
//Player
s16 _playerScale = -1;
u8  bossPhase = 0;

//Return to position 0, at the end of a calculation..
f32 BOSS_X_PHASE_4 = 0;
f32 BOSS_Y_PHASE_4 = 0;
f32 BOSS_SPEED_PHASE_4 = 0;



//Augments
f32 _rotation_Aug = 0.0f;

s16 _enemyScale = 1; //1 is follow right, -1 is turn left,

AEVec2 ENEMY_DIRECTION;
AEVec2 ENEMY_VELOCITY;


f32 AUGMENT_1_FIRE_TIMER      = 0;
f32 AUGMENT_1_FIRE_INTERVAL   = 2.0f;
AEVec2 AUGMENT_1_MOUSE_POSITION;
AEVec2 AUGMENT_1_DIRECTION;
f32 AUGMENT_1_BULLET_SPEED = 100.0f;

//NOT REQUIRED AS IT IS JUST A ROLLING ROCK
//f32 AUGMENT_2_FIRE_TIMER      = 0;
//f32 AUGMENT_2_FIRE_INTERVAL   = 2.0f;
AEVec2 AUGMENT_2_DIRECTION;

f32 AUGMENT_3_FIRE_TIMER	  = 0.0f;
f32 AUGMENT_3_FIRE_INTERVAL   = 2.0f;
AEVec2 AUGMENT_3_DIRECTION;
f32 AUGMENT_3_OFF_TIMER       = 0.0f;
f32 AUGMENT_3_OFF_INTERVAL	  = 0.2f;

f32 AUGMENT_4_FIRE_TIMER      = 0.0f;
f32 AUGMENT_4_FIRE_INTERVAL   = 4.0f;


f32 AUGMENT_4_PROJECTILE_TIMER  = 0.0f;
f32 AUGMENT_4_PROJECTILE_INTERVAL = 2.0f;

f32 AUGMENT_4_EXPLOSION_TIMER = 0.0f;
f32 AUGMENT_4_EXPLOSION_INTERVAL = 1.0f;

bool AUGMENT_4_PROJECTILE_ACTIVE = false;
bool AUGMENT_4_EXPLOSION_ACTIVE = false;

AEVec2 AUGMENT_4_MOUSE_POSITION;
AEVec2 AUGMENT_4_DIRECTION;

f32 AUGMENT_4_ANGLE = 0.0f;
f32 AUGMENT_4_DISTANCE = 0.0f;
f32 AUGMENT_4_DISTANCE_TOLERANCE = 0.0f;
f32 AUGMENT_4_TARGET_DISTANCE = 0.0f;
f32 const AUGMENT_4_BULLET_SPEED = 100.0f; //Bullet Speed


f32 AUGMENT_5_FIRE_TIMER = 0.0f;
f32 AUGMENT_5_FIRE_INTERVAL = 5.0f;

s32 _Player_Experience = 0;
s32 _Player_Level = 1;

int experienceCurve(int level, int& playerExperience, int& reqExp)
{
	

	if (playerExperience >= reqExp) {
		// Increment the player's level and subtract the required experience from their total
		playerExperience -= reqExp;
		level++;
		SkillPoint++;
		int increment = 2 * ((level - 1) / 5);
		reqExp += (level - 1) * increment;
	}
	return level;
}



GameObjInstances* gameObjInstCreate(unsigned long type,
	float scale,
	AEVec2* pPos,
	AEVec2* pVel,
	double dir)
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
			pInst->direction = static_cast<f32>(dir);
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
	pInst->flag = 0;

}
