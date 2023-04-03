#pragma once


#include "AEEngine.h"
#include "Main.h"

#include <fstream>
#include <string>



#define MAX_ENEMIES				100
#define GAME_OBJ_NUM_MAX		16
#define GAME_OBJ_INST_NUM_MAX	1024

#define FLAG_ACTIVE				1

//set flag for pause to false (game is running)
bool pause = false;



f32 const						PLAYER_SIZE = 60.0f;		//Definition of Player Size...
f32 const						AUG_GUN_SIZE = 40.0f;		//Definition of Augment Gun Size
f32 const						BOSS_SIZE = 30.0f;			//Definition of Boss Size
f32 const						BULLET_SIZE = 20.0f;		//Definition of Bullet Size
f32 const						ENEMY_SIZE = 25.0f;			//Definition of Enemy Size

u32 const						MAX_BULLETS = 3;			//Definition of Maximum number of bullets allowed
s32								bulletCount = 0;			//Definition of Number of bullets fired
int								enemyCount = 0;				//Definition of enemyCount to 0
f32 const						BOUNDING_RECT_SIZE = 1.0f;	//Definition of Bounding Rect Size to 1.0f
f32								enemyHealth = 1;			//Definition of enemyHealth
bool							upgradeToggle = 0;			//Definition of upgradeToggle
extern int						SkillPoint = 0;				//Definition of SkillPoint
// Initialize cursor coordinates
s32								cursorX;					//Declaration of cursorX
s32								cursorY;					//Declaration of cursorY


//namespace for boss...
namespace boss {
	AEVec2 velocity;
	AEVec2 velocity2;
	int numBulletsBHell;
	double DelayMovement;
	bool hasDelayTimePassed = false;
	double DelayShoot;
}


//enum for the objects...
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

//Boss phase enum
enum BossPhase {
	TYPE_BHELL1,
	TYPE_BHELL2,
	TYPE_BHELL3,
	TYPE_BHELL4,
	TYPE_BHELL5
};


//GameObjects class
class GameObjects {
private:

public:
	unsigned long type;
	AEGfxVertexList* pMesh;

};
//GameObjectInstances class
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


//Flag to toggle UI
bool				UIToggle = false;


u32					minutes = 0;						//Definition of Minutes 
f32					enemySpeed = 1.0f;					//Definition of enemySpeed
f32					enemySize = 10.0f;					//Definition of enemySize
f32					_deltaTime_Shooting = 0.0f;			//Definition of _deltaTime_Shooting
f32					_deltaTime_State = 0.0f;			//Definition of _deltaTime_State 
bool				toggleHitBox = false;				//Definition of toggleHitBox
bool				hasDelayTimePassed = false;			//Definition of hasDelayTimePassed

AEVec2				velocity;							//Declaration of velocity
AEVec2				velocity2;							//Declaration of velocity2
AEVec2				velocity3;							//Declaration of velocity3
int					numBulletsBHell;					//Declaration of numBulletsBHell
double				DelayMovement;						//Declaration of DelayMovement
double				DelayShoot;							//Declaration of DelayShoot
f32					_deltaTimeEnemySpawner;				//Declaration of _deltaTimeEnemySpawner
f32					_deltaTime;							//Declaration of _deltaTime


float				enemySpawnX = 0, enemySpawnY = 0;
double				_delayTimeBullets;


float				xRange = 683.0f;					//Definition of xRange
float				yRange = 50.0f;						//Definition of yRange

float				xSpeed = 2.0f;						//Definition of xSpeed
float				ySpeed = 4.0f;						//Definition of ySpeed

float				displacementX;						//Declaration of displacementX
float				displacementY;						//Declaration of displacementY

float				yPosition;							//Declaration of yPosition

float				frequency;							//Declaration of frequency
float				times;								//Declaration of times



int					xSpacing = 10;						// Define the x spacing between bullets


int					numBullets = 10;					// Define the number of bullets to create


int					minY = -200;						// Definition the min y position range for the bullet spawn location
int					maxY = 200;							// Definition the max y position range for the bullet spawn location


const float			totalDuration = 15.0f;				// Definition of Total duration of movement in seconds
const float			slowDuration = 3.0f;				// Definition Duration of slow movement at the beginning
				
static float		timer = 0.0f;						// Timer to keep track of the elapsed time

float				rotationA = 0.0f;					//Definition rotationA


const float			halfScreenWidth = AEGetWindowWidth() / 2.0f; // Half of the screen width

//parameters for constructor to fufil..
const f32			GameObjInstancesSpeed = 1.0f;		//Definition of GameObject Instance Speed
const f32			projectileSpeed = 90.0f;			//Definition of Projectile Speed
const f32			GameObjInstances_SIZE = 10.0f;		//Definition of GameObject Instance Size





s32					mouseX, mouseY;						//Declaration of mouseX and mouseY


f32					angle = 0;							//Definition of angle
f32					angle2 = 0;							//Definition of angle2
f32					rotationAngle = 3600;				//Definition of rotationAngle



//Variables for TYPES...

