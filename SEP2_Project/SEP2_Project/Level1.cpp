
#include "Main.h"
#include "GameObjects.h"



void Level_1_Load(void)
{
	memset(sGameObjList, 0, sizeof(GameObjects) * GAME_OBJ_NUM_MAX);

	sGameObjNum = 0;

	memset(sGameObjInstList, 0, sizeof(_Player) * GAME_OBJ_INST_NUM_MAX);
	sGameObjInstNum = 0;

	_Player = nullptr;
	_Bullet = nullptr;
	_Boss   = nullptr;
	_BossBullet = nullptr;


	GameObjects* _PlayerObjects;
	GameObjects* _BulletObjects;
	GameObjects* _BossObjects;
	GameObjects* _AugmentGunObjects;
	GameObjects* _BossBulletObjects_1;

	//0
	_PlayerObjects = sGameObjList + sGameObjNum++;
	_PlayerObjects->type = TYPE_PLAYER;

	AEGfxMeshStart();

	AEGfxTriAdd(
		0.5f, 0.5f, 0xFFFFFF, 1.0f, 0.0f,
		-0.5f, -0.5f, 0xFFFFFF, 0.0f, 1.0f,
		0.5f, -0.5f, 0xFFFFFF, 1.0f, 1.0f);
	AEGfxTriAdd(
		-0.5f, 0.5f, 0xFFFFFF, 0.0f, 0.0f,
		-0.5f, -0.5f, 0xFFFFFF, 0.0f, 1.0f,
		0.5f, 0.5f, 0xFFFFFF, 1.0f, 0.0f);
	_PlayerObjects->pMesh = AEGfxMeshEnd();
	AE_ASSERT_MESG(_PlayerObjects->pMesh, "Fail to create object!!");

	//1
	_BossObjects = sGameObjList + sGameObjNum++;
	_BossObjects->type = TYPE_BOSS;

	AEGfxMeshStart();

	AEGfxTriAdd(
		0.5f, 0.5f, 0x808080, 1.0f, 0.0f,
		-0.5f, -0.5f, 0x808080, 0.0f, 1.0f,
		0.5f, -0.5f, 0x696969, 1.0f, 1.0f);
	AEGfxTriAdd(
		-0.5f, 0.5f, 0x696969, 0.0f, 0.0f,
		-0.5f, -0.5f, 0x696969, 0.0f, 1.0f,
		0.5f, 0.5f, 0x808080, 1.0f, 0.0f);
	_BossObjects->pMesh = AEGfxMeshEnd();
	AE_ASSERT_MESG(_BossObjects->pMesh, "Fail to create object!!");

	//2
	_AugmentGunObjects = sGameObjList + sGameObjNum++;
	_AugmentGunObjects->type = TYPE_AUGMENT1;

	AEGfxMeshStart();

	AEGfxTriAdd(
		0.5f, 0.5f, 0x808080, 1.0f, 0.0f,
		-0.5f, -0.5f, 0x808080, 0.0f, 1.0f,
		0.5f, -0.5f, 0x696969, 1.0f, 1.0f);
	AEGfxTriAdd(
		-0.5f, 0.5f, 0x696969, 0.0f, 0.0f,
		-0.5f, -0.5f, 0x696969, 0.0f, 1.0f,
		0.5f, 0.5f, 0x808080, 1.0f, 0.0f);
	_AugmentGunObjects->pMesh = AEGfxMeshEnd();

	//3
	_BulletObjects = sGameObjList + sGameObjNum++;
	_BulletObjects->type = TYPE_BULLET;

	AEGfxMeshStart();

	AEGfxTriAdd(
		0.5f, 0.5f, 0x808080, 1.0f, 0.0f,
		-0.5f, -0.5f, 0x808080, 0.0f, 1.0f,
		0.5f, -0.5f, 0x696969, 1.0f, 1.0f);
	AEGfxTriAdd(
		-0.5f, 0.5f, 0x696969, 0.0f, 0.0f,
		-0.5f, -0.5f, 0x696969, 0.0f, 1.0f,
		0.5f, 0.5f, 0x808080, 1.0f, 0.0f);
	_BulletObjects->pMesh = AEGfxMeshEnd();
	AE_ASSERT_MESG(_BulletObjects->pMesh, "Fail to create object!!");

	//4	
	_BossBulletObjects_1 = sGameObjList + sGameObjNum++;
	_BossBulletObjects_1->type = TYPE_BOSS_BULLETHELL_BULLET_1;

	AEGfxMeshStart();

	AEGfxTriAdd(
		0.5f, 0.5f, 0x808080, 1.0f, 0.0f,
		-0.5f, -0.5f, 0x808080, 0.0f, 1.0f,
		0.5f, -0.5f, 0x696969, 1.0f, 1.0f);
	AEGfxTriAdd(
		-0.5f, 0.5f, 0x696969, 0.0f, 0.0f,
		-0.5f, -0.5f, 0x696969, 0.0f, 1.0f,
		0.5f, 0.5f, 0x808080, 1.0f, 0.0f);
	_BossBulletObjects_1->pMesh = AEGfxMeshEnd();
	AE_ASSERT_MESG(_BossBulletObjects_1->pMesh, "Fail to create object!!");


}

