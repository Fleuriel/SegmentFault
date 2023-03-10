
#include "Main.h"
#include "GameObjects.h"



void Level_1_Load(void)
{
	memset(sGameObjList, 0, sizeof(GameObjects) * GAME_OBJ_NUM_MAX);

	sGameObjNum = 0;

	memset(sGameObjInstList, 0, sizeof(_Player) * GAME_OBJ_INST_NUM_MAX);
	sGameObjInstNum = 0;

	_Player			= nullptr;
	_Bullet			= nullptr;
	_Boss			= nullptr;
	_BossBullet		= nullptr;
	_Enemy			= nullptr;


	GameObjects* _PlayerObjects;
	GameObjects* _BulletObjects;
	GameObjects* _BossObjects;
	GameObjects* _AugmentGunObjects;
	GameObjects* _BossBulletObjects_1;
	GameObjects* _EnemyObjects;

	//0 TYPE_PLAYER
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

	//1 TYPE_BOSS
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

	//2 TYPE_AUGMENT1
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

	//3 TYPE_BOSS_BULLETHELL_BULLET_1
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


	//4	TYPE_BULLET
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

	//5	TYPE_ENEMY
	_EnemyObjects = sGameObjList + sGameObjNum++;
	_EnemyObjects->type = TYPE_ENEMY;

	AEGfxMeshStart();

	AEGfxTriAdd(
		0.5f, 0.5f, 0x808080, 1.0f, 0.0f,
		-0.5f, -0.5f, 0x808080, 0.0f, 1.0f,
		0.5f, -0.5f, 0x696969, 1.0f, 1.0f);
	AEGfxTriAdd(
		-0.5f, 0.5f, 0x696969, 0.0f, 0.0f,
		-0.5f, -0.5f, 0x696969, 0.0f, 1.0f,
		0.5f, 0.5f, 0x808080, 1.0f, 0.0f);
	_EnemyObjects->pMesh = AEGfxMeshEnd();
	AE_ASSERT_MESG(_EnemyObjects->pMesh, "Fail to create object!!");


}

void Level_1_Init(void)
{
	//0
	_Player = gameObjInstCreate(TYPE_PLAYER, PLAYER_SIZE, nullptr, nullptr, 0.0f);
	AE_ASSERT(_Player);


	//1
	//_Boss = gameObjInstCreate(TYPE_BOSS, BOSS_SIZE, nullptr, nullptr, 0.0f);
	//AE_ASSERT(_Boss);


	//2
	_Augment_Gun = gameObjInstCreate(TYPE_AUGMENT1, AUG_GUN_SIZE, nullptr, nullptr, 0.0f);
	AE_ASSERT(_Augment_Gun);


	//3
	//_BossBullet = gameObjInstCreate(TYPE_BOSS_BULLETHELL_BULLET_1, BULLET_SIZE, nullptr, nullptr, 0.0f);
	//AE_ASSERT(_Boss);
	
	
	//4
	/*_Bullet = gameObjInstCreate(TYPE_BULLET, BULLET_SIZE, nullptr, nullptr, 0.0f);
	AE_ASSERT(_Bullet);*/

	
	//5
	//_Enemy = gameObjInstCreate(TYPE_ENEMY, ENEMY_SIZE, nullptr, nullptr, 0.0f);
	//AE_ASSERT(_Enemy);
}


