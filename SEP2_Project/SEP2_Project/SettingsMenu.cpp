#include "SettingsMenu.h"
#include "Main.h"

// Pointer to Mesh
AEGfxVertexList* pMeshSettings = nullptr;

// Pre-definition for translations of buttons
double backButton_transX;
double backButton_transY;


// Pre-defintion
char howtoplay_buffer[1024]{};
char instructions1_buffer[1024]{};
char instructions2_buffer[1024]{};
char instructions3_buffer[1024]{};
char settingsBackButton_buffer[1024]{};
float settings_textWidth{}, settings_textHeight{};

void Settings_Load(void)
{
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

    pMeshSettings = AEGfxMeshEnd();

}

void Settings_Init(void)
{

    // Gets the scale of 1366x768
    scaleX = getWinWidth() / 1366.f;
    scaleY = getWinHeight() / 768.f;

    // Back button translation
    backButton_transX = 640.f * scaleX;
    backButton_transY = -355.f * scaleY;


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

    // printf("%d\n%d\n", cursorX, cursorY);  //debug
    //printf("%f\n%f\n", button1_midX, button1_midY);  //debug
    // if cursor within buttons, change game state
    if (IsAreaClicked(backButton_midX, backButton_midY, 150.0f * scaleX, 100.0f * scaleY, cursorX, cursorY)
        && AEInputCheckTriggered(AEVK_LBUTTON)) {
        gGameStateNext = MAINMENU;
        //printf("MAINMENU\n");
    }
}
void Settings_Draw(void)
{
    // Back button
    AEGfxTextureSet(NULL, 0, 0);
    AEGfxSetRenderMode(AE_GFX_RM_COLOR);
    AEMtx33 scale = { 0 };
    AEMtx33Scale(&scale, 80.f * scaleX, 50.f * scaleY);
    AEMtx33 rotate = { 0 };
    AEMtx33Rot(&rotate, 0.f);
    AEMtx33 translate = { 0 };
    AEMtx33Trans(&translate, backButton_transX, backButton_transY);
    AEMtx33 transform = { 0 };
    AEMtx33Concat(&transform, &rotate, &scale);
    AEMtx33Concat(&transform, &translate, &transform);
    AEGfxSetTransform(transform.m);
    AEGfxMeshDraw(pMeshSettings, AE_GFX_MDM_TRIANGLES);

    AEGfxSetRenderMode(AE_GFX_RM_COLOR);
    AEGfxTextureSet(NULL, 0, 0);
    AEGfxSetBlendMode(AE_GFX_BM_BLEND);
    sprintf_s(howtoplay_buffer, "HOW TO PLAY:");
    AEGfxPrint(fontID, howtoplay_buffer, (getWinWidth() / (-6000.f * scaleX)), (getWinHeight() / (1000.f * scaleY)), 0.8f * scaleX, 156.0f / 255.f, 205.0f / 255.f, 220.0f / 255.f);

    AEGfxSetRenderMode(AE_GFX_RM_COLOR);
    AEGfxTextureSet(NULL, 0, 0);
    AEGfxSetBlendMode(AE_GFX_BM_BLEND);
    sprintf_s(instructions1_buffer, "Right click for augments.");
    AEGfxPrint(fontID, instructions1_buffer, (getWinWidth() / (-6000.f * scaleX)), (getWinHeight() / (1350.f * scaleY)), 0.8f * scaleX, 156.0f / 255.f, 205.0f / 255.f, 220.0f / 255.f);

    AEGfxSetRenderMode(AE_GFX_RM_COLOR);
    AEGfxTextureSet(NULL, 0, 0);
    AEGfxSetBlendMode(AE_GFX_BM_BLEND);
    sprintf_s(instructions2_buffer, "WASD for movement.");
    AEGfxPrint(fontID, instructions2_buffer, (getWinWidth() / (-6000.f * scaleX)), (getWinHeight() / (2000.f * scaleY)), 0.8f * scaleX, 156.0f / 255.f, 205.0f / 255.f, 220.0f / 255.f);

    AEGfxSetRenderMode(AE_GFX_RM_COLOR);
    AEGfxTextureSet(NULL, 0, 0);
    AEGfxSetBlendMode(AE_GFX_BM_BLEND);
    sprintf_s(instructions3_buffer, "Bullets will follow cursor.");
    AEGfxPrint(fontID, instructions3_buffer, (getWinWidth() / (-6000.f * scaleX)), (getWinHeight() / (4000.f * scaleY)), 0.8f * scaleX, 156.0f / 255.f, 205.0f / 255.f, 220.0f / 255.f);

    AEGfxSetRenderMode(AE_GFX_RM_COLOR);
    AEGfxTextureSet(NULL, 0, 0);
    AEGfxSetBlendMode(AE_GFX_BM_BLEND);
    sprintf_s(settingsBackButton_buffer, "Back");
    AEGfxPrint(fontID, settingsBackButton_buffer, (getWinWidth() / (1655.f * scaleX)), (getWinHeight() / (-798.f * scaleY)), 0.8f * scaleX, 156.0f / 255.f, 205.0f / 255.f, 220.0f / 255.f);
}
void Settings_Free(void)
{

}
void Settings_Unload(void)
{
    AEGfxMeshFree(pMeshSettings);
}