void Level_1_Init(void)
{
	//0
	_Player = gameObjInstCreate(TYPE_PLAYER, PLAYER_SIZE, nullptr, nullptr, 0.0f);
	AE_ASSERT(_Player);
	//1
	_Boss = gameObjInstCreate(TYPE_BOSS, BOSS_SIZE, nullptr, nullptr, 0.0f);
	AE_ASSERT(_Boss);
	//2
	_Augment_Gun = gameObjInstCreate(TYPE_AUGMENT1, AUG_GUN_SIZE, nullptr, nullptr, 0.0f);
	AE_ASSERT(_Augment_Gun);
	//3
	_BossBullet = gameObjInstCreate(TYPE_BOSS_BULLETHELL_BULLET_1, BULLET_SIZE, nullptr, nullptr, 0.0f);
	AE_ASSERT(_Boss);
	//4
	_Bullet = gameObjInstCreate(TYPE_BULLET, BULLET_SIZE, nullptr, nullptr, 0.0f);
	AE_ASSERT(_Bullet);

}


void Level_1_Update(void)
{


	//As of now i will be moving the X and Y coordinates with these, someone need to do the offsets.



	//CHECK TRIGGERED ONLY
	//THE FOLLOWING ONLY CHECK ONCE WHEN PRESSED.
	if (AEInputCheckTriggered(AEVK_LEFT) || AEInputCheckTriggered(AEVK_A))
	{
		if (_playerScale > 0)
		{
			_Player->scaleX *= -1;
			_playerScale *= -1;
		}
	}

	if (AEInputCheckTriggered(AEVK_RIGHT) || AEInputCheckTriggered(AEVK_D))
	{
		if (_playerScale < 0)
		{
			_Player->scaleX *= -1;
			_playerScale *= -1;
		}
	}

	//KeyDown
	if (AEInputCheckCurr(AEVK_RIGHT) || AEInputCheckCurr(AEVK_D))
	{
		_Player->position.x += 5.0;
	}
	if (AEInputCheckCurr(AEVK_LEFT) || AEInputCheckCurr(AEVK_A))
	{
		_Player->position.x -= 5.0;
	}
	if (AEInputCheckCurr(AEVK_DOWN) || AEInputCheckCurr(AEVK_S))
	{
		_Player->position.y -= 5.0;
	}
	if (AEInputCheckCurr(AEVK_UP) || AEInputCheckCurr(AEVK_W))
	{
		_Player->position.y += 5.0;
	}

	if (AEInputCheckTriggered(AEVK_SPACE) || AEInputCheckTriggered(AEVK_C))
	{
		//THIS CODE SHOOTS RIGHT SIDE. AS A MEASURE THAT IT CAN BE DONE.
		//float bulletDirection = _Player->direction; //the bullet follows the direction of where the spaceship is facing...
		//AEVec2 bulletVelocity;
		//AEVec2Set(&bulletVelocity, (f32)cos(bulletDirection), (f32)sin(bulletDirection));
		//AEVec2Scale(&bulletVelocity, &bulletVelocity, 50.0f);
		//gameObjInstCreate(TYPE_BULLET, 25, &_Player->position, &bulletVelocity, _Player->direction);
	}

	for (unsigned long i = 0; i < GAME_OBJ_INST_NUM_MAX; i++)
	{
		GameObjInstances* pInst = sGameObjInstList + i;

		//hit box
		//pInst->boundingBox.min.x = -(BOUNDING_RECT_SIZE / 2.0f) * pInst->scale + pInst->posCurr.x;
		//pInst->boundingBox.min.y = -(BOUNDING_RECT_SIZE / 2.0f) * pInst->scale + pInst->posCurr.y;
		//pInst->boundingBox.max.x = +(BOUNDING_RECT_SIZE / 2.0f) * pInst->scale + pInst->posCurr.x;
		//pInst->boundingBox.max.y = +(BOUNDING_RECT_SIZE / 2.0f) * pInst->scale + pInst->posCurr.y;
		if ((pInst->flag & FLAG_ACTIVE) == 0)
			continue;

		if (pInst->pObject->type == TYPE_AUGMENT1)
		{
			for (int j = 0; j < GAME_OBJ_INST_NUM_MAX; j++)
			{

				GameObjInstances* qInst = sGameObjInstList + j;

				if ((qInst->flag & FLAG_ACTIVE) == 0)
					continue;
				if (qInst->pObject->type == TYPE_PLAYER)
				{
					pInst->position.x = qInst->position.x + 100 * cos(_rotation_Aug);
					pInst->position.y = qInst->position.y + 100 * sin(_rotation_Aug);
				}
			}
		}

		if (pInst->pObject->type == TYPE_BOSS)
		{
			pInst->position.x = 0;
			pInst->position.y = 250;

			int numBullets = 4;

			angle = rotationAngle * sin(g_appTime/10 * 3.142);
			
			//BOWAP
			for (int j = 0; j < numBullets; j++)
			{
				double angleT = angle + (30 * j * 360 / 8);

				AEVec2 velocity = { projectileSpeed* sin(AEDegToRad(angleT)) , projectileSpeed * cos(AEDegToRad(angleT))};
				
				std::cout << angleT << '\n';

				gameObjInstCreate(TYPE_BOSS_BULLETHELL_BULLET_1, 5, &pInst->position, &velocity, angleT);

				for (int k = 0; k < GAME_OBJ_INST_NUM_MAX; k++)
				{
					GameObjInstances* kInst = sGameObjInstList + k;

					if ((kInst->flag & FLAG_ACTIVE) == 0)
						continue;

					if (kInst->pObject->type == TYPE_BOSS_BULLETHELL_BULLET_1)
					{
						// Update movement based on sine wave, (BOWAP)
						kInst->position.x = 2 * pInst->velocity.x * g_dt + pInst->position.x;
						kInst->position.y = 2 * pInst->velocity.y * g_dt + pInst->position.y;
						//kInst->position.x = pInst->position.x + kInst->velocity.x * sin(AEDegToRad(angleT)) * g_appTime;
						//kInst->position.y = pInst->position.y + kInst->velocity.y * cos(AEDegToRad(angleT)) * g_appTime;
					}
				}
			}
		}


		//std::cout  <<  sGameObjNum << '\n';

		if (pInst->pObject->type == TYPE_BULLET)
		{
			pInst->position.x = 2 * pInst->velocity.x * g_dt + pInst->position.x;
			pInst->position.y = 2 * pInst->velocity.y * g_dt + pInst->position.y;
			//
		}

		if (pInst->pObject->type != TYPE_PLAYER)
		{
			if (pInst->position.x > AEGfxGetWinMaxX() ||
				pInst->position.x < AEGfxGetWinMinX() ||
				pInst->position.y > AEGfxGetWinMaxY() ||
				pInst->position.y < AEGfxGetWinMinY())
			{
				gameObjInstDestroy(pInst);
			}
		}

	}

		//Rotation Increase.
		_rotation_Aug += 0.005f;








		for (unsigned long i = 0; i < GAME_OBJ_INST_NUM_MAX; i++)
		{
			GameObjInstances* pInst = sGameObjInstList + i;
			AEMtx33		 translate = {}, rotate = {}, scale = {};

			UNREFERENCED_PARAMETER(translate);
			UNREFERENCED_PARAMETER(rotate);
			UNREFERENCED_PARAMETER(scale);

			// skip non-active object
			if ((pInst->flag & FLAG_ACTIVE) == 0)
				continue;


			// Create a scale matrix that scales by pInst->scale for x and y axes.


			AEMtx33Scale(&scale, pInst->scaleX, pInst->scaleY);


			// Create a rotation matrix that rotates by dirCurr
			AEMtx33Rot(&rotate, pInst->direction);
			// Create a translation matrix that translates by
			// pInst->posCurr.x in the x-axis and pInst->posCurr.y in the y-axis
			AEMtx33Trans(&translate, pInst->position.x, pInst->position.y);
			// Concat the matrices (TRS)
			AEMtx33Concat((AEMtx33*)pInst->transform.m, &rotate, &scale);
			AEMtx33Concat((AEMtx33*)pInst->transform.m, &translate, (AEMtx33*)pInst->transform.m);
			// Choose the transform to use


		}


	
}

