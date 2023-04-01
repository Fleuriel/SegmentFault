#include "Credits.h"
#include "Main.h"


// Pointer to Mesh
AEGfxVertexList* pMeshCredits = nullptr;
AEGfxVertexList* BGmesh_credits = nullptr;

// Pre-definition
AEGfxTexture* BGtexture_credits;
double BGtransX_credits, BGtransY_credits;

// Pre-definition for translations of buttons
double creditsPic_transX;
double creditsPic_transY;
double creditsBackbutton_transX;
double creditsBackbutton_transY;


// Pre-defintion for str buffers
char creditsBack_buffer[1024]{};
char credits1_buffer[1024]{};
float credits_textWidth{}, credits_textHeight{};

// Pre-definition of Rotation
double buttonRotate_creditsBack;

void Credits_Load(void) 
{
    AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);  // conversion -> rgb value/255

    AEGfxMeshStart();

    AEGfxTriAdd(
        0.5f, 0.5f, 0xFF001736, 1.0f, 0.0f,
        -1.2f, -0.5f, 0xFF001736, 0.0f, 1.0f,
        0.5f, -0.5f, 0xFF001736, 1.0f, 1.0f);
    AEGfxTriAdd(
        -1.2f, 0.5f, 0xFF001736, 0.0f, 0.0f,
        -1.2f, -0.5f, 0xFF001736, 0.0f, 1.0f,
        0.5f, 0.5f, 0xFF001736, 1.0f, 0.0f);

    pMeshCredits = AEGfxMeshEnd();

    
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

    BGmesh_credits = AEGfxMeshEnd();

    // Load texture for BG
    BGtexture_credits = AEGfxTextureLoad("Assets\\Assets\\MainMenuBackground.png");

    //end Background

}
void Credits_Init(void) 
{
    scaleX = getWinWidth() / 1366.f;
    scaleY = getWinHeight() / 768.f;

    creditsPic_transX = -120.f * scaleX;
    creditsPic_transY = -150.f * scaleY;
    creditsBackbutton_transX = 640.0f * scaleX;
    creditsBackbutton_transY = -355.0f * scaleY;

    buttonRotate_creditsBack = 0.f;

    BGtransX_credits = 220.0f * scaleX;
    BGtransY_credits = -40 * scaleY;
}
void Credits_Update(void)
{
    // Initialize cursor coordinates
    s32 cursorX;
    s32 cursorY;
    AEInputGetCursorPosition(&cursorX, &cursorY);

    // Credits pic mid points
    float creditsPic_midX = (getWinWidth() / 2.11) + creditsPic_transX;
    float creditsPic_midY = (getWinHeight() / 2) - creditsPic_transY;

    // Credits back button mid points
    float creditsBackbutton_midX = (getWinWidth() / 2.09) + creditsBackbutton_transX;
    float creditsBackbutton_midY = (getWinHeight() / 2) - creditsBackbutton_transY;


    if (IsAreaClicked(creditsBackbutton_midX, creditsBackbutton_midY, 136.0f * scaleX, 50.0f * scaleY, cursorX, cursorY)
        && AEInputCheckTriggered(AEVK_LBUTTON)) {
        gGameStateNext = MAINMENU;
        // printf("Goto MAIN MENU\n");
    }

    if (IsAreaClicked(creditsBackbutton_midX, creditsBackbutton_midY, 136.0f * scaleX, 50.0f * scaleY, cursorX, cursorY))
    {
        buttonRotate_creditsBack = -0.10f;
    }

    if (!IsAreaClicked(creditsBackbutton_midX, creditsBackbutton_midY, 170.0f * scaleX, 100.0f * scaleY, cursorX, cursorY))
    {
        buttonRotate_creditsBack = 0.0f;
    }
}
void Credits_Draw(void) 
{

    //Draw Background
    AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
    AEGfxSetTintColor(0.8f, 0.8f, 0.8f, 0.8f);
    AEGfxSetBlendMode(AE_GFX_BM_BLEND);
    AEGfxSetTransparency(1.0f);
    AEGfxTextureSet(BGtexture_credits, 0, 0);
    AEMtx33 scale0 = { 0 };
    AEMtx33Scale(&scale0, 1100, 800);
    AEMtx33 rotate0 = { 0 };
    AEMtx33Rot(&rotate0, 0.f);
    AEMtx33 translate0 = { 0 };
    AEMtx33Trans(&translate0, BGtransX_credits, BGtransY_credits);
    AEMtx33 transform0 = { 0 };
    AEMtx33Concat(&transform0, &rotate0, &scale0);
    AEMtx33Concat(&transform0, &translate0, &transform0);
    AEGfxSetTransform(transform0.m);
    AEGfxMeshDraw(BGmesh_credits, AE_GFX_MDM_TRIANGLES);
    //Finish Background draw

    // Button 1, Back button
    AEGfxSetRenderMode(AE_GFX_RM_COLOR);
    AEGfxTextureSet(NULL, 0, 0);
    AEMtx33 scale = { 0 };
    AEMtx33Scale(&scale, 80.f * scaleX, 50.f * scaleY);
    AEMtx33 rotate = { 0 };
    AEMtx33Rot(&rotate, buttonRotate_creditsBack);
    AEMtx33 translate = { 0 };
    AEMtx33Trans(&translate, creditsBackbutton_transX, creditsBackbutton_transY);
    AEMtx33 transform = { 0 };
    AEMtx33Concat(&transform, &rotate, &scale);
    AEMtx33Concat(&transform, &translate, &transform);
    AEGfxSetTransform(transform.m);
    AEGfxMeshDraw(pMeshCredits, AE_GFX_MDM_TRIANGLES);
    
    // Rendering texts for the screen

    AEGfxSetRenderMode(AE_GFX_RM_COLOR);
    AEGfxTextureSet(NULL, 0, 0);
    AEGfxSetBlendMode(AE_GFX_BM_BLEND);
    sprintf_s(credits1_buffer, "Developers:");
    AEGfxGetPrintSize(fontID, credits1_buffer, 1.0f, credits_textWidth, credits_textHeight);
    AEGfxPrint(fontID, credits1_buffer, (getWinWidth() / (-2000.f * scaleX)), (getWinHeight() / (1200.f * scaleY)), 0.6f * scaleX, 255.0f / 255.f, 255.0f / 255.f, 255.0f / 255.f);

    AEGfxSetRenderMode(AE_GFX_RM_COLOR);
    AEGfxTextureSet(NULL, 0, 0);
    AEGfxSetBlendMode(AE_GFX_BM_BLEND);
    sprintf_s(credits1_buffer, "ALOYSIUS ANG");
    AEGfxGetPrintSize(fontID, credits1_buffer, 1.0f, credits_textWidth, credits_textHeight);
    AEGfxPrint(fontID, credits1_buffer, (getWinWidth() / (-2000.f * scaleX)), (getWinHeight() / (1800.f * scaleY)), 0.6f * scaleX, 156.0f / 255.f, 205.0f / 255.f, 220.0f / 255.f);

    AEGfxSetRenderMode(AE_GFX_RM_COLOR);
    AEGfxTextureSet(NULL, 0, 0);
    AEGfxSetBlendMode(AE_GFX_BM_BLEND);
    sprintf_s(credits1_buffer, "ANGUS TAN");
    AEGfxGetPrintSize(fontID, credits1_buffer, 1.0f, credits_textWidth, credits_textHeight);
    AEGfxPrint(fontID, credits1_buffer, (getWinWidth() / (-2000.f * scaleX)), (getWinHeight() / (3800.f * scaleY)), 0.6f * scaleX, 156.0f / 255.f, 205.0f / 255.f, 220.0f / 255.f);

    AEGfxSetRenderMode(AE_GFX_RM_COLOR);
    AEGfxTextureSet(NULL, 0, 0);
    AEGfxSetBlendMode(AE_GFX_BM_BLEND);
    sprintf_s(credits1_buffer, "EMERY QUEK");
    AEGfxGetPrintSize(fontID, credits1_buffer, 1.0f, credits_textWidth, credits_textHeight);
    AEGfxPrint(fontID, credits1_buffer, (getWinWidth() / (-2000.f * scaleX)), (getWinHeight() / (-30000.f * scaleY)), 0.6f * scaleX, 156.0f / 255.f, 205.0f / 255.f, 220.0f / 255.f);

    AEGfxSetRenderMode(AE_GFX_RM_COLOR);
    AEGfxTextureSet(NULL, 0, 0);
    AEGfxSetBlendMode(AE_GFX_BM_BLEND);
    sprintf_s(credits1_buffer, "LIU XU JIE");
    AEGfxGetPrintSize(fontID, credits1_buffer, 1.0f, credits_textWidth, credits_textHeight);
    AEGfxPrint(fontID, credits1_buffer, (getWinWidth() / (-2000.f * scaleX)), (getWinHeight() / (-3000.f * scaleY)), 0.6f * scaleX, 156.0f / 255.f, 205.0f / 255.f, 220.0f / 255.f);

    AEGfxSetRenderMode(AE_GFX_RM_COLOR);
    AEGfxTextureSet(NULL, 0, 0);
    AEGfxSetBlendMode(AE_GFX_BM_BLEND);
    sprintf_s(credits1_buffer, "ZHAN PENG");
    AEGfxGetPrintSize(fontID, credits1_buffer, 1.0f, credits_textWidth, credits_textHeight);
    AEGfxPrint(fontID, credits1_buffer, (getWinWidth() / (-2000.f * scaleX)), (getWinHeight() / (-1600.f * scaleY)), 0.6f * scaleX, 156.0f / 255.f, 205.0f / 255.f, 220.0f / 255.f);

    AEGfxSetRenderMode(AE_GFX_RM_COLOR);
    AEGfxTextureSet(NULL, 0, 0);
    AEGfxSetBlendMode(AE_GFX_BM_BLEND);
    sprintf_s(credits1_buffer, "Instructors:");
    AEGfxGetPrintSize(fontID, credits1_buffer, 1.0f, credits_textWidth, credits_textHeight);
    AEGfxPrint(fontID, credits1_buffer, (getWinWidth() / (-5000.f * scaleX)), (getWinHeight() / (1200.f * scaleY)), 0.6f * scaleX, 255.0f / 255.f, 255.0f / 255.f, 255.0f / 255.f);

    AEGfxSetRenderMode(AE_GFX_RM_COLOR);
    AEGfxTextureSet(NULL, 0, 0);
    AEGfxSetBlendMode(AE_GFX_BM_BLEND);
    sprintf_s(credits1_buffer, "CHENG DING XIANG");
    AEGfxGetPrintSize(fontID, credits1_buffer, 1.0f, credits_textWidth, credits_textHeight);
    AEGfxPrint(fontID, credits1_buffer, (getWinWidth() / (-5000.f * scaleX)), (getWinHeight() / (1800.f * scaleY)), 0.6f * scaleX, 156.0f / 255.f, 205.0f / 255.f, 220.0f / 255.f);

    AEGfxSetRenderMode(AE_GFX_RM_COLOR);
    AEGfxTextureSet(NULL, 0, 0);
    AEGfxSetBlendMode(AE_GFX_BM_BLEND);
    sprintf_s(credits1_buffer, "GERALD WONG HANG FENG");
    AEGfxGetPrintSize(fontID, credits1_buffer, 1.0f, credits_textWidth, credits_textHeight);
    AEGfxPrint(fontID, credits1_buffer, (getWinWidth() / (-5000.f * scaleX)), (getWinHeight() / (3800.f * scaleY)), 0.6f * scaleX, 156.0f / 255.f, 205.0f / 255.f, 220.0f / 255.f);

    AEGfxSetRenderMode(AE_GFX_RM_COLOR);
    AEGfxTextureSet(NULL, 0, 0);
    AEGfxSetBlendMode(AE_GFX_BM_BLEND);
    sprintf_s(credits1_buffer, "President:");
    AEGfxGetPrintSize(fontID, credits1_buffer, 1.0f, credits_textWidth, credits_textHeight);
    AEGfxPrint(fontID, credits1_buffer, (getWinWidth() / (-5000.f * scaleX)), (getWinHeight() / (-30000.f * scaleY)), 0.6f * scaleX, 255.0f / 255.f, 255.0f / 255.f, 255.0f / 255.f);

    AEGfxSetRenderMode(AE_GFX_RM_COLOR);
    AEGfxTextureSet(NULL, 0, 0);
    AEGfxSetBlendMode(AE_GFX_BM_BLEND);
    sprintf_s(credits1_buffer, "CLAUDE COMAIR");
    AEGfxGetPrintSize(fontID, credits1_buffer, 1.0f, credits_textWidth, credits_textHeight);
    AEGfxPrint(fontID, credits1_buffer, (getWinWidth() / (-5000.f * scaleX)), (getWinHeight() / (-3000.f * scaleY)), 0.6f * scaleX, 156.0f / 255.f, 205.0f / 255.f, 220.0f / 255.f);

    AEGfxSetRenderMode(AE_GFX_RM_COLOR);
    AEGfxTextureSet(NULL, 0, 0);
    AEGfxSetBlendMode(AE_GFX_BM_BLEND);
    sprintf_s(credits1_buffer, "Executives:");
    AEGfxGetPrintSize(fontID, credits1_buffer, 1.0f, credits_textWidth, credits_textHeight);
    AEGfxPrint(fontID, credits1_buffer, (getWinWidth() / (3500.f * scaleX)), (getWinHeight() / (1200.f * scaleY)), 0.6f * scaleX, 255.0f / 255.f, 255.0f / 255.f, 255.0f / 255.f);

    AEGfxSetRenderMode(AE_GFX_RM_COLOR);
    AEGfxTextureSet(NULL, 0, 0);
    AEGfxSetBlendMode(AE_GFX_BM_BLEND);
    sprintf_s(credits1_buffer, "BEN ELLINGER");
    AEGfxGetPrintSize(fontID, credits1_buffer, 1.0f, credits_textWidth, credits_textHeight);
    AEGfxPrint(fontID, credits1_buffer, (getWinWidth() / (3500.f * scaleX)), (getWinHeight() / (1450.f * scaleY)), 0.5f * scaleX, 156.0f / 255.f, 205.0f / 255.f, 220.0f / 255.f);

    AEGfxSetRenderMode(AE_GFX_RM_COLOR);
    AEGfxTextureSet(NULL, 0, 0);
    AEGfxSetBlendMode(AE_GFX_BM_BLEND);
    sprintf_s(credits1_buffer, "JASON CHU");
    AEGfxGetPrintSize(fontID, credits1_buffer, 1.0f, credits_textWidth, credits_textHeight);
    AEGfxPrint(fontID, credits1_buffer, (getWinWidth() / (3500.f * scaleX)), (getWinHeight() / (1825.f * scaleY)), 0.5f * scaleX, 156.0f / 255.f, 205.0f / 255.f, 220.0f / 255.f);

    AEGfxSetRenderMode(AE_GFX_RM_COLOR);
    AEGfxTextureSet(NULL, 0, 0);
    AEGfxSetBlendMode(AE_GFX_BM_BLEND);
    sprintf_s(credits1_buffer, "SAMIR ABOU SAMRA");
    AEGfxGetPrintSize(fontID, credits1_buffer, 1.0f, credits_textWidth, credits_textHeight);
    AEGfxPrint(fontID, credits1_buffer, (getWinWidth() / (3500.f * scaleX)), (getWinHeight() / (2450.f * scaleY)), 0.5f * scaleX, 156.0f / 255.f, 205.0f / 255.f, 220.0f / 255.f);

    AEGfxSetRenderMode(AE_GFX_RM_COLOR);
    AEGfxTextureSet(NULL, 0, 0);
    AEGfxSetBlendMode(AE_GFX_BM_BLEND);
    sprintf_s(credits1_buffer, "CHRISTOPHER COMAIR");
    AEGfxGetPrintSize(fontID, credits1_buffer, 1.0f, credits_textWidth, credits_textHeight);
    AEGfxPrint(fontID, credits1_buffer, (getWinWidth() / (3500.f * scaleX)), (getWinHeight() / (3800.f * scaleY)), 0.5f * scaleX, 156.0f / 255.f, 205.0f / 255.f, 220.0f / 255.f);

    AEGfxSetRenderMode(AE_GFX_RM_COLOR);
    AEGfxTextureSet(NULL, 0, 0);
    AEGfxSetBlendMode(AE_GFX_BM_BLEND);
    sprintf_s(credits1_buffer, "PRASANNA GHALI");
    AEGfxGetPrintSize(fontID, credits1_buffer, 1.0f, credits_textWidth, credits_textHeight);
    AEGfxPrint(fontID, credits1_buffer, (getWinWidth() / (3500.f * scaleX)), (getWinHeight() / (8450.f * scaleY)), 0.5f * scaleX, 156.0f / 255.f, 205.0f / 255.f, 220.0f / 255.f);

    AEGfxSetRenderMode(AE_GFX_RM_COLOR);
    AEGfxTextureSet(NULL, 0, 0);
    AEGfxSetBlendMode(AE_GFX_BM_BLEND);
    sprintf_s(credits1_buffer, "MICHAEL GATS");
    AEGfxGetPrintSize(fontID, credits1_buffer, 1.0f, credits_textWidth, credits_textHeight);
    AEGfxPrint(fontID, credits1_buffer, (getWinWidth() / (3500.f * scaleX)), (getWinHeight() / (-30000.f * scaleY)), 0.5f * scaleX, 156.0f / 255.f, 205.0f / 255.f, 220.0f / 255.f);

    AEGfxSetRenderMode(AE_GFX_RM_COLOR);
    AEGfxTextureSet(NULL, 0, 0);
    AEGfxSetBlendMode(AE_GFX_BM_BLEND);
    sprintf_s(credits1_buffer, "JOHN BAUER");
    AEGfxGetPrintSize(fontID, credits1_buffer, 1.0f, credits_textWidth, credits_textHeight);
    AEGfxPrint(fontID, credits1_buffer, (getWinWidth() / (3500.f * scaleX)), (getWinHeight() / (-5500.f * scaleY)), 0.5f * scaleX, 156.0f / 255.f, 205.0f / 255.f, 220.0f / 255.f);

    AEGfxSetRenderMode(AE_GFX_RM_COLOR);
    AEGfxTextureSet(NULL, 0, 0);
    AEGfxSetBlendMode(AE_GFX_BM_BLEND);
    sprintf_s(credits1_buffer, "MICHELLE COMAIR");
    AEGfxGetPrintSize(fontID, credits1_buffer, 1.0f, credits_textWidth, credits_textHeight);
    AEGfxPrint(fontID, credits1_buffer, (getWinWidth() / (3500.f * scaleX)), (getWinHeight() / (-3000.f * scaleY)), 0.5f * scaleX, 156.0f / 255.f, 205.0f / 255.f, 220.0f / 255.f);

    AEGfxSetRenderMode(AE_GFX_RM_COLOR);
    AEGfxTextureSet(NULL, 0, 0);
    AEGfxSetBlendMode(AE_GFX_BM_BLEND);
    sprintf_s(credits1_buffer, "DR. ERIK MOHARAMANN");
    AEGfxGetPrintSize(fontID, credits1_buffer, 1.0f, credits_textWidth, credits_textHeight);
    AEGfxPrint(fontID, credits1_buffer, (getWinWidth() / (3500.f * scaleX)), (getWinHeight() / (-2100.f * scaleY)), 0.5f * scaleX, 156.0f / 255.f, 205.0f / 255.f, 220.0f / 255.f);

    AEGfxSetRenderMode(AE_GFX_RM_COLOR);
    AEGfxTextureSet(NULL, 0, 0);
    AEGfxSetBlendMode(AE_GFX_BM_BLEND);
    sprintf_s(credits1_buffer, "RAYMOND YAN");
    AEGfxGetPrintSize(fontID, credits1_buffer, 1.0f, credits_textWidth, credits_textHeight);
    AEGfxPrint(fontID, credits1_buffer, (getWinWidth() / (3500.f * scaleX)), (getWinHeight() / (-1600.f * scaleY)), 0.5f * scaleX, 156.0f / 255.f, 205.0f / 255.f, 220.0f / 255.f);

    AEGfxSetRenderMode(AE_GFX_RM_COLOR);
    AEGfxTextureSet(NULL, 0, 0);
    AEGfxSetBlendMode(AE_GFX_BM_BLEND);
    sprintf_s(credits1_buffer, "MELVIN GONSALVEZ");
    AEGfxGetPrintSize(fontID, credits1_buffer, 1.0f, credits_textWidth, credits_textHeight);
    AEGfxPrint(fontID, credits1_buffer, (getWinWidth() / (3500.f * scaleX)), (getWinHeight() / (-1300.f * scaleY)), 0.5f * scaleX, 156.0f / 255.f, 205.0f / 255.f, 220.0f / 255.f);

    AEGfxSetRenderMode(AE_GFX_RM_COLOR);
    AEGfxTextureSet(NULL, 0, 0);
    AEGfxSetBlendMode(AE_GFX_BM_BLEND);
    sprintf_s(credits1_buffer, "ANGELA KUGLER");
    AEGfxGetPrintSize(fontID, credits1_buffer, 1.0f, credits_textWidth, credits_textHeight);
    AEGfxPrint(fontID, credits1_buffer, (getWinWidth() / (3500.f * scaleX)), (getWinHeight() / (-1085.f * scaleY)), 0.5f * scaleX, 156.0f / 255.f, 205.0f / 255.f, 220.0f / 255.f);

    AEGfxSetRenderMode(AE_GFX_RM_COLOR);
    AEGfxTextureSet(NULL, 0, 0);
    AEGfxSetBlendMode(AE_GFX_BM_BLEND);
    sprintf_s(credits1_buffer, "DR. CHARLES DUBA");
    AEGfxGetPrintSize(fontID, credits1_buffer, 1.0f, credits_textWidth, credits_textHeight);
    AEGfxPrint(fontID, credits1_buffer, (getWinWidth() / (3500.f * scaleX)), (getWinHeight() / (-925.f * scaleY)), 0.5f * scaleX, 156.0f / 255.f, 205.0f / 255.f, 220.0f / 255.f);

    AEGfxSetRenderMode(AE_GFX_RM_COLOR);
    AEGfxTextureSet(NULL, 0, 0);
    AEGfxSetBlendMode(AE_GFX_BM_BLEND);
    sprintf_s(credits1_buffer, "JOHNNY DEEK");
    AEGfxGetPrintSize(fontID, credits1_buffer, 1.0f, credits_textWidth, credits_textHeight);
    AEGfxPrint(fontID, credits1_buffer, (getWinWidth() / (3500.f * scaleX)), (getWinHeight() / (-810.f * scaleY)), 0.5f * scaleX, 156.0f / 255.f, 205.0f / 255.f, 220.0f / 255.f);

    AEGfxSetRenderMode(AE_GFX_RM_COLOR);
    AEGfxTextureSet(NULL, 0, 0);
    AEGfxSetBlendMode(AE_GFX_BM_BLEND);
    sprintf_s(creditsBack_buffer, "ALL CONTENT (C) 2023 DIGIPEN INSTITUTE OF TECHNOLOGY SINGAPORE, ALL RIGHTS RESERVED.");
    AEGfxGetPrintSize(fontID, creditsBack_buffer, 1.0f, credits_textWidth, credits_textHeight);
    AEGfxPrint(fontID, creditsBack_buffer, (getWinWidth() / (-1400.f * scaleX)), (getWinHeight() / (-798.f * scaleY)), 0.35f * scaleX, 156.0f / 255.f, 205.0f / 255.f, 220.0f / 255.f);

    AEGfxSetRenderMode(AE_GFX_RM_COLOR);
    AEGfxTextureSet(NULL, 0, 0);
    AEGfxSetBlendMode(AE_GFX_BM_BLEND);
    sprintf_s(creditsBack_buffer, "Back");
    AEGfxGetPrintSize(fontID, creditsBack_buffer, 1.0f, credits_textWidth, credits_textHeight);
    AEGfxPrint(fontID, creditsBack_buffer, (getWinWidth() / (1655.f * scaleX)), (getWinHeight() / (-798.f * scaleY)), 0.8f * scaleX, 156.0f / 255.f, 205.0f / 255.f, 220.0f / 255.f);
}
void Credits_Free(void) 
{

}
void Credits_Unload(void) 
{
    AEGfxMeshFree(pMeshCredits); 
    AEGfxMeshFree(BGmesh_credits);
}