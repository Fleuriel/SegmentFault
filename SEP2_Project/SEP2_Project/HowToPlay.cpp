/******************************************************************************/
/*!
\file		HowToPlay.cpp
\author		Ang Jun Sheng Aloysius, a.junshengaloysius, 2201807
\par		a.junshengaloysius@digipen.edu
\brief		Contains the definitions of functions that print out instructions for the game onto the screen.

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
 */
 /******************************************************************************/

#include "HowToPlay.h"
#include "Main.h"

// Pointer to Mesh
AEGfxVertexList* pMeshHowToPlay = nullptr;
AEGfxVertexList* BGmesh_HowToPlay = nullptr;

// Pre-definition
AEGfxTexture* BGtexture_HowToPlay;
f32 BGtransX_HowToPlay, BGtransY_HowToPlay;

// Pre-definition for buttons
f32 howTobackButton_transX;
f32 howTobackButton_transY;

// Quit button mid point
f32 howTobackButton_midX;
f32 howTobackButton_midY;

// Pre-defintion
char howtoplay_buffer[1024]{};
char instructions1_buffer[1024]{};
char instructions2_buffer[1024]{};
char instructions3_buffer[1024]{};
char howToBackButton_buffer[1024]{};
float howTo_textWidth{}, howTo_textHeight{};

// Pre-definition of Rotation
f32 buttonRotate_howToBack;


/******************************************************************************/
/*!
    "Load" function of this state
*/
/******************************************************************************/
/*****************************************************************

  \brief
      Loads backgrounds and creates the shapes of the objects.

  \param[in] void
      Takes in no params.

********************************************************************/
void HowToPlay_Load(void)
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

    pMeshHowToPlay = AEGfxMeshEnd();

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

    BGmesh_HowToPlay = AEGfxMeshEnd();

    // Load texture for BG
    BGtexture_HowToPlay = AEGfxTextureLoad("Assets\\Assets\\MainMenuBackground.png");
}

/******************************************************************************/
/*!
    "Initialize" function of this state
*/
/******************************************************************************/
/*!*****************************************************************

  \brief
      Initializes the variables needed for the draw function.

  \param[in] void
      Takes in no params.

********************************************************************/
void HowToPlay_Init(void)
{

    // Gets the scale of 1366x768
    scaleX = getWinWidth() / 1366.f;
    scaleY = getWinHeight() / 768.f;

    // Back button translation
    howTobackButton_transX = 640.f * scaleX;
    howTobackButton_transY = -355.f * scaleY;

    BGtransX_HowToPlay = 220.0f * scaleX;
    BGtransY_HowToPlay = -40 * scaleY;

}

/******************************************************************************/
/*!
    "Update" function of this state
*/
/******************************************************************************/
/*!*****************************************************************

  \brief
      Collision/animation logic of buttons are here.

  \param[in] void
      Takes in no params.

********************************************************************/
void HowToPlay_Update(void)
{
    // Initialize cursor coordinates
    s32 cursorX;
    s32 cursorY;
    AEInputGetCursorPosition(&cursorX, &cursorY);

    // Quit button mid point
    howTobackButton_midX = static_cast<f32>((getWinWidth() / 2.08) + howTobackButton_transX);
    howTobackButton_midY = static_cast<f32>((getWinHeight() / 2) - howTobackButton_transY);

    // if cursor within buttons, change game state
    if (IsAreaClicked(howTobackButton_midX, howTobackButton_midY, 150.0f * scaleX, 100.0f * scaleY, cursorX, cursorY)
        && AEInputCheckReleased(AEVK_LBUTTON)) {
        gGameStateNext = MAINMENU;
    }

    if (IsAreaClicked(howTobackButton_midX, howTobackButton_midY, 136.0f * scaleX, 50.0f * scaleY, cursorX, cursorY))
    {
        buttonRotate_howToBack = -0.10f;
    }

    if (!IsAreaClicked(howTobackButton_midX, howTobackButton_midY, 170.0f * scaleX, 100.0f * scaleY, cursorX, cursorY))
    {
        buttonRotate_howToBack = 0.0f;
    }
}

