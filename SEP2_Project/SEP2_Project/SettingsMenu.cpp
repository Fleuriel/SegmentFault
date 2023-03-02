#include "SettingsMenu.h"
#include "Main.h"

// Pointer to Mesh
AEGfxVertexList* pMeshSettings = nullptr;

// Pre-definition for translations of buttons
double backButton_transX;
double backButton_transY;

// Pre-definition of scaling
double scaleX_settings;
double scaleY_settings;

void Settings_Load(void)
{
	AEGfxSetBackgroundColor(0.329f, 0.408f, 0.471f);

    AEGfxMeshStart();

    AEGfxTriAdd(
        0.5f, 0.5f, 0xFFFFFFFF, 1.0f, 0.0f,
        -1.f, -0.5f, 0xFFFFFFFF, 0.0f, 1.0f,
        0.5f, -0.5f, 0xFFFFFFFF, 1.0f, 1.0f);
    AEGfxTriAdd(
        -1.f, 0.5f, 0xFFFFFFFF, 0.0f, 0.0f,
        -1.f, -0.5f, 0xFFFFFFFF, 0.0f, 1.0f,
        0.5f, 0.5f, 0xFFFFFFFF, 1.0f, 0.0f);

    pMeshSettings = AEGfxMeshEnd();

}

void Settings_Init(void)
{

    // Gets the scale of 1366x768
    scaleX_settings = getWinWidth() / 1366.f;
    scaleY_settings = getWinHeight() / 768.f;

    // Back button translation
    backButton_transX = -300.f * scaleX_settings;
    backButton_transY = -200.f * scaleY_settings;

}
void Settings_Update(void)
{
    // Initialize cursor coordinates
    s32 cursorX;
    s32 cursorY;
    AEInputGetCursorPosition(&cursorX, &cursorY);

    // Quit button mid point
    float backButton_midX = (getWinWidth() / 2.08) + backButton_transX;
    float backButton_midY = (getWinHeight() / 2) - backButton_transY;

    printf("%d\n%d\n", cursorX, cursorY);  //debug
    //printf("%f\n%f\n", button1_midX, button1_midY);  //debug
    // if cursor within buttons, change game state
    if (IsAreaClicked(backButton_midX, backButton_midY, 150.0f * scaleX_settings, 100.0f * scaleY_settings, cursorX, cursorY)
        && AEInputCheckTriggered(AEVK_LBUTTON)) {
        gGameStateNext = MAINMENU;
        printf("MAINMENU\n");
    }
}
void Settings_Draw(void)
{
    // Back button
    AEGfxTextureSet(NULL, 0, 0);
    AEGfxSetRenderMode(AE_GFX_RM_COLOR);
    AEMtx33 scale = { 0 };
    AEMtx33Scale(&scale, 100.f * scaleX_settings, 100.f * scaleY_settings);
    AEMtx33 rotate = { 0 };
    AEMtx33Rot(&rotate, 0.f);
    AEMtx33 translate = { 0 };
    AEMtx33Trans(&translate, backButton_transX, backButton_transY);
    AEMtx33 transform = { 0 };
    AEMtx33Concat(&transform, &rotate, &scale);
    AEMtx33Concat(&transform, &translate, &transform);
    AEGfxSetTransform(transform.m);
    AEGfxMeshDraw(pMeshSettings, AE_GFX_MDM_TRIANGLES);
}
void Settings_Free(void)
{

}
void Settings_Unload(void)
{
    AEGfxMeshFree(pMeshSettings);
}