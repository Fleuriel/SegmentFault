#include "MainMenu.h"
#include "Main.h"



// Pointer to Mesh
AEGfxVertexList* pMesh = nullptr;

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

// Pre-defintion for str buffers
char play_buffer[1024]{};
char upgrade_buffer[1024]{};
char settings_buffer[1024]{};
char credits_buffer[1024]{};
char exit_buffer[1024]{};
float mainMenu_textWidth{}, mainMenu_textHeight{};

// Pre-defintions for Button rotation 
double buttonRotate_play;
double buttonRotate_settings;
double buttonRotate_powerups;
double buttonRotate_credits;


void Menu_Load(void)
{
   

    AEGfxSetBackgroundColor(0.019f, 0.27f, 0.411f);  // conversion -> rgb value/255

    // Create buttons
    AEGfxMeshStart();

    AEGfxTriAdd(
        0.5f, 0.5f, 0xFF001736, 1.0f, 0.0f,
        -1.2f, -0.5f, 0xFF001736, 0.0f, 1.0f,
        0.5f, -0.5f, 0xFF001736, 1.0f, 1.0f);
    AEGfxTriAdd(
        -1.2f, 0.5f, 0xFF001736, 0.0f, 0.0f,
        -1.2f, -0.5f, 0xFF001736, 0.0f, 1.0f,
        0.5f, 0.5f, 0xFF001736, 1.0f, 0.0f);

    pMesh = AEGfxMeshEnd();




}

void Menu_Init(void) 
{
    // Gets the scale of 1366x768
    scaleX = getWinWidth() / 1366.f; 
    scaleY = getWinHeight() / 768.f;


    powerUpButton_transX = -120.f * scaleX;
    powerUpButton_transY = -150.f * scaleY;
    settingsButton_transX = 180.0f * scaleX;
    settingsButton_transY = -150.0f * scaleY;
    playButton_transX = 30.0f * scaleX;
    playButton_transY = 0.0f * scaleY;
    creditsButton_transX = -585.0f * scaleX;
    creditsButton_transY = -355.0f * scaleY;
    exitButton_transX = 663.5f * scaleX;
    exitButton_transY = 355.0f * scaleY;
    
    buttonRotate_play = 0.f;
    buttonRotate_powerups = 0.f;
    buttonRotate_settings = 0.f;
    buttonRotate_credits = 0.f;

}

