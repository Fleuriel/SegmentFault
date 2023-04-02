#include "GameOverMenu.h"
#include "Main.h"

// Pointer to Mesh
AEGfxVertexList* pMeshGameOver = nullptr;

// Background Declarations
AEGfxVertexList* gameOverbMesh = nullptr;
AEGfxTexture* gameOverBGTex;

// Pre-defintion
char gameOver_buffer[1024]{};
char gameOverCont_buffer[1024]{};
char gameOverQuit_buffer[1024]{};
float gameOver_textWidth{}, gameOver_textHeight{};

// Pre-definition for buttons
f32 gameOverContButton_transX;
f32 gameOverContButton_transY;
f32 gameOverQuitButton_transX;
f32 gameOverQuitButton_transY;

// Continue button mid points
f32 gameOverContButton_midX;
f32 gameOverContButton_midY;

// Quit button mid points
f32 gameOverQuitButton_midX;
f32 gameOverQuitButton_midY;


void GameOver_Load(void) 
{

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

	gameOverbMesh = AEGfxMeshEnd();
	gameOverBGTex = AEGfxTextureLoad("Assets\\Assets\\Background.png");
	//end Background

	// Create buttons
	AEGfxMeshStart();

	AEGfxTriAdd(
		0.5f, 0.5f, 0xFF000000, 1.0f, 0.0f,
		-1.2f, -0.5f, 0xFF000000, 0.0f, 1.0f,
		0.5f, -0.5f, 0xFF000000, 1.0f, 1.0f);
	AEGfxTriAdd(
		-1.2f, 0.5f, 0xFF000000, 0.0f, 0.0f,
		-1.2f, -0.5f, 0xFF000000, 0.0f, 1.0f,
		0.5f, 0.5f, 0xFF000000, 1.0f, 0.0f);

	pMeshGameOver = AEGfxMeshEnd();

}

void GameOver_Init(void) 
{
	// Gets the scale of 1366x768
	scaleX = getWinWidth() / 1366.f;
	scaleY = getWinHeight() / 768.f;

	// Continue button translation
	gameOverContButton_transX = 30.f * scaleX;
	gameOverContButton_transY = 0.f * scaleY;

	// Quit button translation
	gameOverQuitButton_transX = 30.f * scaleX;
	gameOverQuitButton_transY = -100.f * scaleY;

}

void GameOver_Update(void) 
{

	// Initialize cursor coordinates
	s32 cursorX;
	s32 cursorY;
	AEInputGetCursorPosition(&cursorX, &cursorY);

	// Continue button mid points
	gameOverContButton_midX = static_cast<f32>((getWinWidth() / 2.11) + gameOverContButton_transX);
	gameOverContButton_midY = static_cast<f32>((getWinHeight() / 2) - gameOverContButton_transY);

	// Quit button mid points
	gameOverQuitButton_midX = static_cast<f32>((getWinWidth() / 2.11) + gameOverQuitButton_transX);
	gameOverQuitButton_midY = static_cast<f32>((getWinHeight() / 2) - gameOverQuitButton_transY);

	printf("%d\n%d\n", cursorX, cursorY);  //debug

	// if cursor within buttons, change game state
	if (IsAreaClicked(gameOverContButton_midX, gameOverContButton_midY, 170.0f * scaleX, 50.0f * scaleY, cursorX, cursorY)
		&& AEInputCheckTriggered(AEVK_LBUTTON)) {
		gGameStateNext = PLAY;
		printf("Goto Play\n");
	}
	else if (IsAreaClicked(gameOverQuitButton_midX, gameOverQuitButton_midY, 170.0f * scaleX, 50.0f * scaleY, cursorX, cursorY)
		&& AEInputCheckTriggered(AEVK_LBUTTON)) {
		gGameStateNext = MAINMENU;
		printf("Goto Main Menu\n");
	}
}

void GameOver_Draw(void) 
{
	//Draw Background
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetTintColor(0.8f, 0.8f, 0.8f, 0.8f);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetTransparency(1.0f);
	AEGfxTextureSet(gameOverBGTex, 0, 0);
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
	AEGfxMeshDraw(gameOverbMesh, AE_GFX_MDM_TRIANGLES);
	//Finish Background draw

	// Quit button
	AEGfxTextureSet(NULL, 0, 0);
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEMtx33 scale1 = { 0 };
	AEMtx33Scale(&scale1, 100.f * scaleX, 50.f * scaleY);
	AEMtx33 rotate1 = { 0 };
	AEMtx33Rot(&rotate1, 0.f);
	AEMtx33 translate1 = { 0 };
	AEMtx33Trans(&translate1, gameOverQuitButton_transX, gameOverQuitButton_transY);
	AEMtx33 transform1 = { 0 };
	AEMtx33Concat(&transform1, &rotate1, &scale1);
	AEMtx33Concat(&transform1, &translate1, &transform1);
	AEGfxSetTransform(transform1.m);
	AEGfxMeshDraw(pMeshGameOver, AE_GFX_MDM_TRIANGLES);

	// Continue button
	AEGfxTextureSet(NULL, 0, 0);
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEMtx33 scale2 = { 0 };
	AEMtx33Scale(&scale2, 100.f * scaleX, 50.f * scaleY);
	AEMtx33 rotate2 = { 0 };
	AEMtx33Rot(&rotate2, 0.f);
	AEMtx33 translate2 = { 0 };
	AEMtx33Trans(&translate2, gameOverContButton_transX, gameOverContButton_transY);
	AEMtx33 transform2 = { 0 };
	AEMtx33Concat(&transform2, &rotate2, &scale2);
	AEMtx33Concat(&transform2, &translate2, &transform2);
	AEGfxSetTransform(transform2.m);
	AEGfxMeshDraw(pMeshGameOver, AE_GFX_MDM_TRIANGLES);

	// Rendering texts for the screen
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxTextureSet(NULL, 0, 0);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	sprintf_s(gameOver_buffer, "GAME OVER");
	AEGfxPrint(fontID, gameOver_buffer, (getWinWidth() / (-7500.f * scaleX)), (getWinHeight() / (4000.f * scaleY)), 0.8f * scaleX, 156.0f / 255.f, 205.0f / 255.f, 220.0f / 255.f);

	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxTextureSet(NULL, 0, 0);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	sprintf_s(gameOverCont_buffer, "Continue?");
	AEGfxPrint(fontID, gameOverCont_buffer, (getWinWidth() / (-12200.f * scaleX)), (getWinHeight() / (-25000.f * scaleY)), 0.6f * scaleX, 156.0f / 255.f, 205.0f / 255.f, 220.0f / 255.f);

	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxTextureSet(NULL, 0, 0);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	sprintf_s(gameOverQuit_buffer, "Title screen");
	AEGfxPrint(fontID, gameOverQuit_buffer, (getWinWidth() / (-10500.f * scaleX)), (getWinHeight() / (-2600.f * scaleY)), 0.6f * scaleX, 156.0f / 255.f, 205.0f / 255.f, 220.0f / 255.f);
}

void GameOver_Free(void) 
{

}

void GameOver_Unload(void) 
{
	AEGfxMeshFree(pMeshGameOver);
	AEGfxMeshFree(gameOverbMesh);
	AEGfxTextureUnload(gameOverBGTex);
}