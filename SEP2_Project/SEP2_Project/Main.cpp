// ---------------------------------------------------------------------------
// includes

#define MAX_ENEMIES 10

#include "AEEngine.h"
#include <iostream>
#include <math.h>
#include "enemy.hpp"
#include <vector>
#include <random>
// ---------------------------------------------------------------------------



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
	AESysSetWindowTitle("Among Them");

	// reset the system modules
	AESysReset();

	int array[MAX_ENEMIES] = {};
	int distanceX[MAX_ENEMIES] = {};
	int distanceY[MAX_ENEMIES] = {};
	//My Own Testing Codes
	AEGfxVertexList* pMesh = 0;
	AEGfxVertexList* oOMesh = 0;
	AEGfxTexture* pTex = AEGfxTextureLoad("Assets/Assets/TrollFace.png");
	AEGfxTexture* oOTex = AEGfxTextureLoad("Assets/Assets/moon.png");
	AEGfxTexture* ETex = AEGfxTextureLoad("Assets/Assets/images.png");

	AEGfxMeshStart();
	AEGfxTriAdd(-0.5f, -0.5f, 0xFFFF00FF, 0.0f, 0.0f,
		0.5f, -0.5f, 0xFFFFFF00, 1.0f, 0.0f,
		-0.5f, 0.5f, 0xFF00FFFF, 0.0f, 1.0f);
	AEGfxTriAdd(0.5f, -0.5f, 0xFFFFFFFF, 1.0f, 0.0f,
		0.5f, 0.5f, 0xFFFFFFFF, 1.0f, 1.0f,
		-0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 1.0f);
	pMesh = AEGfxMeshEnd();
	AEGfxMeshStart();



	int enemySpeed = 1;
	f32 x = 0.0f, y = 0.0f;
	f32 rotationx = 0;
	f32 r = 100.0f, z = 0.0f,x1 = 50.0f, y1  = 50.0f;
	// Game Loop

	f32 enemyX = 200.0f, enemyY = 200.0f;


	f32 distance = 0.0f;
	while (gGameRunning)
	{
		// Informing the system about the loop's start
		AESysFrameStart();

		// Handling Input
		AEInputUpdate();

		for (int i = 0; i < MAX_ENEMIES; i++)
		{


			float distanceX = enemyX - x;
			float distanceY = enemyY - y;

			float magnitude = sqrt(pow(distanceX, 2) + pow(distanceY, 2));
			distanceX /= magnitude;
			distanceY /= magnitude;

			enemyX -= distanceX * enemySpeed;
			enemyY -= distanceY * enemySpeed;
		}
	
		

		//std::cout << distance << '\n';

//		std::cout << "x1: " << x1 << ' ' << "y1: " << y1 << '\n';

		if (AEInputCheckCurr(AEVK_RIGHT))
		{
			x += 5.0f;
			std::cout << "x: " << x << ' ' << "y: " << y << ' ' << "z: " << z << ' ' << "r: " << r << '\n';
		}
		if (AEInputCheckCurr(AEVK_LEFT))
		{
			x -= 5.0f;
			std::cout << "x: " << x << ' ' << "y: " << y << ' ' << "z: " << z << ' ' << "r: " << r << '\n';
		}		
		if (AEInputCheckCurr(AEVK_DOWN))
		{
			y -= 5.0f;
			std::cout << "x: " << x << ' ' << "y: " << y << ' ' << "z: " << z << ' ' << "r: " << r << '\n';
		}		
		if (AEInputCheckCurr(AEVK_UP))
		{
			y += 5.0f;
			std::cout << "x: " << x << ' ' << "y: " << y << ' ' << "z: " << z << ' ' << "r: " << r << '\n';
		}
		if (AEInputCheckCurr(AEVK_A))
		{
			r -= 0.01f;
			std::cout << "x: " << x << ' ' << "y: " << y << ' ' << "z: " << z << ' ' << "r: " << r << '\n';
		}		
		if (AEInputCheckCurr(AEVK_D))
		{
			r += 0.01f;
			std::cout << "x: " << x << ' ' << "y: " << y << ' ' << "z: " << z << ' ' << "r: " << r << '\n';
		}
		if (AEInputCheckCurr(AEVK_1))
		{
			z -= 1.0f;
			std::cout << "x: " << x << ' ' << "y: " << y << ' ' << "z: " << z << ' ' << "r: " << r << '\n';
		}
		if (AEInputCheckCurr(AEVK_2))
		{
			z += 1.0f;
			std::cout << "x: " << x << ' ' << "y: " << y << ' ' << "z: " << z << ' ' << "r: " << r << '\n';
		}
		if (AEInputCheckCurr(AEVK_R))
		{
			z = 100.0f;
			std::cout << "x: " << x << ' ' << "y: " << y << ' ' << "z: " << z << ' ' << "r: " << r << '\n';
		}

		if (rotationx > 360)
		{
			rotationx = 0;
		}
		rotationx -= 0.04;

		x1 = x + 100 * cos(rotationx);
		y1 = y + 100 * sin(rotationx);


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
		AEMtx33Scale(&scale,z ,z);
		// Create a rotation matrix that rotates by 45 degrees
		AEMtx33 rotate = { 0 };
		AEMtx33Rot(&rotate, 135);
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
		

		//let this one be the turning ones.

	
		AEGfxTextureSet(oOTex, 0, 0);
		AEMtx33 scale1 = { 0 };
		AEMtx33Scale(&scale1, 50, 50);
		// Create a rotation matrix that rotates by 45 degrees
		AEMtx33 rotate1 = { 0 };
		AEMtx33Rot(&rotate1, rotationx);
		// Create a translation matrix that translates by
		// 100 in the x-axis and 100 in the y-axis
		AEMtx33 translate1 = { 0 };
		AEMtx33Trans(&translate1, x1, y1);
		// Concat the matrices (TRS)
		AEMtx33 transform1 = { 0 };
		AEMtx33Concat(&transform1, &rotate1, &scale1);
		AEMtx33Concat(&transform1, &translate1, &transform1);
		// Choose the transform to use
		AEGfxSetTransform(transform1.m);
		// Actually drawing the mesh
		AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);
		


		std::cout << "enemyX: " << enemyX << "  enemyY: " << enemyY << '\n';
		/*		A
			   /|
			  / |
		     /  |
			/___|
			C	B
		*/


		AEGfxTextureSet(ETex, 0, 0);
		AEMtx33Scale(&scale1, 50, 50);
		// Create a rotation matrix that rotates by 45 degrees
		AEMtx33Rot(&rotate1, rotationx);
		// Create a translation matrix that translates by
		// 100 in the x-axis and 100 in the y-axis
		AEMtx33Trans(&translate1, enemyX, enemyY);
		// Concat the matrices (TRS)
		
		AEMtx33Concat(&transform1, &rotate1, &scale1);
		AEMtx33Concat(&transform1, &translate1, &transform1);
		// Choose the transform to use
		AEGfxSetTransform(transform1.m);
		// Actually drawing the mesh
		AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);

		AESysFrameEnd();
		// check if forcing the application to quit
		if (AEInputCheckTriggered(AEVK_ESCAPE) || 0 == AESysDoesWindowExist())
			gGameRunning = 0;
	}

	AEGfxMeshFree(pMesh);

	AEGfxTextureUnload(pTex);
	AEGfxTextureUnload(oOTex);

	AEGfxTextureUnload(ETex);

	// free the system
	AESysExit();
}