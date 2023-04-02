#include "SplashPage.h"
#include "Main.h"

// Pointer to Mesh
AEGfxVertexList* pMeshSplash = nullptr;

// Pre-definition for texture
AEGfxTexture* startTex_Splash;

// Pre-definition for translations of buttons
f32 splashPage_transX;
f32 splashPage_transY;

// Pre-definition for transparency
f32 splashPage_transparency;

bool isTransparent;

void SplashPage_Load(void) 
{
    AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);  // conversion -> rgb value/255

    AEGfxMeshStart();

    AEGfxTriAdd(
        0.5f, 0.5f, 0xFF001736, 1.0f, 0.0f,
        -1.0f, -0.5f, 0xFF001736, 0.0f, 1.0f,
        0.5f, -0.5f, 0xFF001736, 1.0f, 1.0f);
    AEGfxTriAdd(
        -1.0f, 0.5f, 0xFF001736, 0.0f, 0.0f,
        -1.0f, -0.5f, 0xFF001736, 0.0f, 1.0f,
        0.5f, 0.5f, 0xFF001736, 1.0f, 0.0f);

    pMeshSplash = AEGfxMeshEnd();

    // Loading textures
    startTex_Splash = AEGfxTextureLoad("Assets\\Assets\\DigiPen_Singapore_WEB_RED.png");
}
void SplashPage_Init(void) 
{
	scaleX = getWinWidth() / 1366.f;
	scaleY = getWinHeight() / 768.f;

	splashPage_transX = 125.f * scaleX;
	splashPage_transY = 0.f * scaleY;

	splashPage_transparency = 0.f;
	isTransparent = true;

}
void SplashPage_Update(void) 
{

	if (isTransparent) 
	{
		splashPage_transparency += 0.005f;
		if (splashPage_transparency >= 1.f) 
		{
			splashPage_transparency += 1.5f;
			isTransparent = false;
		}
	}

	// Goes to main menu after it has done one cycle of fading in and out
	else if (!isTransparent) {
		splashPage_transparency -= 0.005f;
		if (splashPage_transparency <= 0.f) 
		{
			isTransparent = true;
			gGameStateNext = MAINMENU;
		}
	}


}
void SplashPage_Draw(void) 
{
	//Draw Background
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetTintColor(1.f, 1.f, 1.f, 1.f);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetTransparency(splashPage_transparency);
	AEGfxTextureSet(startTex_Splash, 0, 0);
	AEMtx33 scale0 = { 0 };
	AEMtx33Scale(&scale0, 600, 300);
	AEMtx33 rotate0 = { 0 };
	AEMtx33Rot(&rotate0, 0.f);
	AEMtx33 translate0 = { 0 };
	AEMtx33Trans(&translate0, splashPage_transX, splashPage_transY);
	AEMtx33 transform0 = { 0 };
	AEMtx33Concat(&transform0, &rotate0, &scale0);
	AEMtx33Concat(&transform0, &translate0, &transform0);
	AEGfxSetTransform(transform0.m);
	AEGfxMeshDraw(pMeshSplash, AE_GFX_MDM_TRIANGLES);
	//Finish Background draw
}
void SplashPage_Free(void) 
{

}
void SplashPage_Unload(void) 
{
    AEGfxMeshFree(pMeshSplash);
	AEGfxTextureUnload(startTex_Splash);
}