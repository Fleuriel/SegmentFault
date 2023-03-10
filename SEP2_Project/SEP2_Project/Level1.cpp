#include "Main.h"
#include "GameObjects.h"
#include <iostream>
#include <cstdio>

static bool onValueChange = true;
int reqExp = 15;
int expPercent = 0;
// Pointer to Mesh
AEGfxVertexList* ptrMesh = nullptr;

//AugmentOverlay definition
AEGfxVertexList* augmentMesh = nullptr;

// Buttons in AugmentOverlay definition
AEGfxVertexList* augmentButtonMesh = nullptr;

//Background definition
AEGfxVertexList* bMesh = nullptr;
AEVec2 BG = { 0, 0 };

// Pre-definiton for string buffers
char gdt_buffer[1024]{};
char hp_buffer[1024]{};
char boss_hp_buffer[1024]{};
char augment1_buffer[1024]{};
char augment2_buffer[1024]{};
char augment3_buffer[1024]{};
char augment4_buffer[1024]{};
char augmentAdd_buffer[1024]{};
char skillpoint_buffer[1024]{};
char strbuffer1[1024]{};
char strbuffer2[1024]{};
float augments_textWidth{}, augments_textHeight{};

// Pre-definition for translations of buttons
double augment1Button_transX;
double augment1Button_transY;
double augment2Button_transX;
double augment2Button_transY;
double augment3Button_transX;
double augment3Button_transY;
double augment4Button_transX;
double augment4Button_transY;


// Pre-definition of overlay transparency
float overlayTransparency = 0.0f;

// Pre-definition of scaling
double scaleX_level1;
double scaleY_level1;

//Pre-definition for buffers
char level_buffer[16]{};
float textWidth{}, textHeight{};

//// Pre-definition of time
float timeElapsed = 0.f;
float minElapsed = 0.f;

int MaxHealth; // Player max hp 
int OrbCap = 30, OrbCounter = 0; // EXP Orb cap 
int spawnCheck = 1; // Boss Spawn 
int MaxBossHealth;

int Augment1Level = 1;
int Augment2Level = 0;
float Augment1CD = 1.5f;
float Augment2Range = 1;
int Aug2CreateCheck = 0;