void Menu_Update(void) 
{
    // Initialize cursor coordinates
    s32 cursorX;
    s32 cursorY;
    AEInputGetCursorPosition(&cursorX, &cursorY);

    
    //printf("%d\n%f\n", AEGetWindowHeight(), getWinHeight());

    // Powerups button mid points
    float powerUpButton_midX = (getWinWidth() / 2.11) + powerUpButton_transX;
    float powerUpButton_midY = (getWinHeight() / 2) - powerUpButton_transY;

    // Settings button mid points
    float settingsButton_midX = (getWinWidth() / 2.11) + settingsButton_transX;
    float settingsButton_midY = (getWinHeight() / 2) - settingsButton_transY;

    // Play button mid points
    float playButton_midX = (getWinWidth() / 2.11) + playButton_transX;
    float playButton_midY = getWinHeight() / 2 - playButton_transY;

    // Credits button mid points
    float creditsButton_midX = (getWinWidth() / 2.09) + creditsButton_transX;
    float creditsButton_midY = (getWinHeight() / 2) - creditsButton_transY;

    // Exit button mid points
    float exitButton_midX = (getWinWidth() / 2.04) + exitButton_transX;
    float exitButton_midY = (getWinHeight() / 2) - exitButton_transY;
    
    // printf("%d\n%d\n", cursorX, cursorY);  //debug
    // printf("%f\n%f\n", button1_midX, button1_midY);  //debug
    
    /********************************** Button Collision Logic Start ********************************************/
    if (IsAreaClicked(powerUpButton_midX, powerUpButton_midY, 170.0f * scaleX, 100.0f * scaleY, cursorX, cursorY)
        && AEInputCheckTriggered(AEVK_LBUTTON)) 
    {
        gGameStateNext = UPGRADE;
        printf("Goto powerups\n");
    }

    else if (IsAreaClicked(settingsButton_midX, settingsButton_midY, 170.0f * scaleX, 100.0f * scaleY, cursorX, cursorY)
        && AEInputCheckTriggered(AEVK_LBUTTON)) 
    {
        gGameStateNext = SETTINGS;
        printf("Goto Settings\n");
    }

    else if (IsAreaClicked(playButton_midX, playButton_midY, 170.0f * scaleX, 100.0f * scaleY, cursorX, cursorY)
        && AEInputCheckTriggered(AEVK_LBUTTON)) 
    {
        gGameStateNext = PLAY;
        printf("Goto Play\n");
    }

    /*
    else if (IsAreaClicked(creditsButton_midX, creditsButton_midY, 136.0f * scaleX, 50.0f * scaleY, cursorX, cursorY)
        && AEInputCheckTriggered(AEVK_LBUTTON)) {
        gGameStateNext = CREDITS;
        printf("Goto Credits\n");
    }*/

    else if (IsAreaClicked(exitButton_midX, exitButton_midY, 57.8f * scaleX, 50.0f * scaleY, cursorX, cursorY)
        && AEInputCheckTriggered(AEVK_LBUTTON)) 
    {
        gGameStateNext = QUIT;
        printf("QUIT\n");
    }
    /********************************** Button Collision Logic End ********************************************/


    /********************************** Button Animation Logic Start ********************************************/
    if (IsAreaClicked(powerUpButton_midX, powerUpButton_midY, 170.0f * scaleX, 100.0f * scaleY, cursorX, cursorY)) 
    {
        buttonRotate_powerups = -0.10f;
    }

    else if (IsAreaClicked(settingsButton_midX, settingsButton_midY, 170.0f * scaleX, 100.0f * scaleY, cursorX, cursorY)) 
    {
        buttonRotate_settings = -0.10f;
    }

    else if (IsAreaClicked(playButton_midX, playButton_midY, 170.0f * scaleX, 100.0f * scaleY, cursorX, cursorY)) 
    {
        buttonRotate_play = -0.10f;
    }

    
    else if (IsAreaClicked(creditsButton_midX, creditsButton_midY, 136.0f * scaleX, 50.0f * scaleY, cursorX, cursorY)
        && AEInputCheckTriggered(AEVK_LBUTTON)) 
    {
        gGameStateNext = CREDITS;
        printf("Goto Credits\n");
    }

    else if (IsAreaClicked(creditsButton_midX, creditsButton_midY, 136.0f * scaleX, 50.0f * scaleY, cursorX, cursorY))
    {
        buttonRotate_credits = -0.10f;
    }

    if (!IsAreaClicked(powerUpButton_midX, powerUpButton_midY, 170.0f * scaleX, 100.0f * scaleY, cursorX, cursorY))
    {
        buttonRotate_powerups = 0.0f;
    }

    if (!IsAreaClicked(settingsButton_midX, settingsButton_midY, 170.0f * scaleX, 100.0f * scaleY, cursorX, cursorY))
    {
        buttonRotate_settings = 0.0f;
    }

    if (!IsAreaClicked(playButton_midX, playButton_midY, 170.0f * scaleX, 100.0f * scaleY, cursorX, cursorY))
    {
        buttonRotate_play = 0.0f;
    }

    if (!IsAreaClicked(creditsButton_midX, creditsButton_midY, 136.0f * scaleX, 50.0f * scaleY, cursorX, cursorY))
    {
        buttonRotate_credits = 0.0f;
    }

    /********************************** Button Animation Logic End ********************************************/

    
}
void Menu_Draw(void)
{
    
    // Button 1, Power-ups button
    AEGfxTextureSet(NULL, 0, 0);
    AEGfxSetRenderMode(AE_GFX_RM_COLOR);
    AEMtx33 scale = { 0 };
    AEMtx33Scale(&scale, 100.f * scaleX, 100.f * scaleY);
    AEMtx33 rotate = { 0 };
    AEMtx33Rot(&rotate, buttonRotate_powerups);
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
    AEMtx33Rot(&rotate1, buttonRotate_settings);
    AEMtx33 translate1 = { 0 };
    AEMtx33Trans(&translate1, settingsButton_transX, settingsButton_transY);
    AEMtx33 transform1 = { 0 };
    AEMtx33Concat(&transform1, &rotate1, &scale1);
    AEMtx33Concat(&transform1, &translate1, &transform1);
    AEGfxSetTransform(transform1.m);
    AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);

    // Button 3, Play button
    AEGfxSetRenderMode(AE_GFX_RM_COLOR);
    AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
    AEGfxSetBlendMode(AE_GFX_BM_BLEND);
    AEGfxSetTransparency(1.0f);
    AEGfxTextureSet(NULL, 0, 0);
    AEMtx33 scale2 = { 0 };
    AEMtx33Scale(&scale2, 100.f * scaleX, 100.f * scaleY);
    AEMtx33 rotate2 = { 0 };
    AEMtx33Rot(&rotate2, buttonRotate_play);
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
    AEMtx33Rot(&rotate3, buttonRotate_credits);
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
    AEMtx33Scale(&scale4, 34.f * scaleX, 50.f * scaleY);
    AEMtx33 rotate4 = { 0 };
    AEMtx33Rot(&rotate4, 0.f);
    AEMtx33 translate4 = { 0 };
    AEMtx33Trans(&translate4, exitButton_transX, exitButton_transY);
    AEMtx33 transform4 = { 0 };
    AEMtx33Concat(&transform4, &rotate4, &scale4);
    AEMtx33Concat(&transform4, &translate4, &transform4);
    AEGfxSetTransform(transform4.m);
    AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);

    // Rendering texts for the screen
    AEGfxSetRenderMode(AE_GFX_RM_COLOR);
    AEGfxTextureSet(NULL, 0, 0);
    AEGfxSetBlendMode(AE_GFX_BM_BLEND);
    sprintf_s(play_buffer, "Play");
    AEGfxGetPrintSize(fontID, play_buffer, 1.0f, mainMenu_textWidth, mainMenu_textHeight);
    AEGfxPrint(fontID, play_buffer, (getWinWidth() / (-17200.f * scaleX)), (getWinHeight() / (-17000.f * scaleY)), 1.f * scaleX, 156.0f / 255.f, 205.0f / 255.f, 220.0f / 255.f);

    AEGfxSetRenderMode(AE_GFX_RM_COLOR);
    AEGfxTextureSet(NULL, 0, 0);
    AEGfxSetBlendMode(AE_GFX_BM_BLEND);
    sprintf_s(upgrade_buffer, "Upgrade");
    AEGfxGetPrintSize(fontID, upgrade_buffer, 1.0f, mainMenu_textWidth, mainMenu_textHeight);
    AEGfxPrint(fontID, upgrade_buffer, (getWinWidth() / ( - 3950.f * scaleX)), (getWinHeight() / (- 1800.f * scaleY)), 0.8f * scaleX, 156.0f / 255.f, 205.0f / 255.f, 220.0f / 255.f);

    AEGfxSetRenderMode(AE_GFX_RM_COLOR);
    AEGfxTextureSet(NULL, 0, 0);
    AEGfxSetBlendMode(AE_GFX_BM_BLEND);
    sprintf_s(settings_buffer, "Settings");
    AEGfxGetPrintSize(fontID, settings_buffer, 1.0f, mainMenu_textWidth, mainMenu_textHeight);
    AEGfxPrint(fontID, settings_buffer, (getWinWidth() / (13300.f * scaleX)), (getWinHeight() / ( - 1800.f * scaleY)), 0.8f * scaleX, 156.0f / 255.f, 205.0f / 255.f, 220.0f / 255.f);

    AEGfxSetRenderMode(AE_GFX_RM_COLOR);
    AEGfxTextureSet(NULL, 0, 0);
    AEGfxSetBlendMode(AE_GFX_BM_BLEND);
    sprintf_s(credits_buffer, "credits");
    AEGfxGetPrintSize(fontID, credits_buffer, 1.0f, mainMenu_textWidth, mainMenu_textHeight);
    AEGfxPrint(fontID, credits_buffer, (getWinWidth() / ( - 1393.f * scaleX)), (getWinHeight() / ( - 800.f * scaleY)), 0.7f * scaleX, 156.0f / 255.f, 205.0f / 255.f, 220.0f / 255.f);

    AEGfxSetRenderMode(AE_GFX_RM_COLOR);
    AEGfxTextureSet(NULL, 0, 0);
    AEGfxSetBlendMode(AE_GFX_BM_BLEND);
    sprintf_s(exit_buffer, "X");
    AEGfxGetPrintSize(fontID, exit_buffer, 1.0f, mainMenu_textWidth, mainMenu_textHeight);
    AEGfxPrint(fontID, exit_buffer, (getWinWidth() / (1466.f * scaleX)), (getWinHeight() / (880.f * scaleY)), 1.f * scaleX, 222.0f / 255.f, 49.0f / 255.f, 99.0f / 255.f);

}

void Menu_Free(void) 
{

}
void Menu_Unload(void)
{
    AEGfxMeshFree(pMesh);

    // AEGfxTextureUnload(startTex);
}