void Level_1_Draw(void)
{
	char strBuffer[1024];

	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);

	//AEGfxTexture* playerTex = AEGfxTextureLoad("C:\\Users\\angus\\OneDrive\\Documents\\GitHub\\SegmentFault\\SEP2_Project\\Assets\\Assets\\Terran.png");
	//AEGfxTexture* bulletTex = AEGfxTextureLoad("C:\\Users\\angus\\OneDrive\\Documents\\GitHub\\SegmentFault\\SEP2_Project\\Assets\\Assets\\YellowTexture.png");
	AEGfxTexture* playerTex     = AEGfxTextureLoad("..\\..\\Assets\\Assets\\Terran.png");
	AEGfxTexture* bulletTex     = AEGfxTextureLoad("..\\..\\Assets\\Assets\\YellowTexture.png");
	AEGfxTexture* augmentGunTex = AEGfxTextureLoad("..\\..\\Assets\\Assets\\moon.png");
	AEGfxTexture* bossTex = AEGfxTextureLoad("..\\..\\Assets\\Assets\\images.png");
	AEGfxTexture* bossBullet1Tex = AEGfxTextureLoad("..\\..\\Assets\\Assets\\circle-512.png");

	for (unsigned long i = 0; i < GAME_OBJ_INST_NUM_MAX; i++)
	{
		GameObjInstances* pInst = sGameObjInstList + i;
		if ((pInst->flag & FLAG_ACTIVE) == 0)
			continue;

		AEGfxTexture* texture = nullptr;

		AEGfxSetRenderMode(AE_GFX_RM_COLOR);
		AEGfxSetTintColor(0.0f, 0.0f, 0.0f, 0.0f);
		AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
		// Set the tint to white, so that the sprite can // display the full range of colors (default is black). 
		AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);

		if (pInst->pObject->type == TYPE_PLAYER)
		{
			texture = playerTex;
		}
		if (pInst->pObject->type == TYPE_BULLET)
		{
			texture = bulletTex;
		}
		if (pInst->pObject->type == TYPE_AUGMENT1)
		{
			texture = augmentGunTex;
		}
		if (pInst->pObject->type == TYPE_BOSS)
		{
			texture = bossTex;
		}
		if (pInst->pObject->type == TYPE_BOSS_BULLETHELL_BULLET_1)
		{
			texture = bulletTex;
		}



		AEGfxTextureSet(texture, 0, 0);
		AEGfxSetTransform(pInst->transform.m);
		AEGfxMeshDraw(pInst->pObject->pMesh, AE_GFX_MDM_TRIANGLES);

		// skip non-active object


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