/******************************************************************************/
/*!
    "Draw" function of this state
*/
/******************************************************************************/
/*!*****************************************************************

  \brief
      Renders the background, draws the shapes of the objects and prints text onto the screen.

  \param[in] void
      Takes in no params.

********************************************************************/
void HowToPlay_Draw(void)
{


    //Draw Background
    AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
    AEGfxSetTintColor(0.8f, 0.8f, 0.8f, 0.8f);
    AEGfxSetBlendMode(AE_GFX_BM_BLEND);
    AEGfxSetTransparency(1.0f);
    AEGfxTextureSet(BGtexture_HowToPlay, 0, 0);
    AEMtx33 scale0 = { 0 };
    AEMtx33Scale(&scale0, 1100, 800);
    AEMtx33 rotate0 = { 0 };
    AEMtx33Rot(&rotate0, 0.f);
    AEMtx33 translate0 = { 0 };
    AEMtx33Trans(&translate0, BGtransX_HowToPlay, BGtransY_HowToPlay);
    AEMtx33 transform0 = { 0 };
    AEMtx33Concat(&transform0, &rotate0, &scale0);
    AEMtx33Concat(&transform0, &translate0, &transform0);
    AEGfxSetTransform(transform0.m);
    AEGfxMeshDraw(BGmesh_HowToPlay, AE_GFX_MDM_TRIANGLES);
    //Finish Background draw

    // Back button
    AEGfxTextureSet(NULL, 0, 0);
    AEGfxSetRenderMode(AE_GFX_RM_COLOR);
    AEMtx33 scale = { 0 };
    AEMtx33Scale(&scale, 80.f * scaleX, 50.f * scaleY);
    AEMtx33 rotate = { 0 };
    AEMtx33Rot(&rotate, buttonRotate_howToBack);
    AEMtx33 translate = { 0 };
    AEMtx33Trans(&translate, howTobackButton_transX, howTobackButton_transY);
    AEMtx33 transform = { 0 };
    AEMtx33Concat(&transform, &rotate, &scale);
    AEMtx33Concat(&transform, &translate, &transform);
    AEGfxSetTransform(transform.m);
    AEGfxMeshDraw(pMeshHowToPlay, AE_GFX_MDM_TRIANGLES);

    AEGfxSetRenderMode(AE_GFX_RM_COLOR);
    AEGfxTextureSet(NULL, 0, 0);
    AEGfxSetBlendMode(AE_GFX_BM_BLEND);
    sprintf_s(howtoplay_buffer, "How to play:");
    AEGfxPrint(fontID, howtoplay_buffer, (getWinWidth() / (-3500.f * scaleX)), (getWinHeight() / (1000.f * scaleY)), 0.8f * scaleX, 156.0f / 255.f, 205.0f / 255.f, 220.0f / 255.f);

    AEGfxSetRenderMode(AE_GFX_RM_COLOR);
    AEGfxTextureSet(NULL, 0, 0);
    AEGfxSetBlendMode(AE_GFX_BM_BLEND);
    sprintf_s(instructions1_buffer, "> Right mouse click for augments.");
    AEGfxPrint(fontID, instructions1_buffer, (getWinWidth() / (-3500.f * scaleX)), (getWinHeight() / (1350.f * scaleY)), 0.8f * scaleX, 156.0f / 255.f, 205.0f / 255.f, 220.0f / 255.f);

    AEGfxSetRenderMode(AE_GFX_RM_COLOR);
    AEGfxTextureSet(NULL, 0, 0);
    AEGfxSetBlendMode(AE_GFX_BM_BLEND);
    sprintf_s(instructions2_buffer, "> WASD for movement.");
    AEGfxPrint(fontID, instructions2_buffer, (getWinWidth() / (-3500.f * scaleX)), (getWinHeight() / (2000.f * scaleY)), 0.8f * scaleX, 156.0f / 255.f, 205.0f / 255.f, 220.0f / 255.f);

    AEGfxSetRenderMode(AE_GFX_RM_COLOR);
    AEGfxTextureSet(NULL, 0, 0);
    AEGfxSetBlendMode(AE_GFX_BM_BLEND);
    sprintf_s(instructions3_buffer, "> Bullets will follow cursor movement.");
    AEGfxPrint(fontID, instructions3_buffer, (getWinWidth() / (-3500.f * scaleX)), (getWinHeight() / (4000.f * scaleY)), 0.8f * scaleX, 156.0f / 255.f, 205.0f / 255.f, 220.0f / 255.f);

    AEGfxSetRenderMode(AE_GFX_RM_COLOR);
    AEGfxTextureSet(NULL, 0, 0);
    AEGfxSetBlendMode(AE_GFX_BM_BLEND);
    sprintf_s(instructions3_buffer, "> Press 'P' to Pause");
    AEGfxPrint(fontID, instructions3_buffer, (getWinWidth() / (-3500.f * scaleX)), (getWinHeight() / (-25000 * scaleY)), 0.8f * scaleX, 156.0f / 255.f, 205.0f / 255.f, 220.0f / 255.f);

    AEGfxSetRenderMode(AE_GFX_RM_COLOR);
    AEGfxTextureSet(NULL, 0, 0);
    AEGfxSetBlendMode(AE_GFX_BM_BLEND);
    sprintf_s(howToBackButton_buffer, "Back");
    AEGfxPrint(fontID, howToBackButton_buffer, (getWinWidth() / (1655.f * scaleX)), (getWinHeight() / (-798.f * scaleY)), 0.8f * scaleX, 156.0f / 255.f, 205.0f / 255.f, 220.0f / 255.f);




}

/******************************************************************************/
/*!
    "Free" function of the state
*/
/******************************************************************************/
/*!*****************************************************************

  \brief
      Kill each active game object instance if any.

  \param[in] void
      Takes in no params.

********************************************************************/
void HowToPlay_Free(void)
{

}

/******************************************************************************/
/*!
    "Unload" function of the state
*/
/******************************************************************************/
/*!*****************************************************************

  \brief
      Free each used game object (shape) using the "AEGfxMeshFree"/"AEGfxTextureUnload" function.

  \param[in] void
      Takes in no params.

********************************************************************/
void HowToPlay_Unload(void)
{
    AEGfxMeshFree(pMeshHowToPlay);
    AEGfxMeshFree(BGmesh_HowToPlay);
    AEGfxTextureUnload(BGtexture_HowToPlay);
}