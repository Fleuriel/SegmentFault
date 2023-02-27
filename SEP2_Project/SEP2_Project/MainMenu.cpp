#include "MainMenu.h"
#include "AEEngine.h"
#include "GameStateMgr.h"
#include "GameStateList.h"
#include "Utilities.h"


// Pointer to Mesh
AEGfxVertexList* pMesh = nullptr;

// Pre-definition
AEGfxTexture* startTex;

// Pre-definition for translations of buttons
double powerUpButton_transX;
double powerUpButton_transY;
double settingsButton_transX;
double settingsButton_transY;
double playButton_transX;
double playButton_transY;
double creditsButton_transX;
double creditsButton_transY;
double exitButton_transX;
double exitButton_transY;

// Pre-definition of scaling
double scaleX;
double scaleY;

void Menu_Load(void)
{
   

    AEGfxSetBackgroundColor(0.019f, 0.27f, 0.411f);  // conversion -> rgb value/255

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

    pMesh = AEGfxMeshEnd();

    // Loading textures
    startTex = AEGfxTextureLoad("..\\..\\Assets\\Assets\\start.png");

   
}

void Menu_Init(void) 
{
    // Gets the scale of 1366x768
    scaleX = getWinWidth() / 1366.f; 
    scaleY = getWinHeight() / 768.f;


    powerUpButton_transX = -150.f * scaleX;
    powerUpButton_transY = -150.f * scaleY;
    settingsButton_transX = 150.0f * scaleX;
    settingsButton_transY = -150.0f * scaleY;
    playButton_transX = 0.0f * scaleX;
    playButton_transY = 0.0f * scaleY;
    creditsButton_transX = -600.0f * scaleX;
    creditsButton_transY = -355.0f * scaleY;
    exitButton_transX = 660.0f * scaleX;
    exitButton_transY = 355.0f * scaleY;
    
}

