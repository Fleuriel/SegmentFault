#include "Main.h"
#include "GameObjects.h"

static bool onValueChange = true;
int reqExp = 15;
int expPercent = 0;
// Pointer to Mesh
AEGfxVertexList* ptrMesh = nullptr;

//Background definition
AEGfxVertexList* bMesh = nullptr;
AEGfxTexture* BGTex;

// Pre-definiton for printing g_dt
char gdt_buffer[1024]{};


// Pre-definition of scaling
double scaleX_level1;
double scaleY_level1;

void Level_1_Load(void)
{
	std::cout << "Level1_Load\n";
	memset(sGameObjList, 0, sizeof(GameObjects) * GAME_OBJ_NUM_MAX);

	sGameObjNum = 0;

	memset(sGameObjInstList, 0, sizeof(_Player) * GAME_OBJ_INST_NUM_MAX);
	sGameObjInstNum = 0;

	_Player = nullptr;
	_Bullet = nullptr;
	_Boss = nullptr;
	_BossBullet = nullptr;
	_Enemy = nullptr;

	_PlayerHitbox = nullptr;
	_ExpOrbs = nullptr;
	_Augment_One = nullptr;
	_Augment_Two = nullptr;
	_Augment_Three = nullptr;
	_Augment_Four = nullptr;
	_Augment_Five = nullptr;

	GameObjects* _PlayerObjects;
	GameObjects* _BulletObjects;
	GameObjects* _BossObjects;
	GameObjects* _BossBulletObjects_1;
	GameObjects* _EnemyObjects;
	GameObjects* _PlayerHitbox;
	GameObjects* _ExpObjects;

	// Augments to choose,

	//Augment (Gun)
	GameObjects* _AugmentOne_Obj;

	//Augment Rotating Rocks
	GameObjects* _AugmentTwo_Obj;


	GameObjects* _AugmentThree_Obj;

	GameObjects* _AugmentFour_Obj;

	GameObjects* _AugmentFive_Obj;

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



	//2 TYPE_BOSS_BULLETHELL_BULLET_1
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


	//3 TYPE_BULLET
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

	//4	TYPE_ENEMY
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

	//5	TYPE_PLAYER_HITBOX_INDICATOR
	_PlayerHitbox = sGameObjList + sGameObjNum++;
	_PlayerHitbox->type = TYPE_PLAYER_HITBOX_INDICATOR;

	AEGfxMeshStart();

	AEGfxTriAdd(
		0.5f, 0.5f, 0x808080, 1.0f, 0.0f,
		-0.5f, -0.5f, 0x808080, 0.0f, 1.0f,
		0.5f, -0.5f, 0x696969, 1.0f, 1.0f);
	AEGfxTriAdd(
		-0.5f, 0.5f, 0x696969, 0.0f, 0.0f,
		-0.5f, -0.5f, 0x696969, 0.0f, 1.0f,
		0.5f, 0.5f, 0x808080, 1.0f, 0.0f);
	_PlayerHitbox->pMesh = AEGfxMeshEnd();
	AE_ASSERT_MESG(_PlayerHitbox->pMesh, "Fail to create object!!");

	//6 Exp Orbs
	_ExpObjects = sGameObjList + sGameObjNum++;
	_ExpObjects->type = TYPE_EXPERIENCE;

	AEGfxMeshStart();

	AEGfxTriAdd(
		0.5f, 0.5f, 0x808080, 1.0f, 0.0f,
		-0.5f, -0.5f, 0x808080, 0.0f, 1.0f,
		0.5f, -0.5f, 0x696969, 1.0f, 1.0f);
	AEGfxTriAdd(
		-0.5f, 0.5f, 0x696969, 0.0f, 0.0f,
		-0.5f, -0.5f, 0x696969, 0.0f, 1.0f,
		0.5f, 0.5f, 0x808080, 1.0f, 0.0f);
	_ExpObjects->pMesh = AEGfxMeshEnd();
	AE_ASSERT_MESG(_ExpObjects->pMesh, "Fail to create object!!");



	//7 TYPE_AUGMENT1
	_AugmentOne_Obj = sGameObjList + sGameObjNum++;
	_AugmentOne_Obj->type = TYPE_AUGMENT1;

	AEGfxMeshStart();

	AEGfxTriAdd(
		0.5f, 0.5f, 0x808080, 1.0f, 0.0f,
		-0.5f, -0.5f, 0x808080, 0.0f, 1.0f,
		0.5f, -0.5f, 0x696969, 1.0f, 1.0f);
	AEGfxTriAdd(
		-0.5f, 0.5f, 0x696969, 0.0f, 0.0f,
		-0.5f, -0.5f, 0x696969, 0.0f, 1.0f,
		0.5f, 0.5f, 0x808080, 1.0f, 0.0f);
	_AugmentOne_Obj->pMesh = AEGfxMeshEnd();
	AE_ASSERT_MESG(_AugmentOne_Obj->pMesh, "Fail to create object!!");

	//8 TYPE_AUGMENT2
	_AugmentTwo_Obj = sGameObjList + sGameObjNum++;
	_AugmentTwo_Obj->type = TYPE_AUGMENT2;

	AEGfxMeshStart();

	AEGfxTriAdd(
		0.5f, 0.5f, 0x808080, 1.0f, 0.0f,
		-0.5f, -0.5f, 0x808080, 0.0f, 1.0f,
		0.5f, -0.5f, 0x696969, 1.0f, 1.0f);
	AEGfxTriAdd(
		-0.5f, 0.5f, 0x696969, 0.0f, 0.0f,
		-0.5f, -0.5f, 0x696969, 0.0f, 1.0f,
		0.5f, 0.5f, 0x808080, 1.0f, 0.0f);
	_AugmentTwo_Obj->pMesh = AEGfxMeshEnd();
	AE_ASSERT_MESG(_AugmentTwo_Obj->pMesh, "Fail to create object!!");

	//9 TYPE_AUGMENT3
	_AugmentThree_Obj = sGameObjList + sGameObjNum++;
	_AugmentThree_Obj->type = TYPE_AUGMENT3;

	AEGfxMeshStart();

	AEGfxTriAdd(
		0.5f, 0.5f, 0x808080, 1.0f, 0.0f,
		-0.5f, -0.5f, 0x808080, 0.0f, 1.0f,
		0.5f, -0.5f, 0x696969, 1.0f, 1.0f);
	AEGfxTriAdd(
		-0.5f, 0.5f, 0x696969, 0.0f, 0.0f,
		-0.5f, -0.5f, 0x696969, 0.0f, 1.0f,
		0.5f, 0.5f, 0x808080, 1.0f, 0.0f);
	_AugmentThree_Obj->pMesh = AEGfxMeshEnd();
	AE_ASSERT_MESG(_AugmentThree_Obj->pMesh, "Fail to create object!!");

	//10 TYPE_AUGMENT4
	_AugmentFour_Obj = sGameObjList + sGameObjNum++;
	_AugmentFour_Obj->type = TYPE_AUGMENT4;

	AEGfxMeshStart();

	AEGfxTriAdd(
		0.5f, 0.5f, 0x808080, 1.0f, 0.0f,
		-0.5f, -0.5f, 0x808080, 0.0f, 1.0f,
		0.5f, -0.5f, 0x696969, 1.0f, 1.0f);
	AEGfxTriAdd(
		-0.5f, 0.5f, 0x696969, 0.0f, 0.0f,
		-0.5f, -0.5f, 0x696969, 0.0f, 1.0f,
		0.5f, 0.5f, 0x808080, 1.0f, 0.0f);
	_AugmentFour_Obj->pMesh = AEGfxMeshEnd();
	AE_ASSERT_MESG(_AugmentFour_Obj->pMesh, "Fail to create object!!");

	//11 TYPE_AUGMENT5
	_AugmentFive_Obj = sGameObjList + sGameObjNum++;
	_AugmentFive_Obj->type = TYPE_AUGMENT5;

	AEGfxMeshStart();

	AEGfxTriAdd(
		0.5f, 0.5f, 0x808080, 1.0f, 0.0f,
		-0.5f, -0.5f, 0x808080, 0.0f, 1.0f,
		0.5f, -0.5f, 0x696969, 1.0f, 1.0f);
	AEGfxTriAdd(
		-0.5f, 0.5f, 0x696969, 0.0f, 0.0f,
		-0.5f, -0.5f, 0x696969, 0.0f, 1.0f,
		0.5f, 0.5f, 0x808080, 1.0f, 0.0f);
	_AugmentFive_Obj->pMesh = AEGfxMeshEnd();
	AE_ASSERT_MESG(_AugmentFive_Obj->pMesh, "Fail to create object!!");





	if (inputFileStream.good())
	{
		std::cout << "File Exist\n";
		std::string ExpText = "Player Experience and Level...";
		std::string line;

		std::cout << inputFileStream.eof() << '\n';
		inputFileStream.seekg(0, std::ios::beg);




		while (std::getline(inputFileStream, line))
		{
			std::cout << line << '\n';
			if (line == "enemyInstances Positions...")
			{
				
				for (auto it = _enemyList.begin(); it != _enemyList.end(); ) {
					if (*it == nullptr)
						continue;
					if ((*it)->flag == 0) {
						delete* it;
						it = _enemyList.erase(it);
					}
					else {
						++it;
					}
				}

				std::istringstream iss(line);
				int flag, direction, health, showTexture, isInvincible, iFrame;
				float scaleX, scaleY, posX, posY, velX, velY;
				AABB boundingBox;
				AEMtx33 transform;
				
				iss >> flag >> scaleX >> scaleY >> posX >> posY >> velX >> velY >> direction
					>> boundingBox.min.x >> boundingBox.min.y >> boundingBox.max.x >> boundingBox.max.y
					>> transform.m[0][0] >> transform.m[0][1] >> transform.m[0][2]
					>> transform.m[1][0] >> transform.m[1][1] >> transform.m[1][2]
					>> transform.m[2][0] >> transform.m[2][1] >> transform.m[2][2]
					>> health >> showTexture >> isInvincible >> iFrame;
				
				AEVec2 positionCreation{ posX, posY };
				AEVec2 velocityCreation{ velX, velY };
				std::cout << posX  <<' ' << posY << '\n';
				
				GameObjInstances* newEnemyInst = gameObjInstCreate(TYPE_ENEMY, ENEMY_SIZE, &positionCreation, &velocityCreation, 0.0f);
				_enemyList.push_back(newEnemyInst);

			
			}
			if (line == ExpText)
			{
				std::getline(inputFileStream, line);
				std::istringstream iss(line);
				//works
				iss >> _Player_Level >> _Player_Experience;
				//works
				std::cout << _Player_Level << " WHOOPSEY " << _Player_Experience << '\n';
			}
			else
			{

			}
		}

		inputFileStream.close();
	}
	else if(inputFileStream.fail())
	{
		std::cerr << "Error: \n" ;

	}

	//Expbar
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);  // conversion -> rgb value/255

	// Create buttons
	AEGfxMeshStart();

	AEGfxTriAdd(
		0.5f, 0.5f, 0xFFFFFFFF, 1.0f, 0.0f,
		-1.f, -0.5f, 0xFFFFFFFF, 0.0f, 1.0f,
		0.5f, -0.5f, 0xFFFFFFFF, 1.0f, 1.0f);
	AEGfxTriAdd(
		-1.f, 0.5f, 0xFFFFFFFF, 0.0f, 0.0f,
		-1.f, -0.5f, 0xFFFFFFFF, 0.0f, 1.0f,
		0.5f, 0.5f, 0xFFFFFFFF, 1.0f, 0.0f);

	ptrMesh = AEGfxMeshEnd();
	//end Expbar

	//Background
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
	//start Background
	AEGfxMeshStart();

	AEGfxTriAdd(
		0.5f, 0.5f, 0xFFFFFFFF, 1.0f, 0.0f,
		-1.f, -0.5f, 0xFFFFFFFF, 0.0f, 1.0f,
		0.5f, -0.5f, 0xFFFFFFFF, 1.0f, 1.0f);
	AEGfxTriAdd(
		-1.f, 0.5f, 0xFFFFFFFF, 0.0f, 0.0f,
		-1.f, -0.5f, 0xFFFFFFFF, 0.0f, 1.0f,
		0.5f, 0.5f, 0xFFFFFFFF, 1.0f, 0.0f);

	bMesh = AEGfxMeshEnd();
	BGTex = AEGfxTextureLoad("..\\..\\Assets\\Assets\\Background.png");
	//end Background
}

