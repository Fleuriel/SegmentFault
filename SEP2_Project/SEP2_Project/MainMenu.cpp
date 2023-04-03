#include "MainMenu.h"
#include "Main.h"


// Pointer to Mesh
AEGfxVertexList* pMesh = nullptr;
AEGfxVertexList* BGmesh = nullptr;
AEGfxVertexList* pMesh_exit = nullptr;

// Pre-definition for translations of buttons
f32 powerUpButton_transX;
f32 powerUpButton_transY;
f32 settingsButton_transX;
f32 settingsButton_transY;
f32 playButton_transX;
f32 playButton_transY;
f32 creditsButton_transX;
f32 creditsButton_transY;
f32 howToButton_transX;
f32 howToButton_transY;
f32 exitButton_transX;
f32 exitButton_transY;
f32 exitYesButton_transX;
f32 exitYesButton_transY;
f32 exitNoButton_transX;
f32 exitNoButton_transY;

// Powerups button mid points
f32 powerUpButton_midX;
f32 powerUpButton_midY;

// Settings button mid points
f32 settingsButton_midX;
f32 settingsButton_midY;

// Play button mid points
f32 playButton_midX;
f32 playButton_midY;

// Credits button mid points
f32 creditsButton_midX;
f32 creditsButton_midY;

// How to play button mid points
f32 howToButton_midX;
f32 howToButton_midY;

// Exit button mid points
f32 exitButton_midX;
f32 exitButton_midY;
f32 exitYesButton_midX;
f32 exitYesButton_midY;
f32 exitNoButton_midX;
f32 exitNoButton_midY;

// Pre-defintion for str buffers
char text_buffer[100]{};
char play_buffer[1024]{};
char upgrade_buffer[1024]{};
char settings_buffer[1024]{};
char credits_buffer[1024]{};
char exit_buffer[1024]{};
char highScore_buffer[1024]{};
char gold_buffer[1024]{};
float mainMenu_textWidth{}, mainMenu_textHeight{};

// Pre-defintions for Button rotation 
f32 buttonRotate_play;
f32 buttonRotate_settings;
f32 buttonRotate_powerups;
f32 buttonRotate_credits;
f32 buttonRotate_howTo;
f32 buttonRotate_exit;
f32 buttonRotate_exitYes;
f32 buttonRotate_exitNo;

// Condition check for exit button
bool mainMenu_areyouSure = true;

//Audio declaration
AEAudio MMBGM;
AEAudioGroup MMBGM_layer;
bool Audio_Playing = false;
extern float volume;

void Menu_Load(void)
{
    std::ifstream input{ "Assets\\SaveFiles\\Currency.txt" };
    std::ifstream input2{ "Assets\\SaveFiles\\HighScore.txt" };

    AEGfxSetBackgroundColor(0.019f, 0.27f, 0.411f);  // conversion -> rgb value/255

    //Background
    AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
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

    BGmesh = AEGfxMeshEnd();
    //end Background
    
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

    // Create buttons
    AEGfxMeshStart();

    AEGfxTriAdd(
        0.5f, 0.5f, 0xFFADD8E6, 1.0f, 0.0f,
        -1.2f, -0.5f, 0xFFADD8E6, 0.0f, 1.0f,
        0.5f, -0.5f, 0xFFADD8E6, 1.0f, 1.0f);
    AEGfxTriAdd(
        -1.2f, 0.5f, 0xFFADD8E6, 0.0f, 0.0f,
        -1.2f, -0.5f, 0xFFADD8E6, 0.0f, 1.0f,
        0.5f, 0.5f, 0xFFADD8E6, 1.0f, 0.0f);

    pMesh_exit = AEGfxMeshEnd();

    //Open save file of money
    if (input.good())
    {

        input >> Currency;
        input.close();
    }
    if (input2.good())
    {
        input2 >> currHighScoreMin >> currHighScoreSec;
        input2.close();
    }

    //Audio
    MMBGM = AEAudioLoadMusic("Assets\\Music\\Intro.wav");
    if (AEAudioIsValidGroup(MMBGM_layer) == 0) {
        MMBGM_layer = AEAudioCreateGroup();
    }
    else
        AEAudioSetGroupVolume(MMBGM_layer, volume);
    if (Audio_Playing == false) {
        if (volume == 0.f) {
            Audio_Playing = false;
        }
        else {
            AEAudioPlay(MMBGM, MMBGM_layer, volume, 1.f, -1);
            Audio_Playing = true;
        }
    }
    // plays an audio named bgm in an 
    // audio group named bgm_layer with 
    // 100% volume, 100% pitch, looped infinitely.

    
}

