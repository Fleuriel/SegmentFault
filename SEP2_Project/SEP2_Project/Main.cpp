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
	AESysInit(hInstance, nCmdShow, 1366, 768, 1, 144, true, NULL);


	// Changing the window title
	AESysSetWindowTitle("Among Them");

	// reset the system modules
	AESysReset();
	int enemySpeed = 1;
	f32 x = 0.0f, y = 0.0f;
	f32 rotationx = 0;
	f32 r = 100.0f, z = 0.0f, x1 = 50.0f, y1 = 50.0f;
	f32 projRotX = 0.0f , projRotY= 0.0f;


	std::vector<std::pair<int, int>> enemies;
	std::random_device random;
	std::mt19937 gen(random());
	std::uniform_int_distribution<>distX(x - 50, x + 50);
	std::uniform_int_distribution<>distY(y - 50, y + 50);


	f32 array[MAX_ENEMIES] = {0};
	f32 distanceX[MAX_ENEMIES] = {0};
	f32 distanceY[MAX_ENEMIES] = {0};
	f32 enemyX[MAX_ENEMIES] = { 200.0f ,300.0f ,400.0f ,500.0f ,600.0f ,700.0f ,800.0f ,900.0f ,1000.0f ,1100.0f };
	f32 enemyY[MAX_ENEMIES] = { 100.0f ,500.0f ,440.0f ,-300.0f ,-900.0f ,-700.0f ,-144.0f ,900.0f ,1000.0f ,1100.0f };

	f32 projX = 0.0f, projY = 0.0f;
	s32* mousex = new s32, * mousey = new s32;
	//My Own Testing Codes
	AEGfxVertexList* pMesh = 0;
	AEGfxVertexList* oOMesh = 0;
	AEGfxTexture* pTex = AEGfxTextureLoad("Assets/Assets/TrollFace.png");
	AEGfxTexture* oOTex = AEGfxTextureLoad("Assets/Assets/moon.png");
	AEGfxTexture* ETex = AEGfxTextureLoad("Assets/Assets/images.png");
	AEGfxTexture* pewTex = AEGfxTextureLoad("Assets/Assets/YellowTexture.png");
	AEGfxTexture* GOTex = AEGfxTextureLoad("Assets/Assets/GameOver.png"); 
	bool gameOverCheck = 0;

	AEGfxMeshStart();
	AEGfxTriAdd(-0.5f, -0.5f, 0xFFFF00FF, 0.0f, 0.0f,
		0.5f, -0.5f, 0xFFFFFF00, 1.0f, 0.0f,
		-0.5f, 0.5f, 0xFF00FFFF, 0.0f, 1.0f);
	AEGfxTriAdd(0.5f, -0.5f, 0xFFFFFFFF, 1.0f, 0.0f,
		0.5f, 0.5f, 0xFFFFFFFF, 1.0f, 1.0f,
		-0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 1.0f);
	pMesh = AEGfxMeshEnd();
	AEGfxMeshStart();

	f32 projectile_speed = 5.0;
	f32 degrees;

	// Game Loop

	//f32 enemyX = 200.0f, enemyY = 200.0f;

	f32 seconds = 0.0f;
	f32 distance = 0.0f;
	while (gGameRunning)
	{
		// Informing the system about the loop's start
		AESysFrameStart();

		// Handling Input
		AEInputUpdate();

		//if(AEngine_getDT)
		//timer += 1;
		//
		//	AEInputGetCursorPosition(mousex, mousey); 
		//	std::cout << *mousex << *mousey << "\n";
		//	gets the mouse x and y input.



		for (int i = 0; i < MAX_ENEMIES; i++)
		{
			distanceX[i] = enemyX[i] - x;
			distanceY[i] = enemyY[i] - y;

			float magnitude = sqrt(pow(distanceX[i], 2) + pow(distanceY[i], 2));
			distanceX[i] /= magnitude;
			distanceY[i] /= magnitude;

			enemyX[i] -= distanceX[i] * enemySpeed;
			enemyY[i] -= distanceY[i] * enemySpeed;
			//std::cout << "enemyX: " << i << "  " << enemyX[i] << "  enemyY: " << i << "  " << enemyY[i] << '\n';
		}//
	
//		if (AEInputGetCursorPosition());
		

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

		if (AEInputCheckTriggered(AEVK_H))
		{
			std::cout << enemyY[0] - y  <<  "   " << enemyX[0] - x << '\n';
			degrees = acos(enemyY[0]-y/ enemyX[0]-x );
			std::cout << degrees << '\n';
			projRotX = cos(degrees);
			projRotY = sin(degrees);
		}


		projX = projectile_speed *  projRotX;
		projY = projectile_speed *  projRotY;


		std::cout << "ProjRotX: " << projRotX << "ProjRotY : " << projRotY << '\n';
		std::cout << "projX: " << projX << "projY : " << projY << '\n';


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
		
		//projectile
		AEGfxTextureSet(pewTex, 0, 0);
		AEMtx33Scale(&scale1, 50, 50);
		// Create a rotation matrix that rotates by 45 degrees
		AEMtx33Rot(&rotate1, rotationx);
		// Create a translation matrix that translates by
		// 100 in the x-axis and 100 in the y-axis
		AEMtx33Trans(&translate1, projX, projY);
		// Concat the matrices (TRS)
		AEMtx33Concat(&transform1, &rotate1, &scale1);
		AEMtx33Concat(&transform1, &translate1, &transform1);
		// Choose the transform to use
		AEGfxSetTransform(transform1.m);
		// Actually drawing the mesh
		AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);
		/*		A
			   /|
			  / |
		     /  |
			/___|
			C	B
		*/

		if (AEInputCheckTriggered(AEVK_J))
		{
			gameOverCheck = !gameOverCheck;
		}
		if (gameOverCheck == 1) {
			AEGfxTextureSet(GOTex, 0, 0);
			AEMtx33Scale(&scale, 500.f, 200.f);
			AEMtx33Rot(&rotate, 0);
			AEMtx33Trans(&translate, 0, 0);
			AEMtx33Concat(&transform, &rotate, &scale);
			AEMtx33Concat(&transform, &translate, &transform);
			AEGfxSetTransform(transform.m);
			AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);
		}


		for (int i = 0; i < MAX_ENEMIES; i++)
		{
			AEGfxTextureSet(ETex, 0, 0);
			AEMtx33Scale(&scale1, 50, 50);
			// Create a rotation matrix that rotates by 45 degrees
			AEMtx33Rot(&rotate1, rotationx);
			// Create a translation matrix that translates by
			// 100 in the x-axis and 100 in the y-axis
			AEMtx33Trans(&translate1, enemyX[i], enemyY[i]);
			// Concat the matrices (TRS)

			AEMtx33Concat(&transform1, &rotate1, &scale1);
			AEMtx33Concat(&transform1, &translate1, &transform1);
			// Choose the transform to use
			AEGfxSetTransform(transform1.m);
			// Actually drawing the mesh
			AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);
		}

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