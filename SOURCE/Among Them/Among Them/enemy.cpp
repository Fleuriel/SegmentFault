
#include "AEEngine.h"
#include "enemy.hpp"


struct enemyCoord {
	f32 enemyX;
	f32 enemyY;
	//Construct
	enemyCoord() : enemyX(0), enemyY(0){ }
}AI;


struct enemyCoord getInfo(struct enemyCoord AI)
{
	AI.enemyX = 1366.0f;
	AI.enemyY = 768.0f;
	return AI;
}


void Enemy(struct enemyCoord AI, f32 playerX, f32 playerY)
{

	if (AI.enemyX > playerX)
	{
		AI.enemyX--;
	}
	if (AI.enemyX < playerX)
	{
		AI.enemyX++;
	}

	if (AI.enemyY > playerX)
	{
		AI.enemyY--;
	}
	if (AI.enemyY < playerX)
	{
		AI.enemyY++;
	}


}