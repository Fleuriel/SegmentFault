#include "Menu.h"
#include "AEEngine.h"
#include "GameStateMgr.h"
#include "GameStateList.h"

// Function to get window width
float getWinWidth() {
    return AEGfxGetWinMaxX() - AEGfxGetWinMinX();
}

// Function to get window width
float getWinHeight() {
    return AEGfxGetWinMaxY() - AEGfxGetWinMinY();
}

// Pointer to Mesh
AEGfxVertexList* pMesh = nullptr;

// Pre-definition
AEGfxTexture* startTex;

// Pre-definition for translations of buttons
float button1_transX;  
float button1_transY;
float button2_transX;
float button2_transY;
float button3_transX;
float button3_transY;
float button4_transX;
float button4_transY;
float button5_transX;
float button5_transY;

// Pre-definition of scaling
float scaleX;
float scaleY;

// Function to check if the area is being touched/clicked
int IsAreaClicked(float area_center_x, float area_center_y, float area_width, float area_height, int click_x, int click_y)
{
    // TODO
    if (click_x > area_center_x - (area_width / 2) && click_x < area_center_x + (area_width / 2)
        && click_y < area_center_y + (area_height / 2) && click_y > area_center_y - (area_height / 2))
    {
        return 1;
    }

    return 0;
}

void Menu_Load(void)
{
   

    AEGfxSetBackgroundColor(0.019f, 0.27f, 0.411f);

    // Create buttons
    AEGfxMeshStart();

    AEGfxTriAdd(
        0.5f, 0.5f, 0xFFFFFFFF, 1.0f, 0.0f,
        -1.f, -0.5f, 0xFFFFFFFF, 0.0f, 1.0f,
        0.5f, -0.5f, 0xFFFFFFFF, 1.0f, 1.0f);
    AEGfxTriAdd(
        -1.f, 0.5f, 0xFFFFFFFF, 0.0f, 0.0f,
        -1.f, -0.5f, 0xFFFFFFFF, 0.0f, 1.0f,
        0.5f, 0.5f, 0xFFFFFFFF, 1.0f, 0.0f);

    pMesh = AEGfxMeshEnd();

    // Loading textures
    startTex = AEGfxTextureLoad("..\\..\\Assets\\Assets\\start.png");

   
}

void Menu_Init(void) 
{
    // Gets the scale of 1366x768
    scaleX = getWinWidth() / 1366.f; 
    scaleY = getWinHeight() / 768.f;


    button1_transX = -150.f * scaleX;
    button1_transY = -150.f * scaleY;
    button2_transX = 150.0f * scaleX;
    button2_transY = -150.0f * scaleY;
    button3_transX = 0.0f * scaleX;
    button3_transY = 0.0f * scaleY;
    button4_transX = -600.0f * scaleX;
    button4_transY = -355.0f * scaleY;
    button5_transX = 660.0f * scaleX;
    button5_transY = 355.0f * scaleY;
    
}