void Level_1_Load(void)
{
	sGameObjList = (GameObjects*)calloc(GAME_OBJ_NUM_MAX, sizeof(GameObjects));
	sGameObjInstList = (GameObjInstances*)calloc(GAME_OBJ_INST_NUM_MAX, sizeof(GameObjInstances));


	std::cout << "Level1_Load\n";
	sGameObjNum = 0;
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

	GameObjects* _Objects;


	//0 TYPE_PLAYER
	_Objects = sGameObjList + sGameObjNum++;
	_Objects->type = TYPE_PLAYER;

	AEGfxMeshStart();

	AEGfxTriAdd(
		0.5f, 0.5f, 0xFFFFFF, 1.0f, 0.0f,
		-0.5f, -0.5f, 0xFFFFFF, 0.0f, 1.0f,
		0.5f, -0.5f, 0xFFFFFF, 1.0f, 1.0f);
	AEGfxTriAdd(
		-0.5f, 0.5f, 0xFFFFFF, 0.0f, 0.0f,
		-0.5f, -0.5f, 0xFFFFFF, 0.0f, 1.0f,
		0.5f, 0.5f, 0xFFFFFF, 1.0f, 0.0f);
	_Objects->pMesh = AEGfxMeshEnd();
	AE_ASSERT_MESG(_Objects->pMesh, "Fail to create object!!");

	//1 TYPE_BOSS

	_Objects = sGameObjList + sGameObjNum++;
	_Objects->type = TYPE_BOSS;

	AEGfxMeshStart();

	AEGfxTriAdd(
		0.5f, 0.5f, 0x808080, 1.0f, 0.0f,
		-0.5f, -0.5f, 0x808080, 0.0f, 1.0f,
		0.5f, -0.5f, 0x696969, 1.0f, 1.0f);
	AEGfxTriAdd(
		-0.5f, 0.5f, 0x696969, 0.0f, 0.0f,
		-0.5f, -0.5f, 0x696969, 0.0f, 1.0f,
		0.5f, 0.5f, 0x808080, 1.0f, 0.0f);
	_Objects->pMesh = AEGfxMeshEnd();
	AE_ASSERT_MESG(_Objects->pMesh, "Fail to create object!!");



	//2 TYPE_BOSS_BULLETHELL_BULLET_1
	_Objects = sGameObjList + sGameObjNum++;
	_Objects->type = TYPE_BOSS_BULLETHELL_BULLET_1;

	AEGfxMeshStart();

	AEGfxTriAdd(
		0.5f, 0.5f, 0x808080, 1.0f, 0.0f,
		-0.5f, -0.5f, 0x808080, 0.0f, 1.0f,
		0.5f, -0.5f, 0x696969, 1.0f, 1.0f);
	AEGfxTriAdd(
		-0.5f, 0.5f, 0x696969, 0.0f, 0.0f,
		-0.5f, -0.5f, 0x696969, 0.0f, 1.0f,
		0.5f, 0.5f, 0x808080, 1.0f, 0.0f);
	_Objects->pMesh = AEGfxMeshEnd();
	AE_ASSERT_MESG(_Objects->pMesh, "Fail to create object!!");


	//3 TYPE_BULLET
	_Objects = sGameObjList + sGameObjNum++;
	_Objects->type = TYPE_BULLET;

	AEGfxMeshStart();

	AEGfxTriAdd(
		0.5f, 0.5f, 0x808080, 1.0f, 0.0f,
		-0.5f, -0.5f, 0x808080, 0.0f, 1.0f,
		0.5f, -0.5f, 0x696969, 1.0f, 1.0f);
	AEGfxTriAdd(
		-0.5f, 0.5f, 0x696969, 0.0f, 0.0f,
		-0.5f, -0.5f, 0x696969, 0.0f, 1.0f,
		0.5f, 0.5f, 0x808080, 1.0f, 0.0f);
	_Objects->pMesh = AEGfxMeshEnd();
	AE_ASSERT_MESG(_Objects->pMesh, "Fail to create object!!");

	//4	TYPE_ENEMY
	_Objects = sGameObjList + sGameObjNum++;
	_Objects->type = TYPE_ENEMY;

	AEGfxMeshStart();

	AEGfxTriAdd(
		0.5f, 0.5f, 0x808080, 1.0f, 0.0f,
		-0.5f, -0.5f, 0x808080, 0.0f, 1.0f,
		0.5f, -0.5f, 0x696969, 1.0f, 1.0f);
	AEGfxTriAdd(
		-0.5f, 0.5f, 0x696969, 0.0f, 0.0f,
		-0.5f, -0.5f, 0x696969, 0.0f, 1.0f,
		0.5f, 0.5f, 0x808080, 1.0f, 0.0f);
	_Objects->pMesh = AEGfxMeshEnd();
	AE_ASSERT_MESG(_Objects->pMesh, "Fail to create object!!");

	//5	TYPE_PLAYER_HITBOX_INDICATOR
	_Objects = sGameObjList + sGameObjNum++;
	_Objects->type = TYPE_PLAYER_HITBOX_INDICATOR;

	AEGfxMeshStart();

	AEGfxTriAdd(
		0.5f, 0.5f, 0x808080, 1.0f, 0.0f,
		-0.5f, -0.5f, 0x808080, 0.0f, 1.0f,
		0.5f, -0.5f, 0x696969, 1.0f, 1.0f);
	AEGfxTriAdd(
		-0.5f, 0.5f, 0x696969, 0.0f, 0.0f,
		-0.5f, -0.5f, 0x696969, 0.0f, 1.0f,
		0.5f, 0.5f, 0x808080, 1.0f, 0.0f);
	_Objects->pMesh = AEGfxMeshEnd();
	AE_ASSERT_MESG(_Objects->pMesh, "Fail to create object!!");

	//6 Exp Orbs
	_Objects = sGameObjList + sGameObjNum++;
	_Objects->type = TYPE_EXPERIENCE;

	AEGfxMeshStart();

	AEGfxTriAdd(
		0.5f, 0.5f, 0x808080, 1.0f, 0.0f,
		-0.5f, -0.5f, 0x808080, 0.0f, 1.0f,
		0.5f, -0.5f, 0x696969, 1.0f, 1.0f);
	AEGfxTriAdd(
		-0.5f, 0.5f, 0x696969, 0.0f, 0.0f,
		-0.5f, -0.5f, 0x696969, 0.0f, 1.0f,
		0.5f, 0.5f, 0x808080, 1.0f, 0.0f);
	_Objects->pMesh = AEGfxMeshEnd();
	AE_ASSERT_MESG(_Objects->pMesh, "Fail to create object!!");



	//7 TYPE_AUGMENT1
	_Objects = sGameObjList + sGameObjNum++;
	_Objects->type = TYPE_AUGMENT1;

	AEGfxMeshStart();

	AEGfxTriAdd(
		0.5f, 0.5f, 0x808080, 1.0f, 0.0f,
		-0.5f, -0.5f, 0x808080, 0.0f, 1.0f,
		0.5f, -0.5f, 0x696969, 1.0f, 1.0f);
	AEGfxTriAdd(
		-0.5f, 0.5f, 0x696969, 0.0f, 0.0f,
		-0.5f, -0.5f, 0x696969, 0.0f, 1.0f,
		0.5f, 0.5f, 0x808080, 1.0f, 0.0f);
	_Objects->pMesh = AEGfxMeshEnd();
	AE_ASSERT_MESG(_Objects->pMesh, "Fail to create object!!");

	//8 TYPE_AUGMENT2
	_Objects = sGameObjList + sGameObjNum++;
	_Objects->type = TYPE_AUGMENT2;

	AEGfxMeshStart();

	AEGfxTriAdd(
		0.5f, 0.5f, 0x808080, 1.0f, 0.0f,
		-0.5f, -0.5f, 0x808080, 0.0f, 1.0f,
		0.5f, -0.5f, 0x696969, 1.0f, 1.0f);
	AEGfxTriAdd(
		-0.5f, 0.5f, 0x696969, 0.0f, 0.0f,
		-0.5f, -0.5f, 0x696969, 0.0f, 1.0f,
		0.5f, 0.5f, 0x808080, 1.0f, 0.0f);
	_Objects->pMesh = AEGfxMeshEnd();
	AE_ASSERT_MESG(_Objects->pMesh, "Fail to create object!!");

	//9 TYPE_AUGMENT3
	_Objects = sGameObjList + sGameObjNum++;
	_Objects->type = TYPE_AUGMENT3;

	AEGfxMeshStart();

	AEGfxTriAdd(
		0.5f, 0.5f, 0x808080, 1.0f, 0.0f,
		-0.5f, -0.5f, 0x808080, 0.0f, 1.0f,
		0.5f, -0.5f, 0x696969, 1.0f, 1.0f);
	AEGfxTriAdd(
		-0.5f, 0.5f, 0x696969, 0.0f, 0.0f,
		-0.5f, -0.5f, 0x696969, 0.0f, 1.0f,
		0.5f, 0.5f, 0x808080, 1.0f, 0.0f);
	_Objects->pMesh = AEGfxMeshEnd();
	AE_ASSERT_MESG(_Objects->pMesh, "Fail to create object!!");

	//10 TYPE_AUGMENT4
	_Objects = sGameObjList + sGameObjNum++;
	_Objects->type = TYPE_AUGMENT4;

	AEGfxMeshStart();

	AEGfxTriAdd(
		0.5f, 0.5f, 0x808080, 1.0f, 0.0f,
		-0.5f, -0.5f, 0x808080, 0.0f, 1.0f,
		0.5f, -0.5f, 0x696969, 1.0f, 1.0f);
	AEGfxTriAdd(
		-0.5f, 0.5f, 0x696969, 0.0f, 0.0f,
		-0.5f, -0.5f, 0x696969, 0.0f, 1.0f,
		0.5f, 0.5f, 0x808080, 1.0f, 0.0f);
	_Objects->pMesh = AEGfxMeshEnd();
	AE_ASSERT_MESG(_Objects->pMesh, "Fail to create object!!");

	//11 TYPE_AUGMENT5
	_Objects = sGameObjList + sGameObjNum++;
	_Objects->type = TYPE_AUGMENT5;

	AEGfxMeshStart();

	AEGfxTriAdd(
		0.5f, 0.5f, 0x808080, 1.0f, 0.0f,
		-0.5f, -0.5f, 0x808080, 0.0f, 1.0f,
		0.5f, -0.5f, 0x696969, 1.0f, 1.0f);
	AEGfxTriAdd(
		-0.5f, 0.5f, 0x696969, 0.0f, 0.0f,
		-0.5f, -0.5f, 0x696969, 0.0f, 1.0f,
		0.5f, 0.5f, 0x808080, 1.0f, 0.0f);
	_Objects->pMesh = AEGfxMeshEnd();
	AE_ASSERT_MESG(_Objects->pMesh, "Fail to create object!!");




	
	if (inputFileStream.good())
	{
		/*std::cout << "file exist\n";
		std::string line = "";

		std::cout << "hello\t " << inputfilestream.eof() << '\n';*/


		inputFileStream >> Currency;
		std::cout << Currency << '\n';

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
	//end Background
	
	// Create Overlay for Augments
	AEGfxMeshStart();

	AEGfxTriAdd(
		0.5f, 0.5f, 0xFFADD8E6, 1.0f, 0.0f,
		-1.f, -0.5f, 0xFFADD8E6, 0.0f, 1.0f,
		0.5f, -0.5f, 0xFFADD8E6, 1.0f, 1.0f);
	AEGfxTriAdd(
		-1.f, 0.5f, 0xFFADD8E6, 0.0f, 0.0f,
		-1.f, -0.5f, 0xFFADD8E6, 0.0f, 1.0f,
		0.5f, 0.5f, 0xFFADD8E6, 1.0f, 0.0f);

	augmentMesh = AEGfxMeshEnd();
	// End Overlay

	// Create buttons for Augments
	AEGfxMeshStart();

	AEGfxTriAdd(
		0.5f, 0.5f, 0xFF001736, 1.0f, 0.0f,
		-1.2f, -0.5f, 0xFF001736, 0.0f, 1.0f,
		0.5f, -0.5f, 0xFF001736, 1.0f, 1.0f);
	AEGfxTriAdd(
		-1.2f, 0.5f, 0xFF001736, 0.0f, 0.0f,
		-1.2f, -0.5f, 0xFF001736, 0.0f, 1.0f,
		0.5f, 0.5f, 0xFF001736, 1.0f, 0.0f);

	augmentButtonMesh = AEGfxMeshEnd();
	// End Overlay

}

void Level_1_Init(void)
{
	//0
	_Player = gameObjInstCreate(TYPE_PLAYER, PLAYER_SIZE, nullptr, nullptr, 0.0f);
	_Player->health = MaxHealth =20;
	AE_ASSERT(_Player);




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

	
	//9
	_Augment_Three = gameObjInstCreate(TYPE_AUGMENT3, 0.0f, nullptr, nullptr, 0.0f);
	_Augment_Three->scale.x = AUG_GUN_SIZE * 3;
	_Augment_Three->scale.y = AUG_GUN_SIZE;
	//
	//AE_ASSERT(_Augment_Three);

	// Gets the scale of 1366x768
	scaleX_level1 = getWinWidth() / 1366.f;
	scaleY_level1 = getWinHeight() / 768.f;

	// Defintion of the translation for augment buttons
	augment1Button_transX = 0.0f * scaleX_level1;
	augment1Button_transY = 280.0f * scaleY_level1;
	augment2Button_transX = 0.0f * scaleX_level1;
	augment2Button_transY = 195.0f * scaleY_level1;
	augment3Button_transX = 0.0f * scaleX_level1;
	augment3Button_transY = 115.0f * scaleY_level1;
	augment4Button_transX = 0.0f * scaleX_level1;
	augment4Button_transY = 30.0f * scaleY_level1;

}


void Level_1_Update(void)
{
	// Initialize cursor coordinates
	s32 cursorX;
	s32 cursorY;
	AEInputGetCursorPosition(&cursorX, &cursorY);

	// Checking for time passed in seconds;
	timeElapsed += g_dt;
	if (timeElapsed >= 59.5) {
		minElapsed++;
		timeElapsed = 0;
	}

	// Checking if overlay is pressed
	if (AEInputCheckTriggered(AEVK_RBUTTON))
	{
		if (overlayTransparency == 0) {
			overlayTransparency = 0.5;
		}
		else if (overlayTransparency != 0) {
			overlayTransparency = 0;
		}
	}

	// Augment buttons mid points
	float augment1Button_midX = (getWinWidth() / 2.04) + augment1Button_transX;
	float augment1Button_midY = (getWinHeight() / 2) - augment1Button_transY;

	float augment2Button_midX = (getWinWidth() / 2.04) + augment2Button_transX;
	float augment2Button_midY = (getWinHeight() / 2) - augment2Button_transY;

	float augment3Button_midX = (getWinWidth() / 2.04) + augment3Button_transX;
	float augment3Button_midY = (getWinHeight() / 2) - augment3Button_transY;

	float augment4Button_midX = (getWinWidth() / 2.04) + augment4Button_transX;
	float augment4Button_midY = (getWinHeight() / 2) - augment4Button_transY;

	if (overlayTransparency != 0) {
		// Overlay button logic and defintions
		if (IsAreaClicked(augment1Button_midX, augment1Button_midY, 57.8f * scaleX_level1, 50.0f * scaleY_level1, cursorX, cursorY)
			&& AEInputCheckTriggered(AEVK_LBUTTON)) {
			//gGameStateNext = QUIT;
			printf("Augment 1 ++\n");
			if (SkillPoint != 0 && Augment1Level!=4) {
				SkillPoint--;
				Augment1CD -= 0.3;
				Augment1Level++;
			}
		}

		if (IsAreaClicked(augment2Button_midX, augment2Button_midY, 57.8f * scaleX_level1, 50.0f * scaleY_level1, cursorX, cursorY)
			&& AEInputCheckTriggered(AEVK_LBUTTON)) {
			//gGameStateNext = QUIT;
			printf("Augment 2 ++\n");
			if (SkillPoint != 0 && Augment2Level != 4) {
				SkillPoint--;
				Augment2Range += 0.5;
				Augment2Level++;
			}
		}
	}
	if (Augment2Level == 1 && Aug2CreateCheck == 0) {
		_Augment_Two = gameObjInstCreate(TYPE_AUGMENT2, AUG_GUN_SIZE, nullptr, nullptr, 0.0f);
		AE_ASSERT(_Augment_Two);
		Aug2CreateCheck = 1;
	}

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
	if (AEInputCheckTriggered(AEVK_P))
	{
		std::ofstream outputStream{ "..\\..\\Assets\\SaveFiles\\Currency.txt" };
		if (outputStream.is_open())
		{
			outputStream << Currency << '\n';
	
		}

		outputStream.close();

	}

	//Spawn Enemy
	if (_deltaTimeEnemySpawner > 1 && enemyCount<50 && minElapsed < 2)
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
			if(enemyInst!= nullptr){
				enemyInst->health = enemyHealth;
			//std::cout << "Enemy Instance Health: " << enemyInst->health << '\n';
			}
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

	//SPAWN BOSS
	if (minElapsed == 1 && timeElapsed >= 30 && spawnCheck == 1) {
		//1
		_Boss = gameObjInstCreate(TYPE_BOSS, BOSS_SIZE, nullptr, nullptr, 0.0f);
		_Boss->health = MaxBossHealth = 100;
		AE_ASSERT(_Boss);
		_Boss->position.x = 0;
		_Boss->position.y = 50;


		//2
		_BossBullet = gameObjInstCreate(TYPE_BOSS_BULLETHELL_BULLET_1, BULLET_SIZE, nullptr, nullptr, 0.0f);
		AE_ASSERT(_Boss);
		spawnCheck = 0;
		for (unsigned long i = 0; i < GAME_OBJ_INST_NUM_MAX; i++)
		{
			GameObjInstances* ObjInstance1 = sGameObjInstList + i;
			if ((ObjInstance1->flag & FLAG_ACTIVE) == 0)
				continue;
			if ((ObjInstance1->pObject->type == TYPE_ENEMY)) {
				gameObjInstDestroy(ObjInstance1);

			}
			else if ((ObjInstance1->pObject->type == TYPE_EXPERIENCE)) {
				gameObjInstDestroy(ObjInstance1);
			}

		}
	}

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
		for (int i = 1; i < GAME_OBJ_INST_NUM_MAX; i++)
		{

			GameObjInstances* qInst = sGameObjInstList + i;

			if ((qInst->flag & FLAG_ACTIVE) == 0)
				continue;

			// Update enemy position with player velocity
				qInst->position.x -= 5;

		}
		//Background Offset
		BG.x -= 0.5f;
	}
	
	if (AEInputCheckCurr(AEVK_LEFT) || AEInputCheckCurr(AEVK_A))
	{
		for (int i = 1; i < GAME_OBJ_INST_NUM_MAX; i++)
		{

			GameObjInstances* qInst = sGameObjInstList + i;

			if ((qInst->flag & FLAG_ACTIVE) == 0)
				continue;

			// Update enemy position with player velocity
			qInst->position.x += 5;
		}
		//Background Offset
		BG.x += 0.5f;
	}
	if (AEInputCheckCurr(AEVK_DOWN) || AEInputCheckCurr(AEVK_S))
	{
		for (int i = 1; i < GAME_OBJ_INST_NUM_MAX; i++)
		{

			GameObjInstances* qInst = sGameObjInstList + i;

			if ((qInst->flag & FLAG_ACTIVE) == 0)
				continue;

			// Update enemy position with player velocity
			qInst->position.y += 5;
		}
		//Background Offset
		BG.y += 0.5f;
	}
	if (AEInputCheckCurr(AEVK_UP) || AEInputCheckCurr(AEVK_W))
	{
		for (int i = 1; i < GAME_OBJ_INST_NUM_MAX; i++)
		{

			GameObjInstances* qInst = sGameObjInstList + i;

			if ((qInst->flag & FLAG_ACTIVE) == 0)
				continue;

			// Update enemy position with player velocity
			qInst->position.y -= 5;
		}
		//Background Offset
		BG.y -= 0.5;
	}




	if (AEInputCheckTriggered(AEVK_SPACE) || AEInputCheckTriggered(AEVK_C))
	{
		std::cout << "Once\n";
		_Augment_Three->showTexture = true;
	}
	if (AEInputCheckTriggered(AEVK_RCTRL))
	{
		_Augment_Three->showTexture = false;
	}

	//if (AEInputCheckTriggered(AEVK_1))
	//{
	//	bossPhase = TYPE_BHELL1;
	//}
	//if (AEInputCheckTriggered(AEVK_2))
	//{
	//	bossPhase = TYPE_BHELL2;
	//}
	//if (AEInputCheckTriggered(AEVK_3))
	//{
	//	bossPhase = TYPE_BHELL3;
	//}
	//if (AEInputCheckTriggered(AEVK_4))
	//{
	//	bossPhase = TYPE_BHELL4;
	//}
	//if (AEInputCheckTriggered(AEVK_5))
	//{
	//	bossPhase = TYPE_BOWAP;
	//}

	for (unsigned long i = 0; i < GAME_OBJ_INST_NUM_MAX; i++)
	{
		GameObjInstances* pInst = sGameObjInstList + i;

		if ((pInst->flag & FLAG_ACTIVE) == 0)
			continue;

		if (pInst->pObject == nullptr)
			continue;

		if (pInst->pObject->type == TYPE_PLAYER)
		{
			for (unsigned long j = 0; j < GAME_OBJ_INST_NUM_MAX; j++)
			{
				GameObjInstances* qInst = sGameObjInstList + j;

				if ((qInst->flag & FLAG_ACTIVE) == 0)
					continue;

				if (qInst->pObject->type == TYPE_AUGMENT1)
				{
					qInst->position.x = pInst->position.x;
					qInst->position.y = pInst->position.y + 75.0f;

					AUGMENT_1_FIRE_INTERVAL = Augment1CD;

					AUGMENT_1_FIRE_TIMER += g_dt;
					if (AUGMENT_1_FIRE_TIMER >= Augment1CD)
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
						if(bulletInst!=nullptr)
							AEVec2Scale(&bulletInst->velocity, &bulletInst->velocity, BULLET_SPEED);

						// Reset the fire timer
						AUGMENT_1_FIRE_TIMER = 0.0f;
					}
				}

				if (qInst->pObject->type == TYPE_AUGMENT2)
				{
					AUGMENT_2_DIRECTION = { (f32)cos(_rotation_Aug)* Augment2Range, (f32)sin(_rotation_Aug)* Augment2Range };
					AEVec2Scale(&AUGMENT_2_DIRECTION, &AUGMENT_2_DIRECTION, 100.0f );
					AEVec2Add(&qInst->position, &pInst->position , &AUGMENT_2_DIRECTION);
				}

				if (qInst->pObject->type == TYPE_AUGMENT3 )
				{
					if (_playerScale > 0)
					{
						qInst->position.x = pInst->position.x + 50.0f;
						qInst->position.y = pInst->position.y;
					}
					if (_playerScale < 0)
					{
						qInst->position.x = pInst->position.x - 50.0f;
						qInst->position.y = pInst->position.y;
					}
					//increment the timer...
					AUGMENT_3_FIRE_TIMER += g_dt;
					//Make the timer.. AUGMENT_3_FIRE_INTERVAL is at 1.0f;
					if (AUGMENT_3_FIRE_TIMER > AUGMENT_3_FIRE_INTERVAL)
					{
						std::cout << "First\n";
						qInst->showTexture = true;
						//Do damage here....
						//only do ONE INSTANCE of damage per skill.
						
						
						AUGMENT_3_FIRE_TIMER = 0;
					}
					//If the instance is active, then every 0.5s, turn off.
					if (qInst->showTexture == true)
					{
						AUGMENT_3_OFF_TIMER += g_dt;
						if (AUGMENT_3_OFF_TIMER > AUGMENT_3_OFF_INTERVAL)
						{
							//Turns off the instance. (prevents damage)
							qInst->showTexture = false;
							AUGMENT_3_OFF_TIMER = 0;

							std::cout << "Second\n";
						}

					}
					std::cout << "Once111\n";


				}
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
				if (pInst->health <= 0 || _deltaTime_Shooting > 10)
				{
					std::cout << "entry Upon this thing\n";
					double const MAX_DELAY = 4.0f;
					if (_delayTimeBullets > MAX_DELAY)
					{
						std::cout << "Entry2\n";
						bossPhase = TYPE_BHELL2;
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
				//If Boss hp not lesser than 1,
				if (pInst->health > 0)
				{
					//Give time for the previous bullet hell to be over.
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
			//Show the hitbox indicator of the player.
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
	for (unsigned long i = 0; i < GAME_OBJ_INST_NUM_MAX; i++)
	{
		GameObjInstances* ObjInstance2 = sGameObjInstList + i;
		if ((ObjInstance2->flag & FLAG_ACTIVE) == 0)
			continue;

		AEVec2 boundingRect{};
		AEVec2Set(&boundingRect, (BOUNDING_RECT_SIZE / 2.0f) * ObjInstance2->scale.x, (BOUNDING_RECT_SIZE / 2.0f) * ObjInstance2->scale.y);
		AEVec2Sub(&ObjInstance2->boundingBox.min, &ObjInstance2->position, &boundingRect);
		AEVec2Add(&ObjInstance2->boundingBox.max, &ObjInstance2->position, &boundingRect);
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

			if (ObjInstance1->pObject->type == TYPE_ENEMY || ObjInstance1->pObject->type == TYPE_BOSS)
			{
				for (unsigned long j = 0; j < GAME_OBJ_INST_NUM_MAX; j++)
				{
					GameObjInstances* ObjInstance2 = sGameObjInstList + j;

					if ((ObjInstance2->flag & FLAG_ACTIVE) == 0)
						continue;
					if (ObjInstance1->pObject->type == TYPE_BOSS) {
						if (_Boss->iFrame <= 0)
							_Boss->isInvincible = false;
						if (_Boss->iFrame > 0) {
							_Boss->isInvincible = true;
							_Boss->iFrame -= (float)AEFrameRateControllerGetFrameTime();
						}
					}
					if (ObjInstance2->pObject->type == TYPE_BULLET)
					{
						if (CollisionCircleCircle(ObjInstance1->position, ObjInstance1->scale.x, ObjInstance2->position, ObjInstance2->scale.x))
						{	
							if (spawnCheck == 0) {
								if (_Boss->isInvincible == false) {
									//Spawn Orbs of Experience at ObjInstance1 Position...
									//bulletCount--;
									std::cout << "Boss HP: " << _Boss->health << '\n';
									_Boss->iFrame = 50.f;
									ObjInstance1->health--;
									if (ObjInstance1->health <= 0)
									{
										gameObjInstDestroy(ObjInstance1);
										enemyCount--;
										if (OrbCounter < OrbCap) {
											gameObjInstCreate(TYPE_EXPERIENCE, 10, &ObjInstance1->position, 0, 0);
											OrbCounter++;
											//Here
										}
									}
								}
							}
							else if (ObjInstance1->pObject->type == TYPE_ENEMY){
								ObjInstance1->health--;
								if (ObjInstance1->health <= 0)
								{
									gameObjInstDestroy(ObjInstance1);
									enemyCount--;
									if (OrbCounter < OrbCap) {
										gameObjInstCreate(TYPE_EXPERIENCE, 10, &ObjInstance1->position, 0, 0);
										OrbCounter++;
									}
								}
							}
								gameObjInstDestroy(ObjInstance2);
						}
					}
					if (ObjInstance2->pObject->type == TYPE_AUGMENT2)
					{
						if (ObjInstance1->pObject->type == TYPE_BOSS) {
							if (_Boss->iFrame <= 0)
								_Boss->isInvincible = false;
							if (_Boss->iFrame > 0) {
								_Boss->isInvincible = true;
								_Boss->iFrame -= (float)AEFrameRateControllerGetFrameTime();
							}
						}
						if (CollisionCircleCircle(ObjInstance1->position, ObjInstance1->scale.x, ObjInstance2->position, ObjInstance2->scale.x))
						{	
							if (spawnCheck == 0) {
								if (_Boss->isInvincible == false && spawnCheck == 0) {
									//Spawn Orbs of Experience at ObjInstance1 Position...
									//bulletCount--;
									std::cout << _Boss->health << '\n';
									_Boss->iFrame = 50.f;
									ObjInstance1->health--;
									if (ObjInstance1->health <= 0)
									{
										gameObjInstDestroy(ObjInstance1);
										enemyCount--;
										if (OrbCounter < OrbCap) {
											gameObjInstCreate(TYPE_EXPERIENCE, 10, &ObjInstance1->position, 0, 0);
											OrbCounter++;											
										}
									}
								}
							}
							else {
								ObjInstance1->health--;
								if (ObjInstance1->health <= 0)
								{
									gameObjInstDestroy(ObjInstance1);
									enemyCount--;
									if (OrbCounter < OrbCap) {
										gameObjInstCreate(TYPE_EXPERIENCE, 10, &ObjInstance1->position, 0, 0);
										OrbCounter++;
									}
								}
							}
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
							Currency++;
							std::cout << "Player Experience: " << _Player_Experience << '\n';
							std::cout << "Player Level: " << _Player_Level << '\n';
							std::cout << "Currency:" << Currency << '\n';

							gameObjInstDestroy(ObjInstance1);
							OrbCounter--;
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

					if (ObjInstance2->pObject->type == TYPE_ENEMY || ObjInstance2->pObject->type == TYPE_BOSS_BULLETHELL_BULLET_1) {
						if (_Player->iFrame <= 0)
							_Player->isInvincible = false;
						if (_Player->iFrame > 0) {
							_Player->isInvincible = true;
							_Player->iFrame -= (float)AEFrameRateControllerGetFrameTime();
						}
						if (CollisionIntersection_RectRect(ObjInstance1->boundingBox,ObjInstance1->velocity,ObjInstance2->boundingBox,ObjInstance2->velocity)) {
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


	AEGfxTexture* playerTex = AEGfxTextureLoad("Assets\\Assets\\player.png");
	AEGfxTexture* bulletTex = AEGfxTextureLoad("Assets\\Assets\\YellowTexture.png");
	AEGfxTexture* augmentGunTex = AEGfxTextureLoad("Assets\\Assets\\drone.png");
	AEGfxTexture* augment2Tex = AEGfxTextureLoad("Assets\\Assets\\circle-512.png");
	AEGfxTexture* bossTex = AEGfxTextureLoad("Assets\\Assets\\Boss.png");
	AEGfxTexture* bossBullet1Tex = AEGfxTextureLoad("Assets\\Assets\\circle-512.png");
	AEGfxTexture* enemyTex = AEGfxTextureLoad("Assets\\Assets\\enemy.png");
	AEGfxTexture* pHitboxTex = AEGfxTextureLoad("Assets\\Assets\\circle-512.png");
	AEGfxTexture* InvisibleTex = AEGfxTextureLoad("Assets\\Assets\\Invisible.png");
	AEGfxTexture* ExpOrbTex = AEGfxTextureLoad("Assets\\Assets\\Orb.png");

	//Background
	AEGfxTexture* BgroundTexB = AEGfxTextureLoad("Assets\\Assets\\Background.png");
	
	//Draw Background
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetTintColor(0.8f, 0.8f, 0.8f, 0.8f);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetTransparency(1.0f);
	AEGfxTextureSet(BgroundTexB, 0, 0);
	AEMtx33 scale0 = { 0 };
	AEMtx33Scale(&scale0, 1366*1.5, 1000*1.5);
	AEMtx33 rotate0 = { 0 };
	AEMtx33Rot(&rotate0, 0.f);
	AEMtx33 translate0 = { 0 };
	AEMtx33Trans(&translate0, BG.x+1366/2, BG.y);
	AEMtx33 transform0 = { 0 };
	AEMtx33Concat(&transform0, &rotate0, &scale0);
	AEMtx33Concat(&transform0, &translate0, &transform0);
	AEGfxSetTransform(transform0.m);
	AEGfxMeshDraw(bMesh, AE_GFX_MDM_TRIANGLES);
	//Finish Background draw
	

	//Exp bar start
	AEGfxTexture* Expbar0 = AEGfxTextureLoad("Assets\\Assets\\Expbar\\xp0.png");
	AEGfxTexture* Expbar1 = AEGfxTextureLoad("Assets\\Assets\\Expbar\\xp1.png");
	AEGfxTexture* Expbar2 = AEGfxTextureLoad("Assets\\Assets\\Expbar\\xp2.png");
	AEGfxTexture* Expbar3 = AEGfxTextureLoad("Assets\\Assets\\Expbar\\xp3.png");
	AEGfxTexture* Expbar4 = AEGfxTextureLoad("Assets\\Assets\\Expbar\\xp4.png");
	AEGfxTexture* Expbar5 = AEGfxTextureLoad("Assets\\Assets\\Expbar\\xp5.png");
	AEGfxTexture* Expbar6 = AEGfxTextureLoad("Assets\\Assets\\Expbar\\xp6.png");
	AEGfxTexture* Expbar7 = AEGfxTextureLoad("Assets\\Assets\\Expbar\\xp7.png");
	AEGfxTexture* Expbar8 = AEGfxTextureLoad("Assets\\Assets\\Expbar\\xp8.png");
	AEGfxTexture* Expbar9 = AEGfxTextureLoad("Assets\\Assets\\Expbar\\xp9.png");

	
	

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

	//Level print
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxTextureSet(NULL, 0, 0);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	std::string level = "Lv " + std::to_string(_Player_Level);
	sprintf_s(level_buffer, sizeof(level_buffer), "%s", level.c_str());
	AEGfxGetPrintSize(fontID, level_buffer, 1.0f, textWidth, textHeight);
	AEGfxPrint(fontID, level_buffer, -0.985, 0.935, 0.5f, 1, 1, 1);
	
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
		else if (pInst->pObject->type == TYPE_AUGMENT1)
		{
			texture = augmentGunTex;
		}
		else if (pInst->pObject->type == TYPE_AUGMENT2)
		{
			texture = augment2Tex;
		}
		else if (pInst->pObject->type == TYPE_AUGMENT3)
		{
			if(pInst->showTexture == true)
				texture = bulletTex;
			else
			{
				texture = InvisibleTex;
			}
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
			gGameStateNext = GAMEOVER;
		}
		onValueChange = false;
	}

	//Unload
	AEGfxTextureUnload(playerTex);
	AEGfxTextureUnload(bulletTex);
	AEGfxTextureUnload(augmentGunTex);
	AEGfxTextureUnload(augment2Tex);
	AEGfxTextureUnload(bossTex);
	AEGfxTextureUnload(bossBullet1Tex);
	AEGfxTextureUnload(enemyTex);
	AEGfxTextureUnload(pHitboxTex);
	AEGfxTextureUnload(InvisibleTex);
	AEGfxTextureUnload(ExpOrbTex);
	AEGfxTextureUnload(BgroundTexB);

	AEGfxTextureUnload(Expbar0);
	AEGfxTextureUnload(Expbar1);
	AEGfxTextureUnload(Expbar2);
	AEGfxTextureUnload(Expbar3);
	AEGfxTextureUnload(Expbar4);
	AEGfxTextureUnload(Expbar5);
	AEGfxTextureUnload(Expbar6);
	AEGfxTextureUnload(Expbar7);
	AEGfxTextureUnload(Expbar8);
	AEGfxTextureUnload(Expbar9);

	// Rendering texts for the screen	

	if (overlayTransparency != 0)
	{
		// Drawing the augment overlay on the screen
		AEGfxTextureSet(NULL, 0, 0);
		AEGfxSetRenderMode(AE_GFX_RM_COLOR);
		AEGfxSetTransparency(overlayTransparency);
		AEMtx33 scale3 = { 0 };
		AEMtx33Scale(&scale3, 500.f, 650.f);
		AEMtx33 rotate3 = { 0 };
		AEMtx33Rot(&rotate3, 0.f);
		AEMtx33 translate3 = { 0 };
		AEMtx33Trans(&translate3, 125.f, -10.f);
		AEMtx33 transform3 = { 0 };
		AEMtx33Concat(&transform3, &rotate3, &scale3);
		AEMtx33Concat(&transform3, &translate3, &transform3);
		AEGfxSetTransform(transform3.m);
		AEGfxMeshDraw(augmentMesh, AE_GFX_MDM_TRIANGLES);

		AEGfxTextureSet(NULL, 0, 0);
		AEGfxSetRenderMode(AE_GFX_RM_COLOR);
		AEGfxSetTransparency(overlayTransparency);
		AEMtx33 scale4 = { 0 };
		AEMtx33Scale(&scale4, 34.f, 50.f);
		AEMtx33 rotate4 = { 0 };
		AEMtx33Rot(&rotate4, 0.f);
		AEMtx33 translate4 = { 0 };
		AEMtx33Trans(&translate4, augment1Button_transX, augment1Button_transY);
		AEMtx33 transform4 = { 0 };
		AEMtx33Concat(&transform4, &rotate4, &scale4);
		AEMtx33Concat(&transform4, &translate4, &transform4);
		AEGfxSetTransform(transform4.m);
		AEGfxMeshDraw(augmentButtonMesh, AE_GFX_MDM_TRIANGLES);

		AEGfxTextureSet(NULL, 0, 0);
		AEGfxSetRenderMode(AE_GFX_RM_COLOR);
		AEGfxSetTransparency(overlayTransparency);
		AEMtx33 scale5 = { 0 };
		AEMtx33Scale(&scale5, 34.f, 50.f);
		AEMtx33 rotate5 = { 0 };
		AEMtx33Rot(&rotate5, 0.f);
		AEMtx33 translate5 = { 0 };
		AEMtx33Trans(&translate5, augment2Button_transX, augment2Button_transY);
		AEMtx33 transform5 = { 0 };
		AEMtx33Concat(&transform5, &rotate5, &scale5);
		AEMtx33Concat(&transform5, &translate5, &transform5);
		AEGfxSetTransform(transform5.m);
		AEGfxMeshDraw(augmentButtonMesh, AE_GFX_MDM_TRIANGLES);
		// Rendering texts for overlay
		AEGfxSetRenderMode(AE_GFX_RM_COLOR);
		AEGfxTextureSet(NULL, 0, 0);
		AEGfxSetBlendMode(AE_GFX_BM_BLEND);
		sprintf_s(augment1_buffer, "Augment 1");
		// AEGfxGetPrintSize(fontID, augment1_buffer, 1.0f, pause_textWidth, pause_textHeight);
		AEGfxPrint(fontID, augment1_buffer, (getWinWidth() / (-2750.f * scaleX_level1)), (getWinHeight() / (1100.f * scaleY_level1)), 0.6f * scaleX_level1, 0.0f / 255.f, 23.0f / 255.f, 54.0f / 255.f);

		AEGfxSetRenderMode(AE_GFX_RM_COLOR);
		AEGfxTextureSet(NULL, 0, 0);
		AEGfxSetBlendMode(AE_GFX_BM_BLEND);
		sprintf_s(augment2_buffer, "Augment 2");
		AEGfxPrint(fontID, augment2_buffer, (getWinWidth() / (-2750.f * scaleX_level1)), (getWinHeight() / (1595.f * scaleY_level1)), 0.6f * scaleX_level1, 0.0f / 255.f, 23.0f / 255.f, 54.0f / 255.f);

		AEGfxSetRenderMode(AE_GFX_RM_COLOR);
		AEGfxTextureSet(NULL, 0, 0);
		AEGfxSetBlendMode(AE_GFX_BM_BLEND);
		sprintf_s(skillpoint_buffer, "Skill Points: %d", SkillPoint);
		AEGfxPrint(fontID, skillpoint_buffer, -0.5f, -0.8f, 0.8f, 0.0f / 255.f, 23.0f / 255.f, 54.0f / 255.f);

		AEGfxSetRenderMode(AE_GFX_RM_COLOR);
		AEGfxTextureSet(NULL, 0, 0);
		AEGfxSetBlendMode(AE_GFX_BM_BLEND);
		sprintf_s(augmentAdd_buffer, "+");
		AEGfxPrint(fontID, augmentAdd_buffer, (getWinWidth() / (-34000.f * scaleX_level1)), (getWinHeight() / (1130.f * scaleY_level1)), 1.f * scaleX_level1, 241.f / 255.f, 23.0f / 171.f, 185.0f / 255.f);

		AEGfxSetRenderMode(AE_GFX_RM_COLOR);
		AEGfxTextureSet(NULL, 0, 0);
		AEGfxSetBlendMode(AE_GFX_BM_BLEND);
		sprintf_s(augmentAdd_buffer, "+");
		AEGfxPrint(fontID, augmentAdd_buffer, (getWinWidth() / (-34000.f * scaleX_level1)), (getWinHeight() / (1680.f * scaleY_level1)), 1.f * scaleX_level1, 241.f / 255.f, 23.0f / 171.f, 185.0f / 255.f);
		// Overlay end


		AEGfxSetRenderMode(AE_GFX_RM_COLOR);
		AEGfxTextureSet(NULL, 0, 0);
		AEGfxSetBlendMode(AE_GFX_BM_BLEND);
		if (Augment1Level != 4)
			sprintf_s(strbuffer1, "LEVEL %d", Augment1Level);
		if (Augment1Level == 4)
			sprintf_s(strbuffer1, "MAX LEVEL");
		AEGfxPrint(fontID, strbuffer1, 0.075f, 0.725f, 0.3f, 0.0f / 255.f, 23.0f / 255.f, 54.0f / 255.f);


		AEGfxSetRenderMode(AE_GFX_RM_COLOR);
		AEGfxTextureSet(NULL, 0, 0);
		AEGfxSetBlendMode(AE_GFX_BM_BLEND);
		if (Augment2Level != 4)
			sprintf_s(strbuffer2, "LEVEL %d", Augment2Level);
		if (Augment2Level >= 4)
			sprintf_s(strbuffer2, "MAX LEVEL");
		AEGfxPrint(fontID, strbuffer2, 0.075f, 0.5f, 0.3f, 0.0f / 255.f, 23.0f / 255.f, 54.0f / 255.f);
	}

	// Rendering texts for the screen	
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxTextureSet(NULL, 0, 0);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	if (timeElapsed >= 9.5)
		sprintf_s(gdt_buffer, "%.0f:%.0f", minElapsed, timeElapsed);
	else
		sprintf_s(gdt_buffer, "%.0f:0%.0f", minElapsed, timeElapsed);
	AEGfxPrint(fontID, gdt_buffer,0.85f, 0.85f, 0.8f, 255.0f / 255.f, 255.0f / 255.f, 255.0f / 255.f);

	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxTextureSet(NULL, 0, 0);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	sprintf_s(hp_buffer, "HP: %d/%d", _Player->health, MaxHealth);
	AEGfxPrint(fontID, hp_buffer, 0.5f, 0.85f, 0.8f, 255.0f / 255.f, 255.0f / 255.f, 255.0f / 255.f);

	if (spawnCheck == 0) {
		AEGfxSetRenderMode(AE_GFX_RM_COLOR);
		AEGfxTextureSet(NULL, 0, 0);
		AEGfxSetBlendMode(AE_GFX_BM_BLEND);
		sprintf_s(boss_hp_buffer, "BOSS HP: %d/%d", _Boss->health, MaxBossHealth);
		AEGfxPrint(fontID, boss_hp_buffer, -0.8f, -0.8f, 0.8f, 255.0f / 255.f, 255.0f / 255.f, 255.0f / 255.f);
	}
}


void Level_1_Free(void)
{
	for (unsigned int i = 0; i < GAME_OBJ_INST_NUM_MAX; i++)
		gameObjInstDestroy(sGameObjInstList + i);

}

void Level_1_Unload(void)
{
	for (unsigned long i = 0; i < sGameObjNum; i++)
	{
		AEGfxMeshFree(sGameObjList[i].pMesh);
	}
	AEGfxMeshFree(ptrMesh);
	AEGfxMeshFree(augmentMesh);
	AEGfxMeshFree(augmentButtonMesh);
	AEGfxMeshFree(bMesh);

	//AEGfxMeshFree(bMesh);
	Augment1Level = 1;
	Augment2Level = 0;
	Augment1CD = 1.5f;
	Augment2Range = 1;
	Aug2CreateCheck = 0;
	timeElapsed = 0;
	minElapsed = 0;
	spawnCheck = 1;
	enemyCount = 0;
	OrbCounter = 0;
	_Player_Level = 1;
	_Player_Experience = 0;


	free(sGameObjList);
	sGameObjList = nullptr;
	free(sGameObjInstList);
	sGameObjInstList = nullptr;


}