void Menu_Init(void) 
{

    // Gets the scale of 1366x768
    scaleX = getWinWidth() / 1366.0f;
    scaleY = getWinHeight() / 768.0f;


    powerUpButton_transX = -120.f * scaleX;
    powerUpButton_transY = -150.f * scaleY;
    settingsButton_transX = 180.0f * scaleX;
    settingsButton_transY = -150.0f * scaleY;
    playButton_transX = 30.0f * scaleX;
    playButton_transY = 0.0f * scaleY;
    creditsButton_transX = -585.0f * scaleX;
    creditsButton_transY = -355.0f * scaleY;
    howToButton_transX = 640.0f * scaleX;
    howToButton_transY = -355.0f * scaleY;
    exitButton_transX = 663.5f * scaleX;
    exitButton_transY = 355.0f * scaleY;
    BGtransX = 220.0f * scaleX;
    BGtransY = -40 * scaleY;

    buttonRotate_play = 0.f;
    buttonRotate_powerups = 0.f;
    buttonRotate_settings = 0.f;
    buttonRotate_credits = 0.f;
    buttonRotate_exit = 0.f;
    buttonRotate_exitYes = 0.f;
    buttonRotate_exitNo = 0.f;

    // Exit button confirmation translation
    exitYesButton_transX = -210.0f * scaleX;
    exitYesButton_transY = -65.0f * scaleX;
    exitNoButton_transX = 168.0f * scaleX;
    exitNoButton_transY = -65.0f * scaleX;


}

