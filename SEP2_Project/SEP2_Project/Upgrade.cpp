#include "Upgrade.h"
#include "Main.h"

std::ifstream ifs{ "Assets\\SaveFiles\\Tester.txt" };
std::ifstream ifs1{ "Assets\\SaveFiles\\PlayerShipModel.txt" };
std::ifstream ifs2{ "Assets\\SaveFiles\\PlayerStats.txt" };

//bool LevelToggle;
//f32 Timer;

//Pointer to Mesh
AEGfxVertexList* pMeshUpgrade = nullptr;
AEGfxVertexList* pMeshUpgrade1 = nullptr;
AEGfxVertexList* CoinMesh = nullptr;
AEGfxVertexList* BuyButtonMesh = nullptr;
AEGfxVertexList* ShipMesh = nullptr;

// Pre-definition for translations
double UpgradebackButton_transX;
double UpgradebackButton_transY;
double UpgradeStatDisplay_transX;
double UpgradeStatDisplay_transY;

// Pre-definition of scaling
double UpgradescaleX_settings;
double UpgradescaleY_settings;

// 
float Upgrade_textWidth{}, Upgrade_textHeight{};

char Upgrade1_buffer[1024]{};

void Upgrade_Load(void) 
{
	//std::cout << "Upgrade_Load\n";
	AEGfxSetBackgroundColor(0.f, 0.f, 255.f);

	AEGfxMeshStart();

	AEGfxTriAdd(
		0.5f, 0.5f, 0xFF001736, 1.0f, 0.0f,
		-1.2f, -0.5f, 0xFF001736, 0.0f, 1.0f,
		0.5f, -0.5f, 0xFF001736, 1.0f, 1.0f);
	AEGfxTriAdd(
		-1.2f, 0.5f, 0xFF001736, 0.0f, 0.0f,
		-1.2f, -0.5f, 0xFF001736, 0.0f, 1.0f,
		0.5f, 0.5f, 0xFF001736, 1.0f, 0.0f);

	pMeshUpgrade = AEGfxMeshEnd();


	AEGfxMeshStart();

	AEGfxTriAdd(
		0.5f, 0.5f, 0xFF001736, 1.0f, 0.0f,
		-1.2f, -0.5f, 0xFF001736, 0.0f, 1.0f,
		0.5f, -0.5f, 0xFF001736, 1.0f, 1.0f);
	AEGfxTriAdd(
		-1.2f, 0.5f, 0xFF001736, 0.0f, 0.0f,
		-1.2f, -0.5f, 0xFF001736, 0.0f, 1.0f,
		0.5f, 0.5f, 0xFF001736, 1.0f, 0.0f);

	pMeshUpgrade1 = AEGfxMeshEnd();


	//Coin
	AEGfxMeshStart();

	AEGfxTriAdd(
		0.5f, 0.5f, 0xFF001736, 1.0f, 0.0f,
		-1.2f, -0.5f, 0xFF001736, 0.0f, 1.0f,
		0.5f, -0.5f, 0xFF001736, 1.0f, 1.0f);
	AEGfxTriAdd(
		-1.2f, 0.5f, 0xFF001736, 0.0f, 0.0f,
		-1.2f, -0.5f, 0xFF001736, 0.0f, 1.0f,
		0.5f, 0.5f, 0xFF001736, 1.0f, 0.0f);

	CoinMesh = AEGfxMeshEnd();
	//End of Coin
	

	//Buy Button
	AEGfxMeshStart();

	AEGfxTriAdd(
		0.5f, 0.5f, 0xFFAAFF0F, 1.0f, 0.0f,
		-1.2f, -0.5f, 0xFFAAFF0F, 0.0f, 1.0f,
		0.5f, -0.5f, 0xFFAAFF0F, 1.0f, 1.0f);
	AEGfxTriAdd(
		-1.2f, 0.5f, 0xFFAAFF0F, 0.0f, 0.0f,
		-1.2f, -0.5f, 0xFFAAFF0F, 0.0f, 1.0f,
		0.5f, 0.5f, 0xFFAAFF0F, 1.0f, 0.0f);

	BuyButtonMesh = AEGfxMeshEnd();
	//End of Buy Button


	//Ship
	AEGfxMeshStart();

	AEGfxTriAdd(
		0.5f, 0.5f, 0xFF001736, 1.0f, 0.0f,
		-1.2f, -0.5f, 0xFF001736, 0.0f, 1.0f,
		0.5f, -0.5f, 0xFF001736, 1.0f, 1.0f);
	AEGfxTriAdd(
		-1.2f, 0.5f, 0xFF001736, 0.0f, 0.0f,
		-1.2f, -0.5f, 0xFF001736, 0.0f, 1.0f,
		0.5f, 0.5f, 0xFF001736, 1.0f, 0.0f);

	ShipMesh = AEGfxMeshEnd();
	//End of Ship


	//Open save file of money
	if (ifs.good())
	{

		ifs >> Currency;
		std::cout << Currency << '\n';

		ifs.close();
	}
	else if (ifs.fail())
	{
		std::cerr << "Error: \n";

	}
	//End of Open save file of money

	//Open save file of ship
	if (ifs1.good())
	{

		ifs1 >> ShipModel;
		std::cout << ShipModel << '\n';

		ifs1.close();
	}
	else if (ifs1.fail())
	{
		std::cerr << "Error: \n";

	}
	//End of Open save file of ship

	//Open save file of ship
	if (ifs2.good())
	{

		ifs2 >> MaximumPlayerHealth;
		std::cout << MaximumPlayerHealth << '\n';

		ifs2.close();
	}
	else if (ifs2.fail())
	{
		std::cerr << "Error: \n";

	}
	//End of Open save file of ship
}