void Level_1_Init(void)
{
	//0
	_Player = gameObjInstCreate(TYPE_PLAYER, PLAYER_SIZE, nullptr, nullptr, 0.0f);
	_Player->health = 20;
	AE_ASSERT(_Player);


	//1
	//_Boss = gameObjInstCreate(TYPE_BOSS, BOSS_SIZE, nullptr, nullptr, 0.0f);
	//_Boss->health = 100;
	//AE_ASSERT(_Boss);
	//_Boss->position.x = 0;
	//_Boss->position.y = 50;


	//2
	//_BossBullet = gameObjInstCreate(TYPE_BOSS_BULLETHELL_BULLET_1, BULLET_SIZE, nullptr, nullptr, 0.0f);
	//AE_ASSERT(_Boss);


	//3
	/*_Bullet = gameObjInstCreate(TYPE_BULLET, BULLET_SIZE, nullptr, nullptr, 0.0f);
	AE_ASSERT(_Bullet);*/


	//4
	//_Enemy = gameObjInstCreate(TYPE_ENEMY, ENEMY_SIZE, nullptr, nullptr, 0.0f);
	//AE_ASSERT(_Enemy);

	//5
	_PlayerHitbox = gameObjInstCreate(TYPE_PLAYER_HITBOX_INDICATOR, 20.0f, nullptr, nullptr, 0.0f);
	_PlayerHitbox->showTexture = false;

	//_PlayerHitbox->flag = !FLAG_ACTIVE;

	//6 Exp Orbs
	//_ExpOrbs = gameObjInstCreate(TYPE_EXPERIENCE, 10, nullptr, nullptr, 0.0f);
	//AE_ASSERT(_ExpOrbs);


	//7
	_Augment_One = gameObjInstCreate(TYPE_AUGMENT1, AUG_GUN_SIZE, nullptr, nullptr, 0.0f);
	AE_ASSERT(_Augment_One);

	//8
	_Augment_Two = gameObjInstCreate(TYPE_AUGMENT2, AUG_GUN_SIZE, nullptr, nullptr, 0.0f);
	AE_ASSERT(_Augment_Two);

	//9
	//_Augment_Three = gameObjInstCreate(TYPE_AUGMENT3, AUG_GUN_SIZE * 3, nullptr, nullptr, 0.0f);
	//AE_ASSERT(_Augment_Three);



}


