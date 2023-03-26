#include "Credits.h"
#include "Main.h"


// Pointer to Mesh
AEGfxVertexList* pMeshCredits = nullptr;

// Pre-definition
AEGfxTexture* startTex_credits;

// Pre-definition for translations of buttons
double creditsPic_transX;
double creditsPic_transY;
double creditsBackbutton_transX;
double creditsBackbutton_transY;


// Pre-defintion for str buffers
char creditsBack_buffer[1024]{};
char credits1_buffer[1024]{};
char credits2_buffer[1024]{};
char credits3_buffer[1024]{};
char credits4_buffer[1024]{};
float credits_textWidth{}, credits_textHeight{};

// Pre-definition of Rotation
double buttonRotate_creditsBack;

void Credits_Load(void) 
{
    AEGfxSetBackgroundColor(0.019f, 0.27f, 0.411f);  // conversion -> rgb value/255

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

    //// Button 1, TOHRU BUTTON
    //AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
    //AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
    //AEGfxSetBlendMode(AE_GFX_BM_BLEND);
    //AEGfxSetTransparency(1.0f);
    //AEGfxTextureSet(startTex_credits, 0, 0);
    //AEMtx33 scale = { 0 };
    //AEMtx33Scale(&scale, 100.f * scaleX, 100.f * scaleY);
    //AEMtx33 rotate = { 0 };
    //AEMtx33Rot(&rotate, picRotate);
    //AEMtx33 translate = { 0 };
    //AEMtx33Trans(&translate, creditsPic_transX, creditsPic_transY);
    //AEMtx33 transform = { 0 };
    //AEMtx33Concat(&transform, &rotate, &scale);
    //AEMtx33Concat(&transform, &translate, &transform);
    //AEGfxSetTransform(transform.m);
    //AEGfxMeshDraw(pMeshCredits, AE_GFX_MDM_TRIANGLES);



    // Rendering texts for the screen
    AEGfxSetRenderMode(AE_GFX_RM_COLOR);
    AEGfxTextureSet(NULL, 0, 0);
    AEGfxSetBlendMode(AE_GFX_BM_BLEND);
    sprintf_s(credits1_buffer, "Aloysius Ang");
    AEGfxGetPrintSize(fontID, credits1_buffer, 1.0f, credits_textWidth, credits_textHeight);
    AEGfxPrint(fontID, credits1_buffer, (getWinWidth() / (-2800.f * scaleX)), (getWinHeight() / (1200.f * scaleY)), 1.f * scaleX, 156.0f / 255.f, 205.0f / 255.f, 220.0f / 255.f);

    AEGfxSetRenderMode(AE_GFX_RM_COLOR);
    AEGfxTextureSet(NULL, 0, 0);
    AEGfxSetBlendMode(AE_GFX_BM_BLEND);
    sprintf_s(credits1_buffer, "Angus Tan");
    AEGfxGetPrintSize(fontID, credits1_buffer, 1.0f, credits_textWidth, credits_textHeight);
    AEGfxPrint(fontID, credits1_buffer, (getWinWidth() / (-2800.f * scaleX)), (getWinHeight() / (1800.f * scaleY)), 1.f * scaleX, 156.0f / 255.f, 205.0f / 255.f, 220.0f / 255.f);

    AEGfxSetRenderMode(AE_GFX_RM_COLOR);
    AEGfxTextureSet(NULL, 0, 0);
    AEGfxSetBlendMode(AE_GFX_BM_BLEND);
    sprintf_s(credits1_buffer, "Emery Quek");
    AEGfxGetPrintSize(fontID, credits1_buffer, 1.0f, credits_textWidth, credits_textHeight);
    AEGfxPrint(fontID, credits1_buffer, (getWinWidth() / (-2800.f * scaleX)), (getWinHeight() / (3800.f * scaleY)), 1.f * scaleX, 156.0f / 255.f, 205.0f / 255.f, 220.0f / 255.f);

    AEGfxSetRenderMode(AE_GFX_RM_COLOR);
    AEGfxTextureSet(NULL, 0, 0);
    AEGfxSetBlendMode(AE_GFX_BM_BLEND);
    sprintf_s(credits1_buffer, "Liu Xu Jie");
    AEGfxGetPrintSize(fontID, credits1_buffer, 1.0f, credits_textWidth, credits_textHeight);
    AEGfxPrint(fontID, credits1_buffer, (getWinWidth() / (-2800.f * scaleX)), (getWinHeight() / (-30000.f * scaleY)), 1.f * scaleX, 156.0f / 255.f, 205.0f / 255.f, 220.0f / 255.f);

    AEGfxSetRenderMode(AE_GFX_RM_COLOR);
    AEGfxTextureSet(NULL, 0, 0);
    AEGfxSetBlendMode(AE_GFX_BM_BLEND);
    sprintf_s(credits1_buffer, "Zhan Peng");
    AEGfxGetPrintSize(fontID, credits1_buffer, 1.0f, credits_textWidth, credits_textHeight);
    AEGfxPrint(fontID, credits1_buffer, (getWinWidth() / (-2800.f * scaleX)), (getWinHeight() / (-3000.f * scaleY)), 1.f * scaleX, 156.0f / 255.f, 205.0f / 255.f, 220.0f / 255.f);

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
    // AEGfxTextureUnload(startTex_credits);
}