#include "Upgrade.h"
#include "Main.h"

std::ifstream ifs{ "..\\..\\Assets\\SaveFiles\\Currency.txt" };
std::ifstream ifs1{ "..\\..\\Assets\\SaveFiles\\PlayerShipModel.txt" };

//bool LevelToggle;
//f32 Timer;

//Pointer to Mesh
AEGfxVertexList* pMeshUpgrade = nullptr;
AEGfxVertexList* pMeshUpgrade1 = nullptr;
AEGfxVertexList* CoinMesh = nullptr;
AEGfxVertexList* BuyButtonMesh = nullptr;

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

	//Open save file of money
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
	//End of Open save file of money
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

	if (IsAreaClicked((getWinHeight() / 2)+187.f, (getWinHeight() / 2)-130.f, 107.f * UpgradescaleX_settings, 100.f * UpgradescaleY_settings, cursorX, cursorY)
		&& AEInputCheckTriggered(AEVK_LBUTTON)) {
		
		
		std::ofstream outputStream{ "..\\..\\Assets\\SaveFiles\\Currency.txt" };
		std::ofstream outputStream1{ "..\\..\\Assets\\SaveFiles\\PlayerShipModel.txt" };
		if (Currency >=50)
		{
			Currency = Currency - 50;
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

}
void Upgrade_Draw(void) 
{

	
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
	AEMtx33Trans(&translate4, UpgradebackButton_transX-150, UpgradebackButton_transY+700);
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
	AEMtx33Trans(&translate5, UpgradeStatDisplay_transX - 330.f, UpgradeStatDisplay_transY - 210.f);
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
	AEMtx33Trans(&translate6, UpgradeStatDisplay_transX - 120.f, UpgradeStatDisplay_transY - 210.f);
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
	AEMtx33Trans(&translate7, UpgradeStatDisplay_transX - 123.5f, UpgradeStatDisplay_transY - 210.f);
	AEMtx33 transform7 = { 0 };
	AEMtx33Concat(&transform7, &rotate7, &scale7);
	AEMtx33Concat(&transform7, &translate7, &transform7);
	AEGfxSetTransform(transform7.m);
	AEGfxMeshDraw(pMeshUpgrade1, AE_GFX_MDM_TRIANGLES);



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
	AEGfxPrint(fontID, Upgrade1_buffer, (getWinWidth() / (-1960.f * UpgradescaleX_settings)), (getWinHeight() / (1450.f * UpgradescaleY_settings)), 0.8f * UpgradescaleX_settings, 156.0f / 255.f, 205.0f / 255.f, 220.0f / 255.f);


	// "Stats" Text
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxTextureSet(NULL, 0, 0);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	sprintf_s(Upgrade1_buffer, "Stats");
	AEGfxGetPrintSize(fontID, Upgrade1_buffer, 1.0f, Upgrade_textWidth, Upgrade_textHeight);
	AEGfxPrint(fontID, Upgrade1_buffer, (getWinWidth() / (6100.f * UpgradescaleX_settings)), (getWinHeight() / (1450.f * UpgradescaleY_settings)), 0.8f * UpgradescaleX_settings, 156.0f / 255.f, 205.0f / 255.f, 220.0f / 255.f);
	
	// "Buy" Text
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxTextureSet(NULL, 0, 0);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	sprintf_s(Upgrade1_buffer, "BUY");
	AEGfxGetPrintSize(fontID, Upgrade1_buffer, 1.0f, Upgrade_textWidth, Upgrade_textHeight);
	AEGfxPrint(fontID, Upgrade1_buffer, (getWinWidth() / (-6200.f * UpgradescaleX_settings)), (getWinHeight() / (2500.f * UpgradescaleY_settings)), 0.8f * UpgradescaleX_settings, 156.0f / 255.f, 205.0f / 255.f, 220.0f / 255.f);


	AEGfxTextureUnload(coinTex);

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
}