void Level_1_Update(void)
{

	_deltaTime += g_dt;
	_deltaTime_State += g_dt;
	//std::cout << _deltaTime << '\n';
	//Increment Minutes... (Health)
	if (_deltaTime > 60)
	{
		enemyHealth += ++minutes;
		_deltaTime = 0;
	}
	_deltaTimeEnemySpawner += g_dt;
	_delayTimeBullets += g_dt;
	_deltaTime_Shooting += g_dt;


	_Player_Level = experienceCurve(_Player_Level, _Player_Experience, reqExp);
	expPercent = _Player_Experience * 10 /reqExp;



	//SAVE.....
	if (AEInputCheckTriggered(AEVK_P) && _deltaTime_State >= 1.5f)
	{
		std::ofstream outputStream{ "..\\..\\Assets\\SaveFiles\\save.txt" };
		if (outputStream.is_open())
		{
			std::cout << "Current GameObjects\n";
			for (const auto& gameObjInstance : sGameObjInstList)
			{
				if (gameObjInstance.flag == 0 &&
					gameObjInstance.scale.x == 0 &&
					gameObjInstance.scale.y == 0 &&
					gameObjInstance.position.x == 0 &&
					gameObjInstance.position.y == 0 &&
					gameObjInstance.velocity.x == 0 &&
					gameObjInstance.velocity.y == 0 &&
					gameObjInstance.direction == 0 &&
					gameObjInstance.boundingBox.min.x == 0 &&
					gameObjInstance.boundingBox.min.y == 0 &&
					gameObjInstance.boundingBox.max.x == 0 &&
					gameObjInstance.boundingBox.max.y == 0 &&
					gameObjInstance.health == 0 &&
					gameObjInstance.showTexture == false &&
					gameObjInstance.isInvincible == false &&
					gameObjInstance.iFrame == 0.0)
				{
					continue; // Skip this iteration of the loop
				}
				else
				{
					if (gameObjInstance.pObject != nullptr)
					{
						outputStream
							<< gameObjInstance.pObject->type << " "
							<< gameObjInstance.flag << " "
							<< gameObjInstance.scale.x << " "
							<< gameObjInstance.scale.y << " "
							<< gameObjInstance.position.x << " "
							<< gameObjInstance.position.y << " "
							<< gameObjInstance.velocity.x << " "
							<< gameObjInstance.velocity.y << " "
							<< gameObjInstance.direction << " "
							<< gameObjInstance.boundingBox.min.x << " "
							<< gameObjInstance.boundingBox.min.y << " "
							<< gameObjInstance.boundingBox.max.x << " "
							<< gameObjInstance.boundingBox.max.y << " "
							<< gameObjInstance.transform.m << " "
							<< gameObjInstance.health << " "
							<< gameObjInstance.showTexture << " "
							<< gameObjInstance.isInvincible << " "
							<< gameObjInstance.iFrame
							<< "\n";
					}
				}
			}


			outputStream << "enemyInstances Positions...\n";
			for (const auto& enemyInstance : _enemyList) {
				outputStream << enemyInstance->flag << " "
					<< enemyInstance->scale.x << " "
					<< enemyInstance->scale.y << " "
					<< enemyInstance->position.x << " "
					<< enemyInstance->position.y << " "
					<< enemyInstance->velocity.x << " "
					<< enemyInstance->velocity.y << " "
					<< enemyInstance->direction << " "
					<< enemyInstance->boundingBox.min.x << " "
					<< enemyInstance->boundingBox.min.y << " "
					<< enemyInstance->boundingBox.max.x << " "
					<< enemyInstance->boundingBox.max.y << " "
					<< enemyInstance->transform.m << " "
					<< enemyInstance->health << " "
					<< enemyInstance->showTexture << " "
					<< enemyInstance->isInvincible << " "
					<< enemyInstance->iFrame
					<< "\n";
			}
			outputStream << "Player Experience and Level...\n";
			outputStream << _Player_Level << ' ' << _Player_Experience << '\n';
		}

		outputStream.close();



		gGameStateNext = PAUSE;
		_deltaTime_State = 0.0f;
	}





	//Spawn Enemy
	if (_deltaTimeEnemySpawner > 1)
	{
		for (int i = 0; i < 2 * enemyHealth + 1; i++)
		{
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

			enemyInst->health = enemyHealth;
			std::cout << "Enemy Instance Health: " << enemyInst->health << '\n';

			_enemyList.push_back(enemyInst);
		}
		_deltaTimeEnemySpawner = 0;
	}
	//Rotation for Augment...
	//Rotation Increase.
	_rotation_Aug += 0.04f;
	//rotationA += 2 * PI / 180;
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
			_Player->scale.x *= -1;
			_playerScale *= -1;
		}
	}

	if (AEInputCheckTriggered(AEVK_RIGHT) || AEInputCheckTriggered(AEVK_D))
	{
		if (_playerScale < 0)
		{
			_Player->scale.x *= -1;
			_playerScale *= -1;
		}
	}

	//Offset ALL objects instances + adding player velo
	//KeyDown
	if (AEInputCheckCurr(AEVK_RIGHT) || AEInputCheckCurr(AEVK_D))
	{
		_Player->position.x += 5;
		for (int i = 1; i < GAME_OBJ_INST_NUM_MAX; i++)
		{

			GameObjInstances* qInst = sGameObjInstList + i;

			if ((qInst->flag & FLAG_ACTIVE) == 0)
				continue;

			// Update enemy position with player velocity
				qInst->position.x -= 5;

		}
	}
	
	if (AEInputCheckCurr(AEVK_LEFT) || AEInputCheckCurr(AEVK_A))
	{
		_Player->position.x -= 5;
		for (int i = 1; i < GAME_OBJ_INST_NUM_MAX; i++)
		{

			GameObjInstances* qInst = sGameObjInstList + i;

			if ((qInst->flag & FLAG_ACTIVE) == 0)
				continue;

			// Update enemy position with player velocity
			qInst->position.x += 5;

		}
	}
	if (AEInputCheckCurr(AEVK_DOWN) || AEInputCheckCurr(AEVK_S))
	{
		_Player->position.y -= 5;
		for (int i = 1; i < GAME_OBJ_INST_NUM_MAX; i++)
		{

			GameObjInstances* qInst = sGameObjInstList + i;

			if ((qInst->flag & FLAG_ACTIVE) == 0)
				continue;

			// Update enemy position with player velocity
			qInst->position.y += 5;

		}
	}
	if (AEInputCheckCurr(AEVK_UP) || AEInputCheckCurr(AEVK_W))
	{
		_Player->position.y += 5;
		for (int i = 1; i < GAME_OBJ_INST_NUM_MAX; i++)
		{

			GameObjInstances* qInst = sGameObjInstList + i;

			if ((qInst->flag & FLAG_ACTIVE) == 0)
				continue;

			// Update enemy position with player velocity
			qInst->position.y -= 5;

		}
	}



	if (AEInputCheckTriggered(AEVK_SPACE) || AEInputCheckTriggered(AEVK_C))
	{
		std::cout << "Once\n";
	}

	if (AEInputCheckTriggered(AEVK_1))
	{
		bossPhase = TYPE_BHELL1;
	}
	if (AEInputCheckTriggered(AEVK_2))
	{
		bossPhase = TYPE_BHELL2;
	}
	if (AEInputCheckTriggered(AEVK_3))
	{
		bossPhase = TYPE_BHELL3;
	}
	if (AEInputCheckTriggered(AEVK_4))
	{
		bossPhase = TYPE_BHELL4;
	}
	if (AEInputCheckTriggered(AEVK_5))
	{
		bossPhase = TYPE_BOWAP;
	}

	for (unsigned long i = 0; i < GAME_OBJ_INST_NUM_MAX; i++)
	{
		GameObjInstances* pInst = sGameObjInstList + i;

		if ((pInst->flag & FLAG_ACTIVE) == 0)
			continue;

		if (pInst->pObject == nullptr)
			continue;

		if (pInst->pObject->type == TYPE_PLAYER)
		{
			for (int j = 0; j < GAME_OBJ_INST_NUM_MAX; j++)
			{
				GameObjInstances* qInst = sGameObjInstList + j;

				if ((qInst->flag & FLAG_ACTIVE) == 0)
					continue;

				if (qInst->pObject->type == TYPE_AUGMENT1)
				{
					qInst->position.x = pInst->position.x;
					qInst->position.y = pInst->position.y + 75.0f;

					AUGMENT_1_FIRE_INTERVAL = 1.5f;

					AUGMENT_1_FIRE_TIMER += g_dt;
					if (AUGMENT_1_FIRE_TIMER >= AUGMENT_1_FIRE_INTERVAL)
					{
						// Get the mouse cursor position
						AEInputGetCursorPosition(&mouseX, &mouseY);

						// Convert the mouse position to world space
						AUGMENT_1_MOUSE_POSITION = { (f32)mouseX - (1366 / 2), -((f32)mouseY - (768 / 2)) };

						// Compute the direction of the bullet
						AUGMENT_1_DIRECTION = { AUGMENT_1_MOUSE_POSITION.x - qInst->position.x, AUGMENT_1_MOUSE_POSITION.y - qInst->position.y };
						AEVec2Normalize(&AUGMENT_1_DIRECTION, &AUGMENT_1_DIRECTION);

						// Create a new bullet object and set its velocity to point towards the target
						GameObjInstances* bulletInst = gameObjInstCreate(TYPE_BULLET, BULLET_SIZE, &qInst->position, &AUGMENT_1_DIRECTION, 0.0f);

						//std::cout << bulletInst->pObject << '\n';

						AEVec2Scale(&bulletInst->velocity, &bulletInst->velocity, BULLET_SPEED);

						// Reset the fire timer
						AUGMENT_1_FIRE_TIMER = 0.0f;
					}
				}

				if (qInst->pObject->type == TYPE_AUGMENT2)
				{
					AUGMENT_2_DIRECTION = { (f32)cos(_rotation_Aug), (f32)sin(_rotation_Aug) };
					AEVec2Scale(&AUGMENT_2_DIRECTION, &AUGMENT_2_DIRECTION, 100.0f);
					AEVec2Add(&qInst->position, &pInst->position, &AUGMENT_2_DIRECTION);
				}

				//if (qInst->pObject->type == TYPE_AUGMENT3)
				//{
				//
				//	AUGMENT_3_FIRE_TIMER = 0.0f;
				//	AUGMENT_3_FIRE_INTERVAL = 0.0f;
				//
				//
				//}

			}
		}



		if (pInst->pObject->type == TYPE_BOSS)
		{
			AEVec2 velocity;
			AEVec2 velocity2;
			AEVec2 velocity3;
			int numBulletsBHell;
			double DelayMovement;
			bool hasDelayTimePassed = false;
			double DelayShoot;
			if (bossPhase == TYPE_BHELL3 && pInst->health > 0 && pInst->health < 80)
			{
				AEVec2 direction = { cos(rotationA), sin(rotationA) };
				//AEVec2Scale(&direction, &direction, 3.0f);
				AEVec2Add(&pInst->position, &pInst->position, &direction);
			}

			if (AEInputCheckCurr(AEVK_MINUS))
			{
				pInst->health -= 1;
				std::cout << pInst->health << '\n';
			}

			switch (bossPhase)
			{
			case TYPE_BHELL1:
				DelayShoot = 0.25f;
				numBulletsBHell = 11;
				angle = 225;
				std::cout << "Current Time: " << _deltaTime_Shooting << '\n';
				if (pInst->health <= 0 || _deltaTime_Shooting > 10)
				{
					std::cout << "entry Upon this thing\n";
					double const MAX_DELAY = 4.0f;
					if (_delayTimeBullets > MAX_DELAY)
					{
						std::cout << "Entry2\n";
						bossPhase = TYPE_BHELL2;
						pInst->health = 100;
						_deltaTime_Shooting = 0;
						_delayTimeBullets = 0;
					}
				}
				else
				{
					if (_delayTimeBullets >= DelayShoot)
					{
						for (int i = 0; i < numBulletsBHell; i++)
						{
							static f64 angle2 = 0;
							angle -= 10;
							if (angle < 134)
							{
								angle = 225;
							}
							angle2 -= 20;
							if (angle2 < -60)
							{
								angle2 = 60;
							}
							velocity = { projectileSpeed * sin(AEDegToRad(angle)) , projectileSpeed * cos(AEDegToRad(angle)) };
							gameObjInstCreate(TYPE_BOSS_BULLETHELL_BULLET_1, 5, &pInst->position, &velocity, angle);
							velocity2 = { projectileSpeed * sin(AEDegToRad(angle2)) , projectileSpeed * cos(AEDegToRad(angle2)) };
							gameObjInstCreate(TYPE_BOSS_BULLETHELL_BULLET_1, 5, &pInst->position, &velocity2, angle2);


						}
						angle = 0;
						numBulletsBHell = 12;
						//for (int i = 0; i < numBulletsBHell; i++)
						//{
						//	angle += 360/12;
						//
						//	velocity = { projectileSpeed * sin(AEDegToRad(angle)) , projectileSpeed * cos(AEDegToRad(angle)) };
						//	gameObjInstCreate(TYPE_BOSS_BULLETHELL_BULLET_1, 20, &pInst->position, &velocity, angle);
						//
						//
						//
						//}

						_delayTimeBullets = 0;

					}
				}

				break;
			case TYPE_BHELL2:
				DelayShoot = 0.05f;
				numBulletsBHell = 2;
				angle = 390;

				std::cout << "Current Time: " << _deltaTime_Shooting << '\n';
				if (pInst->health <= 0 || _deltaTime_Shooting > 10)
				{
					double const MAX_DELAY = 4.0f;
					if (_delayTimeBullets > MAX_DELAY)
					{
						std::cout << "Entry3\n";
						bossPhase = TYPE_BHELL3;
						pInst->health = 100;
						_deltaTime_Shooting = 0;
						_delayTimeBullets = 0;
					}
				}
				else
				{
					if (_delayTimeBullets >= DelayShoot)
					{
						for (int i = 0; i < numBulletsBHell; i++)
						{
							angle = 360 + 40 * sin(g_appTime * 2.0 * PI / 5.0);
							for (int i = 0; i < 1; i++)
							{
								std::cout << angle << '\n';
								if (angle < 320)
								{
									angle = 400;
								}
								velocity = { projectileSpeed * sin(AEDegToRad(angle)) , projectileSpeed * cos(AEDegToRad(angle)) };
								gameObjInstCreate(TYPE_BOSS_BULLETHELL_BULLET_1, 5, &pInst->position, &velocity, angle);
							}
						}
						_delayTimeBullets = 0;
					}
				}

				break;
			case TYPE_BHELL3:
				DelayShoot = 0.15f;
				std::cout << "Current Time: " << _deltaTime_Shooting << '\n';
				if (pInst->health <= 0 || _deltaTime_Shooting > 10)
				{
					double const MAX_DELAY = 4.0f;
					if (_delayTimeBullets > MAX_DELAY)
					{
						std::cout << "Entry4\n";
						bossPhase = TYPE_BHELL4;
						pInst->health = 100;
						_deltaTime_Shooting = 0;
						_delayTimeBullets = 0;
					}
				}
				else {
					if (_delayTimeBullets >= DelayShoot)
					{
						if (pInst->health >= 80)
						{
							angle = 360;
							static f64 angleOffset = 0;
							DelayShoot = 0.25f;
							numBulletsBHell = 4;
							for (int i = 0; i < numBulletsBHell; i++)
							{
								f32 angleRadians = AEDegToRad(angle + angleOffset);
								velocity = { projectileSpeed * sin(angleRadians), projectileSpeed * cos(angleRadians) };
								gameObjInstCreate(TYPE_BOSS_BULLETHELL_BULLET_1, 5, &pInst->position, &velocity, angle + angleOffset);
								angle -= 120;
							}
							angleOffset += 10.0;
						}

						if (pInst->health >= 60 && pInst->health < 80)
						{
							angle = 360;
							static f64 angleOffset = 0;
							DelayShoot = 0.25f;
							numBulletsBHell = 4;
							for (int i = 0; i < numBulletsBHell; i++)
							{
								f32 angleRadians = AEDegToRad(angle - angleOffset);
								velocity = { projectileSpeed * sin(angleRadians), projectileSpeed * cos(angleRadians) };
								gameObjInstCreate(TYPE_BOSS_BULLETHELL_BULLET_1, 5, &pInst->position, &velocity, -angle - angleOffset);
								angle -= 120;
							}
							angleOffset += 10.0;
						}
						if (pInst->health > 40 && pInst->health < 60)
						{
							angle = 360;
							static f64 angleOffset = 0;
							DelayShoot = 0.25f;
							numBulletsBHell = 4;

							for (int i = 0; i < numBulletsBHell; i++)
							{
								f32 angleRadians = AEDegToRad(angle + angleOffset);
								velocity = { projectileSpeed * sin(angleRadians), projectileSpeed * cos(angleRadians) };
								gameObjInstCreate(TYPE_BOSS_BULLETHELL_BULLET_1, 5, &pInst->position, &velocity, angle + angleOffset);
								angle -= 120;
							}
							for (int i = 0; i < numBulletsBHell; i++)
							{
								f32 angleRadians = AEDegToRad(angle - angleOffset);
								velocity = { projectileSpeed * sin(angleRadians), projectileSpeed * cos(angleRadians) };
								gameObjInstCreate(TYPE_BOSS_BULLETHELL_BULLET_1, 5, &pInst->position, &velocity, -angle - angleOffset);
								angle -= 120;
							}
							angleOffset += 10.0;
						}
						if (pInst->health >= 0 && pInst->health <= 40)
						{
							angle = 360;
							static f64 angleOffset = 0;
							DelayShoot = 0.25f;
							numBulletsBHell = 4;

							for (int i = 0; i < numBulletsBHell; i++)
							{
								f32 angleRadians = AEDegToRad(angle + angleOffset);
								velocity = { projectileSpeed * sin(angleRadians), projectileSpeed * cos(angleRadians) };
								gameObjInstCreate(TYPE_BOSS_BULLETHELL_BULLET_1, 5, &pInst->position, &velocity, angle + angleOffset);
								angle -= 120;
							}
							for (int i = 0; i < numBulletsBHell; i++)
							{
								f32 angleRadians = AEDegToRad(angle - angleOffset);
								velocity = { projectileSpeed * sin(angleRadians), projectileSpeed * cos(angleRadians) };
								gameObjInstCreate(TYPE_BOSS_BULLETHELL_BULLET_1, 5, &pInst->position, &velocity, -angle - angleOffset);
								angle -= 120;
							}
							angle = 90;
							for (int i = 0; i < numBulletsBHell; i++)
							{
								f32 angleRadians = AEDegToRad(angle + angleOffset);
								velocity = { projectileSpeed * sin(angleRadians), projectileSpeed * cos(angleRadians) };
								gameObjInstCreate(TYPE_BOSS_BULLETHELL_BULLET_1, 5, &pInst->position, &velocity, angle + angleOffset);
								angle -= 120;
							}
							for (int i = 0; i < numBulletsBHell; i++)
							{
								f32 angleRadians = AEDegToRad(angle - angleOffset);
								velocity = { projectileSpeed * sin(angleRadians), projectileSpeed * cos(angleRadians) };
								gameObjInstCreate(TYPE_BOSS_BULLETHELL_BULLET_1, 5, &pInst->position, &velocity, -angle - angleOffset);
								angle -= 120;
							}
							angleOffset += 10.0;
						}
						_delayTimeBullets = 0;
					}
				}
				break;
				//Peerless Wind God
			case TYPE_BHELL4:
				numBullets = 7;
				std::cout << "Current Time: " << _deltaTime_Shooting << '\n';
				if (_deltaTime_Shooting > 3 && _deltaTime_Shooting < 18)
				{
					frequency = 1.0f;
					times = g_appTime;
					xSpeed += 0.005;
					std::cout << xSpeed << '\n';
				}

				if (_deltaTime_Shooting < 20)
				{
					angle += 10;
					if (angle > 200 || angle < 160)
					{
						angle = 160;
					}
					if (_deltaTime_Shooting < 10)
					{
						DelayShoot = 0.2f;
					}

					if (_deltaTime_Shooting >= 10 && _deltaTime_Shooting <= 14)
					{
						DelayShoot = 0.05f;
					}
					if (_deltaTime_Shooting > 14 && _deltaTime_Shooting <= 20)
					{
						DelayShoot = 0.015f;
					}

					if (_delayTimeBullets > DelayShoot)
					{
						for (int i = 0; i < numBullets; i++)
						{
							// Calculate the x position for this bullet
							float xPos = pInst->position.x + (i - numBullets / 2) * xSpacing;

							// Calculate the y position for this bullet with a random offset
							float yPos = pInst->position.y + (rand() % (maxY - minY + 1) + minY);

							// Set the bullet's position
							AEVec2 position = { xPos, yPos };
							// Set the bullet's velocity and angle
							AEVec2 velocity = { projectileSpeed * sin(AEDegToRad(angle)), projectileSpeed * cos(AEDegToRad(angle)) };
							float angleOffset = ((float)rand() / RAND_MAX) * 20 - 80;
							gameObjInstCreate(TYPE_BOSS_BULLETHELL_BULLET_1, 7, &position, &velocity, angle - angleOffset);
							_delayTimeBullets = 0;
						}
					}
				}

				if (_deltaTime_Shooting > 19)
				{
					xSpeed -= 0.001;
					if (xSpeed < 0)
					{
						xSpeed = 0;
					}
					ySpeed = 0;
				}

				//16 is the point where they stop..
				if (_deltaTime_Shooting > 22)
				{
					std::cout << "Entry BOWAP\n";
					_delayTimeBullets = 0;
					bossPhase = TYPE_BOWAP;
				}

				//std::cout << "Delay " << _delayTimeBullets << " Speed " << xSpeed << '\n';
				displacementX = xRange * sinf(xSpeed * g_appTime);
				displacementY = yRange * sinf(ySpeed * g_appTime);
				// Set the position of the object
				pInst->position.x = displacementX;
				pInst->position.y = 200.0f + displacementY; // set the y position to a fixed value for now
				break;
				//BOWAP
			case TYPE_BOWAP:
				std::cout << _deltaTime_Shooting << '\n';


				if (pInst->health > 0)
				{
					DelayMovement = 5.0f;
					//Updates position..
					if (hasDelayTimePassed)
					{
						pInst->position = { 0,0 };
					}
					else
					{
						AEVec2 direction = { -pInst->position.x, -pInst->position.y };
						AEVec2Normalize(&direction, &direction);

						// Calculate distance to move based on movement speed and elapsed time
						float distance = 10 * (float)g_dt;

						// Clamp distance to ensure position reaches 0,0
						if (AEVec2Length(&direction) < distance)
						{
							//pInst->position = { 0, 0 };
						}
						else
						{
							// Calculate velocity vector based on distance and direction
							AEVec2 velocity;
							AEVec2Scale(&velocity, &direction, distance);

							// Update position of pInst
							pInst->position.x += velocity.x;
							pInst->position.y += velocity.y;
						}
					}
					if (_delayTimeBullets > DelayMovement)
					{
						numBulletsBHell = 8;
						angle = rotationAngle * sin(g_appTime / 12 * 3.142);

						//BOWAP					
						for (int j = 0; j < numBulletsBHell; j++)
						{
							double angleT = angle + (30 * j * 360 / 14);
							velocity = { projectileSpeed * cos(AEDegToRad(angleT)) , projectileSpeed * sin(AEDegToRad(angleT)) };
							gameObjInstCreate(TYPE_BOSS_BULLETHELL_BULLET_1, 5, &pInst->position, &velocity, angleT);
						}
					}
				}
				break;
			default:
				break;

			}
		}

		if (pInst->pObject->type == TYPE_BOSS_BULLETHELL_BULLET_1)
		{
			pInst->position.x = 2 * pInst->velocity.x * g_dt + pInst->position.x;
			pInst->position.y = 2 * pInst->velocity.y * g_dt + pInst->position.y;
			//

			if (bossPhase == TYPE_BHELL1 && pInst->position.y > AEGfxGetWinMaxY())
			{
				angle = 180 + 45 * sin(g_appTime * 2.0 * PI / 5.0);
				for (int i = 0; i < 1; i++)
				{
					if (angle < 135)
					{
						angle = 225;
					}
					velocity = { projectileSpeed * sin(AEDegToRad(angle)) , projectileSpeed * cos(AEDegToRad(angle)) };
					gameObjInstCreate(TYPE_BOSS_BULLETHELL_BULLET_1, 5, &pInst->position, &velocity, angle);
				}
			}
			if (bossPhase == TYPE_BHELL2 && pInst->position.y > AEGfxGetWinMaxY())
			{
				pInst->position.y = AEGfxGetWinMinY();
			}
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
					AEVec2 ENEMY_DIRECTION = { qInst->position.x - pInst->position.x, qInst->position.y - pInst->position.y };

					// Normalize direction vector to get unit direction
					AEVec2Normalize(&ENEMY_DIRECTION, &ENEMY_DIRECTION);

					// Calculate velocity vector by scaling unit direction by enemy's movement speed
					AEVec2 ENEMY_VELOCITY = { ENEMY_DIRECTION.x * 5.0f, ENEMY_DIRECTION.y * 5.0f };

					// Scale velocity vector by time since last frame to get distance to move this frame
					float distanceToMove = AEVec2Length(&ENEMY_VELOCITY) * g_dt;
					ENEMY_VELOCITY.x *= distanceToMove;
					ENEMY_VELOCITY.y *= distanceToMove;

					// Update enemy position with velocity
					pInst->position.x += ENEMY_VELOCITY.x;
					pInst->position.y += ENEMY_VELOCITY.y;

				}
			}
		}

		if (pInst->pObject->type == TYPE_PLAYER_HITBOX_INDICATOR)
		{
			pInst->position.x = _Player->position.x;
			pInst->position.y = _Player->position.y - 10;
			if (AEInputCheckCurr(AEVK_LSHIFT))
			{
				pInst->showTexture = true;
			}
			else
			{
				pInst->showTexture = false;
			}
		}

		//Window size is 1366x768

		if (pInst->position.x > AEGfxGetWinMaxX() ||
			pInst->position.x < AEGfxGetWinMinX() ||
			pInst->position.y > AEGfxGetWinMaxY() ||
			pInst->position.y < AEGfxGetWinMinY())
		{
			if (pInst->pObject->type == TYPE_PLAYER ||
				pInst->pObject->type == TYPE_AUGMENT1 ||
				pInst->pObject->type == TYPE_ENEMY ||
				pInst->pObject->type == TYPE_BOSS ||
				pInst->pObject->type == TYPE_PLAYER_HITBOX_INDICATOR ||
				pInst->pObject->type == TYPE_AUGMENT2 ||
				pInst->pObject->type == TYPE_AUGMENT3 ||
				pInst->pObject->type == TYPE_AUGMENT4 ||
				pInst->pObject->type == TYPE_AUGMENT5 ||
				pInst->pObject->type == TYPE_EXPERIENCE)
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


		//pInst->boundingBox.min.x = -(BOUNDING_RECT_SIZE / 2.0f) * pInst->scale.x + pInst->position.x;
		//pInst->boundingBox.min.y = -(BOUNDING_RECT_SIZE / 2.0f) * pInst->scale.y + pInst->position.y;
		//pInst->boundingBox.max.x = +(BOUNDING_RECT_SIZE / 2.0f) * pInst->scale.x + pInst->position.x;
		//pInst->boundingBox.max.y = +(BOUNDING_RECT_SIZE / 2.0f) * pInst->scale.y + pInst->position.y;




	}


	///////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////COLLISION////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////

	//TAKE NOTE
	//ObjInstance1 = Instance 1 to check with :  ObjInstance2 = Instance 2 , SIMILARLY TO THE TOP,
	if (_Player->health > 0) {
		for (unsigned long i = 0; i < GAME_OBJ_INST_NUM_MAX; i++)
		{
			GameObjInstances* ObjInstance1 = sGameObjInstList + i;

			if ((ObjInstance1->flag & FLAG_ACTIVE) == 0)
				continue;

			if (ObjInstance1->pObject->type == TYPE_ENEMY)
			{
				for (unsigned long j = 0; j < GAME_OBJ_INST_NUM_MAX; j++)
				{
					GameObjInstances* ObjInstance2 = sGameObjInstList + j;

					if ((ObjInstance2->flag & FLAG_ACTIVE) == 0)
						continue;

					if (ObjInstance2->pObject->type == TYPE_BULLET)
					{
						if (CollisionCircleCircle(ObjInstance1->position, ObjInstance1->scale.x, ObjInstance2->position, ObjInstance2->scale.x))
						{
							//Spawn Orbs of Experience at ObjInstance1 Position...
							//bulletCount--;
							//std::cout << bulletCount << '\n';
							ObjInstance1->health--;
							if (ObjInstance1->health <= 0)
							{
								gameObjInstDestroy(ObjInstance1);
							}
							gameObjInstDestroy(ObjInstance2);

							gameObjInstCreate(TYPE_EXPERIENCE, 10, &ObjInstance1->position, 0, 0);
						}
					}
					if (ObjInstance2->pObject->type == TYPE_AUGMENT2)
					{
						if (CollisionCircleCircle(ObjInstance1->position, ObjInstance1->scale.x, ObjInstance2->position, ObjInstance2->scale.x))
						{
							//Spawn Orbs of Experience at ObjInstance1 Position...
							//bulletCount--;
							//std::cout << bulletCount << '\n';
							ObjInstance1->health--;
							if (ObjInstance1->health <= 0)
							{
								gameObjInstDestroy(ObjInstance1);
							}

							gameObjInstCreate(TYPE_EXPERIENCE, 10, &ObjInstance1->position, 0, 0);
						}
					}

				}
			}


			if (ObjInstance1->pObject->type == TYPE_EXPERIENCE)
			{
				for (unsigned long j = 0; j < GAME_OBJ_INST_NUM_MAX; j++)
				{
					GameObjInstances* ObjInstance2 = sGameObjInstList + j;

					if ((ObjInstance2->flag & FLAG_ACTIVE) == 0)
						continue;

					if (ObjInstance2->pObject->type == TYPE_PLAYER)
					{
						if (CollisionCircleCircle(ObjInstance1->position, ObjInstance1->scale.x, ObjInstance2->position, ObjInstance2->scale.x))
						{
							_Player_Experience++;
							std::cout << "Player Experience: " << _Player_Experience << '\n';
							std::cout << "Player Level: " << _Player_Level << '\n';
							gameObjInstDestroy(ObjInstance1);
						}
					}
				}
			}
			//PLAYER COLLISION
			if (ObjInstance1->pObject->type == TYPE_PLAYER) {
				for (unsigned long j = 0; j < GAME_OBJ_INST_NUM_MAX; j++)
				{
					GameObjInstances* ObjInstance2 = sGameObjInstList + j;
					if ((ObjInstance2->flag & FLAG_ACTIVE) == 0)
						continue;

					if (ObjInstance2->pObject->type == TYPE_ENEMY) {
						if (_Player->iFrame <= 0)
							_Player->isInvincible = false;
						if (_Player->iFrame > 0) {
							_Player->isInvincible = true;
							_Player->iFrame -= (float)AEFrameRateControllerGetFrameTime();
						}
						if (CollisionCircleCircle(ObjInstance1->position, ObjInstance1->scale.x, ObjInstance2->position, ObjInstance2->scale.x)) {
							if (_Player->isInvincible == false) {
								_Player->health--;
								std::cout << "Player HP: " << _Player->health << '\n';
								_Player->iFrame = 50.f;
								onValueChange = true;
							}
						}
					}
				}
			}
		}
	}

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

		AEMtx33Scale(&scale, pInst->scale.x, pInst->scale.y);
		AEMtx33Rot(&rotate, pInst->direction);
		AEMtx33Trans(&translate, pInst->position.x, pInst->position.y);
		AEMtx33Concat((AEMtx33*)pInst->transform.m, &rotate, &scale);
		AEMtx33Concat((AEMtx33*)pInst->transform.m, &translate, (AEMtx33*)pInst->transform.m);
	}
}

