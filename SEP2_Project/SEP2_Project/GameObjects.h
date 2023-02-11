#pragma once
#include <vector>
#include "AEEngine.h"
#include "Main.h"
#define MAX_ENEMIES 100


class Projectile {
public:
	f64 x, y;
	f64 angle;
	f64 speed;

	Projectile(f64 x = 0, f64 y = 0, f64 angle = 0, f64 speed = 0)
		: x(x), y(y), angle(angle), speed(speed) {}

	void updatePosition() {
		x += speed * cos(angle);
		y += speed * sin(angle);
	}
};

class Enemy {
private:
	f64 x, y, distanceX, distanceY;
	f64 angle;
	f64 speed;
	
public:
	//Enemy Constructor with x,y ,angle and speed of enemy.
	Enemy(f64 x = 0, f64 y = 0, f64 angle = 0, f64 speed = 0)
		: x(x), y(y), angle(angle), speed(speed) {}

	//Copy Constructor
//	Enemy (Enemy const& e){ }
	//Destructor..
//	~Enemy(){}

	void updatePosition() {
		x += speed * cos(angle);
		y += speed * sin(angle);
	}

	void updatePosition(double x, double y) {
		distanceX = this->x - x;
		distanceY = this->y - y;

		double magnitude = sqrt(pow(distanceX, 2) + pow(distanceY, 2));
		distanceX /= magnitude;
		distanceY /= magnitude;

		this->x -= distanceX * speed;
		this->y -= distanceY * speed;
	}
	f64 getX() { return x; }
	f64 getY() { return y; }
	f64 getAngle()  { return angle; }
};

//Parameters
//Enemy (Now)
f64 enemyX[MAX_ENEMIES] = { 200.0f , 900.0f, 800.0f, 850.0f, 754.0f, 723.0f, 237.0f, 937.0f, 823.0f, 236.0f };
f64 enemyY[MAX_ENEMIES] = { 200.0f , 100.0f, 200.0f, 350.0f, 664.0f, 423.0f, 537.0f, 737.0f, 423.0f, 736.0f };



//parameters for constructor to fufil..
f64 playerSpeed = 1.0f;
f64 projectileSpeed = 1.0f;


//Creating the objects for enemy and Projectile.
Enemy enemy(enemyX[0], enemyY[0], 0 , playerSpeed);
f64 angle = atan2(enemy.getY() - 0, enemy.getX());
Projectile projectile(0, 0, angle, projectileSpeed);



//Creating Vector(List) for instances..
std::vector<Projectile> _bullet;



//Assets (Images)




//Assets Mesh
AEGfxMeshStart();
AEGfxTriAdd(
	0.5f, 0.5f, 0x292929, 1.0f, 0.0f,
	-0.5f, -0.5f, 0xC0C0C0, 0.0f, 1.0f,
	0.5f, -0.5f, 0x808080, 1.0f, 1.0f);
AEGfxTriAdd(
	-0.5f, 0.5f, 0x808080, 0.0f, 0.0f,
	-0.5f, -0.5f, 0xC0C0C0, 0.0f, 1.0f,
	0.5f, 0.5f, 0x292929, 1.0f, 0.0f);
//Assets (Sound)