void Menu_Update(void) 
{
    s32 cursorX;
    s32 cursorY;
    AEInputGetCursorPosition(&cursorX, &cursorY);

    
    //printf("%d\n%f\n", AEGetWindowHeight(), getWinHeight());

    // Powerups button mid points
    float powerUpButton_midX = (getWinWidth() / 2.08) + powerUpButton_transX;
    float powerUpButton_midY = (getWinHeight() / 2) - powerUpButton_transY;

    // Settings button mid points
    float settingsButton_midX = (getWinWidth() / 2.08) + settingsButton_transX;
    float settingsButton_midY = (getWinHeight() / 2) - settingsButton_transY;

    // Play button mid points
    float playButton_midX = (getWinWidth() / 2.08) + playButton_transX;
    float playButton_midY = getWinHeight() / 2 - playButton_transY;

    // Credits button mid points
    float creditsButton_midX = (getWinWidth() / 2.08) + creditsButton_transX;
    float creditsButton_midY = (getWinHeight() / 2) - creditsButton_transY;

    // Exit button mid points
    float exitButton_midX = (getWinWidth() / 2.08) + exitButton_transX;
    float exitButton_midY = (getWinHeight() / 2) - exitButton_transY;
    
    printf("%d\n%d\n", cursorX, cursorY);  //debug
    //printf("%f\n%f\n", button1_midX, button1_midY);  //debug
    // if cursor within buttons, change game state
    if (IsAreaClicked(powerUpButton_midX, powerUpButton_midY, 150.0f * scaleX, 100.0f * scaleY, cursorX, cursorY)) {
        //gGameStateNext = POWER_UPS;
        printf("Goto powerups\n");
    }
    else if (IsAreaClicked(settingsButton_midX, settingsButton_midY, 150.0f * scaleX, 100.0f * scaleY, cursorX, cursorY)) {
        gGameStateNext = SETTINGS;
        printf("Goto Settings\n");
    }
    else if (IsAreaClicked(playButton_midX, playButton_midY, 150.0f * scaleX, 100.0f * scaleY, cursorX, cursorY)) {
        gGameStateNext = PLAY;
        printf("Goto Play\n");
    }

    else if (IsAreaClicked(creditsButton_midX, creditsButton_midY, 120.0f * scaleX, 50.0f * scaleY, cursorX, cursorY)) {
        //gGameStateNext = CREDITS;
        printf("Goto Credits\n");
    }

    else if (IsAreaClicked(exitButton_midX, exitButton_midY, 57.0f * scaleX, 50.0f * scaleY, cursorX, cursorY)) {
        gGameStateNext = QUIT;
        printf("QUIT\n");
    }


}
void Menu_Draw(void)
{

    // Button 1, Power-ups button
    AEGfxTextureSet(NULL, 0, 0);
    AEGfxSetRenderMode(AE_GFX_RM_COLOR);
    AEMtx33 scale = { 0 };
    AEMtx33Scale(&scale, 100.f * scaleX, 100.f * scaleY);
    AEMtx33 rotate = { 0 };
    AEMtx33Rot(&rotate, 0.f);
    AEMtx33 translate = { 0 };
    AEMtx33Trans(&translate, powerUpButton_transX, powerUpButton_transY);
    AEMtx33 transform = { 0 };
    AEMtx33Concat(&transform, &rotate, &scale);
    AEMtx33Concat(&transform, &translate, &transform);
    AEGfxSetTransform(transform.m);
    AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);

    // Button 2, Settings button
    AEGfxSetRenderMode(AE_GFX_RM_COLOR);
    AEGfxTextureSet(NULL, 0, 0);
    AEMtx33 scale1 = { 0 };
    AEMtx33Scale(&scale1, 100.f * scaleX, 100.f * scaleY);
    AEMtx33 rotate1 = { 0 };
    AEMtx33Rot(&rotate1, 0.f);
    AEMtx33 translate1 = { 0 };
    AEMtx33Trans(&translate1, settingsButton_transX, settingsButton_transY);
    AEMtx33 transform1 = { 0 };
    AEMtx33Concat(&transform1, &rotate1, &scale1);
    AEMtx33Concat(&transform1, &translate1, &transform1);
    AEGfxSetTransform(transform1.m);
    AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);

    // Button 3, Start button
    AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
    AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
    AEGfxSetBlendMode(AE_GFX_BM_BLEND);
    AEGfxSetTransparency(1.0f);
    AEGfxTextureSet(startTex, 0, 0);
    AEMtx33 scale2 = { 0 };
    AEMtx33Scale(&scale2, 100.f * scaleX, 100.f * scaleY);
    AEMtx33 rotate2 = { 0 };
    AEMtx33Rot(&rotate2, 0.f);
    AEMtx33 translate2 = { 0 };
    AEMtx33Trans(&translate2, playButton_transX, playButton_transY);
    AEMtx33 transform2 = { 0 };
    AEMtx33Concat(&transform2, &rotate2, &scale2);
    AEMtx33Concat(&transform2, &translate2, &transform2);
    AEGfxSetTransform(transform2.m);
    AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);

    // Button 4, Credits button
    AEGfxSetRenderMode(AE_GFX_RM_COLOR);
    AEGfxTextureSet(NULL, 0, 0);
    AEMtx33 scale3 = { 0 };
    AEMtx33Scale(&scale3, 80.f * scaleX, 50.f * scaleY);
    AEMtx33 rotate3 = { 0 };
    AEMtx33Rot(&rotate3, 0.f);
    AEMtx33 translate3 = { 0 };
    AEMtx33Trans(&translate3, creditsButton_transX, creditsButton_transY);
    AEMtx33 transform3 = { 0 };
    AEMtx33Concat(&transform3, &rotate3, &scale3);
    AEMtx33Concat(&transform3, &translate3, &transform3);
    AEGfxSetTransform(transform3.m);
    AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);

    // Button 5, Exit button
    AEGfxSetRenderMode(AE_GFX_RM_COLOR);
    AEGfxTextureSet(NULL, 0, 0);
    AEMtx33 scale4 = { 0 };
    AEMtx33Scale(&scale4, 38.f * scaleX, 50.f * scaleY);
    AEMtx33 rotate4 = { 0 };
    AEMtx33Rot(&rotate4, 0.f);
    AEMtx33 translate4 = { 0 };
    AEMtx33Trans(&translate4, exitButton_transX, exitButton_transY);
    AEMtx33 transform4 = { 0 };
    AEMtx33Concat(&transform4, &rotate4, &scale4);
    AEMtx33Concat(&transform4, &translate4, &transform4);
    AEGfxSetTransform(transform4.m);
    AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);
}

void Menu_Free(void) 
{
    
}
void Menu_Unload(void)
{
    AEGfxMeshFree(pMesh);
    
}