void Level_1_Update(void)
{
	_deltaTime += g_dt;

	if (_deltaTime > 1)
	{
		for (int i = 0; i < 7; i++)
		{
			float enemySpawnX = 0, enemySpawnY = 0;
			// Generate a random number to determine which X range to use
			// Outer Box, 1600x900 , Inner Box 1366x768;
			//A
			if (AERandFloat() >= 0 && AERandFloat() < 0.25)
			{
				enemySpawnX = -(1600 / 2) + AERandFloat() * (1366 + (1600 - 1366));
				enemySpawnY = (768 / 2) + AERandFloat() * ((900 - 768) / 2);
			}
			//B
			else if (AERandFloat() >= 0.25 && AERandFloat() < 0.5)
			{
				enemySpawnX = 1366 / 2 + AERandFloat() * (1600 - 1366) / 2;
				enemySpawnY = -(768 / 2) + AERandFloat() * (768 + (900 - 768) / 2);

			}
			//C
			else if (AERandFloat() >= 0.5 && AERandFloat() < 0.75)
			{
				enemySpawnX = -(1366 / 2) + AERandFloat() * (1366 + (1600 - 1366) / 2);
				enemySpawnY = -(900 / 2) + AERandFloat() * ((900 - 768) / 2);
			}
			//D
			else if (AERandFloat() >= 0.75)
			{
				enemySpawnX = -(1366 / 2) - ((1600 - 1366) / 2 * AERandFloat());
				enemySpawnY = -(900 / 2) + AERandFloat() * (768 + (900 - 768) / 2);

			}

			AEVec2 enemySpawn = { enemySpawnX, enemySpawnY };
			AEVec2 velocityEnemy = { 20.0f, 20.0f };
			enemyCount++;
			//spawn enemy :)
			GameObjInstances* enemyInst = gameObjInstCreate(TYPE_ENEMY, ENEMY_SIZE, &enemySpawn, &velocityEnemy, 0.0f);
			enemyInst->isAlive = true;
			enemyInst->health = 2;
			_enemyList.push_back(enemyInst);
		}
		_deltaTime = 0;
	}
	//Rotation for Augment...
	//Rotation Increase.
	_rotation_Aug += 0.04f;

	//MAKE SURE THAT BULLETCOUNT IS ALWAYS more than or equals 0
	/*if (bulletCount < 0)
		bulletCount = 0;*/

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
		std::cout << bulletCount << '\n';
	}

	for (unsigned long i = 0; i < GAME_OBJ_INST_NUM_MAX; i++)
	{
		GameObjInstances* pInst = sGameObjInstList + i;

		if ((pInst->flag & FLAG_ACTIVE) == 0)
			continue;


		if (pInst->pObject->type == TYPE_PLAYER)
		{

			//Checks closes enemiest.
			const float FIRE_INTERVAL = 2.0f; // Fire interval in seconds
			static float fireTimer = 0.0f; // Timer for tracking time since last shot
			fireTimer += g_dt;
			std::priority_queue<std::pair<float, GameObjInstances*>, std::vector<std::pair<float, GameObjInstances*>>, CompareDist> closeEnemies;
			for (unsigned int i = 0; i < GAME_OBJ_INST_NUM_MAX; ++i)
			{
				GameObjInstances* qInst = sGameObjInstList + i;

				if ((qInst->flag & FLAG_ACTIVE) == 0)
					continue;

				if (qInst->pObject->type == TYPE_ENEMY || qInst->pObject->type == TYPE_BOSS)
				{
					float dist = AEVec2Distance(&qInst->position, &pInst->position);
					closeEnemies.push(std::make_pair(dist, qInst));
				}
			}
			//std::cout << g_dt << '\t' << fireTimer << '\n';

			std::set<GameObjInstances*> targetedEnemies;

			if (fireTimer > FIRE_INTERVAL)
			{
				fireTimer = 0;
				targetedEnemies.clear(); // Clear the set before processing the next batch of targets
				for (unsigned int i = 0; i < MAX_BULLETS && !closeEnemies.empty(); ++i)
				{
					GameObjInstances* qInst = closeEnemies.top().second;
					closeEnemies.pop();

					// If this enemy has already been targeted or is not alive, skip it
					if (targetedEnemies.count(qInst) > 0 ) {
						continue;
					}

					// Create a new bullet object
					GameObjInstances* bulletInst = gameObjInstCreate(TYPE_BULLET, BULLET_SIZE, &pInst->position, NULL, 0.0f);

					// Set the bullet's velocity to point towards the enemy/boss
					AEVec2 direction = { qInst->position.x - pInst->position.x, qInst->position.y - pInst->position.y };
					AEVec2Normalize(&direction, &direction);
					AEVec2Scale(&direction, &direction, BULLET_SPEED);
					bulletInst->velocity = direction;

					// Mark this enemy as targeted
					targetedEnemies.insert(qInst);
				}
			}
		}

		if (pInst->pObject->type == TYPE_AUGMENT1)
		{

			for (int j = 0; j < GAME_OBJ_INST_NUM_MAX; j++)
			{
				GameObjInstances* qInst = sGameObjInstList + j;

				if ((qInst->flag & FLAG_ACTIVE) == 0)
					continue;

				if (qInst->pObject->type == TYPE_PLAYER)
				{
					//pInst is the augment that is moving around.
					//qInst is the player position...
					AEVec2 direction = { cos(_rotation_Aug), sin(_rotation_Aug) };
					AEVec2Scale(&direction, &direction, 100.0f);
					AEVec2Add(&pInst->position, &qInst->position, &direction);
				}
			}
		}


		//if (pInst->pObject->type == TYPE_BOSS)
		//{
		//	pInst->position.x = 0;
		//	pInst->position.y = 250;
		//
		//	int numBullets = 8;
		//
		//	angle = rotationAngle * sin(g_appTime/10 * 3.142);
		//	
		//	//BOWAP
		//	for (int j = 0; j < numBullets; j++)
		//	{
		//		double angleT = angle + (30 * j * 360 / 16);
		//
		//		AEVec2 velocity = { projectileSpeed* sin(AEDegToRad(angleT)) , projectileSpeed * cos(AEDegToRad(angleT))};
		//		
		//		//std::cout << angleT << '\n';
		//		
		//		gameObjInstCreate(TYPE_BOSS_BULLETHELL_BULLET_1, 5, &pInst->position, &velocity, angleT);
		//	}
		//}


		if (pInst->pObject->type == TYPE_BOSS_BULLETHELL_BULLET_1)
		{
			pInst->position.x = 2 * pInst->velocity.x * g_dt + pInst->position.x;
			pInst->position.y = 2 * pInst->velocity.y * g_dt + pInst->position.y;
			//
		}

		if (pInst->pObject->type == TYPE_BULLET)
		{
			//move bullet....
			pInst->position.x = 2 * pInst->velocity.x * g_dt + pInst->position.x;
			pInst->position.y = 2 * pInst->velocity.y * g_dt + pInst->position.y;
		}

		if (pInst->pObject->type == TYPE_ENEMY)
		{
			for (int j = 0; j < GAME_OBJ_INST_NUM_MAX; j++)
			{

				GameObjInstances* qInst = sGameObjInstList + j;

				if ((qInst->flag & FLAG_ACTIVE) == 0)
					continue;

				if (qInst->pObject->type == TYPE_PLAYER)
				{
					// Get direction from enemy to player
					AEVec2 direction = { qInst->position.x - pInst->position.x, qInst->position.y - pInst->position.y };

					// Normalize direction vector to get unit direction
					AEVec2Normalize(&direction, &direction);

					// Calculate velocity vector by scaling unit direction by enemy's movement speed
					AEVec2 velocity = { direction.x * 5.0f, direction.y * 5.0f };

					// Scale velocity vector by time since last frame to get distance to move this frame
					float distanceToMove = AEVec2Length(&velocity) * g_dt;
					velocity.x *= distanceToMove;
					velocity.y *= distanceToMove;

					// Update enemy position with velocity
					pInst->position.x += velocity.x;
					pInst->position.y += velocity.y;

					// Update enemy rotation to point towards player
					//pInst->rotation = atan2(direction.y, direction.x);
				}
			}

		}
		//Window size is 1366x768

		if (pInst->position.x > AEGfxGetWinMaxX() ||
			pInst->position.x < AEGfxGetWinMinX() ||
			pInst->position.y > AEGfxGetWinMaxY() ||
			pInst->position.y < AEGfxGetWinMinY())
		{
			if (pInst->pObject->type == TYPE_PLAYER || pInst->pObject->type == TYPE_AUGMENT1 || pInst->pObject->type == TYPE_ENEMY || pInst->pObject->type == TYPE_BOSS)
			{
				continue;
			}

			if (pInst->pObject->type == TYPE_BULLET)
			{
				bulletCount--;
				std::cout << bulletCount << "Out of Screen ." << '\n';
			}

			gameObjInstDestroy(pInst);
		}
		




		//pInst->boundingBox.min.x = -(BOUNDING_RECT_SIZE / 2.0f) * pInst->scaleX + pInst->position.x;
		//pInst->boundingBox.min.y = -(BOUNDING_RECT_SIZE / 2.0f) * pInst->scaleY + pInst->position.y;
		//pInst->boundingBox.max.x = +(BOUNDING_RECT_SIZE / 2.0f) * pInst->scaleX + pInst->position.x;
		//pInst->boundingBox.max.y = +(BOUNDING_RECT_SIZE / 2.0f) * pInst->scaleY + pInst->position.y;
		//

		
	}

	///////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////COLLISION////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////
	
	//TAKE NOTE
	//ObjInstance1 = Instance 1 to check with :  ObjInstance2 = Instance 2 , SIMILARLY TO THE TOP,

	for (unsigned long i = 0; i < GAME_OBJ_INST_NUM_MAX; i++)
	{
		GameObjInstances* ObjInstance1 = sGameObjInstList + i;

		if ((ObjInstance1->flag & FLAG_ACTIVE) == 0)
			continue;



		AEVec2 circleCenter = ObjInstance1->position;
		f32 circleRadius = BOUNDING_RECT_SIZE / 2.0f * ObjInstance1->scaleX;


		if (ObjInstance1->pObject->type == TYPE_BULLET)
		{
			for (unsigned long j = 0; j < GAME_OBJ_INST_NUM_MAX; j++)
			{
				GameObjInstances* ObjInstance2 = sGameObjInstList + j;

				if ((ObjInstance2->flag & FLAG_ACTIVE) == 0)
					continue;

				//if ObjectInstance2 is same as ObjectInstance1, then continue...
				if (ObjInstance2->pObject->type == TYPE_BULLET)
					continue;

				if (ObjInstance2->pObject->type == TYPE_ENEMY || ObjInstance2->pObject->type == TYPE_BOSS)
				{
					//if (CollisionIntersection_RectRect(ObjInstance1->boundingBox, ObjInstance1->velocity, ObjInstance2->boundingBox, ObjInstance2->velocity))
					//{
					//	//Spawn Orbs of Experience at ObjInstance1 Position...
					//	bulletCount--;
					//	std::cout << bulletCount << '\n';
					//	gameObjInstDestroy(ObjInstance1);
					//	gameObjInstDestroy(ObjInstance2);
					//	//std::cout << ObjInstance1->position.x << ObjInstance1->position.y;
					//}

					if (CollisionCircleCircle(ObjInstance1->position, ObjInstance1->scaleX , ObjInstance2->position, ObjInstance2->scaleX))
					{
						//Spawn Orbs of Experience at ObjInstance1 Position...
						bulletCount--;
//						std::cout << bulletCount << '\n';
						gameObjInstDestroy(ObjInstance1);
						gameObjInstDestroy(ObjInstance2);
						std::cout << "Collision Hit at this position (ObjInstance1) X : " << ObjInstance1->position.x << " Y: " << ObjInstance1->position.y << '\n';
						std::cout << "Collision Hit at this position (ObjInstance2) X : " << ObjInstance2->position.x << " Y: " << ObjInstance2->position.y << '\n';

						//std::cout << ObjInstance1->position.x << ObjInstance1->position.y;
					}


				}
			}
		}
	}

	//std::cout << "BulletCount    \t" << bulletCount << '\n';
	///////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////CONCAT MATRIX//////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////
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
	AEGfxTexture* enemyTex      = AEGfxTextureLoad("..\\..\\Assets\\Assets\\ling.png");
	

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
			texture = bossBullet1Tex;
		}	
		if (pInst->pObject->type == TYPE_ENEMY)
		{
			texture = enemyTex;
		}


		AEGfxTextureSet(texture, 0, 0);
		AEGfxSetTransform(pInst->transform.m);
		AEGfxMeshDraw(pInst->pObject->pMesh, AE_GFX_MDM_TRIANGLES);


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