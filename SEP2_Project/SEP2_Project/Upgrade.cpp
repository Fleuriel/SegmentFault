#include "Upgrade.h"
#include "Main.h"

//bool LevelToggle;
//f32 Timer;

//Pointer to Mesh
AEGfxVertexList* pMeshUpgrade = nullptr;

// Pre-definition for translations of buttons
double UpgradebackButton_transX;
double UpgradebackButton_transY;

// Pre-definition of scaling
double UpgradescaleX_settings;
double UpgradescaleY_settings;

// 
float Upgrade_textWidth{}, Upgrade_textHeight{};

char Upgrade1_buffer[1024]{};

void Upgrade_Load(void) 
{
	std::cout << "Upgrade_Load\n";
	AEGfxSetBackgroundColor(0.329f, 0.408f, 0.471f);

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

	printf("%d\n%d\n", cursorX, cursorY);  //debug
	//printf("%f\n%f\n", button1_midX, button1_midY);  //debug
	// if cursor within buttons, change game state
	if (IsAreaClicked(backButton_midX, backButton_midY, 150.0f * UpgradescaleX_settings, 100.0f * UpgradescaleY_settings, cursorX, cursorY)
		&& AEInputCheckTriggered(AEVK_LBUTTON)) {
		gGameStateNext = MAINMENU;
		printf("MAINMENU\n");
	}

}
void Upgrade_Draw(void) 
{
	// Back button
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

	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxTextureSet(NULL, 0, 0);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	sprintf_s(Upgrade1_buffer, "Back");
	AEGfxGetPrintSize(fontID, Upgrade1_buffer, 1.0f, Upgrade_textWidth, Upgrade_textHeight);
	AEGfxPrint(fontID, Upgrade1_buffer, (getWinWidth() / (1655.f * UpgradescaleX_settings)), (getWinHeight() / (-798.f * UpgradescaleY_settings)), 0.8f * UpgradescaleX_settings, 156.0f / 255.f, 205.0f / 255.f, 220.0f / 255.f);

	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxTextureSet(NULL, 0, 0);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	sprintf_s(Upgrade1_buffer, "Upgrades");
	AEGfxGetPrintSize(fontID, Upgrade1_buffer, 1.0f, Upgrade_textWidth, Upgrade_textHeight);
	AEGfxPrint(fontID, Upgrade1_buffer, (getWinWidth() / (-9000.f * UpgradescaleX_settings)), (getWinHeight() / (900.f * UpgradescaleY_settings)), 0.8f * UpgradescaleX_settings, 156.0f / 255.f, 205.0f / 255.f, 220.0f / 255.f);
}
void Upgrade_Free(void) 
{

}
void Upgrade_Unload(void) 
{
	AEGfxMeshFree(pMeshUpgrade);
}