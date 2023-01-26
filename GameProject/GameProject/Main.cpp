// ---------------------------------------------------------------------------
// includes

#include "AEEngine.h"



// ---------------------------------------------------------------------------
// main

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);


	int gGameRunning = 1;


	// Initialization of your own variables go here

	// Using custom window procedure
	AESysInit(hInstance, nCmdShow, 800, 600, 1, 60, true, NULL);

	// Changing the window title
	AESysSetWindowTitle("My New Demo!");

	// reset the system modules
	AESysReset();

	//My Own Testing Codes
	AEGfxVertexList* pMesh = 0;
	AEGfxTexture* pTex = AEGfxTextureLoad("Assets/PlanetTexture.png");

	AEGfxMeshStart();

	AEGfxTriAdd(-0.5f, -0.5f, 0xFFFF00FF, 0.0f, 0.0f,
		0.5f, -0.5f, 0xFFFFFF00, 1.0f, 0.0f,
		-0.5f, 0.5f, 0xFF00FFFF, 0.0f, 1.0f);

	AEGfxTriAdd(0.5f, -0.5f, 0xFFFFFFFF, 1.0f, 0.0f,
		0.5f, 0.5f, 0xFFFFFFFF, 1.0f, 1.0f,
		-0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 1.0f);


	pMesh = AEGfxMeshEnd();

	f32 x = 0.0f, y = 0.0f, r = 0.0f, z = 0.0f;
	// Game Loop

	while (gGameRunning)
	{
		// Informing the system about the loop's start
		AESysFrameStart();

		// Handling Input
		AEInputUpdate();



		//
		if (AEInputCheckCurr(AEVK_RIGHT))
		{
			x += 5.0f;
			//			y = x;
		}
		if (AEInputCheckCurr(AEVK_LEFT))
		{
			x -= 5.0f;
			//			y = x;
		}
		if (AEInputCheckCurr(AEVK_DOWN))
		{
			y -= 5.0f;
		}
		if (AEInputCheckCurr(AEVK_UP))
		{
			y += 5.0f;
		}
		if (AEInputCheckCurr(AEVK_A))
		{
			r -= 0.01f;
		}
		if (AEInputCheckCurr(AEVK_D))
		{
			r += 0.01f;
		}
		if (AEInputCheckCurr(AEVK_1))
		{
			z -= 1.0f;
		}
		if (AEInputCheckCurr(AEVK_2))
		{
			z += 1.0f;
		}
		if (AEInputCheckCurr(AEVK_R))
		{
			z = 100.0f;
		}

		// Set the background to black.
		AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
		// Tell the engine to get ready to draw something with texture.
		AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
		// Set the tint to white, so that the sprite can
		// display the full range of colors (default is black).
		AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
		// Set blend mode to AE_GFX_BM_BLEND
		// This will allow transparency.
		AEGfxSetBlendMode(AE_GFX_BM_BLEND);
		AEGfxSetTransparency(1.0f);
		// Set the texture to pTex
		AEGfxTextureSet(pTex, 0, 0);
		// Create a scale matrix that scales by 100 x and y
		AEMtx33 scale = { 0 };
		AEMtx33Scale(&scale, z, z);
		// Create a rotation matrix that rotates by 45 degrees
		AEMtx33 rotate = { 0 };
		AEMtx33Rot(&rotate, r);
		// Create a translation matrix that translates by
		// 100 in the x-axis and 100 in the y-axis
		AEMtx33 translate = { 0 };
		AEMtx33Trans(&translate, x, y);
		// Concat the matrices (TRS)
		AEMtx33 transform = { 0 };
		AEMtx33Concat(&transform, &rotate, &scale);
		AEMtx33Concat(&transform, &translate, &transform);
		// Choose the transform to use
		AEGfxSetTransform(transform.m);
		// Actually drawing the mesh
		AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);

		//

		// Your own update logic goes here


		// Your own rendering logic goes here
			

		// Informing the system about the loop's end
		AESysFrameEnd();

		// check if forcing the application to quit
		if (AEInputCheckTriggered(AEVK_ESCAPE) || 0 == AESysDoesWindowExist())
			gGameRunning = 0;
	}

	AEGfxMeshFree(pMesh);


	AEGfxTextureUnload(pTex);
	// free the system
	AESysExit();
}