void Menu_Update(void) 
{
    s32 cursorX;
    s32 cursorY;
    AEInputGetCursorPosition(&cursorX, &cursorY);

    
    //printf("%d\n%f\n", AEGetWindowHeight(), getWinHeight());
    //float button1_midX = (AEGfxGetWinMaxX() - (25.f) + button1_transX);
    //float button1_midY = (AEGfxGetWinMaxY() - (68.f) - button1_transY); 
    float button1_midX = (getWinWidth() / 2.08) + button1_transX;
    float button1_midY = (getWinHeight() / 2) - button1_transY;
    //float button2_midX = AEGfxGetWinMaxX() - (25.f) + button2_transX;
    //float button2_midY = AEGfxGetWinMaxY() - (68.f) - button2_transY;
    float button2_midX = (getWinWidth() / 2.08) + button2_transX;
    float button2_midY = (getWinHeight() / 2) - button2_transY;
    //float button3_midX = ((582.f + 732.f) / 2.f);
    //float button3_midY = ((334.f + 434.f) / 2.f);
    float button3_midX = (getWinWidth() / 2.08);
    float button3_midY = getWinHeight() / 2;
    //float button4_midX = AEGfxGetWinMaxX() - (25.f) + button4_transX;
    //float button4_midY = AEGfxGetWinMaxY() - (68.f) - button4_transY;
    float button4_midX = (getWinWidth() / 2.08) + button4_transX;
    float button4_midY = (getWinHeight() / 2) - button4_transY;
    float button5_midX = (getWinWidth() / 2.08) + button5_transX;
    float button5_midY = (getWinHeight() / 2) - button5_transY;
    
    printf("%d\n%d\n", cursorX, cursorY);  //debug
    //printf("%f\n%f\n", button1_midX, button1_midY);  //debug
    // if cursor within buttons, change game state
    if (IsAreaClicked(button1_midX, button1_midY, 150.0f * scaleX, 100.0f * scaleY, cursorX, cursorY)) {
        //gGameStateNext = POWER_UPS;
        printf("Goto powerups\n");
    }
    else if (IsAreaClicked(button2_midX, button2_midY, 150.0f * scaleX, 100.0f * scaleY, cursorX, cursorY)) {
        //gGameStateNext = SETTINGS;
        printf("Goto Settings\n");
    }
    else if (IsAreaClicked(button3_midX, button3_midY, 150.0f * scaleX, 100.0f * scaleY, cursorX, cursorY)) {
        //gGameStateNext = PLAY;
        printf("Goto Play\n");
    }

    else if (IsAreaClicked(button4_midX, button4_midY, 120.0f * scaleX, 50.0f * scaleY, cursorX, cursorY)) {
        //gGameStateNext = CREDITS;
        printf("Goto Credits\n");
    }

    else if (IsAreaClicked(button5_midX, button5_midY, 57.0f * scaleX, 50.0f * scaleY, cursorX, cursorY)) {
        //gGameStateNext = QUIT;
        printf("QUIT\n");
    }


}
void Menu_Draw(void)
{

    // Button 1, Power-ups button
    AEGfxTextureSet(NULL, 0, 0);
    AEGfxSetRenderMode(AE_GFX_RM_COLOR);
    AEMtx33 scale = { 0 };
    AEMtx33Scale(&scale, 100.f * scaleX, 100.f * scaleY);
    AEMtx33 rotate = { 0 };
    AEMtx33Rot(&rotate, 0.f);
    AEMtx33 translate = { 0 };
    AEMtx33Trans(&translate, button1_transX, button1_transY);
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
    AEMtx33Rot(&rotate1, 0.f);
    AEMtx33 translate1 = { 0 };
    AEMtx33Trans(&translate1, button2_transX, button2_transY);
    AEMtx33 transform1 = { 0 };
    AEMtx33Concat(&transform1, &rotate1, &scale1);
    AEMtx33Concat(&transform1, &translate1, &transform1);
    AEGfxSetTransform(transform1.m);
    AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);

    // Button 3, Start button
    AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
    AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
    AEGfxSetBlendMode(AE_GFX_BM_BLEND);
    AEGfxSetTransparency(1.0f);
    AEGfxTextureSet(startTex, 0, 0);
    AEMtx33 scale2 = { 0 };
    AEMtx33Scale(&scale2, 100.f * scaleX, 100.f * scaleY);
    AEMtx33 rotate2 = { 0 };
    AEMtx33Rot(&rotate2, 0.f);
    AEMtx33 translate2 = { 0 };
    AEMtx33Trans(&translate2, button3_transX, button3_transY);
    AEMtx33 transform2 = { 0 };
    AEMtx33Concat(&transform2, &rotate2, &scale2);
    AEMtx33Concat(&transform2, &translate2, &transform2);
    AEGfxSetTransform(transform2.m);
    AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);

    // Button 4, Credits button
    AEGfxSetRenderMode(AE_GFX_RM_COLOR);
    AEGfxTextureSet(NULL, 0, 0);
    AEMtx33 scale4 = { 0 };
    AEMtx33Scale(&scale4, 80.f * scaleX, 50.f * scaleY);
    AEMtx33 rotate4 = { 0 };
    AEMtx33Rot(&rotate4, 0.f);
    AEMtx33 translate4 = { 0 };
    AEMtx33Trans(&translate4, button4_transX, button4_transY);
    AEMtx33 transform4 = { 0 };
    AEMtx33Concat(&transform4, &rotate4, &scale4);
    AEMtx33Concat(&transform4, &translate4, &transform4);
    AEGfxSetTransform(transform4.m);
    AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);

    // Button 5, Exit button
    AEGfxSetRenderMode(AE_GFX_RM_COLOR);
    AEGfxTextureSet(NULL, 0, 0);
    AEMtx33 scale5 = { 0 };
    AEMtx33Scale(&scale5, 38.f * scaleX, 50.f * scaleY);
    AEMtx33 rotate5 = { 0 };
    AEMtx33Rot(&rotate5, 0.f);
    AEMtx33 translate5 = { 0 };
    AEMtx33Trans(&translate5, button5_transX, button5_transY);
    AEMtx33 transform5 = { 0 };
    AEMtx33Concat(&transform5, &rotate5, &scale5);
    AEMtx33Concat(&transform5, &translate5, &transform5);
    AEGfxSetTransform(transform5.m);
    AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);
}

void Menu_Free(void) 
{
    
}
void Menu_Unload(void)
{
    AEGfxMeshFree(pMesh);
    
}