
#include "Main.h"
#include "GameObjects.h"



void Level_1_Load(void)
{
	memset(sGameObjList, 0, sizeof(GameObjects) * GAME_OBJ_NUM_MAX);

	sGameObjNum = 0;

	memset(sGameObjInstList, 0, sizeof(_Player) * GAME_OBJ_INST_NUM_MAX);

	_Player = nullptr;


	GameObjects* _PlayerObjects;

	_PlayerObjects = sGameObjList + sGameObjNum++;
	_PlayerObjects->type = TYPE_PLAYER;

	AEGfxMeshStart();

	AEGfxTriAdd(
		0.5f, 0.5f, 0x292929, 1.0f, 0.0f,
		-0.5f, -0.5f, 0xC0C0C0, 0.0f, 1.0f,
		0.5f, -0.5f, 0x808080, 1.0f, 1.0f);
	AEGfxTriAdd(
		-0.5f, 0.5f, 0x808080, 0.0f, 0.0f,
		-0.5f, -0.5f, 0xC0C0C0, 0.0f, 1.0f,
		0.5f, 0.5f, 0x292929, 1.0f, 0.0f);

	_PlayerObjects->pMesh = AEGfxMeshEnd();

	AE_ASSERT_MESG(_PlayerObjects->pMesh, "Fail to create object!!");
}

void Level_1_Init(void)
{
	_Player = gameObjInstCreate(TYPE_PLAYER, PLAYER_SIZE, nullptr, nullptr, 0.0f);
	AE_ASSERT(_Player);

	
}


void Level_1_Update(void)
{


	//As of now i will be moving the X and Y coordinates with these, someone need to do the offsets.

	if (AEInputCheckCurr(AEVK_RIGHT) || AEInputCheckCurr(AEVK_D))
	{

	}
	if (AEInputCheckCurr(AEVK_LEFT) || AEInputCheckCurr(AEVK_A))
	{

	}
	if (AEInputCheckCurr(AEVK_DOWN) || AEInputCheckCurr(AEVK_S))
	{

	}
	if (AEInputCheckCurr(AEVK_UP) || AEInputCheckCurr(AEVK_W))
	{

	}


	//Updates projectile position.
	for (size_t i = 0; i < _bullet.size(); i++)
	{
		Projectile& projectile = _bullet[i];

		_bullet[i].updatePosition();

		//if bullet is out of the map, delete it. (Can change later, but now to prevent mem leak)
		if (projectile.x > AEGetWindowWidth() || projectile.x < -AEGetWindowWidth() || projectile.y > AEGetWindowHeight() || projectile.y < -AEGetWindowHeight())
		{
			_bullet.erase(_bullet.begin() + i);
			--i;
		}
	}






	for (unsigned long i = 0; i < 2048; i++)
	{
		

	}


}

void Level_1_Draw(void)
{
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);

	for (unsigned long i = 0; i < GAME_OBJ_INST_NUM_MAX; i++)
	{
		GameObjInstances* pInst = sGameObjInstList + i;

		// skip non-active object
		if ((pInst->flag & FLAG_ACTIVE) == 0)
			continue;


	}


}
void Level_1_Free(void)
{
	for (unsigned long i = 0; i < GAME_OBJ_INST_NUM_MAX; i++)
	{
		GameObjInstances* pInst = sGameObjInstList + i;
		// kill all object instances in the array using "gameObjInstDestroy"

		gameObjInstDestroy(pInst);
	}
}

void Level_1_Unload(void) 
{
	for (unsigned long i = 0; i < sGameObjInstNum; i++)
	{

		// kill all object instances in the array using "gameObjInstDestroy"

		AEGfxMeshFree(sGameObjList[i].pMesh);
	}
}