#include "Augments.h"
#include "Main.h"

// Pointer to Mesh
AEGfxVertexList* pMeshAugments = nullptr;

// Pre-defintion
char augment1_buffer[1024]{};
char augment2_buffer[1024]{};
char augment3_buffer[1024]{};
char augment4_buffer[1024]{};
char gdt1_buffer[1024]{};
float augments_textWidth{}, augments_textHeight{};

// Pre-definition for translations of buttons
//double quitButton_transX;
//double quitButton_transY;
//double resumeButton_transX;
//double resumeButton_transY;
double augmentsBackbutton_transX;
double augmentsBackbutton_transY;

// Pre-definition of scaling
double scaleX_augments;
double scaleY_augments;


void Augments_Load(void) 
{
    AEGfxSetBackgroundColor(0.5f, 0.5f, 0.5f);  // conversion -> rgb value/255
    // Create buttons
    AEGfxMeshStart();
    //#9ccddc light blue
    //#001736 midnight blue
    AEGfxTriAdd(
        0.5f, 0.5f, 0xFF001736, 1.0f, 0.0f,
        -1.f, -0.5f, 0xFF001736, 0.0f, 1.0f,
        0.5f, -0.5f, 0xFF001736, 1.0f, 1.0f);
    AEGfxTriAdd(
        -1.f, 0.5f, 0xFF001736, 0.0f, 0.0f,
        -1.f, -0.5f, 0xFF001736, 0.0f, 1.0f,
        0.5f, 0.5f, 0xFF001736, 1.0f, 0.0f);

    pMeshAugments = AEGfxMeshEnd();
}
void Augments_Init(void) 
{
    // Gets the scale of 1366x768
    scaleX_augments = getWinWidth() / 1366.f;
    scaleY_augments = getWinHeight() / 768.f;

    augmentsBackbutton_transX = 640.0f * scaleX_augments;
    augmentsBackbutton_transY = -355.0f * scaleY_augments;
}
void Augments_Update(void) 
{
    // Initialize cursor coordinates
    s32 cursorX;
    s32 cursorY;
    AEInputGetCursorPosition(&cursorX, &cursorY);

    // Augments back button mid points
    float augmentsBackbutton_midX = (getWinWidth() / 2.09) + augmentsBackbutton_transX;
    float augmentsBackbutton_midY = (getWinHeight() / 2) - augmentsBackbutton_transY;

    if (IsAreaClicked(augmentsBackbutton_midX, augmentsBackbutton_midY, 136.0f * scaleX_augments, 50.0f * scaleY_augments, cursorX, cursorY)
        && AEInputCheckTriggered(AEVK_LBUTTON)) {
        gGameStateNext = PAUSE;
        printf("Goto MAIN MENU\n");
    }
    timeElapsed += g_dt;
    if (timeElapsed >= 59.5) {
        minElapsed++;
        timeElapsed = 0;
    }
}

void Augments_Draw(void) 
{

    // Quit button
    AEGfxTextureSet(NULL, 0, 0);
    AEGfxSetRenderMode(AE_GFX_RM_COLOR);
    AEMtx33 scale = { 0 };
    AEMtx33Scale(&scale, 80.f * scaleX_augments, 50.f * scaleY_augments);
    AEMtx33 rotate = { 0 };
    AEMtx33Rot(&rotate, 0.f);
    AEMtx33 translate = { 0 };
    AEMtx33Trans(&translate, augmentsBackbutton_transX, augmentsBackbutton_transY);
    AEMtx33 transform = { 0 };
    AEMtx33Concat(&transform, &rotate, &scale);
    AEMtx33Concat(&transform, &translate, &transform);
    AEGfxSetTransform(transform.m);
    AEGfxMeshDraw(pMeshAugments, AE_GFX_MDM_TRIANGLES);

    // Rendering texts for the screen
    //AEGfxSetRenderMode(AE_GFX_RM_COLOR);
    //AEGfxTextureSet(NULL, 0, 0);
    //AEGfxSetBlendMode(AE_GFX_BM_BLEND);
    //sprintf_s(augment1_buffer, "Augment 1");
    //// AEGfxGetPrintSize(fontID, augment1_buffer, 1.0f, pause_textWidth, pause_textHeight);
    //AEGfxPrint(fontID, augment1_buffer, (getWinWidth() / (-2000.f * scaleX_augments)), (getWinHeight() / (1000.f * scaleY_augments)), 0.6f * scaleX_augments, 156.0f / 255.f, 205.0f / 255.f, 220.0f / 255.f);

    AEGfxSetRenderMode(AE_GFX_RM_COLOR);
    AEGfxTextureSet(NULL, 0, 0);
    AEGfxSetBlendMode(AE_GFX_BM_BLEND);
    sprintf_s(augment2_buffer, "Augment 2");
    // AEGfxGetPrintSize(fontID, augment1_buffer, 1.0f, pause_textWidth, pause_textHeight);
    AEGfxPrint(fontID, augment2_buffer, (getWinWidth() / (-2000.f * scaleX_augments)), (getWinHeight() / (1450.f * scaleY_augments)), 0.6f * scaleX_augments, 156.0f / 255.f, 205.0f / 255.f, 220.0f / 255.f);

    AEGfxSetRenderMode(AE_GFX_RM_COLOR);
    AEGfxTextureSet(NULL, 0, 0);
    AEGfxSetBlendMode(AE_GFX_BM_BLEND);
    sprintf_s(augment3_buffer, "Augment 3");
    // AEGfxGetPrintSize(fontID, augment1_buffer, 1.0f, pause_textWidth, pause_textHeight);
    AEGfxPrint(fontID, augment3_buffer, (getWinWidth() / (-2000.f * scaleX_augments)), (getWinHeight() / (2550.f * scaleY_augments)), 0.6f * scaleX_augments, 156.0f / 255.f, 205.0f / 255.f, 220.0f / 255.f);

    AEGfxSetRenderMode(AE_GFX_RM_COLOR);
    AEGfxTextureSet(NULL, 0, 0);
    AEGfxSetBlendMode(AE_GFX_BM_BLEND);
    sprintf_s(augment3_buffer, "Augment 4");
    // AEGfxGetPrintSize(fontID, augment1_buffer, 1.0f, pause_textWidth, pause_textHeight);
    AEGfxPrint(fontID, augment3_buffer, (getWinWidth() / (-2000.f * scaleX_augments)), (getWinHeight() / (11000.f * scaleY_augments)), 0.6f * scaleX_augments, 156.0f / 255.f, 205.0f / 255.f, 220.0f / 255.f);

    // Rendering texts for the screen
    AEGfxSetRenderMode(AE_GFX_RM_COLOR);
    AEGfxTextureSet(NULL, 0, 0);
    AEGfxSetBlendMode(AE_GFX_BM_BLEND);
    if(timeElapsed>=9.5)
        sprintf_s(gdt1_buffer, "%.0f:%.0f", minElapsed, timeElapsed);
    else
        sprintf_s(gdt1_buffer, "%.0f:0%.0f", minElapsed, timeElapsed);
    printf(gdt1_buffer);
    AEGfxPrint(fontID, gdt1_buffer, (getWinWidth() / (-2500.f * scaleX_augments)), (getWinHeight() / (-1350.f * scaleY_augments)), 1.0f * scaleX_augments, 255.0f / 255.f, 255.0f / 255.f, 255.0f / 255.f);
}
void Augments_Free(void) 
{

}
void Augments_Unload(void) 
{
    AEGfxMeshFree(pMeshAugments);
}