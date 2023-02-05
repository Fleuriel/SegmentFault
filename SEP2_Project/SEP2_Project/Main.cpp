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

	bool check = true;
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
	f64 enemyX[MAX_ENEMIES] = { 200.0f , 900.0f, 800.0f, 850.0f, 754.0f, 723.0f, 237.0f, 937.0f, 823.0f, 236.0f };
	f64 enemyY[MAX_ENEMIES] = { 200.0f , 100.0f, 200.0f, 350.0f, 664.0f, 423.0f, 537.0f, 737.0f, 423.0f, 736.0f };

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
	float playerXMax = x + 15.0f, playerYMax = y + 15.0f, enemyXMax = 0, enemyYMax = 0;
	float playerXMin = x - 15.0f, playerYMin = y - 15.0f, enemyXMin = 0, enemyYMin = 0;
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
	double rot = 0;

	const float projectileSpeed = 2.0f;
	float enemySpeed = 0.4f;

	//Enemy
	Enemy enemy(enemyX[0], enemyY[0]);
	double angle = atan2(enemy.getY() - 0, enemy.getX() - 0);
	Projectile projectile(0, 0, angle, projectileSpeed);
	f64 lmao;
	// Game Loop
	while (gGameRunning)
	{
		//timer
		auto timerStart = std::chrono::high_resolution_clock::now();
		// Informing the system about the loop's start
		deltaTime += elapsed.count();
		//angle
		//angle = atan2(enemyX[0] - y1, enemyY[0] - x1);

		//std::cout << "enemyX: " << enemyX[0] << "EnemyY: " << enemyY[0] << '\n';
		enemyXMax = enemyX[0] + 15.0f, enemyYMax = enemyY[0] + 15.0f;
		enemyXMin = enemyX[0] - 15.0f, enemyYMin = enemyY[0] - 15.0f;

//		angle = atan2(enemyY[0] - y1, enemyX[0] - x1);
		//std::cout <<"Y: " << enemyY[0] << "X: " << enemyY[0];
		//std::cout << angle << '\n';
		double radius = 5.0;
		if(deltaTime > 0.001f)
		{
			angle = atan2(y1 - y, x1 - x);

			if (rot < 180 && check == false)
			{
				rot += 0.2;
			}
			else
			{
				rot -= 0.2;
				check = true;
			}

			if (rot < 0)
			{
				check = false;
			}


			std::mt19937 rng(std::random_device{}());
			std::uniform_int_distribution<int> angleTDist(0, 360);
			int objcount = 0;
			int angleT = angleTDist(rng);
				for (int i = 0; i < 5; ++i) {
					// Create the object using Alpha Engine's object creation functions
					// ...
					angleT += 360 / 5;
				}
				angleT += std::sin(objcount) * std::cos(objcount) * 12;
				++objcount;
				// Replace the yield call with the appropriate code in Alpha Engine
				// 
				Projectile projectile(x, y, angleT, projectileSpeed);

				_bullet.push_back(projectile);
				// ...
			

			std::cout << "Rotation: " << rot << '\n';
			//angle needs to be a multiple of 2.
			
			
			double newX = x;
			double newY = y;

			
			//Projectile projectile(x, y, angle, projectileSpeed);
			//_bullet.push_back(projectile);
			

			//std::cout << "DT: " << static_cast<int>(deltaTime) << '\n';
			deltaTime = 0;
			//std::cout << _bullet.size() << "    Bullet Size \n";

			//angle = atan2(enemyY[0] - y1, enemyX[0] - x1);
			//Projectile projectile(x1, y1, angle, projectileSpeed);
			//_bullet.push_back(projectile);
			//std::cout << "DT: " << static_cast<int>(deltaTime) << '\n';
			//deltaTime = 0;
			//std::cout << _bullet.size() << "    Bullet Size \n";
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

		/*				   y
						   ^
						   |
						   |
		-------------------|------------------->x
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



		if (AEInputCheckCurr(AEVK_RIGHT) || AEInputCheckCurr(AEVK_D))
		{
			x += 5.0f;
			playerXMax += 5.0f;
			playerXMin += 5.0f;

			if (playerScaleX < 0)
			{
				playerScaleX *= -1;
			}
			//std::cout << "x: " << x << ' ' << "y: " << y << ' ' << "z: " << z << ' ' << "r: " << r << '\n';
		}
		if (AEInputCheckCurr(AEVK_LEFT) || AEInputCheckCurr(AEVK_A))
		{
			x -= 5.0f;     
			playerXMax -= 5.0f;
			playerXMin -= 5.0f;
			if(playerScaleX >0)
				playerScaleX *= -1;
			//std::cout << "x: " << x << ' ' << "y: " << y << ' ' << "z: " << z << ' ' << "r: " << r << '\n';
		}		
		if (AEInputCheckCurr(AEVK_DOWN) || AEInputCheckCurr(AEVK_S))
		{
			y -= 5.0f; 
			playerYMin -= 5.0f;
			playerYMax -= 5.0f;
			//std::cout << "x: " << x << ' ' << "y: " << y << ' ' << "z: " << z << ' ' << "r: " << r << '\n';
		}		
		if (AEInputCheckCurr(AEVK_UP) || AEInputCheckCurr(AEVK_W))
		{
			playerYMax += 5.0f;
			playerYMin += 5.0f;
			y += 5.0f;
			//std::cout << "x: " << x << ' ' << "y: " << y << ' ' << "z: " << z << ' ' << "r: " << r << '\n';
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
		//AEGfxTextureSet(TargetTex, 0, 0);
		//AEMtx33Scale(&scale, 50, 50);
		//AEMtx33Rot(&rotate, 0);
		//AEMtx33Trans(&translate, 200.0f, 200.0f);
		//AEMtx33Concat(&transform, &rotate, &scale);
		//AEMtx33Concat(&transform, &translate, &transform);
		//AEGfxSetTransform(transform.m);
		//AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);

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

		//Moon Projection.
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
			AEMtx33Scale(&scale, 5, 5);
			//			AEMtx33Scale(&scale, 50, 5);
			AEMtx33Rot(&rotate, angle);
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

		//GAME OVER CHECK
		//if (((playerXMax < enemyXMin) && (playerYMax < enemyYMin)) || ((playerXMin > enemyXMax) && (playerYMin > enemyYMax)))
		//	gameOverCheck = 0;
		//else
		//	gameOverCheck = 1;
		//
		//if (gameOverCheck == 1) {
		//	AEGfxTextureSet(GOTex, 0, 0);
		//	AEMtx33Scale(&scale, 500.f, 200.f);
		//	AEMtx33Rot(&rotate, 0);
		//	AEMtx33Trans(&translate, 0, 0);
		//	AEMtx33Concat(&transform, &rotate, &scale);
		//	AEMtx33Concat(&transform, &translate, &transform);
		//	AEGfxSetTransform(transform.m);
		//	AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);
		//	deltaTime = 0;
		//	//rotationx +=0.04f;
		//}



		std::cout  << "Enemy X: " << enemyX[0] << " x: " << x << '\n';

		lmao = enemyX[0] - (x*1.0f);
		std::cout << lmao << '\n';
		if (lmao < 0)
		{
			lmao *= -1;
		}

		if (lmao < 2)
		{
			enemySpeed = 0.0f;
		}
		else
		{
			//enemySpeed = 0.4f;
		}

		//std::cout << " X: " << enemyX[0] << " Y: " << enemyY[0] << '\n';

		//Spawn Mob
		for (int i = 0; i < MAX_ENEMIES; i++)
		{
			if (enemyX[i] < x)
			{
				if (enemyScaleX > 0)
				{
					enemyScaleX *= -1;
				}
			}
			if (enemyX[i] > x)
			{
				if (enemyScaleX < 0)
				{
					enemyScaleX *= -1;
				}
			}
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