//Parameters: Testing
//Player
s16					_playerScale = -1;					//Definition the playerScale
u8					bossPhase = 0;						//Definition the boss Phase to 0

//Return to position 0, at the end of a calculation..
f32					BOSS_X_PHASE_4 = 0;					//Definition of BOSS_X_PHASE4
f32					BOSS_Y_PHASE_4 = 0;					//Definition of BOSS_Y_PHASE4
f32					BOSS_SPEED_PHASE_4 = 0;				//Definition of BOSS_SPEED_PHASE_4



//Augments
f32					_rotation_Aug = 0.0f;				//Definition of Rotation Augment

s16					_enemyScale = 1;					//Definition of enemyScale: 1 is follow right, -1 is turn left,

AEVec2				ENEMY_DIRECTION;					//Declaration of Vectors ENEMY_DIRECTION
AEVec2				ENEMY_VELOCITY;						//Declaration of Vectors ENEMY_VELOCITY


f32					AUGMENT_1_FIRE_TIMER      = 0;		//Definition of AUGMENT_1_FIRE_TIMER
AEVec2				AUGMENT_1_MOUSE_POSITION;			//Declaration of AUGMENT_1_MOUSE_POSITION
AEVec2				AUGMENT_1_DIRECTION;				//Declaration of AUGMENT_1_DIRECTION
f32					AUGMENT_1_BULLET_SPEED = 100.0f;	//Definition of AUGMENT_1_BULLET_SPEED

AEVec2				AUGMENT_2_DIRECTION;				//Declaration of AUGMENT_2_DIRECTION

f32					AUGMENT_3_FIRE_TIMER	  = 0.0f;	//Definition of AUGMENT_3_FIRE_TIMER
f32					AUGMENT_3_FIRE_INTERVAL   = 2.0f;	//Definition of AUGMENT_3_FIRE_INTERVAL

AEVec2				AUGMENT_3_DIRECTION;				//Declaration of Vector AUGMENT_3_DIRECTION

f32					AUGMENT_3_OFF_TIMER       = 0.0f;	//Definition of AUGMENT_3_OFF_TIMER
f32					AUGMENT_3_OFF_INTERVAL	  = 0.2f;	//Definition of AUGMENT_3_OFF_INTERVAL
														
f32					AUGMENT_4_FIRE_TIMER      = 0.0f;	//Definition of AUGMENT_4_FIRE_TIMER
f32					AUGMENT_4_FIRE_INTERVAL   = 4.0f;	//Definition of AUGMENT_4_FIRE_INTERVAL


f32					AUGMENT_4_PROJECTILE_TIMER  = 0.0f;	//Definition of AUGMENT_4_PROJECTILE_TIMER			
f32					AUGMENT_4_PROJECTILE_INTERVAL = 2.0f;//Definition of AUGMENT_4_PROJECTILE_INTERVAL	

f32					AUGMENT_4_EXPLOSION_TIMER = 0.0f;	 //Definition of AUGMENT_4_EXPLOSION_TIMER
f32					AUGMENT_4_EXPLOSION_INTERVAL = 1.0f; //Definition of AUGMENT_4_EXPLOSION_INTERVAL

bool				AUGMENT_4_PROJECTILE_ACTIVE = false; //Definition of Flag AUGMENT_4_PROJECTILE_ACTIVE
bool				AUGMENT_4_EXPLOSION_ACTIVE = false;	 //Definition of Flag AUGMENT_4_EXPLOSION_ACTIVE

AEVec2				AUGMENT_4_MOUSE_POSITION;			 //Declaration of Vectors AUGMENT_4_MOUSE_POSITION
AEVec2				AUGMENT_4_DIRECTION;				 //Declaration of Vectors AUGMENT_4_DIRECTION

f32					AUGMENT_4_ANGLE = 0.0f;				//Definition of AUGMENT_4_ANGLE
f32					AUGMENT_4_DISTANCE = 0.0f;			//Definition of AUGMENT_4_DISTANCE
f32					AUGMENT_4_DISTANCE_TOLERANCE = 0.0f;//Definition of AUGMENT_4_DISTANCE_TOLERANCE
f32					AUGMENT_4_TARGET_DISTANCE = 0.0f;	//Definition of AUGMENT_4_TARGET_DISTANCE
f32 const			AUGMENT_4_BULLET_SPEED = 100.0f;	//Definition of AUGMENT_4_BULLET_SPEED


s32					_Player_Experience = 0;				//Definition of _Player_Experience
s32					_Player_Level = 1;					//Definition of _Player_Level

//Experience Curve
int experienceCurve(int level, int& playerExperience, int& reqExp)
{
	//15 17 19 21 23 --> 27 29 31 33 35 --> 39 41 43 45 47 --> 51...
	//EVERY 5 LEVELS +4 experience

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


//GameObjectInstanceCreate Function
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

//Destroy GameOBjects
void gameObjInstDestroy(GameObjInstances* pInst)
{

	// if instance is destroyed before, just return
	if (pInst->flag == 0)
		return;
	pInst->flag = 0;

}