void Level_1_Draw(void)
{
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);


	AEGfxTexture* playerTex = AEGfxTextureLoad("..\\..\\Assets\\Assets\\player.png");
	AEGfxTexture* bulletTex = AEGfxTextureLoad("..\\..\\Assets\\Assets\\YellowTexture.png");
	AEGfxTexture* augmentGunTex = AEGfxTextureLoad("..\\..\\Assets\\Assets\\drone.png");
	AEGfxTexture* bossTex = AEGfxTextureLoad("..\\..\\Assets\\Assets\\Boss.png");
	AEGfxTexture* bossBullet1Tex = AEGfxTextureLoad("..\\..\\Assets\\Assets\\circle-512.png");
	AEGfxTexture* enemyTex = AEGfxTextureLoad("..\\..\\Assets\\Assets\\ling.png");
	AEGfxTexture* pHitboxTex = AEGfxTextureLoad("..\\..\\Assets\\Assets\\circle-512.png");
	AEGfxTexture* spawnerTex = AEGfxTextureLoad("..\\..\\Assets\\Assets\\TrollFace.png");
	AEGfxTexture* InvisibleTex = AEGfxTextureLoad("..\\..\\Assets\\Assets\\Invisible.png");
	AEGfxTexture* ExpOrbTex = AEGfxTextureLoad("..\\..\\Assets\\Assets\\Orb.png");
	AEGfxTexture* BgroundTex = AEGfxTextureLoad("..\\..\\Assets\\Assets\\Background.png");

	//Draw Background
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetTintColor(0.8f, 0.8f, 0.8f, 0.8f);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetTransparency(1.0f);
	AEGfxTextureSet(BGTex, 0, 0);
	AEMtx33 scale0 = { 0 };
	AEMtx33Scale(&scale0, 1366.f, 1000.f);
	AEMtx33 rotate0 = { 0 };
	AEMtx33Rot(&rotate0, 0.f);
	AEMtx33 translate0 = { 0 };
	AEMtx33Trans(&translate0, 0, 0);
	AEMtx33 transform0 = { 0 };
	AEMtx33Concat(&transform0, &rotate0, &scale0);
	AEMtx33Concat(&transform0, &translate0, &transform0);
	AEGfxSetTransform(transform0.m);
	AEGfxMeshDraw(bMesh, AE_GFX_MDM_TRIANGLES);
	//Finish Background draw

	//Exp bar start
	//DOING IT THIS WAY CAUSES LAG/STUTTERING, TO BE FIXED
	
	AEGfxTexture* Expbar0 = AEGfxTextureLoad("..\\..\\Assets\\Assets\\Expbar\\xp0.png");
	AEGfxTexture* Expbar1 = AEGfxTextureLoad("..\\..\\Assets\\Assets\\Expbar\\xp1.png");
	AEGfxTexture* Expbar2 = AEGfxTextureLoad("..\\..\\Assets\\Assets\\Expbar\\xp2.png");
	AEGfxTexture* Expbar3 = AEGfxTextureLoad("..\\..\\Assets\\Assets\\Expbar\\xp3.png");
	AEGfxTexture* Expbar4 = AEGfxTextureLoad("..\\..\\Assets\\Assets\\Expbar\\xp4.png");
	AEGfxTexture* Expbar5 = AEGfxTextureLoad("..\\..\\Assets\\Assets\\Expbar\\xp5.png");
	AEGfxTexture* Expbar6 = AEGfxTextureLoad("..\\..\\Assets\\Assets\\Expbar\\xp6.png");
	AEGfxTexture* Expbar7 = AEGfxTextureLoad("..\\..\\Assets\\Assets\\Expbar\\xp7.png");
	AEGfxTexture* Expbar8 = AEGfxTextureLoad("..\\..\\Assets\\Assets\\Expbar\\xp8.png");
	AEGfxTexture* Expbar9 = AEGfxTextureLoad("..\\..\\Assets\\Assets\\Expbar\\xp9.png");

	
	

	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetTransparency(1.0f);
	if (expPercent == 0) {AEGfxTextureSet(Expbar0, 0, 0);}
	else if (expPercent == 1) {AEGfxTextureSet(Expbar1, 0, 0);}
	else if (expPercent == 2) {AEGfxTextureSet(Expbar2, 0, 0);}
	else if (expPercent == 3) { AEGfxTextureSet(Expbar3, 0, 0); }
	else if (expPercent == 4) { AEGfxTextureSet(Expbar4, 0, 0); }
	else if (expPercent == 5) { AEGfxTextureSet(Expbar5, 0, 0); }
	else if (expPercent == 6) { AEGfxTextureSet(Expbar6, 0, 0); }
	else if (expPercent == 7) { AEGfxTextureSet(Expbar7, 0, 0); }
	else if (expPercent == 8) { AEGfxTextureSet(Expbar8, 0, 0); }
	else if (expPercent == 9) { AEGfxTextureSet(Expbar9, 0, 0); }
	//Exp bar end
	

	AEMtx33 scale2 = { 0 };
	AEMtx33Scale(&scale2, 600.f, 30.f);
	AEMtx33 rotate2 = { 0 };
	AEMtx33Rot(&rotate2, 0.f);
	AEMtx33 translate2 = { 0 };
	AEMtx33Trans(&translate2, -85, 368);
	AEMtx33 transform2 = { 0 };
	AEMtx33Concat(&transform2, &rotate2, &scale2);
	AEMtx33Concat(&transform2, &translate2, &transform2);
	AEGfxSetTransform(transform2.m);
	AEGfxMeshDraw(ptrMesh, AE_GFX_MDM_TRIANGLES);
	//end Exp bar
	
	for (unsigned long i = 0; i < GAME_OBJ_INST_NUM_MAX; i++)
	{
		GameObjInstances* pInst = sGameObjInstList + i;

		AEGfxTexture* texture = nullptr;
		if ((pInst->flag & FLAG_ACTIVE) == 0)
			continue;

		AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
		AEGfxSetTransparency(1);
		// Set the tint to white, so that the sprite can // display the full range of colors (default is black). 
		AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
		AEGfxSetBlendMode(AE_GFX_BM_BLEND);

		// Set the tint to white, so that the sprite can // display the full range of colors (default is black).		
		if (pInst->pObject->type == TYPE_PLAYER)
		{
			texture = playerTex;
		}
		else if (pInst->pObject->type == TYPE_BULLET)
		{
			texture = bulletTex;
		}
		else if (pInst->pObject->type == TYPE_AUGMENT1 || pInst->pObject->type == TYPE_AUGMENT2)
		{
			texture = augmentGunTex;
		}
		else if (pInst->pObject->type == TYPE_BOSS)
		{
			texture = bossTex;
		}
		else if (pInst->pObject->type == TYPE_BOSS_BULLETHELL_BULLET_1)
		{
			texture = bossBullet1Tex;
		}
		else if (pInst->pObject->type == TYPE_ENEMY)
		{
			texture = enemyTex;
		}
		else if (pInst->pObject->type == TYPE_PLAYER_HITBOX_INDICATOR)
		{
			//Improvise, Adapt, Overcome - Bear Grylls
			if (pInst->showTexture == true)
				texture = pHitboxTex;
			else
				texture = InvisibleTex;
		}
		else if (pInst->pObject->type == TYPE_EXPERIENCE)
		{
			texture = ExpOrbTex;
		}
		
		AEGfxTextureSet(texture, 0, 0);
		AEGfxSetTransform(pInst->transform.m);
		AEGfxMeshDraw(pInst->pObject->pMesh, AE_GFX_MDM_TRIANGLES);
	}
	if (onValueChange) {
		if (_Player->health == 0) {
			std::cout << "GAME OVER \n";
		}
		onValueChange = false;
	}
	AEGfxTextureUnload(playerTex);
	AEGfxTextureUnload(bulletTex);
	AEGfxTextureUnload(augmentGunTex);
	AEGfxTextureUnload(bossTex);
	AEGfxTextureUnload(bossBullet1Tex);
	AEGfxTextureUnload(enemyTex);
	AEGfxTextureUnload(pHitboxTex);
	AEGfxTextureUnload(spawnerTex);
	AEGfxTextureUnload(InvisibleTex);
	AEGfxTextureUnload(ExpOrbTex);

	// Rendering texts for the screen
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxTextureSet(NULL, 0, 0);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	sprintf_s(gdt_buffer, "%f", g_dt);
	AEGfxPrint(fontID, gdt_buffer, (getWinWidth() / (-2500.f * scaleX_level1)), (getWinHeight() / (-1350.f * scaleY_level1)), 1.0f * scaleX_level1, 255.0f / 255.f, 0.0f / 255.f, 0.0f / 255.f);


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
	AEGfxMeshFree(ptrMesh);
	AEGfxMeshFree(bMesh);
}