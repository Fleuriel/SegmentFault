/******************************************************************************/
/*!
\file		Upgrade.cpp
\project    Among Them
\author		Emery Quek Cheng Kwang, c.quek, 2201955
\par		c.quek@digipen.edu
\brief		This is a source file which contains functions and UI for purchasing
			ship models & player stat upgrades.

			Copyright (C) 2023 DigiPen Institute of Technology.
			Reproduction or disclosure of this file or its contents
			without the prior written consent of DigiPen Institute of
			Technology is prohibited.
 */
 /******************************************************************************/

#include "Upgrade.h"
#include "Main.h"


//bool LevelToggle;
//f32 Timer;


//Pointer to Mesh
AEGfxVertexList* pMeshUpgrade = nullptr;
AEGfxVertexList* pMeshUpgrade1 = nullptr;
AEGfxVertexList* CoinMesh = nullptr;
AEGfxVertexList* BuyButtonMesh = nullptr;
AEGfxVertexList* ShipMesh = nullptr;
AEGfxVertexList* BackgroundMesh = nullptr;


// Pre-definition for buttons
f32 UpgradebackButton_transX;
f32 UpgradebackButton_transY;
f32 UpgradeStatDisplay_transX;
f32 UpgradeStatDisplay_transY;

// Quit button mid point
f32 backButtonUpgrade_midX;
f32 backButtonUpgrade_midY;

// Pre-definition of scaling
f32 UpgradescaleX_settings;
f32 UpgradescaleY_settings;

// 
float Upgrade_textWidth{}, Upgrade_textHeight{};

char Upgrade1_buffer[1024]{};
bool CheckIfBoughtModel2 = false;
bool CheckIfBoughtModel3 = false;
bool CheckIfBoughtModel4 = false;


