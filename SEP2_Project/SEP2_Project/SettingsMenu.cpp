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
f32 vol1_transX, vol1_transY, vol2_transX, vol2_transY, vol3_transX, vol3_transY, vol4_transX, vol4_transY, vol5_transX, vol5_transY;
f32 sfx1_transX, sfx1_transY, sfx2_transX, sfx2_transY, sfx3_transX, sfx3_transY, sfx4_transX, sfx4_transY, sfx5_transX, sfx5_transY;

// Quit button mid point
f32 backButton_midX;
f32 backButton_midY;

// Vol/sfx button mid points
f32 vol1_midX, vol1_midY, vol2_midX, vol2_midY, vol3_midX, vol3_midY, vol4_midX, vol4_midY, vol5_midX, vol5_midY;
f32 sfx1_midX, sfx1_midY, sfx2_midX, sfx2_midY, sfx3_midX, sfx3_midY, sfx4_midX, sfx4_midY, sfx5_midX, sfx5_midY;

// Pre-defintion
char settingsText_buffer[100]{};
char settingsBackButton_buffer[1024]{};
float settings_textWidth{}, settings_textHeight{};

// Pre-definition of Rotation
f32 buttonRotate_settingsBack;

// Volume and sfx initialization
int volume = 100;
int sfx = 100;

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

    // Vol button translation
    vol1_transX = -50.0f;
    vol1_transY = 100.0f;
    vol2_transX = 50.0f;
    vol2_transY = 100.0f;
    vol3_transX = 150.0f;
    vol3_transY = 100.0f;
    vol4_transX = 250.0f;
    vol4_transY = 100.0f;
    vol5_transX = 350.0f;
    vol5_transY = 100.0f;

    // Sfx button translation
    sfx1_transX = -50.0f;
    sfx1_transY = 0.0f;
    sfx2_transX = 50.0f;
    sfx2_transY = 0.0f;
    sfx3_transX = 150.0f;
    sfx3_transY = 0.0f;
    sfx4_transX = 250.0f;
    sfx4_transY = 0.0f;
    sfx5_transX = 350.0f;
    sfx5_transY = 0.0f;

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

    // Vol button mid points
    vol1_midX = static_cast<f32>((getWinWidth() / 2.04) + vol1_transX);
    vol1_midY = static_cast<f32>((getWinHeight() / 2) - vol1_transY);
    vol2_midX = static_cast<f32>((getWinWidth() / 2.04) + vol2_transX);
    vol2_midY = static_cast<f32>((getWinHeight() / 2) - vol2_transY);
    vol3_midX = static_cast<f32>((getWinWidth() / 2.04) + vol3_transX);
    vol3_midY = static_cast<f32>((getWinHeight() / 2) - vol3_transY);
    vol4_midX = static_cast<f32>((getWinWidth() / 2.04) + vol4_transX);
    vol4_midY = static_cast<f32>((getWinHeight() / 2) - vol4_transY);
    vol5_midX = static_cast<f32>((getWinWidth() / 2.04) + vol5_transX);
    vol5_midY = static_cast<f32>((getWinHeight() / 2) - vol5_transY);

    // Sfx button mid points
    sfx1_midX = static_cast<f32>((getWinWidth() / 2.04) + sfx1_transX);
    sfx1_midY = static_cast<f32>((getWinHeight() / 2) - sfx1_transY);
    sfx2_midX = static_cast<f32>((getWinWidth() / 2.04) + sfx2_transX);
    sfx2_midY = static_cast<f32>((getWinHeight() / 2) - sfx2_transY);
    sfx3_midX = static_cast<f32>((getWinWidth() / 2.04) + sfx3_transX);
    sfx3_midY = static_cast<f32>((getWinHeight() / 2) - sfx3_transY);
    sfx4_midX = static_cast<f32>((getWinWidth() / 2.04) + sfx4_transX);
    sfx4_midY = static_cast<f32>((getWinHeight() / 2) - sfx4_transY);
    sfx5_midX = static_cast<f32>((getWinWidth() / 2.04) + sfx5_transX);
    sfx5_midY = static_cast<f32>((getWinHeight() / 2) - sfx5_transY);

    // if cursor within buttons, change game state
    if (IsAreaClicked(backButton_midX, backButton_midY, 150.0f * scaleX, 100.0f * scaleY, cursorX, cursorY)
        && AEInputCheckReleased(AEVK_LBUTTON)) {
        gGameStateNext = MAINMENU;
    }

    else if (IsAreaClicked(vol1_midX, vol1_midY, 57.8f * scaleX, 50.0f * scaleY, cursorX, cursorY)
        && AEInputCheckReleased(AEVK_LBUTTON))
    {
        printf("0 Vol\n");
        volume = 0;
    }

    else if (IsAreaClicked(vol2_midX, vol2_midY, 57.8f * scaleX, 50.0f * scaleY, cursorX, cursorY)
        && AEInputCheckReleased(AEVK_LBUTTON))
    {
        printf("25 Vol\n");
        volume = 25;
    }

    else if (IsAreaClicked(vol3_midX, vol3_midY, 57.8f * scaleX, 50.0f * scaleY, cursorX, cursorY)
        && AEInputCheckReleased(AEVK_LBUTTON))
    {
        printf("50 Vol\n");
        volume = 50;
    }

    else if (IsAreaClicked(vol4_midX, vol4_midY, 57.8f * scaleX, 50.0f * scaleY, cursorX, cursorY)
        && AEInputCheckReleased(AEVK_LBUTTON))
    {
        printf("75 Vol\n");
        volume = 75;
    }

    else if (IsAreaClicked(vol5_midX, vol5_midY, 57.8f * scaleX, 50.0f * scaleY, cursorX, cursorY)
        && AEInputCheckReleased(AEVK_LBUTTON))
    {
        printf("100 Vol\n");
        volume = 100;
    }

    else if (IsAreaClicked(sfx1_midX, sfx1_midY, 57.8f * scaleX, 50.0f * scaleY, cursorX, cursorY)
        && AEInputCheckReleased(AEVK_LBUTTON))
    {
        printf("0 Sfx\n");
        sfx = 0;
    }

    else if (IsAreaClicked(sfx2_midX, sfx2_midY, 57.8f * scaleX, 50.0f * scaleY, cursorX, cursorY)
        && AEInputCheckReleased(AEVK_LBUTTON))
    {
        printf("25 Sfx\n");
        sfx = 25;
    }

    else if (IsAreaClicked(sfx3_midX, sfx3_midY, 57.8f * scaleX, 50.0f * scaleY, cursorX, cursorY)
        && AEInputCheckReleased(AEVK_LBUTTON))
    {
        printf("50 Sfx\n");
        sfx = 50;
    }

    else if (IsAreaClicked(sfx4_midX, sfx4_midY, 57.8f * scaleX, 50.0f * scaleY, cursorX, cursorY)
        && AEInputCheckReleased(AEVK_LBUTTON))
    {
        printf("75 Sfx\n");
        sfx = 75;
    }

    else if (IsAreaClicked(sfx5_midX, sfx5_midY, 57.8f * scaleX, 50.0f * scaleY, cursorX, cursorY)
        && AEInputCheckReleased(AEVK_LBUTTON))
    {
        printf("100 Sfx\n");
        sfx = 100;
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

    // Volume buttons start //
    AEGfxSetRenderMode(AE_GFX_RM_COLOR);
    AEGfxTextureSet(NULL, 0, 0);
    AEMtx33Scale(&scale, 34.f * scaleX, 50.f * scaleY);
    AEMtx33Rot(&rotate, 0);
    AEMtx33Trans(&translate, vol1_transX, vol1_transY);
    AEMtx33Concat(&transform, &rotate, &scale);
    AEMtx33Concat(&transform, &translate, &transform);
    AEGfxSetTransform(transform.m);
    AEGfxMeshDraw(pMeshSettings, AE_GFX_MDM_TRIANGLES);

    AEGfxSetRenderMode(AE_GFX_RM_COLOR);
    AEGfxTextureSet(NULL, 0, 0);
    AEMtx33Scale(&scale, 34.f * scaleX, 50.f * scaleY);
    AEMtx33Rot(&rotate, 0);
    AEMtx33Trans(&translate, vol2_transX, vol2_transY);
    AEMtx33Concat(&transform, &rotate, &scale);
    AEMtx33Concat(&transform, &translate, &transform);
    AEGfxSetTransform(transform.m);
    AEGfxMeshDraw(pMeshSettings, AE_GFX_MDM_TRIANGLES);

    AEGfxSetRenderMode(AE_GFX_RM_COLOR);
    AEGfxTextureSet(NULL, 0, 0);
    AEMtx33Scale(&scale, 34.f * scaleX, 50.f * scaleY);
    AEMtx33Rot(&rotate, 0);
    AEMtx33Trans(&translate, vol3_transX, vol3_transY);
    AEMtx33Concat(&transform, &rotate, &scale);
    AEMtx33Concat(&transform, &translate, &transform);
    AEGfxSetTransform(transform.m);
    AEGfxMeshDraw(pMeshSettings, AE_GFX_MDM_TRIANGLES);

    AEGfxSetRenderMode(AE_GFX_RM_COLOR);
    AEGfxTextureSet(NULL, 0, 0);
    AEMtx33Scale(&scale, 34.f * scaleX, 50.f * scaleY);
    AEMtx33Rot(&rotate, 0);
    AEMtx33Trans(&translate, vol4_transX, vol4_transY);
    AEMtx33Concat(&transform, &rotate, &scale);
    AEMtx33Concat(&transform, &translate, &transform);
    AEGfxSetTransform(transform.m);
    AEGfxMeshDraw(pMeshSettings, AE_GFX_MDM_TRIANGLES);

    AEGfxSetRenderMode(AE_GFX_RM_COLOR);
    AEGfxTextureSet(NULL, 0, 0);
    AEMtx33Scale(&scale, 34.f * scaleX, 50.f * scaleY);
    AEMtx33Rot(&rotate, 0);
    AEMtx33Trans(&translate, vol5_transX, vol5_transY);
    AEMtx33Concat(&transform, &rotate, &scale);
    AEMtx33Concat(&transform, &translate, &transform);
    AEGfxSetTransform(transform.m);
    AEGfxMeshDraw(pMeshSettings, AE_GFX_MDM_TRIANGLES);
    // Volume buttons end //

    // Sfx buttons start //
    AEGfxSetRenderMode(AE_GFX_RM_COLOR);
    AEGfxTextureSet(NULL, 0, 0);
    AEMtx33Scale(&scale, 34.f * scaleX, 50.f * scaleY);
    AEMtx33Rot(&rotate, 0);
    AEMtx33Trans(&translate, sfx1_transX, sfx1_transY);
    AEMtx33Concat(&transform, &rotate, &scale);
    AEMtx33Concat(&transform, &translate, &transform);
    AEGfxSetTransform(transform.m);
    AEGfxMeshDraw(pMeshSettings, AE_GFX_MDM_TRIANGLES);

    AEGfxSetRenderMode(AE_GFX_RM_COLOR);
    AEGfxTextureSet(NULL, 0, 0);
    AEMtx33Scale(&scale, 34.f * scaleX, 50.f * scaleY);
    AEMtx33Rot(&rotate, 0);
    AEMtx33Trans(&translate, sfx2_transX, sfx2_transY);
    AEMtx33Concat(&transform, &rotate, &scale);
    AEMtx33Concat(&transform, &translate, &transform);
    AEGfxSetTransform(transform.m);
    AEGfxMeshDraw(pMeshSettings, AE_GFX_MDM_TRIANGLES);

    AEGfxSetRenderMode(AE_GFX_RM_COLOR);
    AEGfxTextureSet(NULL, 0, 0);
    AEMtx33Scale(&scale, 34.f * scaleX, 50.f * scaleY);
    AEMtx33Rot(&rotate, 0);
    AEMtx33Trans(&translate, sfx3_transX, sfx3_transY);
    AEMtx33Concat(&transform, &rotate, &scale);
    AEMtx33Concat(&transform, &translate, &transform);
    AEGfxSetTransform(transform.m);
    AEGfxMeshDraw(pMeshSettings, AE_GFX_MDM_TRIANGLES);

    AEGfxSetRenderMode(AE_GFX_RM_COLOR);
    AEGfxTextureSet(NULL, 0, 0);
    AEMtx33Scale(&scale, 34.f * scaleX, 50.f * scaleY);
    AEMtx33Rot(&rotate, 0);
    AEMtx33Trans(&translate, sfx4_transX, sfx4_transY);
    AEMtx33Concat(&transform, &rotate, &scale);
    AEMtx33Concat(&transform, &translate, &transform);
    AEGfxSetTransform(transform.m);
    AEGfxMeshDraw(pMeshSettings, AE_GFX_MDM_TRIANGLES);

    AEGfxSetRenderMode(AE_GFX_RM_COLOR);
    AEGfxTextureSet(NULL, 0, 0);
    AEMtx33Scale(&scale, 34.f * scaleX, 50.f * scaleY);
    AEMtx33Rot(&rotate, 0);
    AEMtx33Trans(&translate, sfx5_transX, sfx5_transY);
    AEMtx33Concat(&transform, &rotate, &scale);
    AEMtx33Concat(&transform, &translate, &transform);
    AEGfxSetTransform(transform.m);
    AEGfxMeshDraw(pMeshSettings, AE_GFX_MDM_TRIANGLES);
    // SFX Buttons End //
    
    //AEGfxSetRenderMode(AE_GFX_RM_COLOR);
    //AEGfxTextureSet(NULL, 0, 0);
    //AEGfxSetBlendMode(AE_GFX_BM_BLEND);
    //sprintf_s(settingsText_buffer, "HOW TO PLAY:");
    //AEGfxPrint(fontID, settingsText_buffer, (getWinWidth() / (-3500.f * scaleX)), (getWinHeight() / (1000.f * scaleY)), 0.8f * scaleX, 156.0f / 255.f, 205.0f / 255.f, 220.0f / 255.f);

    //AEGfxSetRenderMode(AE_GFX_RM_COLOR);
    //AEGfxTextureSet(NULL, 0, 0);
    //AEGfxSetBlendMode(AE_GFX_BM_BLEND);
    //sprintf_s(settingsText_buffer, "Right mouse click for augments.");
    //AEGfxPrint(fontID, settingsText_buffer, (getWinWidth() / (-3500.f * scaleX)), (getWinHeight() / (1350.f * scaleY)), 0.8f * scaleX, 156.0f / 255.f, 205.0f / 255.f, 220.0f / 255.f);

    AEGfxSetRenderMode(AE_GFX_RM_COLOR);
    AEGfxTextureSet(NULL, 0, 0);
    AEGfxSetBlendMode(AE_GFX_BM_BLEND);
    sprintf_s(settingsText_buffer, "Volume:");
    AEGfxPrint(fontID, settingsText_buffer, (getWinWidth() / (-3500.f * scaleX)), (getWinHeight() / (4000.f * scaleY)), 0.8f * scaleX, 156.0f / 255.f, 205.0f / 255.f, 220.0f / 255.f);

    AEGfxSetRenderMode(AE_GFX_RM_COLOR);
    AEGfxTextureSet(NULL, 0, 0);
    AEGfxSetBlendMode(AE_GFX_BM_BLEND);
    sprintf_s(settingsText_buffer, "SFX:");
    AEGfxPrint(fontID, settingsText_buffer, (getWinWidth() / (-3500.f * scaleX)), (getWinHeight() / (-25000 * scaleY)), 0.8f * scaleX, 156.0f / 255.f, 205.0f / 255.f, 220.0f / 255.f);

    AEGfxSetRenderMode(AE_GFX_RM_COLOR);
    AEGfxTextureSet(NULL, 0, 0);
    AEGfxSetBlendMode(AE_GFX_BM_BLEND);
    sprintf_s(settingsText_buffer, "Back");
    AEGfxPrint(fontID, settingsText_buffer, (getWinWidth() / (1655.f * scaleX)), (getWinHeight() / (-798.f * scaleY)), 0.8f * scaleX, 156.0f / 255.f, 205.0f / 255.f, 220.0f / 255.f);

    AEGfxSetRenderMode(AE_GFX_RM_COLOR);
    AEGfxTextureSet(NULL, 0, 0);
    AEGfxSetBlendMode(AE_GFX_BM_BLEND);
    sprintf_s(settingsText_buffer, "0");
    AEGfxPrint(fontID, settingsText_buffer, (getWinWidth() / (-14300.f * scaleX)), (getWinHeight() / (2000.f * scaleY)), 0.8f * scaleX, 156.0f / 255.f, 205.0f / 255.f, 220.0f / 255.f);

    AEGfxSetRenderMode(AE_GFX_RM_COLOR);
    AEGfxTextureSet(NULL, 0, 0);
    AEGfxSetBlendMode(AE_GFX_BM_BLEND);
    sprintf_s(settingsText_buffer, "25");
    AEGfxPrint(fontID, settingsText_buffer, (getWinWidth() / (120000.f * scaleX)), (getWinHeight() / (2000.f * scaleY)), 0.8f * scaleX, 156.0f / 255.f, 205.0f / 255.f, 220.0f / 255.f);

    AEGfxSetRenderMode(AE_GFX_RM_COLOR);
    AEGfxTextureSet(NULL, 0, 0);
    AEGfxSetBlendMode(AE_GFX_BM_BLEND);
    sprintf_s(settingsText_buffer, "50");
    AEGfxPrint(fontID, settingsText_buffer, (getWinWidth() / (10000.f * scaleX)), (getWinHeight() / (2000.f * scaleY)), 0.8f * scaleX, 156.0f / 255.f, 205.0f / 255.f, 220.0f / 255.f);

    AEGfxSetRenderMode(AE_GFX_RM_COLOR);
    AEGfxTextureSet(NULL, 0, 0);
    AEGfxSetBlendMode(AE_GFX_BM_BLEND);
    sprintf_s(settingsText_buffer, "75");
    AEGfxPrint(fontID, settingsText_buffer, (getWinWidth() / (5250.f * scaleX)), (getWinHeight() / (2000.f * scaleY)), 0.8f * scaleX, 156.0f / 255.f, 205.0f / 255.f, 220.0f / 255.f);

    AEGfxSetRenderMode(AE_GFX_RM_COLOR);
    AEGfxTextureSet(NULL, 0, 0);
    AEGfxSetBlendMode(AE_GFX_BM_BLEND);
    sprintf_s(settingsText_buffer, "100");
    AEGfxPrint(fontID, settingsText_buffer, (getWinWidth() / (3600.f * scaleX)), (getWinHeight() / (2000.f * scaleY)), 0.8f * scaleX, 156.0f / 255.f, 205.0f / 255.f, 220.0f / 255.f);

    // Indicator for volume and sfx //
    AEGfxSetRenderMode(AE_GFX_RM_COLOR);
    AEGfxTextureSet(NULL, 0, 0);
    AEGfxSetBlendMode(AE_GFX_BM_BLEND);
    sprintf_s(settingsText_buffer, "Volume: %d", volume);
    AEGfxPrint(fontID, settingsText_buffer, (getWinWidth() / (-3500.f * scaleX)), (getWinHeight() / (-3000.f * scaleY)), 0.8f * scaleX, 156.0f / 255.f, 205.0f / 255.f, 220.0f / 255.f);

    AEGfxSetRenderMode(AE_GFX_RM_COLOR);
    AEGfxTextureSet(NULL, 0, 0);
    AEGfxSetBlendMode(AE_GFX_BM_BLEND);
    sprintf_s(settingsText_buffer, "Sfx: %d", sfx);
    AEGfxPrint(fontID, settingsText_buffer, (getWinWidth() / (-3500.f * scaleX)), (getWinHeight() / (-1600.f * scaleY)), 0.8f * scaleX, 156.0f / 255.f, 205.0f / 255.f, 220.0f / 255.f);


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