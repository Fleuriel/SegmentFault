// ---------------------------------------------------------------------------
// includes

#define MAX_ENEMIES 10

#include "AEEngine.h"
#include <iostream>
#include <cmath>
//#include "enemy.hpp"
#include <vector>
#include <random>
#include <ctime>
#include <chrono>

std::chrono::duration<double> elapsed;

class Projectile {
public:
	double x, y;
	double angle;
	double speed;

	Projectile(double x, double y, double angle, double speed)
		: x(x), y(y), angle(angle), speed(speed) {}

	void updatePosition() {
		x += speed * cos(angle);
		y += speed * sin(angle);
	}
};

class Enemy {
private:
	double x, y;
public:
	Enemy(double x, double y) : x(x), y(y) {}
	double getX() { return x; }
	double getY() { return y; }
};

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

	std::vector <Projectile> _bullet;

	//deltaTime
	//const clock_t begin_Time = std::clock();


	// Changing the window title
	AESysSetWindowTitle("Among Them");

	// reset the system modules
	AESysReset();
	//int enemySpeed = 1;
	f64 x = 0.0f, y = 0.0f;
	f64 rotationx = 0;
	f64 r = 100.0f, z = 0.0f, x1 = 50.0f, y1 = 50.0f;

	//random || DO NOT DELETE. this is testing purposes.
	//std::vector<std::pair<int, int>> enemies;
	//std::random_device random;
	//std::mt19937 gen(random());
	//std::uniform_int_distribution<>distX(x - 50, x + 50);
	//std::uniform_int_distribution<>distY(y - 50, y + 50);

	//initialize the texture settings.
	AEMtx33 scale = { 0 };
	AEMtx33 rotate = { 0 };
	AEMtx33 translate = { 0 };
	AEMtx33 transform = { 0 };

	//Dumb array, need to change for dynamic array.
	f64 distanceX[MAX_ENEMIES] = {0};
	f64 distanceY[MAX_ENEMIES] = {0};
	f64 enemyX[MAX_ENEMIES] = { 200.0f };
	f64 enemyY[MAX_ENEMIES] = { 200.0f };

	s32* mouseX = new s32, * mouseY = new s32;
	//My Own Testing Codes
	//Mesh
	AEGfxVertexList* pMesh = 0;
	//Texture Start
	AEGfxTexture* pTex = AEGfxTextureLoad("Assets/Assets/Terran.png");
	AEGfxTexture* oOTex = AEGfxTextureLoad("Assets/Assets/moon.png");
	AEGfxTexture* ETex = AEGfxTextureLoad("Assets/Assets/ling.png");
	AEGfxTexture* pewTex = AEGfxTextureLoad("Assets/Assets/YellowTexture.png");
	AEGfxTexture* GOTex = AEGfxTextureLoad("Assets/Assets/GameOver.png"); 
	AEGfxTexture* TargetTex = AEGfxTextureLoad("Assets/Assets/Target.png");

	f64 deltaTime = 0;
	//Texture End

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

	int playerScaleX = 75;
	int playerScaleY = 75;
	int enemyScaleX = 75;

	const float projectileSpeed = 5.0f;
	const float enemySpeed = 1.0f;

	//Enemy
	Enemy enemy(enemyX[0], enemyY[0]);
	double angle = atan2(enemy.getY() - 0, enemy.getX() - 0);
	Projectile projectile(0, 0, angle, projectileSpeed);

	// Game Loop
	while (gGameRunning)
	{
		//timer
		auto timerStart = std::chrono::high_resolution_clock::now();
		// Informing the system about the loop's start
		deltaTime += elapsed.count();

		if(static_cast<int>(deltaTime) %2 == 1)
		{
			Projectile projectile(x1, y1, angle, projectileSpeed);
			_bullet.push_back(projectile);
			std::cout << "DT: " << static_cast<int>(deltaTime) << '\n';
			deltaTime = 0;
			std::cout << _bullet.size() << "    Bullet Size \n";
		}

		AESysFrameStart();

		AEInputUpdate();
		// Handling Input
		for (size_t i = 0; i < _bullet.size(); i++)
		{
			Projectile& projectile = _bullet[i];
			_bullet[i].updatePosition();
		
			//if bullet is out of the map, delete it. (Can change later, but now to prevent mem leak)
			if (projectile.x > AEGetWindowWidth() || projectile.x < -AEGetWindowWidth() || projectile.y > AEGetWindowHeight() || projectile.y < -AEGetWindowHeight())
			{
				_bullet.erase(_bullet.begin() + i);
				--i;
			}
		}
		
		//if (AEInputCheckTriggered(AEVK_C))
		//{
			//Projectile projectile(*mouseX - AEGetWindowWidth() / 2, -(*mouseY - AEGetWindowHeight() / 2), angle, projectileSpeed);
		//	Projectile projectile(x1,y1, angle, projectileSpeed);
		//	_bullet.push_back(projectile);
		//}

		/*				  y
						  ^
						  |
						  |
		------------------|------------------->x
						  |
						  |
							  */
		//if (projectile.x > 400 || projectile.y > 400)
		//{
		//	projectile.x = projectile.y = 0;
		//}
		AEInputGetCursorPosition(mouseX, mouseY); 
		//std::cout << "Mouse X: " << *mousex << "   Mouse Y: " << *mousey << "\n";
		//	gets the mouse x and y input.
		if (gameOverCheck == 0)
		{
			if (*mouseX >= 500 && *mouseX <= 800)
			{
				if (*mouseY >= 500 && *mouseY <= 800)
				{
					if (AEInputCheckTriggered(AEVK_LBUTTON))
					{
						gameOverCheck = !gameOverCheck;
					}
				}
			}
		}


		for (int i = 0; i < MAX_ENEMIES; i++)
		{
			distanceX[i] = enemyX[i] - x;
			distanceY[i] = enemyY[i] - y;

			f64 magnitude = sqrt(pow(distanceX[i], 2) + pow(distanceY[i], 2));
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
			if (playerScaleX < 0)
			{
				playerScaleX *= -1;
			}
			std::cout << "x: " << x << ' ' << "y: " << y << ' ' << "z: " << z << ' ' << "r: " << r << '\n';
		}
		if (AEInputCheckCurr(AEVK_LEFT))
		{
			x -= 5.0f;
			if(playerScaleX >0)
				playerScaleX *= -1;
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

		//if (AEInputCheckTriggered(AEVK_H))
		//{
		//	std::cout << enemyY[0] - y  <<  "   " << enemyX[0] - x << '\n';
		//	degrees = acos(enemyY[0]-y/ enemyX[0]-x );
		//	std::cout << degrees << '\n';
		//	projRotX = cos(degrees);
		//	projRotY = sin(degrees);
		//}

		//projX = projectile_speed *  projRotX;
		//projY = projectile_speed *  projRotY;


		//std::cout << "ProjRotX: " << projRotX << "ProjRotY : " << projRotY << '\n';
		//std::cout << "projX: " << projX << "projY : " << projY << '\n';




		// Set the background to black.
		AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
		AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
		AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
		AEGfxSetBlendMode(AE_GFX_BM_BLEND);
		AEGfxSetTransparency(1.0f);
		// Set the texture to pTex

		//X
		AEGfxTextureSet(TargetTex, 0, 0);
		AEMtx33Scale(&scale, 50, 50);
		AEMtx33Rot(&rotate, 0);
		AEMtx33Trans(&translate, 200.0f, 200.0f);
		AEMtx33Concat(&transform, &rotate, &scale);
		AEMtx33Concat(&transform, &translate, &transform);
		AEGfxSetTransform(transform.m);
		AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);

		//
		AEGfxTextureSet(pTex, 0, 0);
		// Create a scale matrix that scales by 100 x and y
		AEMtx33Scale(&scale,playerScaleX, 75);
		// Create a rotation matrix that rotates by 45 degrees
		AEMtx33Rot(&rotate, AEDegToRad(180));
		// Create a translation matrix that translates by
		// 100 in the x-axis and 100 in the y-axis
		AEMtx33Trans(&translate, x, y);
		// Concat the matrices (TRS)
		AEMtx33Concat(&transform, &rotate, &scale);
		AEMtx33Concat(&transform, &translate, &transform);
		// Choose the transform to use
		AEGfxSetTransform(transform.m);
		// Actually drawing the mesh
		AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);
		

		//let this one be the turning ones.

	
		AEGfxTextureSet(oOTex, 0, 0);
		AEMtx33Scale(&scale, 50, 50);
		AEMtx33Rot(&rotate, rotationx);
		AEMtx33Trans(&translate, x1, y1);
		AEMtx33Concat(&transform, &rotate, &scale);
		AEMtx33Concat(&transform, &translate, &transform);
		AEGfxSetTransform(transform.m);
		AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);
		
		//projectile
		for (size_t i = 0; i < _bullet.size(); i++)
		{
			AEGfxTextureSet(pewTex, 0, 0);
			AEMtx33Scale(&scale, 5, 50);
			AEMtx33Rot(&rotate, angle - 30);
			AEMtx33Trans(&translate, _bullet[i].x, _bullet[i].y);
			AEMtx33Concat(&transform, &rotate, &scale);
			AEMtx33Concat(&transform, &translate, &transform);
			AEGfxSetTransform(transform.m);
			AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);
		}
		/*		A
			   /|
			  / |
		     /  |
			/___|
			C	B
		*/

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

		if (enemyX[0] < x)
		{
			if (enemyScaleX > 0)
			{
				enemyScaleX *= -1;
			}
		}		
		if (enemyX[0] > x)
		{
			if (enemyScaleX < 0)
			{
				enemyScaleX *= -1;
			}
		}

		for (int i = 0; i < MAX_ENEMIES; i++)
		{
			AEGfxTextureSet(ETex, 0, 0);
			AEMtx33Scale(&scale, enemyScaleX, 75);
			AEMtx33Rot(&rotate,  AEDegToRad(180));
			AEMtx33Trans(&translate, enemyX[i], enemyY[i]);
			AEMtx33Concat(&transform, &rotate, &scale);
			AEMtx33Concat(&transform, &translate, &transform);
			AEGfxSetTransform(transform.m);
			AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);
		}

		AESysFrameEnd();
		// check if forcing the application to quit
		if (AEInputCheckTriggered(AEVK_ESCAPE) || 0 == AESysDoesWindowExist())
			gGameRunning = 0;


		auto timerEnd = std::chrono::high_resolution_clock::now();
		//static double elapsed_time_ms = std::chrono::duration<double, std::milli>(timerEnd - timerStart).count();
		elapsed = timerEnd - timerStart;
	}

	AEGfxMeshFree(pMesh);

	AEGfxTextureUnload(pTex);
	AEGfxTextureUnload(oOTex);

	AEGfxTextureUnload(ETex);

	// free the system
	
	AESysExit();
}