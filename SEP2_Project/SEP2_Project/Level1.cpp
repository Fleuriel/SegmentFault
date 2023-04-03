#include "Main.h"
#include "GameObjects.h"
#include <iostream>
#include <cstdio>
#include <cmath>

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
char augment1_buffer[104]{};
char augmentAdd_buffer[1024]{};
char skillpoint_buffer[1024]{};
char strbuffer1[1024]{};
char strbuffer2[1024]{};
char strbuffer3[1024]{};
char strbuffer4[1024]{};
char goldbuffer[1024]{};
char bossCD[1024]{};
float augments_textWidth{}, augments_textHeight{};

// Pre-definition for translations of buttons
float augment1Button_transX;
float augment1Button_transY;
float augment2Button_transX;
float augment2Button_transY;
float augment3Button_transX;
float augment3Button_transY;
float augment4Button_transX;
float augment4Button_transY;
float augment5Button_transX;
float augment5Button_transY;
float augment6Button_transX;
float augment6Button_transY;
float mainMenu_Button_transX;
float mainMenu_Button_transY;
float quitButton_transX;
float quitButton_transY;
float yesButton_transX;
float yesButton_transY;
float noButton_transX;
float noButton_transY;

// Pre-definition for rotation of buttons in pause
float buttonRotate_mainMenu;
float buttonRotate_quit;
float buttonRotate_Yes;
float buttonRotate_No;

// Pre-definition of overlay transparency
float overlayTransparency = 0.0f;
float pauseTransparency = 0.0f;

//Pre-definition for buffers
char level_buffer[16]{};
float textWidth{}, textHeight{};

//// Pre-definition of time
float secElapsed = 0.f;
float secElapsedInt = 0.f;
int minElapsed = 0;
int bossCooldownMin = 4;
float bossCooldownSec = 0.f;
float bossCooldownSecInt = 0.f;
bool bossCoolDownCheck = false;

int MaxHealth; // Player max hp 
bool spawnCheck = false; // Boss Spawn 
int MaxBossHealth; // Max hp of boss
int MaxEnemyCount = 50; // Max Enemy count
int BossKills = 0;

//Outerbounds of World Screen
AEVec2 OuterEnemySpawnBounds = { 1920.f,1080.f };


// Initialised variable for augments
int Augment1Level = 1;
int Augment2Level = 0;
int Augment3Level = 0;
int Augment4Level = 0;
bool Aug2CreateCheck = false;
float Augment1CD = 1.5f;
float Augment2Range = 1.f;
float Augment2RotSpd = 0.f;
float Augment3Range = 0;
float Augment4Radius = 0;
float offset = 5.f;
bool mUp = true, mDown = true, mRight = true, mLeft = true;
float Augment4Scale = 50;
float RegenerationTimer = 15.0f;

// Condition check for game over
static bool onValueChange = true;

// Condition check for pause UI
int areyouSure = true;
bool clicked_MainMenu = true;
bool clicked_Quit = true;

//number of gold coins
int currencyCount = 0;

AEAudio BGM;
AEAudioGroup BGM_layer;
extern float volume;

void Level_1_Load(void)
{
	std::ifstream inputFileStream{ "Assets\\SaveFiles\\Currency.txt" };
	std::ifstream inputFileStream1{ "Assets\\SaveFiles\\PlayerShipModel.txt" };
	std::ifstream inputFileStream2{ "Assets\\SaveFiles\\HighScore.txt" };
	std::ifstream inputFileStream3{ "Assets\\SaveFiles\\PlayerStats.txt" };
	sGameObjList = (GameObjects*)calloc(GAME_OBJ_NUM_MAX, sizeof(GameObjects));
	sGameObjInstList = (GameObjInstances*)calloc(GAME_OBJ_INST_NUM_MAX, sizeof(GameObjInstances));

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
	if (_Objects != nullptr) {
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
			-0.5f, -0.1f, 0xFFFFFF00, 0.0f, 0.0f,
			-0.5f, 0.1f, 0xFFFFFF00, 0.0f, 0.0f,
			0.5f, -0.1f, 0xFFFFFF00, 0.0f, 0.0f);

		AEGfxTriAdd(
			0.5f, -0.1f, 0xFFFFFF00, 0.0f, 0.0f,
			-0.5f, 0.1f, 0xFFFFFF00, 0.0f, 0.0f,
			0.5f, 0.1f, 0xFFFFFF00, 0.0f, 0.0f);
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
		_Objects->type = TYPE_CURRENCY;

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

		//11 TYPE_AUGMENT4_PROJECTILE
		_Objects = sGameObjList + sGameObjNum++;
		_Objects->type = TYPE_AUGMENT4_PROJECTILE;

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

		//12 TYPE_AUGMENT4_EXPLOSION
		_Objects = sGameObjList + sGameObjNum++;
		_Objects->type = TYPE_AUGMENT4_EXPLOSION;

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

	}

	//Save file for currency
	if (inputFileStream.good())
	{
		inputFileStream >> Currency;
		inputFileStream.close();
	}

	//save file for player ship model
	if (inputFileStream1.good())
	{
		inputFileStream1 >> ShipModel;
		inputFileStream1.close();
	}
	else if (inputFileStream1.fail())
	{
		ShipModel = 0;
	}

	//Save file for highscore
	if (inputFileStream2.good())
	{
		inputFileStream2 >> currHighScoreMin >> currHighScoreSec;
		inputFileStream.close();
	}


	//Save file for player's stats
	if (inputFileStream3.good())
	{
		inputFileStream3 >> MaximumPlayerHealth >> ProjectileSpeed_upgrade >> CD_upgrade >> Regen_upgrade;
		inputFileStream3.close();
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

	//// Loads a music from given filepath and assign to ‘audio’
	BGM = AEAudioLoadMusic("Assets\\Music\\Bossmusic.wav");

	BGM_layer = AEAudioCreateGroup();


	//Upgrades
	for (int i = ProjectileSpeed_upgrade; i >= 0; i--) {
		AUGMENT_1_BULLET_SPEED += 20;
		Augment2RotSpd += 0.0075f;
	}
	for (int i = CD_upgrade; i >= 0; i--) {
		Augment1CD -= 0.025f;
		AUGMENT_4_FIRE_INTERVAL -= 0.25f;
	}
	for (int i = Regen_upgrade; i >= 0; i--) {
		RegenerationTimer--;
	}
}

void Level_1_Init(void)
{
	//0
	_Player = gameObjInstCreate(TYPE_PLAYER, PLAYER_SIZE, nullptr, nullptr, 0.0f);
	_Player->health = MaxHealth = 20 + MaximumPlayerHealth;
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
	_Augment_One = gameObjInstCreate(TYPE_AUGMENT1, AUG_GUN_SIZE, nullptr, nullptr, 0);
	AE_ASSERT(_Augment_One);

	//8
	//_Augment_Two

	//9
	_Augment_Three = gameObjInstCreate(TYPE_AUGMENT3, 0.0f, nullptr, nullptr, 0.0f);
	_Augment_Three->scale.x = AUG_GUN_SIZE * 3;
	_Augment_Three->scale.y = AUG_GUN_SIZE;

	//
	//AE_ASSERT(_Augment_Three);

	//10
	_Augment_Four = gameObjInstCreate(TYPE_AUGMENT4, AUG_GUN_SIZE, nullptr, nullptr, 0);



	// Gets the scale of Game_Dimension.xxGame_Dimension.y
	scaleX = getWinWidth() / Game_Dimension.x;
	scaleY = getWinHeight() / Game_Dimension.y;

	// Defintion of the translation for augment buttons
	augment1Button_transX = 0.0f * scaleX;
	augment1Button_transY = 280.0f * scaleY;
	augment2Button_transX = 0.0f * scaleX;
	augment2Button_transY = 195.0f * scaleY;
	augment3Button_transX = 0.0f * scaleX;
	augment3Button_transY = 110.0f * scaleY;
	augment4Button_transX = 0.0f * scaleX;
	augment4Button_transY = 25.0f * scaleY;
	augment5Button_transX = 0.0f * scaleX;
	augment5Button_transY = -60.0f * scaleY;
	augment6Button_transX = 0.0f * scaleX;
	augment6Button_transY = -145.0f * scaleY;
	mainMenu_Button_transX = -255.0f * scaleX;
	mainMenu_Button_transY = -300.0f * scaleY;
	quitButton_transX = 310.0f * scaleX;
	quitButton_transY = -300.0f * scaleY;
	yesButton_transX = -120.0f * scaleX;
	yesButton_transY = -65.0f * scaleX;
	noButton_transX = 168.0f * scaleX;
	noButton_transY = -65.0f * scaleX;

	// Initialize the button rotation
	buttonRotate_Yes = 0.f;
	buttonRotate_No = 0.f;
	buttonRotate_mainMenu = 0.f;
	buttonRotate_quit = 0.f;

	// plays an audio named ‘bgm’ in an 
	// audio group named ‘bgm_layer’ with 
	// 100% volume, 100% pitch, looped infinitely.
	AEAudioPlay(BGM, BGM_layer, volume, 1.f, -1);
}