void Menu_Update(void) 
{
    // Initialize cursor coordinates
    s32 cursorX;
    s32 cursorY;
    AEInputGetCursorPosition(&cursorX, &cursorY);

    if (mainMenu_areyouSure == false)
    {
        // Powerups button mid points
        exitYesButton_midX = static_cast<f32>((getWinWidth() / 2.11) + exitYesButton_transX);
        exitYesButton_midY = static_cast<f32>((getWinHeight() / 2) - exitYesButton_transY);

        // Settings button mid points
        exitNoButton_midX = static_cast<f32>((getWinWidth() / 2.11) + exitNoButton_transX);
        exitNoButton_midY = static_cast<f32>((getWinHeight() / 2) - exitNoButton_transY);

        // Overlay button logic and defintions
        if (IsAreaClicked(exitYesButton_midX, exitYesButton_midY, 136.0f * scaleX, 50.0f * scaleY, cursorX, cursorY)
            && AEInputCheckReleased(AEVK_LBUTTON)) 
        {
            gGameStateNext = QUIT;
        }

        if (IsAreaClicked(exitNoButton_midX, exitNoButton_midY, 136.0f * scaleX, 50.0f * scaleY, cursorX, cursorY)
            && AEInputCheckReleased(AEVK_LBUTTON)) 
        {
            mainMenu_areyouSure = true;
        }

    }

    // Powerups button mid points
    powerUpButton_midX = static_cast<f32>((getWinWidth() / 2.11) + powerUpButton_transX);
    powerUpButton_midY = static_cast<f32>((getWinHeight() / 2) - powerUpButton_transY);

    // Settings button mid points
    settingsButton_midX = static_cast<f32>((getWinWidth() / 2.11) + settingsButton_transX);
    settingsButton_midY = static_cast<f32>((getWinHeight() / 2) - settingsButton_transY);

    // Play button mid points
    playButton_midX = static_cast<f32>((getWinWidth() / 2.11) + playButton_transX);
    playButton_midY = static_cast<f32>((getWinHeight() / 2 - playButton_transY));

    // Credits button mid points
    creditsButton_midX = static_cast<f32>((getWinWidth() / 2.09) + creditsButton_transX);
    creditsButton_midY = static_cast<f32>((getWinHeight() / 2) - creditsButton_transY);

    // Exit button mid points
    exitButton_midX = static_cast<f32>((getWinWidth() / 2.04) + exitButton_transX);
    exitButton_midY = static_cast<f32>((getWinHeight() / 2) - exitButton_transY);

    // How to play button mid points
    howToButton_midX = static_cast<f32>((getWinWidth() / 2.09) + howToButton_transX);
    howToButton_midY = static_cast<f32>((getWinHeight() / 2) - howToButton_transY);
    
    
    /********************************** Button Collision Logic Start ********************************************/
    if (mainMenu_areyouSure) 
    {
        if (IsAreaClicked(powerUpButton_midX, powerUpButton_midY, 170.0f * scaleX, 100.0f * scaleY, cursorX, cursorY)
            && AEInputCheckReleased(AEVK_LBUTTON))
        {
            gGameStateNext = UPGRADE;
        }

        else if (IsAreaClicked(settingsButton_midX, settingsButton_midY, 170.0f * scaleX, 100.0f * scaleY, cursorX, cursorY)
            && AEInputCheckReleased(AEVK_LBUTTON))
        {
            gGameStateNext = SETTINGS;
        }

        else if (IsAreaClicked(playButton_midX, playButton_midY, 170.0f * scaleX, 100.0f * scaleY, cursorX, cursorY)
            && AEInputCheckReleased(AEVK_LBUTTON))
        {
            AEAudioStopGroup(MMBGM_layer);
            gGameStateNext = PLAY;
        }


        else if (IsAreaClicked(exitButton_midX, exitButton_midY, 57.8f * scaleX, 50.0f * scaleY, cursorX, cursorY)
            && AEInputCheckReleased(AEVK_LBUTTON))
        {
            mainMenu_areyouSure = false;
        }

        else if (IsAreaClicked(creditsButton_midX, creditsButton_midY, 136.0f * scaleX, 50.0f * scaleY, cursorX, cursorY)
            && AEInputCheckReleased(AEVK_LBUTTON))
        {
            gGameStateNext = CREDITS;
        }

        else if (IsAreaClicked(howToButton_midX, howToButton_midY, 136.0f * scaleX, 50.0f * scaleY, cursorX, cursorY)
            && AEInputCheckReleased(AEVK_LBUTTON))
        {
            gGameStateNext = HOWTOPLAY;
        }
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

    else if (IsAreaClicked(exitButton_midX, exitButton_midY, 57.8f * scaleX, 50.0f * scaleY, cursorX, cursorY))
    {
        buttonRotate_exit = -0.10f;
    }

    else if (IsAreaClicked(exitYesButton_midX, exitYesButton_midY, 136.0f * scaleX, 50.0f * scaleY, cursorX, cursorY))
    {
        buttonRotate_exitYes = -0.10f;
    }

    else if (IsAreaClicked(exitNoButton_midX, exitNoButton_midY, 136.0f * scaleX, 50.0f * scaleY, cursorX, cursorY))
    {
        buttonRotate_exitNo = -0.10f;
    }

    else if (IsAreaClicked(creditsButton_midX, creditsButton_midY, 136.0f * scaleX, 50.0f * scaleY, cursorX, cursorY))
    {
        buttonRotate_credits = -0.10f;
    }

    else if (IsAreaClicked(howToButton_midX, howToButton_midY, 136.0f * scaleX, 50.0f * scaleY, cursorX, cursorY))
    {
        buttonRotate_howTo = -0.10f;
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

    if (!IsAreaClicked(howToButton_midX, howToButton_midY, 136.0f * scaleX, 50.0f * scaleY, cursorX, cursorY))
    {
        buttonRotate_howTo = 0.0f;
    }

    if (!IsAreaClicked(exitButton_midX, exitButton_midY, 57.8f * scaleX, 50.0f * scaleY, cursorX, cursorY))
    {
        buttonRotate_exit = 0.0f;
    }

    if (!IsAreaClicked(exitYesButton_midX, exitYesButton_midY, 136.0f * scaleX, 50.0f * scaleY, cursorX, cursorY))
    {
        buttonRotate_exitYes = 0.0f;
    }

    if (!IsAreaClicked(exitNoButton_midX, exitNoButton_midY, 136.0f * scaleX, 50.0f * scaleY, cursorX, cursorY))
    {
        buttonRotate_exitNo = 0.0f;
    }

    /********************************** Button Animation Logic End ********************************************/

    
}
void Menu_Draw(void)
{
    //Background
    AEGfxTexture* BGtexture = AEGfxTextureLoad("Assets\\Assets\\MainMenuBackground.png");

    //Draw Background
    AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
    AEGfxSetTintColor(0.8f, 0.8f, 0.8f, 0.8f);
    AEGfxSetBlendMode(AE_GFX_BM_BLEND);
    AEGfxSetTransparency(1.0f);
    AEGfxTextureSet(BGtexture, 0, 0);
    AEMtx33 scale0 = { 0 };
    AEMtx33Scale(&scale0, 1100, 800);
    AEMtx33 rotate0 = { 0 };
    AEMtx33Rot(&rotate0, 0.f);
    AEMtx33 translate0 = { 0 };
    AEMtx33Trans(&translate0, BGtransX, BGtransY);
    AEMtx33 transform0 = { 0 };
    AEMtx33Concat(&transform0, &rotate0, &scale0);
    AEMtx33Concat(&transform0, &translate0, &transform0);
    AEGfxSetTransform(transform0.m);
    AEGfxMeshDraw(BGmesh, AE_GFX_MDM_TRIANGLES);
    //Finish Background draw
   
 
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
    AEGfxSetTransparency(1.0f);
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
    AEMtx33Rot(&rotate4, buttonRotate_exit);
    AEMtx33 translate4 = { 0 };
    AEMtx33Trans(&translate4, exitButton_transX, exitButton_transY);
    AEMtx33 transform4 = { 0 };
    AEMtx33Concat(&transform4, &rotate4, &scale4);
    AEMtx33Concat(&transform4, &translate4, &transform4);
    AEGfxSetTransform(transform4.m);
    AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);

    // Button 6, How to play button
    AEGfxSetRenderMode(AE_GFX_RM_COLOR);
    AEGfxTextureSet(NULL, 0, 0);
    AEMtx33 scale5 = { 0 };
    AEMtx33Scale(&scale5, 80.f * scaleX, 50.f * scaleY);
    AEMtx33 rotate5 = { 0 };
    AEMtx33Rot(&rotate5, buttonRotate_howTo);
    AEMtx33 translate5 = { 0 };
    AEMtx33Trans(&translate5, howToButton_transX, howToButton_transY);
    AEMtx33 transform5 = { 0 };
    AEMtx33Concat(&transform5, &rotate5, &scale5);
    AEMtx33Concat(&transform5, &translate5, &transform5);
    AEGfxSetTransform(transform5.m);
    AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);

    // Rendering texts for the screen

    // Title start
    AEGfxSetRenderMode(AE_GFX_RM_COLOR);
    AEGfxTextureSet(NULL, 0, 0);
    AEGfxSetBlendMode(AE_GFX_BM_BLEND);
    sprintf_s(text_buffer, "AMONG");
    AEGfxPrint(fontID, text_buffer, (getWinWidth() / (-6900.f * scaleX)), (getWinHeight() / (1100.f * scaleY)), 1.5f * scaleX, 180.0f / 255.f, 24.0f / 255.f, 7.0f / 255.f);

    AEGfxSetRenderMode(AE_GFX_RM_COLOR);
    AEGfxTextureSet(NULL, 0, 0);
    AEGfxSetBlendMode(AE_GFX_BM_BLEND);
    sprintf_s(text_buffer, "THEM");
    AEGfxPrint(fontID, text_buffer, (getWinWidth() / (-8700.f * scaleX)), (getWinHeight() / (1700.f * scaleY)), 1.5f * scaleX, 180.0f / 255.f, 24.0f / 255.f, 7.0f / 255.f);

    // Title end

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
    sprintf_s(credits_buffer, "how to play");
    AEGfxGetPrintSize(fontID, credits_buffer, 1.0f, mainMenu_textWidth, mainMenu_textHeight);
    AEGfxPrint(fontID, credits_buffer, (getWinWidth() / (1690.f * scaleX)), (getWinHeight() / (-800.f * scaleY)), 0.45f * scaleX, 156.0f / 255.f, 205.0f / 255.f, 220.0f / 255.f);

    AEGfxSetRenderMode(AE_GFX_RM_COLOR);
    AEGfxTextureSet(NULL, 0, 0);
    AEGfxSetBlendMode(AE_GFX_BM_BLEND);
    sprintf_s(exit_buffer, "X");
    AEGfxGetPrintSize(fontID, exit_buffer, 1.0f, mainMenu_textWidth, mainMenu_textHeight);
    AEGfxPrint(fontID, exit_buffer, (getWinWidth() / (1466.f * scaleX)), (getWinHeight() / (880.f * scaleY)), 1.f * scaleX, 222.0f / 255.f, 49.0f / 255.f, 99.0f / 255.f);

    if (currHighScoreSec < 10) {
        AEGfxSetRenderMode(AE_GFX_RM_COLOR);
        AEGfxTextureSet(NULL, 0, 0);
        AEGfxSetBlendMode(AE_GFX_BM_BLEND);
        sprintf_s(highScore_buffer, "Highscore: %.f:0%.f", currHighScoreMin, currHighScoreSec);
        AEGfxGetPrintSize(fontID, highScore_buffer, 1.0f, mainMenu_textWidth, mainMenu_textHeight);
        AEGfxPrint(fontID, highScore_buffer, (getWinWidth() / (-1400.f * scaleX)), (getWinHeight() / (880.f * scaleY)), 1.f * scaleX, 80.0f / 255.f, 200.0f / 255.f, 120.0f / 255.f);
    }
    else {
        AEGfxSetRenderMode(AE_GFX_RM_COLOR);
        AEGfxTextureSet(NULL, 0, 0);
        AEGfxSetBlendMode(AE_GFX_BM_BLEND);
        sprintf_s(highScore_buffer, "Highscore: %.f:%.f", currHighScoreMin, currHighScoreSec);
        AEGfxGetPrintSize(fontID, highScore_buffer, 1.0f, mainMenu_textWidth, mainMenu_textHeight);
        AEGfxPrint(fontID, highScore_buffer, (getWinWidth() / (-1400.f * scaleX)), (getWinHeight() / (880.f * scaleY)), 1.f * scaleX, 80.0f / 255.f, 200.0f / 255.f, 120.0f / 255.f);
    }

    AEGfxSetRenderMode(AE_GFX_RM_COLOR);
    AEGfxTextureSet(NULL, 0, 0);
    AEGfxSetBlendMode(AE_GFX_BM_BLEND);
    sprintf_s(gold_buffer, "Gold: %d", Currency);
    AEGfxGetPrintSize(fontID, gold_buffer, 1.0f, mainMenu_textWidth, mainMenu_textHeight);
    AEGfxPrint(fontID, gold_buffer, (getWinWidth() / (-1400.f * scaleX)), (getWinHeight() / (1100.f * scaleY)), 1.f * scaleX, 212.0f / 255.f, 175.0f / 255.f, 55.0f / 255.f);
    if(BGtexture!=nullptr)
    AEGfxTextureUnload(BGtexture);

    if (mainMenu_areyouSure == false)
    {
        // Drawing the yes/no overlay on the screen
        AEGfxTextureSet(NULL, 0, 0);
        AEGfxSetRenderMode(AE_GFX_RM_COLOR);
        AEGfxSetTransparency(0.5f);
        AEMtx33 scale8 = { 0 };
        AEMtx33Scale(&scale8, 500.f, 300.f);
        AEMtx33 rotate8 = { 0 };
        AEMtx33Rot(&rotate8, 0.f);
        AEMtx33 translate8 = { 0 };
        AEMtx33Trans(&translate8, 175.f, -10.f);
        AEMtx33 transform8 = { 0 };
        AEMtx33Concat(&transform8, &rotate8, &scale8);
        AEMtx33Concat(&transform8, &translate8, &transform8);
        AEGfxSetTransform(transform8.m);
        AEGfxMeshDraw(pMesh_exit, AE_GFX_MDM_TRIANGLES);

        AEGfxSetRenderMode(AE_GFX_RM_COLOR);
        AEGfxSetTransparency(0.3f);
        AEGfxTextureSet(NULL, 0, 0);
        AEMtx33 scale6 = { 0 };
        AEMtx33Scale(&scale6, 80.f * scaleX, 50.f * scaleY);
        AEMtx33 rotate6 = { 0 };
        AEMtx33Rot(&rotate6, buttonRotate_exitYes);
        AEMtx33 translate6 = { 0 };
        AEMtx33Trans(&translate6, exitYesButton_transX, exitYesButton_transY);
        AEMtx33 transform6 = { 0 };
        AEMtx33Concat(&transform6, &rotate6, &scale6);
        AEMtx33Concat(&transform6, &translate6, &transform6);
        AEGfxSetTransform(transform6.m);
        AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);

        AEGfxSetRenderMode(AE_GFX_RM_COLOR);
        AEGfxSetTransparency(0.3f);
        AEGfxTextureSet(NULL, 0, 0);
        AEMtx33 scale7 = { 0 };
        AEMtx33Scale(&scale7, 80.f * scaleX, 50.f * scaleY);
        AEMtx33 rotate7 = { 0 };
        AEMtx33Rot(&rotate7, buttonRotate_exitNo);
        AEMtx33 translate7 = { 0 };
        AEMtx33Trans(&translate7, exitNoButton_transX, exitNoButton_transY);
        AEMtx33 transform7 = { 0 };
        AEMtx33Concat(&transform7, &rotate7, &scale7);
        AEMtx33Concat(&transform7, &translate7, &transform7);
        AEGfxSetTransform(transform7.m);
        AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);

        // Rendering texts for overlay
        AEGfxSetRenderMode(AE_GFX_RM_COLOR);
        AEGfxTextureSet(NULL, 0, 0);
        AEGfxSetBlendMode(AE_GFX_BM_BLEND);
        sprintf_s(exit_buffer, "ARE YOU SURE?");
        AEGfxPrint(fontID, exit_buffer, (getWinWidth() / (-3000.f * scaleX)), (getWinHeight() / (5000.f * scaleY)), 0.7f * scaleX, 0.0f / 255.f, 23.0f / 255.f, 54.0f / 255.f);

        AEGfxSetRenderMode(AE_GFX_RM_COLOR);
        AEGfxTextureSet(NULL, 0, 0);
        AEGfxSetBlendMode(AE_GFX_BM_BLEND);
        sprintf_s(exit_buffer, "YES");
        AEGfxPrint(fontID, exit_buffer, (getWinWidth() / (-3425.f * scaleX)), (getWinHeight() / (-3800.f * scaleY)), 0.7f * scaleX, 0.0f / 255.f, 23.0f / 255.f, 54.0f / 255.f);

        AEGfxSetRenderMode(AE_GFX_RM_COLOR);
        AEGfxTextureSet(NULL, 0, 0);
        AEGfxSetBlendMode(AE_GFX_BM_BLEND);
        sprintf_s(exit_buffer, "NO");
        AEGfxPrint(fontID, exit_buffer, (getWinWidth() / (8100.f * scaleX)), (getWinHeight() / (-3800.f * scaleY)), 0.7f * scaleX, 0.0f / 255.f, 23.0f / 255.f, 54.0f / 255.f);
    }
}

void Menu_Free(void) 
{

}
void Menu_Unload(void)
{
    std::cout << gGameStatePrev << "\n";
    std::cout << gGameStateNext <<"\n";
    AEGfxMeshFree(pMesh);
    AEGfxMeshFree(pMesh_exit);
    AEGfxMeshFree(BGmesh);
    if(gGameStateNext == 1)
        Audio_Playing = false;
}