void Upgrade_Init(void) 
{
	//LevelToggle = false;
	//Timer = 0.0f;

	// Gets the scale of 1366x768
	UpgradescaleX_settings = getWinWidth() / 1366.f;
	UpgradescaleY_settings = getWinHeight() / 768.f;

	// Back button translation
	UpgradebackButton_transX = 640 * UpgradescaleX_settings;
	UpgradebackButton_transY = -355.f * UpgradescaleY_settings;

	UpgradeStatDisplay_transX = 33 * UpgradescaleX_settings;
	UpgradeStatDisplay_transY = 340.f * UpgradescaleY_settings;



}
void Upgrade_Update(void) 
{
	//Timer += g_dt;

	//if (AEInputCheckPrev(AEVK_P) && Timer >= 1.5f)
	//{
	//	gGameStateNext = PLAY;
	//	std::cout << "Back\n";
	//	Timer = 0;
	//}

	// Initialize cursor coordinates
	s32 cursorX;
	s32 cursorY;
	AEInputGetCursorPosition(&cursorX, &cursorY);

	// Quit button mid point
	float backButton_midX = (getWinWidth() / 2.08) + UpgradebackButton_transX;
	float backButton_midY = (getWinHeight() / 2) - UpgradebackButton_transY;


	// if cursor within buttons, change game state
	if (IsAreaClicked(backButton_midX, backButton_midY, 150.0f * UpgradescaleX_settings, 100.0f * UpgradescaleY_settings, cursorX, cursorY)
		&& AEInputCheckTriggered(AEVK_LBUTTON)) {
		gGameStateNext = MAINMENU;
		printf("MAINMENU\n");
	}



	if (IsAreaClicked((getWinHeight() / 2) + 274.f, (getWinHeight() / 2) - 223.f, 107.f * UpgradescaleX_settings, 100.f * UpgradescaleY_settings, cursorX, cursorY)
		&& AEInputCheckTriggered(AEVK_LBUTTON)) {

		std::ofstream outputStream{ "Assets\\SaveFiles\\Tester.txt" };
		std::ofstream outputStream1{ "Assets\\SaveFiles\\PlayerShipModel.txt" };

		ShipModel = 0;
		std::cout << "Thank you for purchase\n";

		outputStream << Currency;
		outputStream.close();
		outputStream1 << ShipModel;
		outputStream1.close();
	}

	if (IsAreaClicked((getWinHeight() / 2) + 274.f, (getWinHeight() / 2) -93.f, 107.f * UpgradescaleX_settings, 100.f * UpgradescaleY_settings, cursorX, cursorY)
		&& AEInputCheckTriggered(AEVK_LBUTTON)) {

		std::ofstream outputStream{ "Assets\\SaveFiles\\Tester.txt" };
		std::ofstream outputStream1{ "Assets\\SaveFiles\\PlayerShipModel.txt" };

		if (Currency >= 200)
		{
			Currency = Currency - 200;
			ShipModel = 1;
			std::cout << "Thank you for purchase\n";

			outputStream << Currency;
			outputStream.close();
			outputStream1 << ShipModel;
			outputStream1.close();
		}
		else
		{
			std::cout << "You don't have enough gold..\n";
		}
		outputStream.close();
		outputStream1.close();
	}


	if (IsAreaClicked((getWinHeight() / 2) + 784.f, (getWinHeight() / 2) - 223.f, 107.f * UpgradescaleX_settings, 100.f * UpgradescaleY_settings, cursorX, cursorY)
		&& AEInputCheckTriggered(AEVK_LBUTTON)) {

		std::ofstream outputStream{ "Assets\\SaveFiles\\Tester.txt" };
		std::ofstream outputStream1{ "Assets\\SaveFiles\\PlayerStats.txt" };
		
		if (Currency >= 300)
		{
			Currency = Currency - 300;
			MaximumPlayerHealth = MaximumPlayerHealth+1;
			std::cout << "Thank you for purchase\n";

			outputStream << Currency;
			outputStream.close();
			outputStream1 << MaximumPlayerHealth;
			outputStream1.close();
		}
		else
		{
			std::cout << "You don't have enough gold..\n";
		}
		outputStream.close();
		outputStream1.close();
		
	}

	

}
void Upgrade_Draw(void) 
{

	//Coin Display
	AEGfxTexture* coinTex = AEGfxTextureLoad("Assets\\Assets\\Coin.png");
	
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetTransparency(1.0f);
	AEGfxTextureSet(coinTex, 0, 0);
	AEMtx33 scale4 = { 0 };
	AEMtx33Scale(&scale4, 60, 65);
	AEMtx33 rotate4 = { 0 };
	AEMtx33Rot(&rotate4, 0.f);
	AEMtx33 translate4 = { 0 };
	AEMtx33Trans(&translate4, UpgradebackButton_transX-170, UpgradebackButton_transY+820);
	AEMtx33 transform4 = { 0 };
	AEMtx33Concat(&transform4, &rotate4, &scale4);
	AEMtx33Concat(&transform4, &translate4, &transform4);
	AEGfxSetTransform(transform4.m);
	AEGfxMeshDraw(CoinMesh, AE_GFX_MDM_TRIANGLES);


	



	//Amount of coins player displayed in text
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxTextureSet(NULL, 0, 0);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	sprintf_s(Upgrade1_buffer, "%d", Currency);
	AEGfxGetPrintSize(fontID, Upgrade1_buffer, 1.0f, Upgrade_textWidth, Upgrade_textHeight);
	AEGfxPrint(fontID, Upgrade1_buffer, (getWinWidth() / (1800.f * UpgradescaleX_settings)), (getWinHeight() / (900.f * UpgradescaleY_settings)), 1.0f * UpgradescaleX_settings, 255.f,255.f,0.f);

	// Back word box
	AEGfxTextureSet(NULL, 0, 0);
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEMtx33 scale = { 0 };
	AEMtx33Scale(&scale, 80.f * UpgradescaleX_settings, 50.f * UpgradescaleY_settings);
	AEMtx33 rotate = { 0 };
	AEMtx33Rot(&rotate, 0.f);
	AEMtx33 translate = { 0 };
	AEMtx33Trans(&translate, UpgradebackButton_transX, UpgradebackButton_transY);
	AEMtx33 transform = { 0 };
	AEMtx33Concat(&transform, &rotate, &scale);
	AEMtx33Concat(&transform, &translate, &transform);
	AEGfxSetTransform(transform.m);
	AEGfxMeshDraw(pMeshUpgrade, AE_GFX_MDM_TRIANGLES);

	// Upgrades word box
	AEGfxTextureSet(NULL, 0, 0);
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEMtx33 scale1 = { 0 };
	AEMtx33Scale(&scale1, 120.f * UpgradescaleX_settings, 60.f * UpgradescaleY_settings);
	AEMtx33 rotate1 = { 0 };
	AEMtx33Rot(&rotate1, 0.f);
	AEMtx33 translate1 = { 0 };
	AEMtx33Trans(&translate1, UpgradeStatDisplay_transX, UpgradeStatDisplay_transY);
	AEMtx33 transform1 = { 0 };
	AEMtx33Concat(&transform1, &rotate1, &scale1);
	AEMtx33Concat(&transform1, &translate1, &transform1);
	AEGfxSetTransform(transform1.m);
	AEGfxMeshDraw(pMeshUpgrade1, AE_GFX_MDM_TRIANGLES);

	// Ship Models word box
	AEGfxTextureSet(NULL, 0, 0);
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEMtx33 scale2 = { 0 };
	AEMtx33Scale(&scale2, 150.f * UpgradescaleX_settings, 60.f * UpgradescaleY_settings);
	AEMtx33 rotate2 = { 0 };
	AEMtx33Rot(&rotate2, 0.f);
	AEMtx33 translate2 = { 0 };
	AEMtx33Trans(&translate2, UpgradeStatDisplay_transX - 350.f , UpgradeStatDisplay_transY -120.f);
	AEMtx33 transform2 = { 0 };
	AEMtx33Concat(&transform2, &rotate2, &scale2);
	AEMtx33Concat(&transform2, &translate2, &transform2);
	AEGfxSetTransform(transform2.m);
	AEGfxMeshDraw(pMeshUpgrade1, AE_GFX_MDM_TRIANGLES);

	// Stats word box
	AEGfxTextureSet(NULL, 0, 0);
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEMtx33 scale3 = { 0 };
	AEMtx33Scale(&scale3, 80.f * UpgradescaleX_settings, 60.f * UpgradescaleY_settings);
	AEMtx33 rotate3 = { 0 };
	AEMtx33Rot(&rotate3, 0.f);
	AEMtx33 translate3 = { 0 };
	AEMtx33Trans(&translate3, UpgradeStatDisplay_transX + 200.f, UpgradeStatDisplay_transY - 120.f);
	AEMtx33 transform3 = { 0 };
	AEMtx33Concat(&transform3, &rotate3, &scale3);
	AEMtx33Concat(&transform3, &translate3, &transform3);
	AEGfxSetTransform(transform3.m);
	AEGfxMeshDraw(pMeshUpgrade1, AE_GFX_MDM_TRIANGLES);

	// Ship Model 1 Box
	AEGfxTextureSet(NULL, 0, 0);
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEMtx33 scale5 = { 0 };
	AEMtx33Scale(&scale5, 250.f * UpgradescaleX_settings, 100.f * UpgradescaleY_settings);
	AEMtx33 rotate5 = { 0 };
	AEMtx33Rot(&rotate5, 0.f);
	AEMtx33 translate5 = { 0 };
	AEMtx33Trans(&translate5, UpgradeStatDisplay_transX - 330.f, UpgradeStatDisplay_transY - 230.f);
	AEMtx33 transform5 = { 0 };
	AEMtx33Concat(&transform5, &rotate5, &scale5);
	AEMtx33Concat(&transform5, &translate5, &transform5);
	AEGfxSetTransform(transform5.m);
	AEGfxMeshDraw(pMeshUpgrade1, AE_GFX_MDM_TRIANGLES);

	// Ship Model 1 Purchase box1
	AEGfxTextureSet(NULL, 0, 0);
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEMtx33 scale6 = { 0 };
	AEMtx33Scale(&scale6, 65.f * UpgradescaleX_settings, 100.f * UpgradescaleY_settings);
	AEMtx33 rotate6 = { 0 };
	AEMtx33Rot(&rotate6, 0.f);
	AEMtx33 translate6 = { 0 };
	AEMtx33Trans(&translate6, UpgradeStatDisplay_transX - 87.f, UpgradeStatDisplay_transY - 230.f);
	AEMtx33 transform6 = { 0 };
	AEMtx33Concat(&transform6, &rotate6, &scale6);
	AEMtx33Concat(&transform6, &translate6, &transform6);
	AEGfxSetTransform(transform6.m);
	AEGfxMeshDraw(BuyButtonMesh, AE_GFX_MDM_TRIANGLES);

	// Ship Model 1 Purchase box2
	AEGfxTextureSet(NULL, 0, 0);
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEMtx33 scale7 = { 0 };
	AEMtx33Scale(&scale7, 55.f * UpgradescaleX_settings, 85.f * UpgradescaleY_settings);
	AEMtx33 rotate7 = { 0 };
	AEMtx33Rot(&rotate7, 0.f);
	AEMtx33 translate7 = { 0 };
	AEMtx33Trans(&translate7, UpgradeStatDisplay_transX - 91.f, UpgradeStatDisplay_transY - 230.f);
	AEMtx33 transform7 = { 0 };
	AEMtx33Concat(&transform7, &rotate7, &scale7);
	AEMtx33Concat(&transform7, &translate7, &transform7);
	AEGfxSetTransform(transform7.m);
	AEGfxMeshDraw(pMeshUpgrade1, AE_GFX_MDM_TRIANGLES);


	// Ship Model 2 Box
	AEGfxTextureSet(NULL, 0, 0);
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEMtx33 scale8 = { 0 };
	AEMtx33Scale(&scale8, 250.f * UpgradescaleX_settings, 100.f * UpgradescaleY_settings);
	AEMtx33 rotate8 = { 0 };
	AEMtx33Rot(&rotate8, 0.f);
	AEMtx33 translate8 = { 0 };
	AEMtx33Trans(&translate8, UpgradeStatDisplay_transX - 330.f, UpgradeStatDisplay_transY - 360.f);
	AEMtx33 transform8 = { 0 };
	AEMtx33Concat(&transform8, &rotate8, &scale8);
	AEMtx33Concat(&transform8, &translate8, &transform8);
	AEGfxSetTransform(transform8.m);
	AEGfxMeshDraw(pMeshUpgrade1, AE_GFX_MDM_TRIANGLES);

	// Ship Model 2 Purchase box1
	AEGfxTextureSet(NULL, 0, 0);
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEMtx33 scale11 = { 0 };
	AEMtx33Scale(&scale11, 65.f * UpgradescaleX_settings, 100.f * UpgradescaleY_settings);
	AEMtx33 rotate11 = { 0 };
	AEMtx33Rot(&rotate11, 0.f);
	AEMtx33 translate11 = { 0 };
	AEMtx33Trans(&translate11, UpgradeStatDisplay_transX - 87.f, UpgradeStatDisplay_transY - 360.f);
	AEMtx33 transform11 = { 0 };
	AEMtx33Concat(&transform11, &rotate11, &scale11);
	AEMtx33Concat(&transform11, &translate11, &transform11);
	AEGfxSetTransform(transform11.m);
	AEGfxMeshDraw(BuyButtonMesh, AE_GFX_MDM_TRIANGLES);

	// Ship Model 2 Purchase box2
	AEGfxTextureSet(NULL, 0, 0);
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEMtx33 scale12 = { 0 };
	AEMtx33Scale(&scale12, 55.f * UpgradescaleX_settings, 85.f * UpgradescaleY_settings);
	AEMtx33 rotate12 = { 0 };
	AEMtx33Rot(&rotate12, 0.f);
	AEMtx33 translate12 = { 0 };
	AEMtx33Trans(&translate12, UpgradeStatDisplay_transX - 91.f, UpgradeStatDisplay_transY - 360.f);
	AEMtx33 transform12 = { 0 };
	AEMtx33Concat(&transform12, &rotate12, &scale12);
	AEMtx33Concat(&transform12, &translate12, &transform12);
	AEGfxSetTransform(transform12.m);
	AEGfxMeshDraw(pMeshUpgrade1, AE_GFX_MDM_TRIANGLES);


	// Ship Model 3 Box
	AEGfxTextureSet(NULL, 0, 0);
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEMtx33 scale9 = { 0 };
	AEMtx33Scale(&scale9, 250.f * UpgradescaleX_settings, 100.f * UpgradescaleY_settings);
	AEMtx33 rotate9 = { 0 };
	AEMtx33Rot(&rotate9, 0.f);
	AEMtx33 translate9 = { 0 };
	AEMtx33Trans(&translate9, UpgradeStatDisplay_transX - 330.f, UpgradeStatDisplay_transY - 490.f);
	AEMtx33 transform9 = { 0 };
	AEMtx33Concat(&transform9, &rotate9, &scale9);
	AEMtx33Concat(&transform9, &translate9, &transform9);
	AEGfxSetTransform(transform9.m);
	AEGfxMeshDraw(pMeshUpgrade1, AE_GFX_MDM_TRIANGLES);

	// Ship Model 3 Purchase box1
	AEGfxTextureSet(NULL, 0, 0);
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEMtx33 scale24 = { 0 };
	AEMtx33Scale(&scale24, 65.f * UpgradescaleX_settings, 100.f * UpgradescaleY_settings);
	AEMtx33 rotate24 = { 0 };
	AEMtx33Rot(&rotate24, 0.f);
	AEMtx33 translate24 = { 0 };
	AEMtx33Trans(&translate24, UpgradeStatDisplay_transX - 87.f, UpgradeStatDisplay_transY - 490.f);
	AEMtx33 transform24 = { 0 };
	AEMtx33Concat(&transform24, &rotate24, &scale24);
	AEMtx33Concat(&transform24, &translate24, &transform24);
	AEGfxSetTransform(transform24.m);
	AEGfxMeshDraw(BuyButtonMesh, AE_GFX_MDM_TRIANGLES);

	// Ship Model 3 Purchase box2
	AEGfxTextureSet(NULL, 0, 0);
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEMtx33 scale25 = { 0 };
	AEMtx33Scale(&scale25, 55.f * UpgradescaleX_settings, 85.f * UpgradescaleY_settings);
	AEMtx33 rotate25 = { 0 };
	AEMtx33Rot(&rotate25, 0.f);
	AEMtx33 translate25 = { 0 };
	AEMtx33Trans(&translate25, UpgradeStatDisplay_transX - 91.f, UpgradeStatDisplay_transY - 490.f);
	AEMtx33 transform25 = { 0 };
	AEMtx33Concat(&transform25, &rotate25, &scale25);
	AEMtx33Concat(&transform25, &translate25, &transform25);
	AEGfxSetTransform(transform25.m);
	AEGfxMeshDraw(pMeshUpgrade1, AE_GFX_MDM_TRIANGLES);



	// Ship Model 4 Box
	AEGfxTextureSet(NULL, 0, 0);
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEMtx33 scale10 = { 0 };
	AEMtx33Scale(&scale10, 250.f * UpgradescaleX_settings, 100.f * UpgradescaleY_settings);
	AEMtx33 rotate10 = { 0 };
	AEMtx33Rot(&rotate10, 0.f);
	AEMtx33 translate10 = { 0 };
	AEMtx33Trans(&translate10, UpgradeStatDisplay_transX - 330.f, UpgradeStatDisplay_transY - 620.f);
	AEMtx33 transform10 = { 0 };
	AEMtx33Concat(&transform10, &rotate10, &scale10);
	AEMtx33Concat(&transform10, &translate10, &transform10);
	AEGfxSetTransform(transform10.m);
	AEGfxMeshDraw(pMeshUpgrade1, AE_GFX_MDM_TRIANGLES);


	// Ship Model 4 Purchase box1
	AEGfxTextureSet(NULL, 0, 0);
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEMtx33 scale26 = { 0 };
	AEMtx33Scale(&scale26, 65.f * UpgradescaleX_settings, 100.f * UpgradescaleY_settings);
	AEMtx33 rotate26 = { 0 };
	AEMtx33Rot(&rotate26, 0.f);
	AEMtx33 translate26 = { 0 };
	AEMtx33Trans(&translate26, UpgradeStatDisplay_transX - 87.f, UpgradeStatDisplay_transY - 620.f);
	AEMtx33 transform26 = { 0 };
	AEMtx33Concat(&transform26, &rotate26, &scale26);
	AEMtx33Concat(&transform26, &translate26, &transform26);
	AEGfxSetTransform(transform26.m);
	AEGfxMeshDraw(BuyButtonMesh, AE_GFX_MDM_TRIANGLES);

	// Ship Model 4 Purchase box2
	AEGfxTextureSet(NULL, 0, 0);
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEMtx33 scale27 = { 0 };
	AEMtx33Scale(&scale27, 55.f * UpgradescaleX_settings, 85.f * UpgradescaleY_settings);
	AEMtx33 rotate27 = { 0 };
	AEMtx33Rot(&rotate27, 0.f);
	AEMtx33 translate27 = { 0 };
	AEMtx33Trans(&translate27, UpgradeStatDisplay_transX - 91.f, UpgradeStatDisplay_transY - 620.f);
	AEMtx33 transform27 = { 0 };
	AEMtx33Concat(&transform27, &rotate27, &scale27);
	AEMtx33Concat(&transform27, &translate27, &transform27);
	AEGfxSetTransform(transform27.m);
	AEGfxMeshDraw(pMeshUpgrade1, AE_GFX_MDM_TRIANGLES);


	// Stat Box 1
	AEGfxTextureSet(NULL, 0, 0);
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEMtx33 scale15 = { 0 };
	AEMtx33Scale(&scale15, 180.f * UpgradescaleX_settings, 100.f * UpgradescaleY_settings);
	AEMtx33 rotate15 = { 0 };
	AEMtx33Rot(&rotate15, 0.f);
	AEMtx33 translate15 = { 0 };
	AEMtx33Trans(&translate15, UpgradeStatDisplay_transX + 220.f, UpgradeStatDisplay_transY - 230.f);
	AEMtx33 transform15 = { 0 };
	AEMtx33Concat(&transform15, &rotate15, &scale15);
	AEMtx33Concat(&transform15, &translate15, &transform15);
	AEGfxSetTransform(transform15.m);
	AEGfxMeshDraw(pMeshUpgrade1, AE_GFX_MDM_TRIANGLES);

	// Stat Box 1 Purchase box1
	AEGfxTextureSet(NULL, 0, 0);
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEMtx33 scale19 = { 0 };
	AEMtx33Scale(&scale19, 65.f * UpgradescaleX_settings, 100.f * UpgradescaleY_settings);
	AEMtx33 rotate19 = { 0 };
	AEMtx33Rot(&rotate19, 0.f);
	AEMtx33 translate19 = { 0 };
	AEMtx33Trans(&translate19, UpgradeStatDisplay_transX + 422.f, UpgradeStatDisplay_transY - 230.f);
	AEMtx33 transform19 = { 0 };
	AEMtx33Concat(&transform19, &rotate19, &scale19);
	AEMtx33Concat(&transform19, &translate19, &transform19);
	AEGfxSetTransform(transform19.m);
	AEGfxMeshDraw(BuyButtonMesh, AE_GFX_MDM_TRIANGLES);

	// Stat Box 1 Purchase box2
	AEGfxTextureSet(NULL, 0, 0);
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEMtx33 scale20 = { 0 };
	AEMtx33Scale(&scale20, 55.f * UpgradescaleX_settings, 85.f * UpgradescaleY_settings);
	AEMtx33 rotate20 = { 0 };
	AEMtx33Rot(&rotate20, 0.f);
	AEMtx33 translate20 = { 0 };
	AEMtx33Trans(&translate20, UpgradeStatDisplay_transX +417.f, UpgradeStatDisplay_transY - 230.f);
	AEMtx33 transform20 = { 0 };
	AEMtx33Concat(&transform20, &rotate20, &scale20);
	AEMtx33Concat(&transform20, &translate20, &transform20);
	AEGfxSetTransform(transform20.m);
	AEGfxMeshDraw(pMeshUpgrade1, AE_GFX_MDM_TRIANGLES);

	// Stat Box 2
	AEGfxTextureSet(NULL, 0, 0);
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEMtx33 scale16 = { 0 };
	AEMtx33Scale(&scale16, 180.f * UpgradescaleX_settings, 100.f * UpgradescaleY_settings);
	AEMtx33 rotate16 = { 0 };
	AEMtx33Rot(&rotate16, 0.f);
	AEMtx33 translate16 = { 0 };
	AEMtx33Trans(&translate16, UpgradeStatDisplay_transX + 220.f, UpgradeStatDisplay_transY - 360.f);
	AEMtx33 transform16 = { 0 };
	AEMtx33Concat(&transform16, &rotate16, &scale16);
	AEMtx33Concat(&transform16, &translate16,&transform16);
	AEGfxSetTransform(transform16.m);
	AEGfxMeshDraw(pMeshUpgrade1, AE_GFX_MDM_TRIANGLES);
	
	// Stat Box 3
	AEGfxTextureSet(NULL, 0, 0);
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEMtx33 scale17 = { 0 };
	AEMtx33Scale(&scale17, 180.f * UpgradescaleX_settings, 100.f * UpgradescaleY_settings);
	AEMtx33 rotate17 = { 0 };
	AEMtx33Rot(&rotate17, 0.f);
	AEMtx33 translate17 = { 0 };
	AEMtx33Trans(&translate17, UpgradeStatDisplay_transX + 220.f, UpgradeStatDisplay_transY - 490.f);
	AEMtx33 transform17 = { 0 };
	AEMtx33Concat(&transform17, &rotate17, &scale17);
	AEMtx33Concat(&transform17, &translate17, &transform17);
	AEGfxSetTransform(transform17.m);
	AEGfxMeshDraw(pMeshUpgrade1, AE_GFX_MDM_TRIANGLES);

	// Stat Box 4
	AEGfxTextureSet(NULL, 0, 0);
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEMtx33 scale18 = { 0 };
	AEMtx33Scale(&scale18, 180.f * UpgradescaleX_settings, 100.f * UpgradescaleY_settings);
	AEMtx33 rotate18 = { 0 };
	AEMtx33Rot(&rotate18, 0.f);
	AEMtx33 translate18 = { 0 };
	AEMtx33Trans(&translate18, UpgradeStatDisplay_transX + 220.f, UpgradeStatDisplay_transY - 620.f);
	AEMtx33 transform18 = { 0 };
	AEMtx33Concat(&transform18, &rotate18, &scale18);
	AEMtx33Concat(&transform18, &translate18, &transform18);
	AEGfxSetTransform(transform18.m);
	AEGfxMeshDraw(pMeshUpgrade1, AE_GFX_MDM_TRIANGLES);



	//Player Ship 0 Display
	AEGfxTexture* playership0Tex = AEGfxTextureLoad("Assets\\Assets\\player0.png");

	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetTransparency(1.0f);
	AEGfxTextureSet(playership0Tex, 0, 0);
	AEMtx33 scale13 = { 0 };
	AEMtx33Scale(&scale13, 55, 70);
	AEMtx33 rotate13 = { 0 };
	AEMtx33Rot(&rotate13, 0.f);
	AEMtx33 translate13 = { 0 };
	AEMtx33Trans(&translate13, UpgradebackButton_transX - 1320, UpgradebackButton_transY + 585);
	AEMtx33 transform13 = { 0 };
	AEMtx33Concat(&transform13, &rotate13, &scale13);
	AEMtx33Concat(&transform13, &translate13, &transform13);
	AEGfxSetTransform(transform13.m);
	AEGfxMeshDraw(ShipMesh, AE_GFX_MDM_TRIANGLES);


	//Player Ship 1 Display
	AEGfxTexture* playership1Tex = AEGfxTextureLoad("Assets\\Assets\\player1.png");

	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetTransparency(1.0f);
	AEGfxTextureSet(playership1Tex, 0, 0);
	AEMtx33 scale14 = { 0 };
	AEMtx33Scale(&scale14, 55, 70);
	AEMtx33 rotate14 = { 0 };
	AEMtx33Rot(&rotate14, 0.f);
	AEMtx33 translate14 = { 0 };
	AEMtx33Trans(&translate14, UpgradebackButton_transX - 1320, UpgradebackButton_transY + 455);
	AEMtx33 transform14 = { 0 };
	AEMtx33Concat(&transform14, &rotate14, &scale14);
	AEMtx33Concat(&transform14, &translate14, &transform14);
	AEGfxSetTransform(transform14.m);
	AEGfxMeshDraw(ShipMesh, AE_GFX_MDM_TRIANGLES);


	//Player ship 2 Display
	AEGfxTexture* playership2Tex = AEGfxTextureLoad("Assets\\Assets\\player2.png");

	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetTransparency(1.0f);
	AEGfxTextureSet(playership2Tex, 0, 0);
	AEMtx33 scale22 = { 0 };
	AEMtx33Scale(&scale22, 55, 70);
	AEMtx33 rotate22 = { 0 };
	AEMtx33Rot(&rotate22, 0.f);
	AEMtx33 translate22 = { 0 };
	AEMtx33Trans(&translate22, UpgradebackButton_transX - 1320, UpgradebackButton_transY + 325);
	AEMtx33 transform22 = { 0 };
	AEMtx33Concat(&transform22, &rotate22, &scale22);
	AEMtx33Concat(&transform22, &translate22, &transform22);
	AEGfxSetTransform(transform22.m);
	AEGfxMeshDraw(ShipMesh, AE_GFX_MDM_TRIANGLES);


	//Player ship 3 Display
	AEGfxTexture* playership3Tex = AEGfxTextureLoad("Assets\\Assets\\player3.png");

	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetTransparency(1.0f);
	AEGfxTextureSet(playership3Tex, 0, 0);
	AEMtx33 scale23 = { 0 };
	AEMtx33Scale(&scale23, 55, 70);
	AEMtx33 rotate23 = { 0 };
	AEMtx33Rot(&rotate23, 0.f);
	AEMtx33 translate23 = { 0 };
	AEMtx33Trans(&translate23, UpgradebackButton_transX - 1320, UpgradebackButton_transY + 195);
	AEMtx33 transform23 = { 0 };
	AEMtx33Concat(&transform23, &rotate23, &scale23);
	AEMtx33Concat(&transform23, &translate23, &transform23);
	AEGfxSetTransform(transform23.m);
	AEGfxMeshDraw(ShipMesh, AE_GFX_MDM_TRIANGLES);


	//Heart image display
	AEGfxTexture* playerHPTex = AEGfxTextureLoad("Assets\\Assets\\Health.png");

	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetTransparency(1.0f);
	AEGfxTextureSet(playerHPTex, 0, 0);
	AEMtx33 scale21 = { 0 };
	AEMtx33Scale(&scale21, 55, 70);
	AEMtx33 rotate21 = { 0 };
	AEMtx33Rot(&rotate21, 0.f);
	AEMtx33 translate21 = { 0 };
	AEMtx33Trans(&translate21, UpgradebackButton_transX - 670, UpgradebackButton_transY + 585);
	AEMtx33 transform21 = { 0 };
	AEMtx33Concat(&transform21, &rotate21, &scale21);
	AEMtx33Concat(&transform21, &translate21, &transform21);
	AEGfxSetTransform(transform21.m);
	AEGfxMeshDraw(ShipMesh, AE_GFX_MDM_TRIANGLES);


	// "Back" Text
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxTextureSet(NULL, 0, 0);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	sprintf_s(Upgrade1_buffer, "Back");
	AEGfxGetPrintSize(fontID, Upgrade1_buffer, 1.0f, Upgrade_textWidth, Upgrade_textHeight);
	AEGfxPrint(fontID, Upgrade1_buffer, (getWinWidth() / (1655.f * UpgradescaleX_settings)), (getWinHeight() / (-798.f * UpgradescaleY_settings)), 0.8f * UpgradescaleX_settings, 156.0f / 255.f, 205.0f / 255.f, 220.0f / 255.f);

	// "Upgrades" Text
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxTextureSet(NULL, 0, 0);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	sprintf_s(Upgrade1_buffer, "Upgrades");
	AEGfxGetPrintSize(fontID, Upgrade1_buffer, 1.0f, Upgrade_textWidth, Upgrade_textHeight);
	AEGfxPrint(fontID, Upgrade1_buffer, (getWinWidth() / (-9000.f * UpgradescaleX_settings)), (getWinHeight() / (900.f * UpgradescaleY_settings)), 0.8f * UpgradescaleX_settings, 156.0f / 255.f, 205.0f / 255.f, 220.0f / 255.f);

	
	// "Ship Models" Text
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxTextureSet(NULL, 0, 0);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	sprintf_s(Upgrade1_buffer, "Ship Models");
	AEGfxGetPrintSize(fontID, Upgrade1_buffer, 1.0f, Upgrade_textWidth, Upgrade_textHeight);
	AEGfxPrint(fontID, Upgrade1_buffer, (getWinWidth() / (-2200.f * UpgradescaleX_settings)), (getWinHeight() / (1300.f * UpgradescaleY_settings)), 0.8f * UpgradescaleX_settings, 156.0f / 255.f, 205.0f / 255.f, 220.0f / 255.f);


	// "Stats" Text
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxTextureSet(NULL, 0, 0);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	sprintf_s(Upgrade1_buffer, "Stats");
	AEGfxGetPrintSize(fontID, Upgrade1_buffer, 1.0f, Upgrade_textWidth, Upgrade_textHeight);
	AEGfxPrint(fontID, Upgrade1_buffer, (getWinWidth() / (7300.f * UpgradescaleX_settings)), (getWinHeight() / (1300.f * UpgradescaleY_settings)), 0.8f * UpgradescaleX_settings, 156.0f / 255.f, 205.0f / 255.f, 220.0f / 255.f);
	
	//Start of description text for Stats 1//

	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxTextureSet(NULL, 0, 0);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	sprintf_s(Upgrade1_buffer, "+1 Max HP");
	AEGfxGetPrintSize(fontID, Upgrade1_buffer, 1.0f, Upgrade_textWidth, Upgrade_textHeight);
	AEGfxPrint(fontID, Upgrade1_buffer, (getWinWidth() / (9300.f * UpgradescaleX_settings)), (getWinHeight() / (2000.f * UpgradescaleY_settings)), 0.8f * UpgradescaleX_settings, 156.0f / 255.f, 205.0f / 255.f, 220.0f / 255.f);

	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxTextureSet(NULL, 0, 0);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	sprintf_s(Upgrade1_buffer, "Cost: $300");
	AEGfxGetPrintSize(fontID, Upgrade1_buffer, 1.0f, Upgrade_textWidth, Upgrade_textHeight);
	AEGfxPrint(fontID, Upgrade1_buffer, (getWinWidth() / (9300.f * UpgradescaleX_settings)), (getWinHeight() / (2800.f * UpgradescaleY_settings)), 0.8f * UpgradescaleX_settings, 255.f, 255.f, 0.f);

	//End of description text for Stats 1//










	// "Buy" Text for Ship Model 1
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxTextureSet(NULL, 0, 0);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	sprintf_s(Upgrade1_buffer, "BUY");
	AEGfxGetPrintSize(fontID, Upgrade1_buffer, 1.0f, Upgrade_textWidth, Upgrade_textHeight);
	AEGfxPrint(fontID, Upgrade1_buffer, (getWinWidth() / (-8900.f * UpgradescaleX_settings)), (getWinHeight() / (2300.f * UpgradescaleY_settings)), 0.8f * UpgradescaleX_settings, 156.0f / 255.f, 205.0f / 255.f, 220.0f / 255.f);



	//Start of description text for Ship Model 1//

	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxTextureSet(NULL, 0, 0);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	sprintf_s(Upgrade1_buffer, "Model: Default");
	AEGfxGetPrintSize(fontID, Upgrade1_buffer, 1.0f, Upgrade_textWidth, Upgrade_textHeight);
	AEGfxPrint(fontID, Upgrade1_buffer, (getWinWidth() / (-2050.f * UpgradescaleX_settings)), (getWinHeight() / (2000.f * UpgradescaleY_settings)), 0.8f * UpgradescaleX_settings, 156.0f / 255.f, 205.0f / 255.f, 220.0f / 255.f);
	
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxTextureSet(NULL, 0, 0);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	sprintf_s(Upgrade1_buffer, "Cost:  $0");
	AEGfxGetPrintSize(fontID, Upgrade1_buffer, 1.0f, Upgrade_textWidth, Upgrade_textHeight);
	AEGfxPrint(fontID, Upgrade1_buffer, (getWinWidth() / (-2050.f * UpgradescaleX_settings)), (getWinHeight() / (2800.f * UpgradescaleY_settings)), 0.8f * UpgradescaleX_settings,255.f,255.f,0.f);
	
	//End of description text for Ship Model 1//




	// "Buy" Text for Ship Model 2
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxTextureSet(NULL, 0, 0);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	sprintf_s(Upgrade1_buffer, "BUY");
	AEGfxGetPrintSize(fontID, Upgrade1_buffer, 1.0f, Upgrade_textWidth, Upgrade_textHeight);
	AEGfxPrint(fontID, Upgrade1_buffer, (getWinWidth() / (-8900.f * UpgradescaleX_settings)), (getWinHeight() / (15000.f * UpgradescaleY_settings)), 0.8f * UpgradescaleX_settings, 156.0f / 255.f, 205.0f / 255.f, 220.0f / 255.f);


	//Start of description text for Ship Model 2//

	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxTextureSet(NULL, 0, 0);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	sprintf_s(Upgrade1_buffer, "Model: Small");
	AEGfxGetPrintSize(fontID, Upgrade1_buffer, 1.0f, Upgrade_textWidth, Upgrade_textHeight);
	AEGfxPrint(fontID, Upgrade1_buffer, (getWinWidth() / (-2050.f * UpgradescaleX_settings)), (getWinHeight() / (7500.f * UpgradescaleY_settings)), 0.8f * UpgradescaleX_settings, 156.0f / 255.f, 205.0f / 255.f, 220.0f / 255.f);

	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxTextureSet(NULL, 0, 0);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	sprintf_s(Upgrade1_buffer, "Cost:  $200");
	AEGfxGetPrintSize(fontID, Upgrade1_buffer, 1.0f, Upgrade_textWidth, Upgrade_textHeight);
	AEGfxPrint(fontID, Upgrade1_buffer, (getWinWidth() / (-2050.f * UpgradescaleX_settings)), (getWinHeight() / (-45000.f * UpgradescaleY_settings)), 0.8f * UpgradescaleX_settings, 255.f, 255.f, 0.f);

	//End of description text for Ship Model 2//


	// "Buy" Text for Ship Model 3
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxTextureSet(NULL, 0, 0);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	sprintf_s(Upgrade1_buffer, "BUY");
	AEGfxGetPrintSize(fontID, Upgrade1_buffer, 1.0f, Upgrade_textWidth, Upgrade_textHeight);
	AEGfxPrint(fontID, Upgrade1_buffer, (getWinWidth() / (-8900.f * UpgradescaleX_settings)), (getWinHeight() / (-3200.f * UpgradescaleY_settings)), 0.8f * UpgradescaleX_settings, 156.0f / 255.f, 205.0f / 255.f, 220.0f / 255.f);

	//Start of description text for Ship Model 3//

	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxTextureSet(NULL, 0, 0);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	sprintf_s(Upgrade1_buffer, "Model: Smaller");
	AEGfxGetPrintSize(fontID, Upgrade1_buffer, 1.0f, Upgrade_textWidth, Upgrade_textHeight);
	AEGfxPrint(fontID, Upgrade1_buffer, (getWinWidth() / (-2050.f * UpgradescaleX_settings)), (getWinHeight() / (-3900.f * UpgradescaleY_settings)), 0.8f * UpgradescaleX_settings, 156.0f / 255.f, 205.0f / 255.f, 220.0f / 255.f);

	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxTextureSet(NULL, 0, 0);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	sprintf_s(Upgrade1_buffer, "Cost:  $1000");
	AEGfxGetPrintSize(fontID, Upgrade1_buffer, 1.0f, Upgrade_textWidth, Upgrade_textHeight);
	AEGfxPrint(fontID, Upgrade1_buffer, (getWinWidth() / (-2050.f * UpgradescaleX_settings)), (getWinHeight() / (-2500.f * UpgradescaleY_settings)), 0.8f * UpgradescaleX_settings, 255.f, 255.f, 0.f);

	//End of description text for Ship Model 3//


	// "Buy" Text for Ship Model 4
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxTextureSet(NULL, 0, 0);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	sprintf_s(Upgrade1_buffer, "BUY");
	AEGfxGetPrintSize(fontID, Upgrade1_buffer, 1.0f, Upgrade_textWidth, Upgrade_textHeight);
	AEGfxPrint(fontID, Upgrade1_buffer, (getWinWidth() / (-8900.f * UpgradescaleX_settings)), (getWinHeight() / (-1450.f * UpgradescaleY_settings)), 0.8f * UpgradescaleX_settings, 156.0f / 255.f, 205.0f / 255.f, 220.0f / 255.f);

	//Start of description text for Ship Model 4//

	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxTextureSet(NULL, 0, 0);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	sprintf_s(Upgrade1_buffer, "Model: Smallest");
	AEGfxGetPrintSize(fontID, Upgrade1_buffer, 1.0f, Upgrade_textWidth, Upgrade_textHeight);
	AEGfxPrint(fontID, Upgrade1_buffer, (getWinWidth() / (-2050.f * UpgradescaleX_settings)), (getWinHeight() / (-1600.f * UpgradescaleY_settings)), 0.8f * UpgradescaleX_settings, 156.0f / 255.f, 205.0f / 255.f, 220.0f / 255.f);

	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxTextureSet(NULL, 0, 0);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	sprintf_s(Upgrade1_buffer, "Cost:  $3000");
	AEGfxGetPrintSize(fontID, Upgrade1_buffer, 1.0f, Upgrade_textWidth, Upgrade_textHeight);
	AEGfxPrint(fontID, Upgrade1_buffer, (getWinWidth() / (-2050.f * UpgradescaleX_settings)), (getWinHeight() / (-1300.f * UpgradescaleY_settings)), 0.8f * UpgradescaleX_settings, 255.f, 255.f, 0.f);

	//End of description text for Ship Model 4//






	// "Buy" Text for Stat 1
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxTextureSet(NULL, 0, 0);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	sprintf_s(Upgrade1_buffer, "BUY");
	AEGfxGetPrintSize(fontID, Upgrade1_buffer, 1.0f, Upgrade_textWidth, Upgrade_textHeight);
	AEGfxPrint(fontID, Upgrade1_buffer, (getWinWidth() / (+2840.f * UpgradescaleX_settings)), (getWinHeight() / (2300.f * UpgradescaleY_settings)), 0.8f * UpgradescaleX_settings, 156.0f / 255.f, 205.0f / 255.f, 220.0f / 255.f);




	AEGfxTextureUnload(coinTex);
	AEGfxTextureUnload(playership0Tex);
	AEGfxTextureUnload(playership1Tex);
	AEGfxTextureUnload(playership2Tex);
	AEGfxTextureUnload(playership3Tex);
	AEGfxTextureUnload(playerHPTex);
	

}
void Upgrade_Free(void) 
{

}
void Upgrade_Unload(void) 
{
	AEGfxMeshFree(pMeshUpgrade);
	AEGfxMeshFree(pMeshUpgrade1);
	AEGfxMeshFree(CoinMesh);
	AEGfxMeshFree(BuyButtonMesh);
	AEGfxMeshFree(ShipMesh);
}