void Level_1_Update(void)
{
	AEAudioUpdate();
	AEInputGetCursorPosition(&cursorX, &cursorY);

	if (AEInputCheckReleased(AEVK_P) || AEInputCheckReleased(AEVK_ESCAPE))
	{
		pause = !pause;
		if (pauseTransparency == 0) {
			pauseTransparency = 0.5;
		}
		else if (pauseTransparency != 0) {
			pauseTransparency = 0;
		}

	}

	if (pause == true) 
	{
		float mainMenu_Button_midX = (getWinWidth() / static_cast<float>(2.09)) + mainMenu_Button_transX;
		float mainMenu_Button_midY = (getWinHeight() / static_cast<float>(2)) - mainMenu_Button_transY;

		float quitButton_midX = (getWinWidth() / static_cast<float>(2.09)) + quitButton_transX;
		float quitButton_midY = (getWinHeight() / static_cast<float>(2)) - quitButton_transY;

		float yesButton_midX = (getWinWidth() / static_cast<float>(2.09)) + yesButton_transX;
		float yesButton_midY = (getWinHeight() / static_cast<float>(2)) - yesButton_transY;

		float noButton_midX = (getWinWidth() / static_cast<float>(2.09)) + noButton_transX;
		float noButton_midY = (getWinHeight() / static_cast<float>(2)) - noButton_transY;

		if (static_cast<double>(pauseTransparency) != static_cast<double>(0)) 
		{
			// Overlay button logic and defintions
			if (IsAreaClicked(mainMenu_Button_midX, mainMenu_Button_midY, 136.0f * scaleX, 50.0f * scaleY, cursorX, cursorY)
				&& AEInputCheckReleased(AEVK_LBUTTON)) 
			{
				printf("MainMenu\n");
				areyouSure = false;
				clicked_MainMenu = true;
				pauseTransparency = 0.0f;
			}

			if (IsAreaClicked(quitButton_midX, quitButton_midY, 136.0f * scaleX, 50.0f * scaleY, cursorX, cursorY)
				&& AEInputCheckReleased(AEVK_LBUTTON)) 
			{
				printf("Quit\n");
				areyouSure = false;
				clicked_MainMenu = false;
				pauseTransparency = 0.0f;
			}

		}

		if (areyouSure == false) 
		{
			// Overlay button logic and defintions
			if (IsAreaClicked(yesButton_midX, yesButton_midY, 136.0f * scaleX, 50.0f * scaleY, cursorX, cursorY)
				&& AEInputCheckReleased(AEVK_LBUTTON)) {
				if (clicked_MainMenu) 
				{
					printf("Goto Main Menu\n");
					gGameStateNext = MAINMENU;
				}
				else if (!clicked_MainMenu)
				{
					printf("Quit\n");
					gGameStateNext = QUIT;
				}
			}

			if (IsAreaClicked(noButton_midX, noButton_midY, 136.0f * scaleX, 50.0f * scaleY, cursorX, cursorY)
				&& AEInputCheckReleased(AEVK_LBUTTON)) {
				printf("Go Back to pause UI\n");
				pauseTransparency = 0.5f;
				areyouSure = true;
			}

		}

		/********************************** Button Animation Logic Start ********************************************/
		if (IsAreaClicked(mainMenu_Button_midX, mainMenu_Button_midY, 136.0f * scaleX, 50.0f * scaleY, cursorX, cursorY))
		{
			buttonRotate_mainMenu = -0.10f;
		}

		else if (IsAreaClicked(quitButton_midX, quitButton_midY, 136.0f * scaleX, 50.0f * scaleY, cursorX, cursorY))
		{
			buttonRotate_quit = -0.10f;
		}

		else if (IsAreaClicked(yesButton_midX, yesButton_midY, 136.0f * scaleX, 50.0f * scaleY, cursorX, cursorY))
		{
			buttonRotate_Yes = -0.10f;
		}

		else if (IsAreaClicked(noButton_midX, noButton_midY, 136.0f * scaleX, 50.0f * scaleY, cursorX, cursorY))
		{
			buttonRotate_No = -0.10f;
		}

		if (!IsAreaClicked(mainMenu_Button_midX, mainMenu_Button_midY, 136.0f * scaleX, 50.0f * scaleY, cursorX, cursorY))
		{
			buttonRotate_mainMenu = 0.0f;
		}

		if (!IsAreaClicked(quitButton_midX, quitButton_midY, 136.0f * scaleX, 50.0f * scaleY, cursorX, cursorY))
		{
			buttonRotate_quit = 0.0f;
		}

		if (!IsAreaClicked(yesButton_midX, yesButton_midY, 136.0f * scaleX, 50.0f * scaleY, cursorX, cursorY))
		{
			buttonRotate_Yes = 0.0f;
		}

		if (!IsAreaClicked(noButton_midX, noButton_midY, 136.0f * scaleX, 50.0f * scaleY, cursorX, cursorY))
		{
			buttonRotate_No = 0.0f;
		}
		/********************************** Button Animation Logic End ********************************************/

	}

	if (pause == false)
	{

		// Checking for time passed in seconds;
		secElapsed += g_dt;
		if (secElapsed >= 59.5) {
			minElapsed++;
			secElapsed = 0;
		}
		modf(secElapsed, &secElapsedInt);
		bossCooldownSec -= g_dt;
		if (bossCooldownSec <0) {
			bossCooldownMin--;
			bossCooldownSec = 60.f;
		}
		modf(bossCooldownSec, &bossCooldownSecInt);

		if (bossCooldownMin < 0 ) {
			bossCoolDownCheck = true;
		}

		if (_Player->health != MaxHealth) {
			RegenerationTimer -= g_dt;
		}
		if (RegenerationTimer <= 0 && _Player->health != MaxHealth) {
			_Player->health++;
			RegenerationTimer = 15.f - Regen_upgrade;
		}

		// Checking if overlay is pressed
		if (AEInputCheckReleased(AEVK_RBUTTON))
		{
			if (overlayTransparency == 0) {
				overlayTransparency = 0.5;
			}
			else if (overlayTransparency != 0) {
				overlayTransparency = 0;
			}
		}

		if (AEInputCheckReleased(AEVK_INSERT))
		{
			SkillPoint = 90;
		}

		// Augment buttons mid points
		float augment1Button_midX = (getWinWidth() / static_cast<float>(2.04)) + augment1Button_transX;
		float augment1Button_midY = (getWinHeight() / static_cast<float>(2)) - augment1Button_transY;

		float augment2Button_midX = (getWinWidth() / static_cast<float>(2.04)) + augment2Button_transX;
		float augment2Button_midY = (getWinHeight() / static_cast<float>(2)) - augment2Button_transY;

		float augment3Button_midX = (getWinWidth() / static_cast<float>(2.04)) + augment3Button_transX;
		float augment3Button_midY = (getWinHeight() / static_cast<float>(2)) - augment3Button_transY;

		float augment4Button_midX = (getWinWidth() / static_cast<float>(2.04)) + augment4Button_transX;
		float augment4Button_midY = (getWinHeight() / static_cast<float>(2)) - augment4Button_transY;

		float augment5Button_midX = (getWinWidth() / static_cast<float>(2.04)) + augment5Button_transX;
		float augment5Button_midY = (getWinHeight() / static_cast<float>(2)) - augment5Button_transY;



		if (static_cast<double>(overlayTransparency) != static_cast<double>(0)) {
			// Overlay button logic and defintions
			if (IsAreaClicked(augment1Button_midX, augment1Button_midY, 57.8f * scaleX, 50.0f * scaleY, cursorX, cursorY)
				&& AEInputCheckReleased(AEVK_LBUTTON)) {
				if (SkillPoint != 0 && Augment1Level != 8) {
					SkillPoint--;
					Augment1CD -= static_cast<float>(0.15);
					Augment1Level++;
				}
			}

			if (IsAreaClicked(augment2Button_midX, augment2Button_midY, 57.8f * scaleX, 50.0f * scaleY, cursorX, cursorY)
				&& AEInputCheckReleased(AEVK_LBUTTON)) {
				if (SkillPoint != 0 && Augment2Level != 8) {
					SkillPoint--;
					Augment2Range += static_cast<float>(0.2);
					Augment2RotSpd += 0.005f;
					Augment2Level++;
				}
			}

			if (IsAreaClicked(augment3Button_midX, augment3Button_midY, 57.8f * scaleX, 50.0f * scaleY, cursorX, cursorY)
				&& AEInputCheckReleased(AEVK_LBUTTON)) {
				if (SkillPoint != 0 && Augment3Level != 8) {
					SkillPoint--;
					Augment3Range += static_cast<float>(3);
					Augment3Level++;
					if (_Augment_Three->scale.x >= 0)
						_Augment_Three->scale.x += Augment3Range;
					else
						_Augment_Three->scale.x -= Augment3Range;
				}
			}

			if (IsAreaClicked(augment4Button_midX, augment4Button_midY, 57.8f * scaleX, 50.0f * scaleY, cursorX, cursorY)
				&& AEInputCheckReleased(AEVK_LBUTTON)) {
				if (SkillPoint != 0 && Augment4Level != 8) {
					SkillPoint--;
					Augment4Level++;
					Augment4Radius += 5.f;
					Augment4Scale += Augment4Radius;
				}
			}

			if (IsAreaClicked(augment5Button_midX, augment5Button_midY, 57.8f * scaleX, 50.0f * scaleY, cursorX, cursorY)
				&& AEInputCheckReleased(AEVK_LBUTTON)) {
				if (SkillPoint != 0) {
					SkillPoint--;
					MaxHealth++;
					_Player->health++;
				}
			}

		}


		if (Augment2Level == 1 && Aug2CreateCheck == false) {
			_Augment_Two = gameObjInstCreate(TYPE_AUGMENT2, AUG_GUN_SIZE, nullptr, nullptr, 0.0f);
			AE_ASSERT(_Augment_Two);
			Aug2CreateCheck = true;
		}

		_deltaTime += g_dt;
		_deltaTime_State += g_dt;
		if (_deltaTime > 60)
		{
			enemyHealth += ++minutes;
			_deltaTime = 0;
		}
		_deltaTimeEnemySpawner += g_dt;
		_delayTimeBullets += g_dt;
		_deltaTime_Shooting += g_dt;


		_Player_Level = experienceCurve(_Player_Level, _Player_Experience, reqExp);
		expPercent = _Player_Experience * 10 / reqExp;

		//Spawn Enemy
		if (_deltaTimeEnemySpawner > static_cast<float>(1) && enemyCount < MaxEnemyCount)
		{
			for (int i = 0; i < 2 * enemyHealth + 1; i++)
			{
				// Generate a random number to determine which X range to use
				// Outer Box, 1600x900 , Inner Box Game_Dimension.xxGame_Dimension.y;
				//A
				if (AERandFloat() >= 0 && AERandFloat() < 0.25)
				{
					enemySpawnX = -(OuterEnemySpawnBounds.x / 2.f) + AERandFloat() * (Game_Dimension.x + (OuterEnemySpawnBounds.x - Game_Dimension.x));
					enemySpawnY = (Game_Dimension.y / 2.f) + AERandFloat() * ((OuterEnemySpawnBounds.y - Game_Dimension.y) / 2.f);
				}
				//B
				else if (AERandFloat() >= 0.25 && AERandFloat() < 0.5)
				{
					enemySpawnX = Game_Dimension.x / 2.f + AERandFloat() * (OuterEnemySpawnBounds.x - Game_Dimension.x) / 2.f;
					enemySpawnY = -(Game_Dimension.y / 2.f) + AERandFloat() * (Game_Dimension.y + (OuterEnemySpawnBounds.y - Game_Dimension.y) / 2.f);
				}
				//C
				else if (AERandFloat() >= 0.5 && AERandFloat() < 0.75)
				{
					enemySpawnX = -(Game_Dimension.x / 2.f) + AERandFloat() * (Game_Dimension.x + (OuterEnemySpawnBounds.x - Game_Dimension.x) / 2.f);
					enemySpawnY = -(OuterEnemySpawnBounds.y / 2.f) + AERandFloat() * ((OuterEnemySpawnBounds.y - Game_Dimension.y) / 2.f);
				}
				//D
				else if (AERandFloat() >= 0.75)
				{
					enemySpawnX = -(Game_Dimension.x / 2.f) - ((OuterEnemySpawnBounds.x - Game_Dimension.x) / 2 * AERandFloat());
					enemySpawnY = -(OuterEnemySpawnBounds.y / 2.f) + AERandFloat() * (Game_Dimension.y + (OuterEnemySpawnBounds.y - Game_Dimension.y) / 2.f);
				}
				AEVec2 enemySpawn = { enemySpawnX, enemySpawnY };
				AEVec2 velocityEnemy = { 20.0f, 20.0f };
				enemyCount++;
				//spawn enemy :)
				GameObjInstances* enemyInst = gameObjInstCreate(TYPE_ENEMY, ENEMY_SIZE, &enemySpawn, &velocityEnemy, 0.0f);
				if (enemyInst != nullptr) {
					enemyInst->health = static_cast<s32>(enemyHealth);
				}
			}
			_deltaTimeEnemySpawner = 0;
		}
		//Rotation for Augment...
		//Rotation Increase.
		_rotation_Aug += (0.04f+ Augment2RotSpd);

		if (AEInputCheckTriggered(AEVK_0))
		{
			bossCooldownMin = 0;
			bossCooldownSec = 5;
			enemyCount = 100;
			spawnCheck = 0;
		}

		if (spawnCheck == false && bossCoolDownCheck == true) {
			spawnCheck = 1;
			_Boss = gameObjInstCreate(TYPE_BOSS, BOSS_SIZE, nullptr, nullptr, 0.0f);
			_Boss->health = MaxBossHealth = 50 * (1 + BossKills);
			AE_ASSERT(_Boss);
			_Boss->position.x = 0;
			_Boss->position.y = 220;
			bossPhase = 0;

			for (unsigned long i = 0; i < GAME_OBJ_INST_NUM_MAX; i++)
			{
				GameObjInstances* ObjInstance1 = sGameObjInstList + i;
				if ((ObjInstance1->flag & FLAG_ACTIVE) == 0)
					continue;
				if ((ObjInstance1->pObject->type == TYPE_ENEMY)) {
					gameObjInstDestroy(ObjInstance1);

				}
				else if ((ObjInstance1->pObject->type == TYPE_CURRENCY)) {
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

		//spawncheck to lock or unlock camera for boss fight
		if (spawnCheck == 1) { offset = 0; }
		else if (spawnCheck == 0) {
			offset = 5;
			_Player->position.x -= (_Player->position.x - 0) / 10;
			_Player->position.y -= (_Player->position.y - 0) / 10;
		}

		//Movement flag check
		if (_Player->position.x > getWinWidth() / 2 - PLAYER_SIZE / 2) {
			mRight = false;
		}
		else {
			mRight = true;
		}
		if (_Player->position.x < -getWinWidth() / 2 + PLAYER_SIZE / 2) {
			mLeft = false;
		}
		else {
			mLeft = true;
		}
		if (_Player->position.y > getWinHeight() / 2 - PLAYER_SIZE / 2) {
			mUp = false;
		}
		else {
			mUp = true;
		}
		if (_Player->position.y < -getWinHeight() / 2 + PLAYER_SIZE / 2) {
			mDown = false;
		}
		else {
			mDown = true;
		}

		//Offset ALL objects instances + adding player velo
		//KeyDown
		if ((AEInputCheckCurr(AEVK_RIGHT) || AEInputCheckCurr(AEVK_D)) && mRight == true)
		{
			for (int i = 1; i < GAME_OBJ_INST_NUM_MAX; i++)
			{

				GameObjInstances* qInst = sGameObjInstList + i;

				if ((qInst->flag & FLAG_ACTIVE) == 0)
					continue;

				// Update enemy position with player velocity
				qInst->position.x -= offset;

			}
			//player movement
			_Player->position.x += (5 - offset);

			//Background Offset
			BG.x -= 0.5f;
		}

		if ((AEInputCheckCurr(AEVK_LEFT) || AEInputCheckCurr(AEVK_A)) && mLeft == true)
		{
			for (int i = 1; i < GAME_OBJ_INST_NUM_MAX; i++)
			{

				GameObjInstances* qInst = sGameObjInstList + i;

				if ((qInst->flag & FLAG_ACTIVE) == 0)
					continue;

				// Update enemy position with player velocity
				qInst->position.x += offset;
			}
			//player movement
			_Player->position.x += (-5 + offset);

			//Background Offset
			BG.x += 0.5f;
		}
		if ((AEInputCheckCurr(AEVK_DOWN) || AEInputCheckCurr(AEVK_S)) && mDown == true)
		{
			for (int i = 1; i < GAME_OBJ_INST_NUM_MAX; i++)
			{

				GameObjInstances* qInst = sGameObjInstList + i;

				if ((qInst->flag & FLAG_ACTIVE) == 0)
					continue;

				// Update enemy position with player velocity
				qInst->position.y += offset;
			}
			//player movement
			_Player->position.y += (-5 + offset);

			//Background Offset
			BG.y += 0.5f;
		}
		if ((AEInputCheckCurr(AEVK_UP) || AEInputCheckCurr(AEVK_W)) && mUp == true)
		{
			for (int i = 1; i < GAME_OBJ_INST_NUM_MAX; i++)
			{

				GameObjInstances* qInst = sGameObjInstList + i;

				if ((qInst->flag & FLAG_ACTIVE) == 0)
					continue;

				// Update enemy position with player velocity
				qInst->position.y -= offset;
			}
			//player movement
			_Player->position.y += (5 - offset);

			//Background Offset
			BG.y -= 0.5;
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
			bossPhase = TYPE_BHELL5;
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
							AUGMENT_1_MOUSE_POSITION = { (f32)mouseX - (Game_Dimension.x / 2), -((f32)mouseY - (Game_Dimension.y / 2)) };

							// Compute the direction of the bullet
							AUGMENT_1_DIRECTION = { AUGMENT_1_MOUSE_POSITION.x - qInst->position.x, AUGMENT_1_MOUSE_POSITION.y - qInst->position.y };
							AEVec2Normalize(&AUGMENT_1_DIRECTION, &AUGMENT_1_DIRECTION);

							// Create a new bullet object and set its velocity to point towards the target
							GameObjInstances* bulletInst = gameObjInstCreate(TYPE_BULLET, BULLET_SIZE, &qInst->position, &AUGMENT_1_DIRECTION, getCursorRad(_Player->position));

							if (bulletInst != nullptr)
								AEVec2Scale(&bulletInst->velocity, &bulletInst->velocity, AUGMENT_1_BULLET_SPEED);

							// Reset the fire timer
							AUGMENT_1_FIRE_TIMER = 0.0f;
						}
					}

					if (qInst->pObject->type == TYPE_AUGMENT2)
					{
						AUGMENT_2_DIRECTION = { (f32)cos(_rotation_Aug) * Augment2Range, (f32)sin(_rotation_Aug) * Augment2Range };
						AEVec2Scale(&AUGMENT_2_DIRECTION, &AUGMENT_2_DIRECTION, 100.0f);
						AEVec2Add(&qInst->position, &pInst->position, &AUGMENT_2_DIRECTION);
					}

					if (qInst->pObject->type == TYPE_AUGMENT3 && Augment3Level != 0)
					{
						if (_playerScale > 0)
						{
							qInst->position.x = pInst->position.x + 85.f + Augment3Range;
							qInst->position.y = pInst->position.y;
							if (qInst->scale.x < 0)
								qInst->scale.x *= -1;
						}
						if (_playerScale < 0)
						{
							qInst->position.x = pInst->position.x - 85.f - Augment3Range;
							qInst->position.y = pInst->position.y;
							if (qInst->scale.x > 0)
								qInst->scale.x *= -1;

						}
						//increment the timer...
						AUGMENT_3_FIRE_TIMER += g_dt;
						//Make the timer.. AUGMENT_3_FIRE_INTERVAL is at 1.0f;
						if (AUGMENT_3_FIRE_TIMER > AUGMENT_3_FIRE_INTERVAL)
						{
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
							}
						}
					}


					if (qInst->pObject->type == TYPE_AUGMENT4)
					{
						qInst->position = pInst->position;
						//Get Mouse cursor Pos
						AEInputGetCursorPosition(&mouseX, &mouseY);

						//Convert Mouse pos to world space coordinates.
						AUGMENT_4_MOUSE_POSITION = { (f32)mouseX - (Game_Dimension.x / 2), -((f32)mouseY - (Game_Dimension.y / 2)) };

						//Compute the direction of bullet with 60 deg angle discrepancies.


						AUGMENT_4_DIRECTION = { AUGMENT_4_MOUSE_POSITION.x - qInst->position.x, AUGMENT_4_MOUSE_POSITION.y - qInst->position.y };

						AEVec2Normalize(&AUGMENT_4_DIRECTION, &AUGMENT_4_DIRECTION);


						f32 angleDiscrepancy = PI / 180.0f * 30.0f;
						AUGMENT_4_ANGLE = atan2f(AUGMENT_4_DIRECTION.y, AUGMENT_4_DIRECTION.x) + ((AERandFloat() * 2.0f - 1.0f) * angleDiscrepancy);


						AUGMENT_4_DIRECTION.x = cosf(AUGMENT_4_ANGLE);
						AUGMENT_4_DIRECTION.y = sinf(AUGMENT_4_ANGLE);

						AUGMENT_4_DISTANCE = AEVec2Distance(&qInst->position, &AUGMENT_4_MOUSE_POSITION);
						AUGMENT_4_DISTANCE_TOLERANCE = 0.1f * AUGMENT_4_DISTANCE;

						AUGMENT_4_TARGET_DISTANCE = AUGMENT_4_DISTANCE + (AERandFloat() * 2.0f - 1.0f) * AUGMENT_4_DISTANCE_TOLERANCE;

						AUGMENT_4_FIRE_TIMER += g_dt;

						GameObjInstances* AUG4_BULLET = nullptr;

						if (AUGMENT_4_FIRE_TIMER > AUGMENT_4_FIRE_INTERVAL && Augment4Level != 0)
						{
							//Shoot the bullet to the direction.
							AUG4_BULLET = gameObjInstCreate(TYPE_AUGMENT4_PROJECTILE, BULLET_SIZE, &qInst->position, &AUGMENT_4_DIRECTION, getCursorRad(_Player->position));

							AUGMENT_4_PROJECTILE_ACTIVE = true;

							AUGMENT_4_FIRE_TIMER = 0;
						}
						if (AUG4_BULLET != nullptr)
						{
							AEVec2Scale(&AUG4_BULLET->velocity, &AUG4_BULLET->velocity, AUGMENT_4_BULLET_SPEED);
						}
					}

					if (qInst->pObject->type == TYPE_AUGMENT4_PROJECTILE)
					{
						if (AUGMENT_4_PROJECTILE_ACTIVE == true)
						{
							AUGMENT_4_PROJECTILE_TIMER += g_dt;
						}

						if (AUGMENT_4_PROJECTILE_TIMER > AUGMENT_4_PROJECTILE_INTERVAL && Augment4Level != 0)
						{
							if (qInst != nullptr)
							{
								gameObjInstDestroy(qInst);
								AUGMENT_4_PROJECTILE_ACTIVE = false;
								gameObjInstCreate(TYPE_AUGMENT4_EXPLOSION, Augment4Scale, &qInst->position, 0, 0);
								AUGMENT_4_EXPLOSION_ACTIVE = true;
							}
							AUGMENT_4_PROJECTILE_TIMER = 0;
						}
					}

					if (qInst->pObject->type == TYPE_AUGMENT4_EXPLOSION)
					{
						if (AUGMENT_4_EXPLOSION_ACTIVE == true)
						{
							AUGMENT_4_EXPLOSION_TIMER += g_dt;
						}

						if (AUGMENT_4_EXPLOSION_TIMER > AUGMENT_4_EXPLOSION_INTERVAL)
						{
							gameObjInstDestroy(qInst);
							AUGMENT_4_EXPLOSION_ACTIVE = false;
							AUGMENT_4_EXPLOSION_TIMER = 0;
						}

					}


				}
			}



			if (pInst->pObject->type == TYPE_BOSS)
			{
				switch (bossPhase)
				{
				case TYPE_BHELL1:
					boss::DelayShoot = 0.25f;
					boss::numBulletsBHell = 13;
					angle = 225;
					if (pInst->health <= (float)MaxBossHealth * (0.8f))
					{
						double const MAX_DELAY = 4.0f;
						_Boss->iFrame = MAX_DELAY;
						if (_delayTimeBullets > MAX_DELAY)
						{
							bossPhase = TYPE_BHELL2;
							_deltaTime_Shooting = 0;
							_delayTimeBullets = 0;
						}
					}
					else
					{
						if (_delayTimeBullets >= boss::DelayShoot)
						{
							angle2 = 84;
							for (int q = 0; q < boss::numBulletsBHell; q++)
							{
								
								angle -= 10;
								if (angle < 134)
								{
									angle = 225;
								}

								angle2 -= 12;
								if (angle2 < -84)
								{
									angle2 = 84;
								}

								std::cout << angle2 << '\n';


								boss::velocity = { projectileSpeed * sin(AEDegToRad(angle)) , projectileSpeed * cos(AEDegToRad(angle)) };
								gameObjInstCreate(TYPE_BOSS_BULLETHELL_BULLET_1, 5, &pInst->position, &boss::velocity, angle);


								boss::velocity2 = { projectileSpeed * sin(AEDegToRad(angle2)) , projectileSpeed * cos(AEDegToRad(angle2)) };
								gameObjInstCreate(TYPE_BOSS_BULLETHELL_BULLET_1, 5, &pInst->position, &boss::velocity2, angle2);


							}
							angle = 0;

							boss::numBulletsBHell = 12;

							_delayTimeBullets = 0;

						}
					}

					break;
				case TYPE_BHELL2:
					DelayShoot = 0.05f;
					numBulletsBHell = 2;
					angle = 390;

					if (pInst->health <= (float)MaxBossHealth * (0.6f))
					{
						double const MAX_DELAY = 4.0f;
						_Boss->iFrame = MAX_DELAY;
						if (_delayTimeBullets > MAX_DELAY)
						{
							bossPhase = TYPE_BHELL3;
							_deltaTime_Shooting = 0;
							_delayTimeBullets = 0;
						}
					}
					else
					{
						if (_delayTimeBullets >= DelayShoot)
						{
							for (int q = 0; q < numBulletsBHell; q++)
							{
								angle = static_cast<float>(360) + static_cast<float>((static_cast<float>(40) * sin(g_appTime * 2.0 * PI / 5.0)));
								for (int w = 0; w < 1; w++)
								{
									if (angle < 320)
									{
										angle = 400;
									}
									velocity = { projectileSpeed * sin(AEDegToRad(angle)) , projectileSpeed * cos(AEDegToRad(angle)) };
									gameObjInstCreate(TYPE_BOSS_BULLETHELL_BULLET_1, static_cast<float>(5), &pInst->position, &velocity, angle);
								}
							}
							_delayTimeBullets = 0;
						}
					}

					break;
				case TYPE_BHELL3:
					DelayShoot = 0.15f;
					if (pInst->health <= (float)MaxBossHealth * (0.4f))
					{
						double const MAX_DELAY = 4.0f;
						if (_delayTimeBullets > MAX_DELAY)
						{
							bossPhase = TYPE_BHELL4;
							_deltaTime_Shooting = 0;
							_delayTimeBullets = 0;
						}
					}
					else {
						if (_delayTimeBullets >= DelayShoot)
						{
							angle = 360;
							static f32 angleOffset = 0;
							DelayShoot = 0.25f;
							numBulletsBHell = 4;

							for (int q = 0; q < numBulletsBHell; q++)
							{
								f32 angleRadians = AEDegToRad(angle + angleOffset);
								velocity = { projectileSpeed * sin(angleRadians), projectileSpeed * cos(angleRadians) };
								gameObjInstCreate(TYPE_BOSS_BULLETHELL_BULLET_1, 5, &pInst->position, &velocity, angle + angleOffset);
								angle -= 120;
							}
							for (int q = 0; q < numBulletsBHell; q++)
							{
								f32 angleRadians = AEDegToRad(angle - angleOffset);
								velocity = { projectileSpeed * sin(angleRadians), projectileSpeed * cos(angleRadians) };
								gameObjInstCreate(TYPE_BOSS_BULLETHELL_BULLET_1, 5, &pInst->position, &velocity, -angle - angleOffset);
								angle -= 120;
							}
							angle = 90;
							for (int q = 0; q < numBulletsBHell; q++)
							{
								f32 angleRadians = AEDegToRad(angle + angleOffset);
								velocity = { projectileSpeed * sin(angleRadians), projectileSpeed * cos(angleRadians) };
								gameObjInstCreate(TYPE_BOSS_BULLETHELL_BULLET_1, 5, &pInst->position, &velocity, angle + angleOffset);
								angle -= 120;
							}
							for (int q = 0; q < numBulletsBHell; q++)
							{
								f32 angleRadians = AEDegToRad(angle - angleOffset);
								velocity = { projectileSpeed * sin(angleRadians), projectileSpeed * cos(angleRadians) };
								gameObjInstCreate(TYPE_BOSS_BULLETHELL_BULLET_1, 5, &pInst->position, &velocity, -angle - angleOffset);
								angle -= 120;
							}
							angleOffset += 10.0;
							_delayTimeBullets = 0;
						}
					}
					break;
					//Peerless Wind God
				case TYPE_BHELL4:
					_Boss->iFrame = 1.f;
					numBullets = 7;
					if (_deltaTime_Shooting > 3 && _deltaTime_Shooting < 18)
					{
						frequency = 1.0f;
						times = static_cast<float>(g_appTime);
						xSpeed += static_cast<float>(0.005);
					}

					if (_deltaTime_Shooting < 20)
					{
						angle += static_cast<float>(10);
						if (angle > 200 || angle < 160)
						{
							angle = static_cast<float>(160);
						}
						if (_deltaTime_Shooting < 10)
						{
							DelayShoot = 0.2f;
						}

						if (_deltaTime_Shooting >= static_cast<float>(10) && _deltaTime_Shooting <= static_cast<float>(14))
						{
							DelayShoot = 0.05f;
						}
						if (_deltaTime_Shooting > static_cast<float>(14) && _deltaTime_Shooting <= static_cast<float>(20))
						{
							DelayShoot = 0.035f;
						}

						if (_delayTimeBullets > DelayShoot)
						{
							for (int q = 0; q < numBullets; q++)
							{
								// Calculate the x position for this bullet
								float xPos = pInst->position.x + (q - numBullets / 2.f) * xSpacing;

								// Calculate the y position for this bullet with a random offset
								float yPos = pInst->position.y + (rand() % (maxY - minY + 1) + minY);

								// Set the bullet's position
								AEVec2 position = { xPos, yPos };
								// Set the bullet's velocity and angle
								velocity = { projectileSpeed * sin(AEDegToRad(angle)), projectileSpeed * cos(AEDegToRad(angle)) };
								float angleOffset = ((float)rand() / RAND_MAX) * 20 - 80;
								gameObjInstCreate(TYPE_BOSS_BULLETHELL_BULLET_1, 7, &position, &velocity, angle - angleOffset);
								_delayTimeBullets = 0;
							}
						}
					}

					if (_deltaTime_Shooting > 19)
					{
						xSpeed -= static_cast<float>(0.001);
						if (xSpeed < static_cast<float>(0))
						{
							xSpeed = static_cast<float>(0);
						}
						ySpeed = static_cast<float>(0);
					}

					//16 is the point where they stop..
					if (_deltaTime_Shooting > 22)
					{
						_delayTimeBullets = 0;
						pInst->health = (s32)(MaxBossHealth * (0.2f));
						_Boss->iFrame = 5.f;
						bossPhase = TYPE_BHELL5;
					}

					displacementX = xRange * static_cast<float>(sinf(static_cast<float>(xSpeed) * static_cast<float>(g_appTime)));
					displacementY = yRange * static_cast<float>(sinf(static_cast<float>(ySpeed) * static_cast<float>(g_appTime)));
					// Set the position of the object
					pInst->position.x = displacementX;
					pInst->position.y = 200.0f + displacementY; // set the y position to a fixed value for now
					break;
					//BOWAP
				case TYPE_BHELL5:
					_Boss->position.x = 0;
					_Boss->position.y = 220;
					//If Boss hp not lesser than 1,
					if (pInst->health <= (float)MaxBossHealth * (0.2f))
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
								velocity;
								AEVec2Scale(&velocity, &direction, distance);

								// Update position of pInst
								pInst->position.x += velocity.x;
								pInst->position.y += velocity.y;
							}
						}
						if (_delayTimeBullets > DelayMovement)
						{
							numBulletsBHell = 8;
							angle = rotationAngle * static_cast<float>(sin(g_appTime / 12 * 3.142));

							//BOWAP					
							for (int j = 0; j < numBulletsBHell; j++)
							{
								float angleT = angle + (30.f * j * 360.f / 14.f);
								velocity = { projectileSpeed * static_cast<float>(cos(AEDegToRad(angleT))) ,projectileSpeed * static_cast<float>(sin(AEDegToRad(angleT))) };
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
					angle = static_cast<float>(180) + static_cast<float>(45) * static_cast<float>(sin(g_appTime * 2.0 * PI / 5.0));
					for (int q = 0; q < 1; q++)
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

			if (pInst->pObject->type == TYPE_BULLET || pInst->pObject->type == TYPE_AUGMENT4_PROJECTILE)
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
						ENEMY_DIRECTION = { qInst->position.x - pInst->position.x, qInst->position.y - pInst->position.y };

						// Normalize direction vector to get unit direction
						AEVec2Normalize(&ENEMY_DIRECTION, &ENEMY_DIRECTION);

						// Calculate velocity vector by scaling unit direction by enemy's movement speed
						ENEMY_VELOCITY = { ENEMY_DIRECTION.x * 5.0f, ENEMY_DIRECTION.y * 5.0f };

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

			//Window size is Game_Dimension.xxGame_Dimension.y

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
					pInst->pObject->type == TYPE_CURRENCY)
				{
					continue;
				}

				if (pInst->pObject->type == TYPE_BULLET)
				{
					bulletCount--;

				}
				gameObjInstDestroy(pInst);
			}
		}

		//Update bounding box
		for (unsigned long i = 0; i < GAME_OBJ_INST_NUM_MAX; i++)
		{
			GameObjInstances* ObjInstance2 = sGameObjInstList + i;
			if ((ObjInstance2->flag & FLAG_ACTIVE) == 0)
				continue;
			if (ObjInstance2->pObject->type == TYPE_AUGMENT3) {
				AEVec2 boundingRectAug3{};
				float tempScaleX;
				tempScaleX = ObjInstance2->scale.x;
				if (tempScaleX < 0)
					tempScaleX = -tempScaleX;
				AEVec2Set(&boundingRectAug3, (BOUNDING_RECT_SIZE / 2.0f) * tempScaleX, (BOUNDING_RECT_SIZE / 2.0f) * ObjInstance2->scale.y);
				AEVec2Sub(&ObjInstance2->boundingBox.min, &ObjInstance2->position, &boundingRectAug3);
				AEVec2Add(&ObjInstance2->boundingBox.max, &ObjInstance2->position, &boundingRectAug3);
			}
			if (ObjInstance2->pObject->type == TYPE_AUGMENT4_EXPLOSION) {
				AEVec2 boundingRectAug4{};
				AEVec2Set(&boundingRectAug4, (BOUNDING_RECT_SIZE / 2.0f) * ObjInstance2->scale.x, (BOUNDING_RECT_SIZE / 2.0f) * ObjInstance2->scale.y);
				AEVec2Sub(&ObjInstance2->boundingBox.min, &ObjInstance2->position, &boundingRectAug4);
				AEVec2Add(&ObjInstance2->boundingBox.max, &ObjInstance2->position, &boundingRectAug4);
			}
			if (ObjInstance2->pObject->type == TYPE_PLAYER && spawnCheck == 1) {
				AEVec2 boundingRectPlayer{};
				AEVec2Set(&boundingRectPlayer, (BOUNDING_RECT_SIZE / 2.0f) * ObjInstance2->scale.x, (BOUNDING_RECT_SIZE / 2.0f) * ObjInstance2->scale.y);
				AEVec2Sub(&ObjInstance2->boundingBox.min, &ObjInstance2->position, &boundingRectPlayer);
				AEVec2Add(&ObjInstance2->boundingBox.max, &ObjInstance2->position, &boundingRectPlayer);
			}
			if (spawnCheck != 1) {
				if (ObjInstance2->velocity.x == 0 || ObjInstance2->velocity.y == 0)
					continue;
			}
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
		if (_Player->iFrame <= 0)
			_Player->isInvincible = false;
		if (_Player->iFrame > 0) {
			_Player->isInvincible = true;
			_Player->iFrame -= g_dt;
		}
		if (spawnCheck == 1) {
			if (_Boss->iFrame <= 0)
				_Boss->isInvincible = false;
			if (_Boss->iFrame > 0) {
				_Boss->isInvincible = true;
				_Boss->iFrame -= (float)AEFrameRateControllerGetFrameTime();
			}
		}
		if (_Enemy != nullptr) {
			if (_Enemy->iFrame <= 0)
				_Enemy->isInvincible = false;
			if (_Enemy->iFrame > 0) {
				_Enemy->isInvincible = true;
				_Enemy->iFrame -= (float)AEFrameRateControllerGetFrameTime();
			}
		}

		if (_Player->health > 0) {
			for (unsigned long i = 0; i < GAME_OBJ_INST_NUM_MAX; i++)
			{
				GameObjInstances* ObjInstance1 = sGameObjInstList + i;

				if ((ObjInstance1->flag & FLAG_ACTIVE) == 0)
					continue;
				//ENEMY COLLISION
				if (ObjInstance1->pObject->type == TYPE_ENEMY || ObjInstance1->pObject->type == TYPE_BOSS)
				{
					for (unsigned long j = 0; j < GAME_OBJ_INST_NUM_MAX; j++)
					{
						GameObjInstances* ObjInstance2 = sGameObjInstList + j;

						if ((ObjInstance2->flag & FLAG_ACTIVE) == 0)
							continue;
						//AUGMENT 1 COLLISON
						if (ObjInstance2->pObject->type == TYPE_BULLET)
						{
							if (CollisionIntersection_RectRect(ObjInstance1->boundingBox, ObjInstance1->velocity, ObjInstance2->boundingBox, ObjInstance2->velocity))
							{
								if (spawnCheck == 1) {
									if (_Boss->isInvincible == false) {
										_Boss->iFrame = 0.5f;
										ObjInstance1->health--;
										break;
									}
								}
								else if (ObjInstance1->pObject->type == TYPE_ENEMY) {
									ObjInstance1->health--;
									if (ObjInstance1->health > 0) {
										if (_Enemy != nullptr) {
											_Enemy->iFrame = 0.25f;
										}
									}
									break;
								}
								gameObjInstDestroy(ObjInstance2);
							}
						}
						//AUGMENT 2 COLLISION
						if (ObjInstance2->pObject->type == TYPE_AUGMENT2)
						{
							if (CollisionCircleCircle(ObjInstance1->position, ObjInstance1->scale.x, ObjInstance2->position, ObjInstance2->scale.x))
							{
								if (spawnCheck == 1) {
									if (_Boss->isInvincible == false && spawnCheck == 1) {
										_Boss->iFrame = 1.f;
										ObjInstance1->health--;
										break;
									}
								}
								else {
									ObjInstance1->health--;
									if (ObjInstance1->health > 0) {
										if (_Enemy != nullptr) {
											_Enemy->iFrame = 0.25f;
										}
									}
									break;
								}
							}
						}
						//AUGMENT3 COLLISION
						if (ObjInstance2->pObject->type == TYPE_AUGMENT3 && ObjInstance2->showTexture == true)
						{
							if (CollisionIntersection_RectRect(ObjInstance1->boundingBox, ObjInstance1->velocity, ObjInstance2->boundingBox, ObjInstance2->velocity))
							{
								if (spawnCheck == 1) {
									if (_Boss->isInvincible == false && spawnCheck == 1) {
										_Boss->iFrame = 1.f;
										ObjInstance1->health--;
										break;
									}
								}
								else {
									ObjInstance1->health--;
									if (ObjInstance1->health > 0) {
										if (_Enemy != nullptr) {
											_Enemy->iFrame = 0.25f;
										}
									}
									break;
								}
							}
						}
						//AUGMENT4 COLLISION
						if (ObjInstance2->pObject->type == TYPE_AUGMENT4_EXPLOSION)
						{
							if (CollisionIntersection_RectRect(ObjInstance1->boundingBox, ObjInstance1->velocity, ObjInstance2->boundingBox, ObjInstance2->velocity))
							{
								if (spawnCheck == 1) {
									if (_Boss->isInvincible == false && spawnCheck == 1) {
										_Boss->iFrame = 1.f;
										ObjInstance1->health -= 3;
										break;
									}
								}
								else {
									ObjInstance1->health -= 3;
									if (ObjInstance1->health > 0) {
										if (_Enemy != nullptr) {
											_Enemy->iFrame = 0.25f;
										}
									}
									break;
								}
							}
						}
					}
					if ((ObjInstance1->health <= 0) && ObjInstance1->pObject->type != TYPE_BOSS) {
						gameObjInstDestroy(ObjInstance1);
						enemyCount--;
						_Player_Experience++;
						if (currencyCount <= 100) {
							gameObjInstCreate(TYPE_CURRENCY, 10, &ObjInstance1->position, 0, 0);
							currencyCount++;
							break;
						}
					}
					if (ObjInstance1->health <= 0 && ObjInstance1->pObject->type == TYPE_BOSS) {
						gameObjInstDestroy(ObjInstance1);
						spawnCheck = 0;
						++BossKills;
						Currency += (1000 * BossKills);
						enemyCount = 0;
						bossCoolDownCheck = false;
						bossCooldownMin = 4;
						bossCooldownSec = 0.f;
					}
				}

				// PLAYER COIN COLLISION
				if (ObjInstance1->pObject->type == TYPE_CURRENCY)
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
								Currency++;
								gameObjInstDestroy(ObjInstance1);
								currencyCount--;
								break;
							}
						}
					}
				}
				//PLAYER ENEMY COLLISION
				if (ObjInstance1->pObject->type == TYPE_PLAYER)
				{
					for (unsigned long j = 0; j < GAME_OBJ_INST_NUM_MAX; j++)
					{
						GameObjInstances* ObjInstance2 = sGameObjInstList + j;
						if ((ObjInstance2->flag & FLAG_ACTIVE) == 0)
							continue;
						if (ObjInstance2->pObject->type == TYPE_ENEMY || ObjInstance2->pObject->type == TYPE_BOSS_BULLETHELL_BULLET_1) {
							if (CollisionIntersection_RectRect(ObjInstance1->boundingBox, ObjInstance1->velocity, ObjInstance2->boundingBox, ObjInstance2->velocity)) {
								if (_Player->isInvincible == false) {
									_Player->iFrame = 2.f;
									_Player->health--;
									onValueChange = true;
									break;
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
}

void Level_1_Draw(void)
{
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
	AEGfxTexture* playerTex = nullptr;
	if (ShipModel == 0) {
		playerTex = AEGfxTextureLoad("Assets\\Assets\\player0.png");
	}
	if (ShipModel == 1) {
		playerTex = AEGfxTextureLoad("Assets\\Assets\\player1.png");
	}
	if (ShipModel == 2) {
		playerTex = AEGfxTextureLoad("Assets\\Assets\\player2.png");
	}
	if (ShipModel == 3) {
		playerTex = AEGfxTextureLoad("Assets\\Assets\\player3.png");
	}
	AEGfxTexture* bulletTex = AEGfxTextureLoad("Assets\\Assets\\YellowTexture.png");
	AEGfxTexture* augmentGunTex = AEGfxTextureLoad("Assets\\Assets\\drone.png");
	AEGfxTexture* augment2Tex = AEGfxTextureLoad("Assets\\Assets\\circle-512.png");
	AEGfxTexture* bossTex = AEGfxTextureLoad("Assets\\Assets\\Boss.png");
	AEGfxTexture* bossBullet1Tex = AEGfxTextureLoad("Assets\\Assets\\circle-512.png");
	AEGfxTexture* enemyTex = AEGfxTextureLoad("Assets\\Assets\\newenemy.png");
	AEGfxTexture* pHitboxTex = AEGfxTextureLoad("Assets\\Assets\\circle-512.png");
	AEGfxTexture* InvisibleTex = AEGfxTextureLoad("Assets\\Assets\\Invisible.png");
	AEGfxTexture* coinTex = AEGfxTextureLoad("Assets\\Assets\\Coin.png");
	AEGfxTexture* augment3Tex = AEGfxTextureLoad("Assets\\Assets\\Slash.png");
	AEGfxTexture* augment4Tex = AEGfxTextureLoad("Assets\\Assets\\GrenadeBall.png");

	//Background
	AEGfxTexture* BgroundTexB = AEGfxTextureLoad("Assets\\Assets\\Background.png");

	//Draw Background
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetTintColor(0.8f, 0.8f, 0.8f, 0.8f);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetTransparency(1.0f);
	AEGfxTextureSet(BgroundTexB, 0, 0);
	AEMtx33 scale0 = { 0 };
	AEMtx33Scale(&scale0, Game_Dimension.x * static_cast<float>(1.5), 1000 * static_cast<float>(1.5));
	AEMtx33 rotate0 = { 0 };
	AEMtx33Rot(&rotate0, 0.f);
	AEMtx33 translate0 = { 0 };
	AEMtx33Trans(&translate0, BG.x + Game_Dimension.x / 2.f, BG.y);
	AEMtx33 transform0 = { 0 };
	AEMtx33Concat(&transform0, &rotate0, &scale0);
	AEMtx33Concat(&transform0, &translate0, &transform0);
	AEGfxSetTransform(transform0.m);
	AEGfxMeshDraw(bMesh, AE_GFX_MDM_TRIANGLES);
	//Finish Background draw


	//Exp bar start
	AEGfxTexture* Expbar[10] = { AEGfxTextureLoad("Assets\\Assets\\Expbar\\xp0.png"),
							 AEGfxTextureLoad("Assets\\Assets\\Expbar\\xp1.png"),
							 AEGfxTextureLoad("Assets\\Assets\\Expbar\\xp2.png"),
							 AEGfxTextureLoad("Assets\\Assets\\Expbar\\xp3.png"),
							 AEGfxTextureLoad("Assets\\Assets\\Expbar\\xp4.png"),
							 AEGfxTextureLoad("Assets\\Assets\\Expbar\\xp5.png"),
							 AEGfxTextureLoad("Assets\\Assets\\Expbar\\xp6.png"),
							 AEGfxTextureLoad("Assets\\Assets\\Expbar\\xp7.png"),
							 AEGfxTextureLoad("Assets\\Assets\\Expbar\\xp8.png"),
							 AEGfxTextureLoad("Assets\\Assets\\Expbar\\xp9.png") };




	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetTransparency(1.0f);
	AEGfxTextureSet(Expbar[expPercent], 0, 0);
	//Exp bar end


	AEMtx33 scale2 = { 0 };
	AEMtx33Scale(&scale2, 600.f, 30.f);
	AEMtx33 rotate2 = { 0 };
	AEMtx33Rot(&rotate2, 0.f);
	AEMtx33 translate2 = { 0 };
	AEMtx33Trans(&translate2, -getWinWidth() / 8, getWinHeight() / 2 - getWinHeight() / 50 + getWinHeight() / getWinHeight());
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
	AEGfxPrint(fontID, level_buffer, static_cast<float>(-0.985), static_cast<float>(0.94), 0.5f, static_cast<float>(1), static_cast<float>(1), static_cast<float>(1));

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
		else if (pInst->pObject->type == TYPE_AUGMENT2 || pInst->pObject->type == TYPE_AUGMENT4_EXPLOSION)
		{
			texture = augment2Tex;
		}
		else if (pInst->pObject->type == TYPE_AUGMENT3)
		{
			if (pInst->showTexture == true)
				texture = augment3Tex;
			else
			{
				texture = InvisibleTex;
			}
		}
		else if (pInst->pObject->type == TYPE_AUGMENT4)
		{
			texture = InvisibleTex;
		}
		else if (pInst->pObject->type == TYPE_AUGMENT4_PROJECTILE)
		{
			texture = augment4Tex;
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
		else if (pInst->pObject->type == TYPE_CURRENCY)
		{
			texture = coinTex;
		}

		AEGfxTextureSet(texture, 0, 0);
		AEGfxSetTransform(pInst->transform.m);
		AEGfxMeshDraw(pInst->pObject->pMesh, AE_GFX_MDM_TRIANGLES);
	}
	if (onValueChange) {
		if (_Player->health == 0) {
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
	AEGfxTextureUnload(coinTex);
	AEGfxTextureUnload(BgroundTexB);
	AEGfxTextureUnload(augment3Tex);
	AEGfxTextureUnload(augment4Tex);

	for (int i = 0; i < 10; i++) {
		AEGfxTextureUnload(Expbar[i]);
	}

	/********************************** Augment UI Start ********************************************/
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

		AEGfxTextureSet(NULL, 0, 0);
		AEGfxSetRenderMode(AE_GFX_RM_COLOR);
		AEGfxSetTransparency(overlayTransparency);
		AEMtx33 scale6 = { 0 };
		AEMtx33Scale(&scale6, 34.f, 50.f);
		AEMtx33 rotate6 = { 0 };
		AEMtx33Rot(&rotate6, 0.f);
		AEMtx33 translate6 = { 0 };
		AEMtx33Trans(&translate6, augment3Button_transX, augment3Button_transY);
		AEMtx33 transform6 = { 0 };
		AEMtx33Concat(&transform6, &rotate6, &scale6);
		AEMtx33Concat(&transform6, &translate6, &transform6);
		AEGfxSetTransform(transform6.m);
		AEGfxMeshDraw(augmentButtonMesh, AE_GFX_MDM_TRIANGLES);

		AEGfxTextureSet(NULL, 0, 0);
		AEGfxSetRenderMode(AE_GFX_RM_COLOR);
		AEGfxSetTransparency(overlayTransparency);
		AEMtx33 scale7 = { 0 };
		AEMtx33Scale(&scale7, 34.f, 50.f);
		AEMtx33 rotate7 = { 0 };
		AEMtx33Rot(&rotate7, 0.f);
		AEMtx33 translate7 = { 0 };
		AEMtx33Trans(&translate7, augment4Button_transX, augment4Button_transY);
		AEMtx33 transform7 = { 0 };
		AEMtx33Concat(&transform7, &rotate7, &scale7);
		AEMtx33Concat(&transform7, &translate7, &transform7);
		AEGfxSetTransform(transform7.m);
		AEGfxMeshDraw(augmentButtonMesh, AE_GFX_MDM_TRIANGLES);

		AEGfxTextureSet(NULL, 0, 0);
		AEGfxSetRenderMode(AE_GFX_RM_COLOR);
		AEGfxSetTransparency(overlayTransparency);
		AEMtx33 scale8 = { 0 };
		AEMtx33Scale(&scale8, 34.f, 50.f);
		AEMtx33 rotate8 = { 0 };
		AEMtx33Rot(&rotate8, 0.f);
		AEMtx33 translate8 = { 0 };
		AEMtx33Trans(&translate8, augment5Button_transX, augment5Button_transY);
		AEMtx33 transform8 = { 0 };
		AEMtx33Concat(&transform8, &rotate8, &scale8);
		AEMtx33Concat(&transform8, &translate8, &transform8);
		AEGfxSetTransform(transform8.m);
		AEGfxMeshDraw(augmentButtonMesh, AE_GFX_MDM_TRIANGLES);

		AEGfxTextureSet(NULL, 0, 0);
		AEGfxSetRenderMode(AE_GFX_RM_COLOR);
		AEGfxSetTransparency(overlayTransparency);
		AEMtx33 scale9 = { 0 };
		AEMtx33Scale(&scale9, 34.f, 50.f);
		AEMtx33 rotate9 = { 0 };
		AEMtx33Rot(&rotate9, 0.f);
		AEMtx33 translate9 = { 0 };
		AEMtx33 transform9 = { 0 };
		AEMtx33Concat(&transform9, &rotate9, &scale9);
		AEMtx33Concat(&transform9, &translate9, &transform9);
		AEGfxSetTransform(transform9.m);
		AEGfxMeshDraw(augmentButtonMesh, AE_GFX_MDM_TRIANGLES);

		// Rendering texts for overlay
		AEGfxSetRenderMode(AE_GFX_RM_COLOR);
		AEGfxTextureSet(NULL, 0, 0);
		AEGfxSetBlendMode(AE_GFX_BM_BLEND);
		sprintf_s(augment1_buffer, "Guns");
		AEGfxPrint(fontID, augment1_buffer, (getWinWidth() / (-4000.f * scaleX)), (getWinHeight() / (1550.f * scaleY)), 0.7f * scaleX, 0.0f / 255.f, 23.0f / 255.f, 54.0f / 255.f);

		AEGfxSetRenderMode(AE_GFX_RM_COLOR);
		AEGfxTextureSet(NULL, 0, 0);
		AEGfxSetBlendMode(AE_GFX_BM_BLEND);
		sprintf_s(augment1_buffer, "Orbiter");
		AEGfxPrint(fontID, augment1_buffer, (getWinWidth() / (-4000.f * scaleX)), (getWinHeight() / (2200.f * scaleY)), 0.7f * scaleX, 0.0f / 255.f, 23.0f / 255.f, 54.0f / 255.f);

		AEGfxSetRenderMode(AE_GFX_RM_COLOR);
		AEGfxTextureSet(NULL, 0, 0);
		AEGfxSetBlendMode(AE_GFX_BM_BLEND);
		sprintf_s(augment1_buffer, "Sonic Slash");
		AEGfxPrint(fontID, augment1_buffer, (getWinWidth() / (-4000.f * scaleX)), (getWinHeight() / (4200.f * scaleY)), 0.7f * scaleX, 0.0f / 255.f, 23.0f / 255.f, 54.0f / 255.f);

		AEGfxSetRenderMode(AE_GFX_RM_COLOR);
		AEGfxTextureSet(NULL, 0, 0);
		AEGfxSetBlendMode(AE_GFX_BM_BLEND);
		sprintf_s(augment1_buffer, "Bomb Launcher");
		AEGfxPrint(fontID, augment1_buffer, (getWinWidth() / (-4000.f * scaleX)), (getWinHeight() / (26500.f * scaleY)), 0.7f * scaleX, 0.0f / 255.f, 23.0f / 255.f, 54.0f / 255.f);

		AEGfxSetRenderMode(AE_GFX_RM_COLOR);
		AEGfxTextureSet(NULL, 0, 0);
		AEGfxSetBlendMode(AE_GFX_BM_BLEND);
		sprintf_s(augment1_buffer, "HP");
		AEGfxPrint(fontID, augment1_buffer, (getWinWidth() / (-4000.f * scaleX)), (getWinHeight() / (-5500.f * scaleY)), 0.7f * scaleX, 0.0f / 255.f, 23.0f / 255.f, 54.0f / 255.f);


		AEGfxSetRenderMode(AE_GFX_RM_COLOR);
		AEGfxTextureSet(NULL, 0, 0);
		AEGfxSetBlendMode(AE_GFX_BM_BLEND);
		sprintf_s(skillpoint_buffer, "Skill Points: %d", SkillPoint);
		AEGfxPrint(fontID, skillpoint_buffer, -0.45f, -0.7f, 0.8f, 0.0f / 255.f, 23.0f / 255.f, 54.0f / 255.f);

		AEGfxSetRenderMode(AE_GFX_RM_COLOR);
		AEGfxTextureSet(NULL, 0, 0);
		AEGfxSetBlendMode(AE_GFX_BM_BLEND);
		sprintf_s(augmentAdd_buffer, "+");
		AEGfxPrint(fontID, augmentAdd_buffer, (getWinWidth() / (-47000.f * scaleX)), (getWinHeight() / (1550.f * scaleY)), 1.f * scaleX, 241.f / 255.f, 23.0f / 171.f, 185.0f / 255.f);

		AEGfxSetRenderMode(AE_GFX_RM_COLOR);
		AEGfxTextureSet(NULL, 0, 0);
		AEGfxSetBlendMode(AE_GFX_BM_BLEND);
		sprintf_s(augmentAdd_buffer, "+");
		AEGfxPrint(fontID, augmentAdd_buffer, (getWinWidth() / (-47000.f * scaleX)), (getWinHeight() / (2300.f * scaleY)), 1.f * scaleX, 241.f / 255.f, 23.0f / 171.f, 185.0f / 255.f);

		AEGfxSetRenderMode(AE_GFX_RM_COLOR);
		AEGfxTextureSet(NULL, 0, 0);
		AEGfxSetBlendMode(AE_GFX_BM_BLEND);
		sprintf_s(augmentAdd_buffer, "+");
		AEGfxPrint(fontID, augmentAdd_buffer, (getWinWidth() / (-47000.f * scaleX)), (getWinHeight() / (4500.f * scaleY)), 1.f * scaleX, 241.f / 255.f, 23.0f / 171.f, 185.0f / 255.f);

		AEGfxSetRenderMode(AE_GFX_RM_COLOR);
		AEGfxTextureSet(NULL, 0, 0);
		AEGfxSetBlendMode(AE_GFX_BM_BLEND);
		sprintf_s(augmentAdd_buffer, "+");
		AEGfxPrint(fontID, augmentAdd_buffer, (getWinWidth() / (-47000.f * scaleX)), (getWinHeight() / (60000.f * scaleY)), 1.f * scaleX, 241.f / 255.f, 23.0f / 171.f, 185.0f / 255.f);

		AEGfxSetRenderMode(AE_GFX_RM_COLOR);
		AEGfxTextureSet(NULL, 0, 0);
		AEGfxSetBlendMode(AE_GFX_BM_BLEND);
		sprintf_s(augmentAdd_buffer, "+");
		AEGfxPrint(fontID, augmentAdd_buffer, (getWinWidth() / (-47000.f * scaleX)), (getWinHeight() / (-5000.f * scaleY)), 1.f * scaleX, 241.f / 255.f, 23.0f / 171.f, 185.0f / 255.f);


		AEGfxSetRenderMode(AE_GFX_RM_COLOR);
		AEGfxTextureSet(NULL, 0, 0);
		AEGfxSetBlendMode(AE_GFX_BM_BLEND);
		if (Augment1Level != 8)
			sprintf_s(strbuffer1, "LEVEL %d", Augment1Level);
		if (Augment1Level == 8)
			sprintf_s(strbuffer1, "MAX LEVEL");
		AEGfxPrint(fontID, strbuffer1, static_cast<float>(0.075), (getWinHeight() / (1500.f * scaleY)), 0.4f, 0.0f / 255.f, 23.0f / 255.f, 54.0f / 255.f);


		AEGfxSetRenderMode(AE_GFX_RM_COLOR);
		AEGfxTextureSet(NULL, 0, 0);
		AEGfxSetBlendMode(AE_GFX_BM_BLEND);
		if (Augment2Level != 8)
			sprintf_s(strbuffer2, "LEVEL %d", Augment2Level);
		if (Augment2Level >= 8)
			sprintf_s(strbuffer2, "MAX LEVEL");
		AEGfxPrint(fontID, strbuffer2, static_cast<float>(0.075), (getWinHeight() / (2150.f * scaleY)), 0.4f, 0.0f / 255.f, 23.0f / 255.f, 54.0f / 255.f);

		AEGfxSetRenderMode(AE_GFX_RM_COLOR);
		AEGfxTextureSet(NULL, 0, 0);
		AEGfxSetBlendMode(AE_GFX_BM_BLEND);
		if (Augment3Level != 8)
			sprintf_s(strbuffer3, "LEVEL %d", Augment3Level);
		if (Augment3Level >= 8)
			sprintf_s(strbuffer3, "MAX LEVEL");
		AEGfxPrint(fontID, strbuffer3, static_cast<float>(0.075), (getWinHeight() / (4000.f * scaleY)), 0.4f, 0.0f / 255.f, 23.0f / 255.f, 54.0f / 255.f);

		AEGfxSetRenderMode(AE_GFX_RM_COLOR);
		AEGfxTextureSet(NULL, 0, 0);
		AEGfxSetBlendMode(AE_GFX_BM_BLEND);
		if (Augment4Level != 8)
			sprintf_s(strbuffer4, "LEVEL %d", Augment4Level);
		if (Augment4Level >= 8)
			sprintf_s(strbuffer4, "MAX LEVEL");
		AEGfxPrint(fontID, strbuffer4, static_cast<float>(0.075), (getWinHeight() / (25000.f * scaleY)), 0.4f, 0.0f / 255.f, 23.0f / 255.f, 54.0f / 255.f);

		AEGfxSetRenderMode(AE_GFX_RM_COLOR);
		AEGfxTextureSet(NULL, 0, 0);
		AEGfxSetBlendMode(AE_GFX_BM_BLEND);
		sprintf_s(augment1_buffer, "Increase Frequency");
		AEGfxPrint(fontID, augment1_buffer, (getWinWidth() / (8000.f * scaleX)), (getWinHeight() / (1500.f * scaleY)), 0.4f * scaleX, 128.0f / 255.f, 0.0f / 255.f, 0.0f / 255.f);

		AEGfxSetRenderMode(AE_GFX_RM_COLOR);
		AEGfxTextureSet(NULL, 0, 0);
		AEGfxSetBlendMode(AE_GFX_BM_BLEND);
		sprintf_s(augment1_buffer, "Increase Range/Speed");
		AEGfxPrint(fontID, augment1_buffer, (getWinWidth() / (8000.f * scaleX)), (getWinHeight() / (2150.f * scaleY)), 0.35f * scaleX, 128.0f / 255.f, 0.0f / 255.f, 0.0f / 255.f);

		AEGfxSetRenderMode(AE_GFX_RM_COLOR);
		AEGfxTextureSet(NULL, 0, 0);
		AEGfxSetBlendMode(AE_GFX_BM_BLEND);
		sprintf_s(augment1_buffer, "Increase Range");
		AEGfxPrint(fontID, augment1_buffer, (getWinWidth() / (8000.f * scaleX)), (getWinHeight() / (4000.f * scaleY)), 0.4f * scaleX, 128.0f / 255.f, 0.0f / 255.f, 0.0f / 255.f);

		AEGfxSetRenderMode(AE_GFX_RM_COLOR);
		AEGfxTextureSet(NULL, 0, 0);
		AEGfxSetBlendMode(AE_GFX_BM_BLEND);
		sprintf_s(augment1_buffer, "Increase AOE");
		AEGfxPrint(fontID, augment1_buffer, (getWinWidth() / (8000.f * scaleX)), (getWinHeight() / (26500.f * scaleY)), 0.4f * scaleX, 128.0f / 255.f, 0.0f / 255.f, 0.0f / 255.f);

		AEGfxSetRenderMode(AE_GFX_RM_COLOR);
		AEGfxTextureSet(NULL, 0, 0);
		AEGfxSetBlendMode(AE_GFX_BM_BLEND);
		sprintf_s(augment1_buffer, "Increase HP by 1");
		AEGfxPrint(fontID, augment1_buffer, (getWinWidth() / (8000.f * scaleX)), (getWinHeight() / (-5500.f * scaleY)), 0.4f * scaleX, 128.0f / 255.f, 0.0f / 255.f, 0.0f / 255.f);

	}
	/********************************** Augment UI End ********************************************/


	/********************************** Pause UI Start ********************************************/
	if (pauseTransparency != 0)
	{
		// Drawing the pause overlay on the screen
		AEGfxTextureSet(NULL, 0, 0);
		AEGfxSetRenderMode(AE_GFX_RM_COLOR);
		AEGfxSetTransparency(pauseTransparency);
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

		AEGfxSetRenderMode(AE_GFX_RM_COLOR);
		AEGfxSetTransparency(pauseTransparency);
		AEGfxTextureSet(NULL, 0, 0);
		AEMtx33 scale4 = { 0 };
		AEMtx33Scale(&scale4, 80.f * scaleX, 50.f * scaleY);
		AEMtx33 rotate4 = { 0 };
		AEMtx33Rot(&rotate4, buttonRotate_mainMenu);
		AEMtx33 translate4 = { 0 };
		AEMtx33Trans(&translate4, mainMenu_Button_transX, mainMenu_Button_transY);
		AEMtx33 transform4 = { 0 };
		AEMtx33Concat(&transform4, &rotate4, &scale4);
		AEMtx33Concat(&transform4, &translate4, &transform4);
		AEGfxSetTransform(transform4.m);
		AEGfxMeshDraw(augmentButtonMesh, AE_GFX_MDM_TRIANGLES);

		AEGfxSetRenderMode(AE_GFX_RM_COLOR);
		AEGfxSetTransparency(pauseTransparency);
		AEGfxTextureSet(NULL, 0, 0);
		AEMtx33 scale5 = { 0 };
		AEMtx33Scale(&scale5, 80.f * scaleX, 50.f * scaleY);
		AEMtx33 rotate5 = { 0 };
		AEMtx33Rot(&rotate5, buttonRotate_quit);
		AEMtx33 translate5 = { 0 };
		AEMtx33Trans(&translate5, quitButton_transX, quitButton_transY);
		AEMtx33 transform5 = { 0 };
		AEMtx33Concat(&transform5, &rotate5, &scale5);
		AEMtx33Concat(&transform5, &translate5, &transform5);
		AEGfxSetTransform(transform5.m);
		AEGfxMeshDraw(augmentButtonMesh, AE_GFX_MDM_TRIANGLES);

		// Rendering texts for overlay
		AEGfxSetRenderMode(AE_GFX_RM_COLOR);
		AEGfxTextureSet(NULL, 0, 0);
		AEGfxSetBlendMode(AE_GFX_BM_BLEND);
		sprintf_s(augment1_buffer, "How to play:");
		AEGfxPrint(fontID, augment1_buffer, (getWinWidth() / (-4000.f * scaleX)), (getWinHeight() / (1550.f * scaleY)), 0.7f * scaleX, 0.0f / 255.f, 23.0f / 255.f, 54.0f / 255.f);

		AEGfxSetRenderMode(AE_GFX_RM_COLOR);
		AEGfxTextureSet(NULL, 0, 0);
		AEGfxSetBlendMode(AE_GFX_BM_BLEND);
		sprintf_s(augment1_buffer, "> Right mouse click for augments.");
		AEGfxPrint(fontID, augment1_buffer, (getWinWidth() / (-4000.f * scaleX)), (getWinHeight() / (2200.f * scaleY)), 0.7f * scaleX, 0.0f / 255.f, 23.0f / 255.f, 54.0f / 255.f);

		AEGfxSetRenderMode(AE_GFX_RM_COLOR);
		AEGfxTextureSet(NULL, 0, 0);
		AEGfxSetBlendMode(AE_GFX_BM_BLEND);
		sprintf_s(augment1_buffer, "> WASD for movement.");
		AEGfxPrint(fontID, augment1_buffer, (getWinWidth() / (-4000.f * scaleX)), (getWinHeight() / (4200.f * scaleY)), 0.7f * scaleX, 0.0f / 255.f, 23.0f / 255.f, 54.0f / 255.f);

		AEGfxSetRenderMode(AE_GFX_RM_COLOR);
		AEGfxTextureSet(NULL, 0, 0);
		AEGfxSetBlendMode(AE_GFX_BM_BLEND);
		sprintf_s(augment1_buffer, "> Bullets will follow cursor movement.");
		AEGfxPrint(fontID, augment1_buffer, (getWinWidth() / (-4000.f * scaleX)), (getWinHeight() / (26500.f * scaleY)), 0.7f * scaleX, 0.0f / 255.f, 23.0f / 255.f, 54.0f / 255.f);

		AEGfxSetRenderMode(AE_GFX_RM_COLOR);
		AEGfxTextureSet(NULL, 0, 0);
		AEGfxSetBlendMode(AE_GFX_BM_BLEND);
		sprintf_s(augment1_buffer, "> Press 'P' or 'esc' again to resume");
		AEGfxPrint(fontID, augment1_buffer, (getWinWidth() / (-4000.f * scaleX)), (getWinHeight() / (-5500.f * scaleY)), 0.7f * scaleX, 0.0f / 255.f, 23.0f / 255.f, 54.0f / 255.f);

		AEGfxSetRenderMode(AE_GFX_RM_COLOR);
		AEGfxTextureSet(NULL, 0, 0);
		AEGfxSetBlendMode(AE_GFX_BM_BLEND);
		sprintf_s(skillpoint_buffer, "Menu");
		AEGfxPrint(fontID, skillpoint_buffer, -0.412f, -0.7f, 0.8f, 0.0f / 255.f, 23.0f / 255.f, 54.0f / 255.f);

		AEGfxSetRenderMode(AE_GFX_RM_COLOR);
		AEGfxTextureSet(NULL, 0, 0);
		AEGfxSetBlendMode(AE_GFX_BM_BLEND);
		sprintf_s(skillpoint_buffer, "Quit");
		AEGfxPrint(fontID, skillpoint_buffer, 0.305f, -0.7f, 0.8f, 0.0f / 255.f, 23.0f / 255.f, 54.0f / 255.f);

	}

	if (areyouSure == false)
	{
		// Drawing the yes/no overlay on the screen
		AEGfxTextureSet(NULL, 0, 0);
		AEGfxSetRenderMode(AE_GFX_RM_COLOR);
		AEGfxSetTransparency(0.5f);
		AEMtx33 scale3 = { 0 };
		AEMtx33Scale(&scale3, 500.f, 300.f);
		AEMtx33 rotate3 = { 0 };
		AEMtx33Rot(&rotate3, 0.f);
		AEMtx33 translate3 = { 0 };
		AEMtx33Trans(&translate3, 125.f, -10.f);
		AEMtx33 transform3 = { 0 };
		AEMtx33Concat(&transform3, &rotate3, &scale3);
		AEMtx33Concat(&transform3, &translate3, &transform3);
		AEGfxSetTransform(transform3.m);
		AEGfxMeshDraw(augmentMesh, AE_GFX_MDM_TRIANGLES);

		AEGfxSetRenderMode(AE_GFX_RM_COLOR);
		AEGfxSetTransparency(0.3f);
		AEGfxTextureSet(NULL, 0, 0);
		AEMtx33 scale6 = { 0 };
		AEMtx33Scale(&scale6, 80.f * scaleX, 50.f * scaleY);
		AEMtx33 rotate6 = { 0 };
		AEMtx33Rot(&rotate6, buttonRotate_Yes);
		AEMtx33 translate6 = { 0 };
		AEMtx33Trans(&translate6, yesButton_transX, yesButton_transY);
		AEMtx33 transform6 = { 0 };
		AEMtx33Concat(&transform6, &rotate6, &scale6);
		AEMtx33Concat(&transform6, &translate6, &transform6);
		AEGfxSetTransform(transform6.m);
		AEGfxMeshDraw(augmentButtonMesh, AE_GFX_MDM_TRIANGLES);

		AEGfxSetRenderMode(AE_GFX_RM_COLOR);
		AEGfxSetTransparency(0.3f);
		AEGfxTextureSet(NULL, 0, 0);
		AEMtx33 scale7 = { 0 };
		AEMtx33Scale(&scale7, 80.f * scaleX, 50.f * scaleY);
		AEMtx33 rotate7 = { 0 };
		AEMtx33Rot(&rotate7, buttonRotate_No);
		AEMtx33 translate7 = { 0 };
		AEMtx33Trans(&translate7, noButton_transX, noButton_transY);
		AEMtx33 transform7 = { 0 };
		AEMtx33Concat(&transform7, &rotate7, &scale7);
		AEMtx33Concat(&transform7, &translate7, &transform7);
		AEGfxSetTransform(transform7.m);
		AEGfxMeshDraw(augmentButtonMesh, AE_GFX_MDM_TRIANGLES);

		// Rendering texts for overlay
		AEGfxSetRenderMode(AE_GFX_RM_COLOR);
		AEGfxTextureSet(NULL, 0, 0);
		AEGfxSetBlendMode(AE_GFX_BM_BLEND);
		sprintf_s(augment1_buffer, "ARE YOU SURE?");
		AEGfxPrint(fontID, augment1_buffer, (getWinWidth() / (-4000.f * scaleX)), (getWinHeight() / (5000.f * scaleY)), 0.7f * scaleX, 0.0f / 255.f, 23.0f / 255.f, 54.0f / 255.f);

		AEGfxSetRenderMode(AE_GFX_RM_COLOR);
		AEGfxTextureSet(NULL, 0, 0);
		AEGfxSetBlendMode(AE_GFX_BM_BLEND);
		sprintf_s(augment1_buffer, "YES");
		AEGfxPrint(fontID, augment1_buffer, (getWinWidth() / (-7000.f * scaleX)), (getWinHeight() / (-5200.f * scaleY)), 0.7f * scaleX, 0.0f / 255.f, 23.0f / 255.f, 54.0f / 255.f);

		AEGfxSetRenderMode(AE_GFX_RM_COLOR);
		AEGfxTextureSet(NULL, 0, 0);
		AEGfxSetBlendMode(AE_GFX_BM_BLEND);
		sprintf_s(augment1_buffer, "NO");
		AEGfxPrint(fontID, augment1_buffer, (getWinWidth() / (11000.f * scaleX)), (getWinHeight() / (-5200.f * scaleY)), 0.7f * scaleX, 0.0f / 255.f, 23.0f / 255.f, 54.0f / 255.f);
	}
	/********************************** Pause UI End ********************************************/

	// Rendering texts for the screen	
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxTextureSet(NULL, 0, 0);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	if (secElapsedInt > 9)
		sprintf_s(gdt_buffer, "%d:%.0f", minElapsed, secElapsedInt);
	else
		sprintf_s(gdt_buffer, "%d:0%.0f", minElapsed, secElapsedInt);
	AEGfxPrint(fontID, gdt_buffer, 0.85f, 0.85f, 0.8f, 255.0f / 255.f, 255.0f / 255.f, 255.0f / 255.f);

	if (spawnCheck != true) {
		AEGfxSetRenderMode(AE_GFX_RM_COLOR);
		AEGfxTextureSet(NULL, 0, 0);
		AEGfxSetBlendMode(AE_GFX_BM_BLEND);
		if (bossCooldownSecInt > 9)
			sprintf_s(gdt_buffer, "BOSS APPROACHING IN %d:%.0f", bossCooldownMin, bossCooldownSecInt);
		else {
			if (bossCooldownSec >= 60.0f)
				sprintf_s(gdt_buffer, "BOSS APPROACHING IN %d:59", bossCooldownMin);
			else
				sprintf_s(gdt_buffer, "BOSS APPROACHING IN %d:0%.0f", bossCooldownMin, bossCooldownSecInt);
		}

		AEGfxPrint(fontID, gdt_buffer, 0.25f, 0.75f, 0.8f, 255.0f / 255.f, 255.0f / 255.f, 255.0f / 255.f);
	}


	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxTextureSet(NULL, 0, 0);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	sprintf_s(hp_buffer, "HP: %d/%d", _Player->health, MaxHealth);
	AEGfxPrint(fontID, hp_buffer, 0.5f, 0.85f, 0.8f, 255.0f / 255.f, 255.0f / 255.f, 255.0f / 255.f);

	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxTextureSet(NULL, 0, 0);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	sprintf_s(goldbuffer, "Gold: %d", Currency);
	AEGfxPrint(fontID, goldbuffer, -0.925f, 0.725f, 0.8f, 255.0f / 255.f, 255.0f / 255.f, 255.0f / 255.f);

	if (spawnCheck == 1) {
		AEGfxSetRenderMode(AE_GFX_RM_COLOR);
		AEGfxTextureSet(NULL, 0, 0);
		AEGfxSetBlendMode(AE_GFX_BM_BLEND);
		sprintf_s(boss_hp_buffer, "BOSS HP: %d/%d", _Boss->health, MaxBossHealth);
		if (_Boss == nullptr)
			sprintf_s(boss_hp_buffer, "0");
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
	AEAudioStopGroup(BGM_layer);
	for (unsigned long i = 0; i < sGameObjNum; i++)
	{
		AEGfxMeshFree(sGameObjList[i].pMesh);
	}
	AEGfxMeshFree(ptrMesh);
	AEGfxMeshFree(augmentMesh);
	AEGfxMeshFree(augmentButtonMesh);
	AEGfxMeshFree(bMesh);

	if (minElapsed >= currHighScoreMin) {
		if (secElapsed > currHighScoreSec) {
			std::ofstream outputStream{ "Assets\\SaveFiles\\HighScore.txt" };
			if (outputStream.is_open())
			{
				outputStream << minElapsed << ' ' << secElapsedInt << '\n';
			}
			outputStream.close();
		}
	}
	std::ofstream outputStream{ "Assets\\SaveFiles\\Currency.txt" };
	if (outputStream.is_open())
	{
		outputStream << Currency << '\n';
		outputStream.close();
	}

	//AEGfxMeshFree(bMesh);
	AUGMENT_1_BULLET_SPEED = 100.f;
	pause = false;
	Augment1Level = 1;
	Augment2Level = 0;
	Augment1CD = 1.5f;
	Augment2Range = 1;
	Augment2RotSpd = 0.f;
	Aug2CreateCheck = false;
	Augment3Level = 0;
	Augment3Range = 0;
	Augment4Level = 0;
	Augment4Radius = 0;
	Augment4Scale = 50;
	secElapsed = 0;
	minElapsed = 0;
	spawnCheck = 0;
	enemyCount = 0;
	_Player_Level = 1;
	_Player_Experience = 0;
	pause = false;
	areyouSure = true;
	bossCoolDownCheck = false;
	bossCooldownMin = 4;
	bossCooldownSec = 0.f;
	RegenerationTimer = 15.0f;
	AUGMENT_4_FIRE_INTERVAL = 4.0f;
	currencyCount = 0;


	
	free(sGameObjList);
	sGameObjList = nullptr;
	free(sGameObjInstList);
	sGameObjInstList = nullptr;
}