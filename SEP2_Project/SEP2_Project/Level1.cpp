
#include "Main.h"
#include "GameObjects.h"



void Level_1_Load(void)
{
	
}

void Level_1_Init(void)
{

}
void Level_1_Update(void)
{


	//As of now i will be moving the X and Y coordinates with these, someone need to do the offsets.

	if (AEInputCheckCurr(AEVK_RIGHT) || AEInputCheckCurr(AEVK_D))
	{

	}
	if (AEInputCheckCurr(AEVK_LEFT) || AEInputCheckCurr(AEVK_A))
	{

	}
	if (AEInputCheckCurr(AEVK_DOWN) || AEInputCheckCurr(AEVK_S))
	{

	}
	if (AEInputCheckCurr(AEVK_UP) || AEInputCheckCurr(AEVK_W))
	{

	}


	//Updates projectile position.
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

}

void Level_1_Draw(void)
{




}
void Level_1_Free(void)
{

}

void Level_1_Unload(void) 
{

}