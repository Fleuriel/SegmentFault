#include <iostream>
#include "PauseMenu.h"
#include "Main.h"
#include "Utilities.h"
#include "GameStateMgr.h"


bool LevelToggle;
f32 Timer;

// Pointer to Mesh
AEGfxVertexList* pMeshPause = nullptr;

// Pre-defintion
//s8 fontID;
//char quit_buffer[100] = "Quit";

// Pre-definition for translations of buttons
double quitButton_transX;
double quitButton_transY;
double resumeButton_transX;
double resumeButton_transY;
double augmentButton_transX;
double augmentButton_transY;

// Pre-definition of scaling
double scaleX_pause;
double scaleY_pause;

void Pause_Load(void)
{
	AEGfxSetBackgroundColor(0.5f, 0.5f, 0.5f);  // conversion -> rgb value/255
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

    pMeshPause = AEGfxMeshEnd();

    // Load font
    // fontID = AEGfxCreateFont("..\\..\\Assets\\Assets\\Minecraft.ttf", 30);

}

void Pause_Init(void)
{

    LevelToggle = false;
    Timer = 0.0f;

    // Gets the scale of 1366x768
    scaleX_pause = getWinWidth() / 1366.f;
    scaleY_pause = getWinHeight() / 768.f;

    // Quit button translation
    quitButton_transX = -300.f * scaleX_pause;
    quitButton_transY = -200.f * scaleY_pause;

    // Resume button translation
    resumeButton_transX = 300.f * scaleX_pause;
    resumeButton_transY = -200.f * scaleY_pause;

    // Resume button translation
    augmentButton_transX = 0.f * scaleX_pause;
    augmentButton_transY = 200.f * scaleY_pause;


}
void Pause_Update(void)
{
    s32 cursorX;
    s32 cursorY;
    AEInputGetCursorPosition(&cursorX, &cursorY);

    // Quit button mid point
    float quitButton_midX = (getWinWidth() / 2.08) + quitButton_transX;
    float quitButton_midY = (getWinHeight() / 2) - quitButton_transY;

    // Resume button mid point
    float resumeButton_midX = (getWinWidth() / 2.08) + resumeButton_transX;
    float resumeButton_midY = (getWinHeight() / 2) - resumeButton_transY;

    // Augment button mid point
    float augmentButton_midX = (getWinWidth() / 2.08) + augmentButton_transX;
    float augmentButton_midY = (getWinHeight() / 2) - augmentButton_transY;

    
    // snprintf(buffer, sizeof buffer, "%d", 9);
    // AEGfxPrint(fontID, quit_buffer, 0, 0, 0.7f, 0.0f, 0.0f, 0.0f);

    printf("%d\n%d\n", cursorX, cursorY);  //debug
    //printf("%f\n%f\n", button1_midX, button1_midY);  //debug
    // if cursor within buttons, change game state
    if (IsAreaClicked(quitButton_midX, quitButton_midY, 150.0f * scaleX_pause, 100.0f * scaleY_pause, cursorX, cursorY)
        && AEInputCheckTriggered(AEVK_LBUTTON)) {
        gGameStateNext = MAINMENU;
        printf("MAINMENU\n");
    }
    else if (IsAreaClicked(resumeButton_midX, resumeButton_midY, 150.0f * scaleX_pause, 100.0f * scaleY_pause, cursorX, cursorY)
        && AEInputCheckTriggered(AEVK_LBUTTON)) {
        gGameStateNext = PLAY;
        printf("RESUME\n");
    }

    else if (IsAreaClicked(augmentButton_midX, augmentButton_midY, 150.0f * scaleX_pause, 100.0f * scaleY_pause, cursorX, cursorY)
        && AEInputCheckTriggered(AEVK_LBUTTON)) {
        //gGameStateNext = UPGRADE;
        printf("UPGRADES\n");
    }

    Timer += g_dt;

    if (AEInputCheckPrev(AEVK_P) && Timer >= 1.5f)
    {
        gGameStateNext = PLAY;
        std::cout << "Back\n";
        Timer = 0;
    }
}
void Pause_Draw(void)
{

    // Quit button
    AEGfxTextureSet(NULL, 0, 0);
    AEGfxSetRenderMode(AE_GFX_RM_COLOR);
    AEMtx33 scale = { 0 };
    AEMtx33Scale(&scale, 100.f * scaleX_pause, 100.f * scaleY_pause);
    AEMtx33 rotate = { 0 };
    AEMtx33Rot(&rotate, 0.f);
    AEMtx33 translate = { 0 };
    AEMtx33Trans(&translate, quitButton_transX, quitButton_transY);
    AEMtx33 transform = { 0 };
    AEMtx33Concat(&transform, &rotate, &scale);
    AEMtx33Concat(&transform, &translate, &transform);
    AEGfxSetTransform(transform.m);
    AEGfxMeshDraw(pMeshPause, AE_GFX_MDM_TRIANGLES);

    // Resume button
    AEGfxTextureSet(NULL, 0, 0);
    AEGfxSetRenderMode(AE_GFX_RM_COLOR);
    AEMtx33 scale1 = { 0 };
    AEMtx33Scale(&scale1, 100.f * scaleX_pause, 100.f * scaleY_pause);
    AEMtx33 rotate1 = { 0 };
    AEMtx33Rot(&rotate1, 0.f);
    AEMtx33 translate1 = { 0 };
    AEMtx33Trans(&translate1, resumeButton_transX, resumeButton_transY);
    AEMtx33 transform1 = { 0 };
    AEMtx33Concat(&transform1, &rotate1, &scale1);
    AEMtx33Concat(&transform1, &translate1, &transform1);
    AEGfxSetTransform(transform1.m);
    AEGfxMeshDraw(pMeshPause, AE_GFX_MDM_TRIANGLES);

    // Augment button
    AEGfxTextureSet(NULL, 0, 0);
    AEGfxSetRenderMode(AE_GFX_RM_COLOR);
    AEMtx33 scale2 = { 0 };
    AEMtx33Scale(&scale2, 100.f * scaleX_pause, 100.f * scaleY_pause);
    AEMtx33 rotate2 = { 0 };
    AEMtx33Rot(&rotate2, 0.f);
    AEMtx33 translate2 = { 0 };
    AEMtx33Trans(&translate2, augmentButton_transX, augmentButton_transY);
    AEMtx33 transform2 = { 0 };
    AEMtx33Concat(&transform2, &rotate2, &scale2);
    AEMtx33Concat(&transform2, &translate2, &transform2);
    AEGfxSetTransform(transform2.m);
    AEGfxMeshDraw(pMeshPause, AE_GFX_MDM_TRIANGLES);

}
void Pause_Free(void)
{

}
void Pause_Unload(void)
{
    //AEGfxDestroyFont(fontID);
    AEGfxMeshFree(pMeshPause);
}