void Upgrade_Load(void) 
{
	std::ifstream ifs{ "Assets\\SaveFiles\\Currency.txt" };
	std::ifstream ifs1{ "Assets\\SaveFiles\\PlayerShipModel.txt" };
	std::ifstream ifs2{ "Assets\\SaveFiles\\PlayerStats.txt" };
	std::ifstream ifs3{ "Assets\\SaveFiles\\BoughtModels.txt" };

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

	BackgroundMesh = AEGfxMeshEnd();
	//end Background

	//Open save file of money
	if (ifs.good())
	{

		ifs >> Currency;
		ifs.close();
	}
	//End of Open save file of money

	//Open save file of ship
	if (ifs1.good())
	{

		ifs1 >> ShipModel;

		ifs1.close();
	}

	//End of Open save file of ship

	//Open save file of stats
	if (ifs2.good())
	{

		ifs2 >> MaximumPlayerHealth >> ProjectileSpeed_upgrade >> CD_upgrade >> Regen_upgrade;

		ifs2.close();
	}

	if (ifs3.good()) {
		ifs3 >> CheckIfBoughtModel2 >> CheckIfBoughtModel3 >> CheckIfBoughtModel4;
		ifs3.close();
	}
	//End of Open save file of stats

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
	// Initialize cursor coordinates
	s32 cursorX;
	s32 cursorY;
	AEInputGetCursorPosition(&cursorX, &cursorY);

	// Quit button mid point
	backButtonUpgrade_midX = static_cast<f32>((getWinWidth() / 2.08) + UpgradebackButton_transX);
	backButtonUpgrade_midY = static_cast<f32>((getWinHeight() / 2) - UpgradebackButton_transY);


	// if cursor within buttons, change game state
	if (IsAreaClicked(backButtonUpgrade_midX, backButtonUpgrade_midY, 150.0f * UpgradescaleX_settings, 100.0f * UpgradescaleY_settings, cursorX, cursorY)
		&& AEInputCheckReleased(AEVK_LBUTTON)) {
		gGameStateNext = MAINMENU;
	}


	//Purchase ship model 1
	if (IsAreaClicked((getWinHeight() / 2) + 274.f, (getWinHeight() / 2) - 173.f, 107.f * UpgradescaleX_settings, 100.f * UpgradescaleY_settings, cursorX, cursorY)
		&& AEInputCheckReleased(AEVK_LBUTTON)) {

		std::ofstream outputStream{ "Assets\\SaveFiles\\Currency.txt" };
		std::ofstream outputStream1{ "Assets\\SaveFiles\\PlayerShipModel.txt" };
		if (ShipModel != 0)
		{
			ShipModel = 0;		
		}

		outputStream << Currency;
		outputStream.close();
		outputStream1 << ShipModel;
		outputStream1.close();
	}

	//Purchase ship model 2
	if (IsAreaClicked((getWinHeight() / 2) + 274.f, (getWinHeight() / 2) -43.f, 107.f * UpgradescaleX_settings, 100.f * UpgradescaleY_settings, cursorX, cursorY)
		&& AEInputCheckReleased(AEVK_LBUTTON)) {

		std::ofstream outputStream{ "Assets\\SaveFiles\\Currency.txt" };
		std::ofstream outputStream1{ "Assets\\SaveFiles\\PlayerShipModel.txt" };

		
		if (Currency >= 200 && ShipModel!=1 && CheckIfBoughtModel2 == false)
		{
			Currency = Currency - 200;
			ShipModel = 1;
			outputStream << Currency;
			outputStream.close();
			outputStream1 << ShipModel;
			outputStream1.close();
			CheckIfBoughtModel2 = true;
		}
		else if (CheckIfBoughtModel2 == true && ShipModel != 1) {
			ShipModel = 1;
			outputStream1 << ShipModel;
			outputStream1.close();
		}

		outputStream.close();
		outputStream1.close();
	}

	//Purchase ship model 3
	if (IsAreaClicked((getWinHeight() / 2) + 274.f, (getWinHeight() / 2) +90.f, 107.f * UpgradescaleX_settings, 100.f * UpgradescaleY_settings, cursorX, cursorY)
		&& AEInputCheckReleased(AEVK_LBUTTON)) {

		std::ofstream outputStream{ "Assets\\SaveFiles\\Currency.txt" };
		std::ofstream outputStream1{ "Assets\\SaveFiles\\PlayerShipModel.txt" };

		if (Currency >= 1000 && ShipModel!=2 && CheckIfBoughtModel3 == false)
		{
			Currency = Currency - 1000;
			ShipModel = 2;
			outputStream << Currency;
			outputStream.close();
			outputStream1 << ShipModel;
			outputStream1.close();
			CheckIfBoughtModel3 = true;

		}
		else if (CheckIfBoughtModel3 == true && ShipModel != 2) {
			ShipModel = 2;
			outputStream1 << ShipModel;
			outputStream1.close();
		}
		outputStream.close();
		outputStream1.close();
	}

	//Purchase ship model 4
	if (IsAreaClicked((getWinHeight() / 2) + 274.f, (getWinHeight() / 2) + 221.f, 107.f * UpgradescaleX_settings, 100.f * UpgradescaleY_settings, cursorX, cursorY)
		&& AEInputCheckReleased(AEVK_LBUTTON)) {

		std::ofstream outputStream{ "Assets\\SaveFiles\\Currency.txt" };
		std::ofstream outputStream1{ "Assets\\SaveFiles\\PlayerShipModel.txt" };

		if (Currency >= 3000 && ShipModel!=3 && CheckIfBoughtModel4 == false)
		{
			Currency = Currency - 3000;
			ShipModel = 3;
			outputStream << Currency;
			outputStream.close();
			outputStream1 << ShipModel;
			outputStream1.close();
			CheckIfBoughtModel4 = true;
		}
		else if (CheckIfBoughtModel4 == true && ShipModel != 3) {
			ShipModel = 3;
			outputStream1 << ShipModel;
			outputStream1.close();
		}
		outputStream.close();
		outputStream1.close();
	}





	//Purchase Max HP
	if (IsAreaClicked((getWinHeight() / 2) + 784.f, (getWinHeight() / 2) - 173.f, 107.f * UpgradescaleX_settings, 100.f * UpgradescaleY_settings, cursorX, cursorY)
		&& AEInputCheckReleased(AEVK_LBUTTON)) {
		
		if (Currency >= 300)
		{
			Currency = Currency - 300;
			MaximumPlayerHealth++;

		}
		
	}


	//Purchase Bullet speed
	if (IsAreaClicked((getWinHeight() / 2) + 784.f, (getWinHeight() / 2) - 43.f, 107.f * UpgradescaleX_settings, 100.f * UpgradescaleY_settings, cursorX, cursorY)
		&& AEInputCheckReleased(AEVK_LBUTTON)) {

		if (Currency >= 300 && ProjectileSpeed_upgrade != 10)
		{
			Currency = Currency - 300;
			ProjectileSpeed_upgrade++;
		}

	}

	//Purchase Cooldown reduction
	if (IsAreaClicked((getWinHeight() / 2) + 784.f, (getWinHeight() / 2) + 90.f, 107.f * UpgradescaleX_settings, 100.f * UpgradescaleY_settings, cursorX, cursorY)
		&& AEInputCheckReleased(AEVK_LBUTTON)) {

		if (Currency >= 400 && CD_upgrade != 10)
		{
			Currency = Currency - 400;
			CD_upgrade++;
		}
	}
	

	//Purchase HP regen
	if (IsAreaClicked((getWinHeight() / 2) + 784.f, (getWinHeight() / 2) + 221.f, 107.f * UpgradescaleX_settings, 100.f * UpgradescaleY_settings, cursorX, cursorY)
		&& AEInputCheckReleased(AEVK_LBUTTON)) {



		if (Currency >= 800 && Regen_upgrade != 10)
		{
			Currency = Currency - 800;
			Regen_upgrade++;
		}

	}

}
void Upgrade_Draw(void) 
{
	//Background
	AEGfxTexture* BGtexture = AEGfxTextureLoad("Assets\\Assets\\MainMenuBackground.png");

	//Draw Background
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetTintColor(0.8f, 0.8f, 0.8f, 0.8f);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetTransparency(1.0f);
	AEGfxTextureSet(BGtexture, 0, 0);
	AEMtx33 scale0 = { 0 };
	AEMtx33Scale(&scale0, 1100, 800);
	AEMtx33 rotate0 = { 0 };
	AEMtx33Rot(&rotate0, 0.f);
	AEMtx33 translate0 = { 0 };
	AEMtx33Trans(&translate0, BGtransX, BGtransY);
	AEMtx33 transform0 = { 0 };
	AEMtx33Concat(&transform0, &rotate0, &scale0);
	AEMtx33Concat(&transform0, &translate0, &transform0);
	AEGfxSetTransform(transform0.m);
	AEGfxMeshDraw(BackgroundMesh, AE_GFX_MDM_TRIANGLES);
	//Finish Background draw

	AEGfxTextureUnload(BGtexture);


	//Text display for current ship
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxTextureSet(NULL, 0, 0);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	sprintf_s(Upgrade1_buffer, "Current ship model: %d", ShipModel+1);
	AEGfxGetPrintSize(fontID, Upgrade1_buffer, 1.0f, Upgrade_textWidth, Upgrade_textHeight);
	AEGfxPrint(fontID, Upgrade1_buffer, (getWinWidth() / (-4000.f * UpgradescaleX_settings)), (getWinHeight() / (-800.f * UpgradescaleY_settings)), 0.8f * UpgradescaleX_settings, 156.0f / 255.f, 205.0f / 255.f, 220.0f / 255.f);






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


	//Projectile image display
	AEGfxTexture* ProjectileTex = AEGfxTextureLoad("Assets\\Assets\\Bulletspeed.png");

	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetTransparency(1.0f);
	AEGfxTextureSet(ProjectileTex, 0, 0);
	AEMtx33 scale30 = { 0 };
	AEMtx33Scale(&scale30, 55, 70);
	AEMtx33 rotate30 = { 0 };
	AEMtx33Rot(&rotate30, 0.f);
	AEMtx33 translate30 = { 0 };
	AEMtx33Trans(&translate30, UpgradebackButton_transX - 670, UpgradebackButton_transY + 455);
	AEMtx33 transform30 = { 0 };
	AEMtx33Concat(&transform30, &rotate30, &scale30);
	AEMtx33Concat(&transform30, &translate30, &transform30);
	AEGfxSetTransform(transform30.m);
	AEGfxMeshDraw(ShipMesh, AE_GFX_MDM_TRIANGLES);

	//Projectile image display
	AEGfxTexture* CooldownTex = AEGfxTextureLoad("Assets\\Assets\\Cooldown.png");

	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetTransparency(1.0f);
	AEGfxTextureSet(CooldownTex, 0, 0);
	AEMtx33 scale31 = { 0 };
	AEMtx33Scale(&scale31, 55, 70);
	AEMtx33 rotate31 = { 0 };
	AEMtx33Rot(&rotate31, 0.f);
	AEMtx33 translate31 = { 0 };
	AEMtx33Trans(&translate31, UpgradebackButton_transX - 670, UpgradebackButton_transY + 325);
	AEMtx33 transform31 = { 0 };
	AEMtx33Concat(&transform31, &rotate31, &scale31);
	AEMtx33Concat(&transform31, &translate31, &transform31);
	AEGfxSetTransform(transform31.m);
	AEGfxMeshDraw(ShipMesh, AE_GFX_MDM_TRIANGLES);

	//iframe image display
	AEGfxTexture* iframeTex = AEGfxTextureLoad("Assets\\Assets\\HealthRegen.png");

	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetTransparency(1.0f);
	AEGfxTextureSet(iframeTex, 0, 0);
	AEMtx33 scale32 = { 0 };
	AEMtx33Scale(&scale32, 55, 70);
	AEMtx33 rotate32 = { 0 };
	AEMtx33Rot(&rotate32, 0.f);
	AEMtx33 translate32 = { 0 };
	AEMtx33Trans(&translate32, UpgradebackButton_transX - 670, UpgradebackButton_transY + 195);
	AEMtx33 transform32 = { 0 };
	AEMtx33Concat(&transform32, &rotate32, &scale32);
	AEMtx33Concat(&transform32, &translate32, &transform32);
	AEGfxSetTransform(transform32.m);
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
	sprintf_s(Upgrade1_buffer, "SWAP");
	AEGfxGetPrintSize(fontID, Upgrade1_buffer, 1.0f, Upgrade_textWidth, Upgrade_textHeight);
	AEGfxPrint(fontID, Upgrade1_buffer, (getWinWidth() / (-8900.f * UpgradescaleX_settings)), (getWinHeight() / (2300.f * UpgradescaleY_settings)), 0.7f * UpgradescaleX_settings, 156.0f / 255.f, 205.0f / 255.f, 220.0f / 255.f);



	//Start of description text for Ship Model 1//

	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxTextureSet(NULL, 0, 0);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	sprintf_s(Upgrade1_buffer, "Model: AA-Mark 1");
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
	if (CheckIfBoughtModel2 == false) {
		AEGfxSetRenderMode(AE_GFX_RM_COLOR);
		AEGfxTextureSet(NULL, 0, 0);
		AEGfxSetBlendMode(AE_GFX_BM_BLEND);
		sprintf_s(Upgrade1_buffer, "BUY");
		AEGfxGetPrintSize(fontID, Upgrade1_buffer, 1.0f, Upgrade_textWidth, Upgrade_textHeight);
		AEGfxPrint(fontID, Upgrade1_buffer, (getWinWidth() / (-8900.f * UpgradescaleX_settings)), (getWinHeight() / (15000.f * UpgradescaleY_settings)), 0.8f * UpgradescaleX_settings, 156.0f / 255.f, 205.0f / 255.f, 220.0f / 255.f);
	}

	else {
		AEGfxSetRenderMode(AE_GFX_RM_COLOR);
		AEGfxTextureSet(NULL, 0, 0);
		AEGfxSetBlendMode(AE_GFX_BM_BLEND);
		sprintf_s(Upgrade1_buffer, "SWAP");
		AEGfxGetPrintSize(fontID, Upgrade1_buffer, 1.0f, Upgrade_textWidth, Upgrade_textHeight);
		AEGfxPrint(fontID, Upgrade1_buffer, (getWinWidth() / (-8900.f * UpgradescaleX_settings)), (getWinHeight() / (15000 * UpgradescaleY_settings)), 0.7f * UpgradescaleX_settings, 156.0f / 255.f, 205.0f / 255.f, 220.0f / 255.f);
	}

	//Start of description text for Ship Model 2//

	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxTextureSet(NULL, 0, 0);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	sprintf_s(Upgrade1_buffer, "Model: AT-Mark 2");
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
	if (CheckIfBoughtModel3 == false) {
		AEGfxSetRenderMode(AE_GFX_RM_COLOR);
		AEGfxTextureSet(NULL, 0, 0);
		AEGfxSetBlendMode(AE_GFX_BM_BLEND);
		sprintf_s(Upgrade1_buffer, "BUY");
		AEGfxGetPrintSize(fontID, Upgrade1_buffer, 1.0f, Upgrade_textWidth, Upgrade_textHeight);
		AEGfxPrint(fontID, Upgrade1_buffer, (getWinWidth() / (-8900.f * UpgradescaleX_settings)), (getWinHeight() / (-3200.f * UpgradescaleY_settings)), 0.8f * UpgradescaleX_settings, 156.0f / 255.f, 205.0f / 255.f, 220.0f / 255.f);
	}
	else {
		AEGfxSetRenderMode(AE_GFX_RM_COLOR);
		AEGfxTextureSet(NULL, 0, 0);
		AEGfxSetBlendMode(AE_GFX_BM_BLEND);
		sprintf_s(Upgrade1_buffer, "SWAP");
		AEGfxGetPrintSize(fontID, Upgrade1_buffer, 1.0f, Upgrade_textWidth, Upgrade_textHeight);
		AEGfxPrint(fontID, Upgrade1_buffer, (getWinWidth() / (-8900.f * UpgradescaleX_settings)), (getWinHeight() / (-3200.f * UpgradescaleY_settings)), 0.7f * UpgradescaleX_settings, 156.0f / 255.f, 205.0f / 255.f, 220.0f / 255.f);
	}


	//Start of description text for Ship Model 3//

	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxTextureSet(NULL, 0, 0);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	sprintf_s(Upgrade1_buffer, "Model: ZP-Mark 3");
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
	if (CheckIfBoughtModel4 == false) {
		AEGfxSetRenderMode(AE_GFX_RM_COLOR);
		AEGfxTextureSet(NULL, 0, 0);
		AEGfxSetBlendMode(AE_GFX_BM_BLEND);
		sprintf_s(Upgrade1_buffer, "BUY");
		AEGfxGetPrintSize(fontID, Upgrade1_buffer, 1.0f, Upgrade_textWidth, Upgrade_textHeight);
		AEGfxPrint(fontID, Upgrade1_buffer, (getWinWidth() / (-8900.f * UpgradescaleX_settings)), (getWinHeight() / (-1450.f * UpgradescaleY_settings)), 0.8f * UpgradescaleX_settings, 156.0f / 255.f, 205.0f / 255.f, 220.0f / 255.f);
	}
	else{
		AEGfxSetRenderMode(AE_GFX_RM_COLOR);
		AEGfxTextureSet(NULL, 0, 0);
		AEGfxSetBlendMode(AE_GFX_BM_BLEND);
		sprintf_s(Upgrade1_buffer, "SWAP");
		AEGfxGetPrintSize(fontID, Upgrade1_buffer, 1.0f, Upgrade_textWidth, Upgrade_textHeight);
		AEGfxPrint(fontID, Upgrade1_buffer, (getWinWidth() / (-8900.f * UpgradescaleX_settings)), (getWinHeight() / (-1450.f * UpgradescaleY_settings)), 0.7f * UpgradescaleX_settings, 156.0f / 255.f, 205.0f / 255.f, 220.0f / 255.f);
	}

	//Start of description text for Ship Model 4//

	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxTextureSet(NULL, 0, 0);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	sprintf_s(Upgrade1_buffer, "Model: XJ-Mark 4");
	AEGfxGetPrintSize(fontID, Upgrade1_buffer, 1.0f, Upgrade_textWidth, Upgrade_textHeight);
	AEGfxPrint(fontID, Upgrade1_buffer, (getWinWidth() / (-2050.f * UpgradescaleX_settings)), (getWinHeight() / (-1600.f * UpgradescaleY_settings)), 0.8f * UpgradescaleX_settings, 156.0f / 255.f, 205.0f / 255.f, 220.0f / 255.f);

	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxTextureSet(NULL, 0, 0);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	sprintf_s(Upgrade1_buffer, "Cost:  $3000");
	AEGfxGetPrintSize(fontID, Upgrade1_buffer, 1.0f, Upgrade_textWidth, Upgrade_textHeight);
	AEGfxPrint(fontID, Upgrade1_buffer, (getWinWidth() / (-2050.f * UpgradescaleX_settings)), (getWinHeight() / (-1300.f * UpgradescaleY_settings)), 0.8f * UpgradescaleX_settings, 255.f, 255.f, 0.f);

	//End of description text for Ship Model 4//



	// Stat 2 Purchase box1
	AEGfxTextureSet(NULL, 0, 0);
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEMtx33 scale33 = { 0 };
	AEMtx33Scale(&scale33, 65.f * UpgradescaleX_settings, 100.f * UpgradescaleY_settings);
	AEMtx33 rotate33 = { 0 };
	AEMtx33Rot(&rotate33, 0.f);
	AEMtx33 translate33 = { 0 };
	AEMtx33Trans(&translate33, UpgradeStatDisplay_transX + 422.f, UpgradeStatDisplay_transY - 360.f);
	AEMtx33 transform33 = { 0 };
	AEMtx33Concat(&transform33, &rotate33, &scale33);
	AEMtx33Concat(&transform33, &translate33, &transform33);
	AEGfxSetTransform(transform33.m);
	AEGfxMeshDraw(BuyButtonMesh, AE_GFX_MDM_TRIANGLES);

	// Stat 2 Purchase box2
	AEGfxTextureSet(NULL, 0, 0);
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEMtx33 scale34 = { 0 };
	AEMtx33Scale(&scale34, 55.f * UpgradescaleX_settings, 85.f * UpgradescaleY_settings);
	AEMtx33 rotate34 = { 0 };
	AEMtx33Rot(&rotate34, 0.f);
	AEMtx33 translate34 = { 0 };
	AEMtx33Trans(&translate34, UpgradeStatDisplay_transX +417.f, UpgradeStatDisplay_transY - 360.f);
	AEMtx33 transform34 = { 0 };
	AEMtx33Concat(&transform34, &rotate34, &scale34);
	AEMtx33Concat(&transform34, &translate34, &transform34);
	AEGfxSetTransform(transform34.m);
	AEGfxMeshDraw(pMeshUpgrade1, AE_GFX_MDM_TRIANGLES);


	// Stat 3 Purchase box1
	AEGfxTextureSet(NULL, 0, 0);
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEMtx33 scale35 = { 0 };
	AEMtx33Scale(&scale35, 65.f * UpgradescaleX_settings, 100.f * UpgradescaleY_settings);
	AEMtx33 rotate35 = { 0 };
	AEMtx33Rot(&rotate35, 0.f);
	AEMtx33 translate35 = { 0 };
	AEMtx33Trans(&translate35, UpgradeStatDisplay_transX + 422.f, UpgradeStatDisplay_transY - 490.f);
	AEMtx33 transform35 = { 0 };
	AEMtx33Concat(&transform35, &rotate35, &scale35);
	AEMtx33Concat(&transform35, &translate35, &transform35);
	AEGfxSetTransform(transform35.m);
	AEGfxMeshDraw(BuyButtonMesh, AE_GFX_MDM_TRIANGLES);

	// Stat 3 Purchase box2
	AEGfxTextureSet(NULL, 0, 0);
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEMtx33 scale36 = { 0 };
	AEMtx33Scale(&scale36, 55.f * UpgradescaleX_settings, 85.f * UpgradescaleY_settings);
	AEMtx33 rotate36 = { 0 };
	AEMtx33Rot(&rotate36, 0.f);
	AEMtx33 translate36 = { 0 };
	AEMtx33Trans(&translate36, UpgradeStatDisplay_transX +417.f, UpgradeStatDisplay_transY - 490.f);
	AEMtx33 transform36 = { 0 };
	AEMtx33Concat(&transform36, &rotate36, &scale36);
	AEMtx33Concat(&transform36, &translate36, &transform36);
	AEGfxSetTransform(transform36.m);
	AEGfxMeshDraw(pMeshUpgrade1, AE_GFX_MDM_TRIANGLES);


	// Stat 4 Purchase box1
	AEGfxTextureSet(NULL, 0, 0);
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEMtx33 scale37 = { 0 };
	AEMtx33Scale(&scale37, 65.f * UpgradescaleX_settings, 100.f * UpgradescaleY_settings);
	AEMtx33 rotate37 = { 0 };
	AEMtx33Rot(&rotate37, 0.f);
	AEMtx33 translate37 = { 0 };
	AEMtx33Trans(&translate37, UpgradeStatDisplay_transX +422.f, UpgradeStatDisplay_transY - 620.f);
	AEMtx33 transform37 = { 0 };
	AEMtx33Concat(&transform37, &rotate37, &scale37);
	AEMtx33Concat(&transform37, &translate37, &transform37);
	AEGfxSetTransform(transform37.m);
	AEGfxMeshDraw(BuyButtonMesh, AE_GFX_MDM_TRIANGLES);

	// Stat 4 Purchase box2
	AEGfxTextureSet(NULL, 0, 0);
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEMtx33 scale38 = { 0 };
	AEMtx33Scale(&scale38, 55.f * UpgradescaleX_settings, 85.f * UpgradescaleY_settings);
	AEMtx33 rotate38 = { 0 };
	AEMtx33Rot(&rotate38, 0.f);
	AEMtx33 translate38 = { 0 };
	AEMtx33Trans(&translate38, UpgradeStatDisplay_transX +417.f, UpgradeStatDisplay_transY - 620.f);
	AEMtx33 transform38 = { 0 };
	AEMtx33Concat(&transform38, &rotate38, &scale38);
	AEMtx33Concat(&transform38, &translate38, &transform38);
	AEGfxSetTransform(transform38.m);
	AEGfxMeshDraw(pMeshUpgrade1, AE_GFX_MDM_TRIANGLES);







	// "Buy" Text for Stat 1
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxTextureSet(NULL, 0, 0);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	sprintf_s(Upgrade1_buffer, "BUY");
	AEGfxGetPrintSize(fontID, Upgrade1_buffer, 1.0f, Upgrade_textWidth, Upgrade_textHeight);
	AEGfxPrint(fontID, Upgrade1_buffer, (getWinWidth() / (+2840.f * UpgradescaleX_settings)), (getWinHeight() / (2300.f * UpgradescaleY_settings)), 0.8f * UpgradescaleX_settings, 156.0f / 255.f, 205.0f / 255.f, 220.0f / 255.f);


	// "Buy" Text for Stat 2
	if (ProjectileSpeed_upgrade != 10) {
		AEGfxSetRenderMode(AE_GFX_RM_COLOR);
		AEGfxTextureSet(NULL, 0, 0);
		AEGfxSetBlendMode(AE_GFX_BM_BLEND);
		sprintf_s(Upgrade1_buffer, "BUY");
		AEGfxGetPrintSize(fontID, Upgrade1_buffer, 1.0f, Upgrade_textWidth, Upgrade_textHeight);
		AEGfxPrint(fontID, Upgrade1_buffer, (getWinWidth() / (+2840.f * UpgradescaleX_settings)), (getWinHeight() / (15000.f * UpgradescaleY_settings)), 0.8f * UpgradescaleX_settings, 156.0f / 255.f, 205.0f / 255.f, 220.0f / 255.f);
	}
	else {
		AEGfxSetRenderMode(AE_GFX_RM_COLOR);
		AEGfxTextureSet(NULL, 0, 0);
		AEGfxSetBlendMode(AE_GFX_BM_BLEND);
		sprintf_s(Upgrade1_buffer, "MAX");
		AEGfxGetPrintSize(fontID, Upgrade1_buffer, 1.0f, Upgrade_textWidth, Upgrade_textHeight);
		AEGfxPrint(fontID, Upgrade1_buffer, (getWinWidth() / (+2840.f * UpgradescaleX_settings)), (getWinHeight() / (15000.f * UpgradescaleY_settings)), 0.8f * UpgradescaleX_settings, 156.0f / 255.f, 205.0f / 255.f, 220.0f / 255.f);
	}

	// "Buy" Text for Stat 3
	if (CD_upgrade != 10) {
		AEGfxSetRenderMode(AE_GFX_RM_COLOR);
		AEGfxTextureSet(NULL, 0, 0);
		AEGfxSetBlendMode(AE_GFX_BM_BLEND);
		sprintf_s(Upgrade1_buffer, "BUY");
		AEGfxGetPrintSize(fontID, Upgrade1_buffer, 1.0f, Upgrade_textWidth, Upgrade_textHeight);
		AEGfxPrint(fontID, Upgrade1_buffer, (getWinWidth() / (+2840.f * UpgradescaleX_settings)), (getWinHeight() / (-3200.f * UpgradescaleY_settings)), 0.8f * UpgradescaleX_settings, 156.0f / 255.f, 205.0f / 255.f, 220.0f / 255.f);
	}
	else {
		AEGfxSetRenderMode(AE_GFX_RM_COLOR);
		AEGfxTextureSet(NULL, 0, 0);
		AEGfxSetBlendMode(AE_GFX_BM_BLEND);
		sprintf_s(Upgrade1_buffer, "MAX");
		AEGfxGetPrintSize(fontID, Upgrade1_buffer, 1.0f, Upgrade_textWidth, Upgrade_textHeight);
		AEGfxPrint(fontID, Upgrade1_buffer, (getWinWidth() / (+2840.f * UpgradescaleX_settings)), (getWinHeight() / (-3200.f * UpgradescaleY_settings)), 0.8f * UpgradescaleX_settings, 156.0f / 255.f, 205.0f / 255.f, 220.0f / 255.f);
	}
	// "Buy" Text for Stat 4
	if (Regen_upgrade != 10) {
		AEGfxSetRenderMode(AE_GFX_RM_COLOR);
		AEGfxTextureSet(NULL, 0, 0);
		AEGfxSetBlendMode(AE_GFX_BM_BLEND);
		sprintf_s(Upgrade1_buffer, "BUY");
		AEGfxGetPrintSize(fontID, Upgrade1_buffer, 1.0f, Upgrade_textWidth, Upgrade_textHeight);
		AEGfxPrint(fontID, Upgrade1_buffer, (getWinWidth() / (+2840.f * UpgradescaleX_settings)), (getWinHeight() / (-1450.f * UpgradescaleY_settings)), 0.8f * UpgradescaleX_settings, 156.0f / 255.f, 205.0f / 255.f, 220.0f / 255.f);
	}
	else {
		AEGfxSetRenderMode(AE_GFX_RM_COLOR);
		AEGfxTextureSet(NULL, 0, 0);
		AEGfxSetBlendMode(AE_GFX_BM_BLEND);
		sprintf_s(Upgrade1_buffer, "MAX");
		AEGfxGetPrintSize(fontID, Upgrade1_buffer, 1.0f, Upgrade_textWidth, Upgrade_textHeight);
		AEGfxPrint(fontID, Upgrade1_buffer, (getWinWidth() / (+2840.f * UpgradescaleX_settings)), (getWinHeight() / (-1450.f * UpgradescaleY_settings)), 0.8f * UpgradescaleX_settings, 156.0f / 255.f, 205.0f / 255.f, 220.0f / 255.f);
	}
	//Start of description text for Stat 2//

	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxTextureSet(NULL, 0, 0);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	sprintf_s(Upgrade1_buffer, "Bullet Spd");
	AEGfxGetPrintSize(fontID, Upgrade1_buffer, 1.0f, Upgrade_textWidth, Upgrade_textHeight);
	AEGfxPrint(fontID, Upgrade1_buffer, (getWinWidth() / (9300.f * UpgradescaleX_settings)), (getWinHeight() / (7500.f * UpgradescaleY_settings)), 0.8f * UpgradescaleX_settings, 156.0f / 255.f, 205.0f / 255.f, 220.0f / 255.f);

	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxTextureSet(NULL, 0, 0);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	sprintf_s(Upgrade1_buffer, "Cost: $300");
	AEGfxGetPrintSize(fontID, Upgrade1_buffer, 1.0f, Upgrade_textWidth, Upgrade_textHeight);
	AEGfxPrint(fontID, Upgrade1_buffer, (getWinWidth() / (9300.f * UpgradescaleX_settings)), (getWinHeight() / (-45000.f * UpgradescaleY_settings)), 0.8f * UpgradescaleX_settings, 255.f, 255.f, 0.f);

	//End of description text for Stat 2//



	//Start of description text for Stat 3//

	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxTextureSet(NULL, 0, 0);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	sprintf_s(Upgrade1_buffer, "- Cooldown");
	AEGfxGetPrintSize(fontID, Upgrade1_buffer, 1.0f, Upgrade_textWidth, Upgrade_textHeight);
	AEGfxPrint(fontID, Upgrade1_buffer, (getWinWidth() / (9300.f * UpgradescaleX_settings)), (getWinHeight() / (-3900.f * UpgradescaleY_settings)), 0.8f * UpgradescaleX_settings, 156.0f / 255.f, 205.0f / 255.f, 220.0f / 255.f);

	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxTextureSet(NULL, 0, 0);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	sprintf_s(Upgrade1_buffer, "Cost: $400");
	AEGfxGetPrintSize(fontID, Upgrade1_buffer, 1.0f, Upgrade_textWidth, Upgrade_textHeight);
	AEGfxPrint(fontID, Upgrade1_buffer, (getWinWidth() / (9300.f * UpgradescaleX_settings)), (getWinHeight() / (-2500.f * UpgradescaleY_settings)), 0.8f * UpgradescaleX_settings, 255.f, 255.f, 0.f);

	//End of description text for Stat 3//


	//Start of description text for Stat 4//

	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxTextureSet(NULL, 0, 0);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	sprintf_s(Upgrade1_buffer, "HP Regen");
	AEGfxGetPrintSize(fontID, Upgrade1_buffer, 1.0f, Upgrade_textWidth, Upgrade_textHeight);
	AEGfxPrint(fontID, Upgrade1_buffer, (getWinWidth() / (9300.f * UpgradescaleX_settings)), (getWinHeight() / (-1600.f * UpgradescaleY_settings)), 0.8f * UpgradescaleX_settings, 156.0f / 255.f, 205.0f / 255.f, 220.0f / 255.f);

	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxTextureSet(NULL, 0, 0);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	sprintf_s(Upgrade1_buffer, "Cost: $800");
	AEGfxGetPrintSize(fontID, Upgrade1_buffer, 1.0f, Upgrade_textWidth, Upgrade_textHeight);
	AEGfxPrint(fontID, Upgrade1_buffer, (getWinWidth() / (9300.f * UpgradescaleX_settings)), (getWinHeight() / (-1300.f * UpgradescaleY_settings)), 0.8f * UpgradescaleX_settings, 255.f, 255.f, 0.f);

	//End of description text for Stat 4//








	AEGfxTextureUnload(coinTex);
	AEGfxTextureUnload(playership0Tex);
	AEGfxTextureUnload(playership1Tex);
	AEGfxTextureUnload(playership2Tex);
	AEGfxTextureUnload(playership3Tex);
	AEGfxTextureUnload(playerHPTex);
	AEGfxTextureUnload(ProjectileTex);
	AEGfxTextureUnload(CooldownTex);
	AEGfxTextureUnload(iframeTex);
	

}
void Upgrade_Free(void) 
{

}
void Upgrade_Unload(void) 
{
	std::ofstream outputStream2{ "Assets\\SaveFiles\\BoughtModels.txt" };
	if (CheckIfBoughtModel2 == true)
		outputStream2 << "1 " << std::endl;
	else
		outputStream2 << "0 " << std::endl;
	if (CheckIfBoughtModel3 == true)
		outputStream2 << "1 " << std::endl;
	else
		outputStream2 << "0 " << std::endl;
	if (CheckIfBoughtModel4 == true)
		outputStream2 << "1 " << std::endl;
	else
		outputStream2 << "0 " << std::endl;
	std::ofstream outputStream{ "Assets\\SaveFiles\\Currency.txt" };
	std::ofstream outputStream1{ "Assets\\SaveFiles\\PlayerStats.txt" };

	outputStream << Currency;
	outputStream.close();
	outputStream1 <<MaximumPlayerHealth<<std::endl<< ProjectileSpeed_upgrade << std::endl << CD_upgrade << std::endl <<Regen_upgrade << std::endl;
	outputStream1.close();
	outputStream2.close();
	AEGfxMeshFree(pMeshUpgrade);
	AEGfxMeshFree(pMeshUpgrade1);
	AEGfxMeshFree(CoinMesh);
	AEGfxMeshFree(BuyButtonMesh);
	AEGfxMeshFree(ShipMesh);
	AEGfxMeshFree(BackgroundMesh);
}