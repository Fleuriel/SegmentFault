#include "SettingsMenu.h"
#include "Main.h"

// Pointer to Mesh
AEGfxVertexList* pMeshSettings = nullptr;
AEGfxVertexList* BGmesh_settings = nullptr;

// Pre-definition
AEGfxTexture* BGtexture_settings;
f32 BGtransX_settings, BGtransY_settings;

// Pre-definition for buttons
f32 backButton_transX;
f32 backButton_transY;

// Quit button mid point
f32 backButton_midX;
f32 backButton_midY;


// Pre-defintion
char howtoplay_buffer[1024]{};
char instructions1_buffer[1024]{};
char instructions2_buffer[1024]{};
char instructions3_buffer[1024]{};
char settingsBackButton_buffer[1024]{};
float settings_textWidth{}, settings_textHeight{};

// Pre-definition of Rotation
f32 buttonRotate_settingsBack;

void Settings_Load(void)
{
    AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);

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

    BGmesh_settings = AEGfxMeshEnd();

    // Load texture for BG
    BGtexture_settings = AEGfxTextureLoad("Assets\\Assets\\MainMenuBackground.png");
}

void Settings_Init(void)
{

    // Gets the scale of 1366x768
    scaleX = getWinWidth() / 1366.f;
    scaleY = getWinHeight() / 768.f;

    // Back button translation
    backButton_transX = 640.f * scaleX;
    backButton_transY = -355.f * scaleY;

    BGtransX_settings = 220.0f * scaleX;
    BGtransY_settings = -40 * scaleY;


}
void Settings_Update(void)
{
    // Initialize cursor coordinates
    s32 cursorX;
    s32 cursorY;
    AEInputGetCursorPosition(&cursorX, &cursorY);

    // Quit button mid point
    backButton_midX = static_cast<f32>((getWinWidth() / 2.08) + backButton_transX);
    backButton_midY = static_cast<f32>((getWinHeight() / 2) - backButton_transY);

    // if cursor within buttons, change game state
    if (IsAreaClicked(backButton_midX, backButton_midY, 150.0f * scaleX, 100.0f * scaleY, cursorX, cursorY)
        && AEInputCheckTriggered(AEVK_LBUTTON)) {
        gGameStateNext = MAINMENU;
    }

    if (IsAreaClicked(backButton_midX, backButton_midY, 136.0f * scaleX, 50.0f * scaleY, cursorX, cursorY))
    {
        buttonRotate_settingsBack = -0.10f;
    }

    if (!IsAreaClicked(backButton_midX, backButton_midY, 170.0f * scaleX, 100.0f * scaleY, cursorX, cursorY))
    {
        buttonRotate_settingsBack = 0.0f;
    }
}
void Settings_Draw(void)
{
    

    //Draw Background
    AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
    AEGfxSetTintColor(0.8f, 0.8f, 0.8f, 0.8f);
    AEGfxSetBlendMode(AE_GFX_BM_BLEND);
    AEGfxSetTransparency(1.0f);
    AEGfxTextureSet(BGtexture_settings, 0, 0);
    AEMtx33 scale0 = { 0 };
    AEMtx33Scale(&scale0, 1100, 800);
    AEMtx33 rotate0 = { 0 };
    AEMtx33Rot(&rotate0, 0.f);
    AEMtx33 translate0 = { 0 };
    AEMtx33Trans(&translate0, BGtransX_settings, BGtransY_settings);
    AEMtx33 transform0 = { 0 };
    AEMtx33Concat(&transform0, &rotate0, &scale0);
    AEMtx33Concat(&transform0, &translate0, &transform0);
    AEGfxSetTransform(transform0.m);
    AEGfxMeshDraw(BGmesh_settings, AE_GFX_MDM_TRIANGLES);
    //Finish Background draw
    
    // Back button
    AEGfxTextureSet(NULL, 0, 0);
    AEGfxSetRenderMode(AE_GFX_RM_COLOR);
    AEMtx33 scale = { 0 };
    AEMtx33Scale(&scale, 80.f * scaleX, 50.f * scaleY);
    AEMtx33 rotate = { 0 };
    AEMtx33Rot(&rotate, buttonRotate_settingsBack);
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
    AEGfxMeshFree(BGmesh_settings);
    AEGfxTextureUnload(BGtexture_settings);
}