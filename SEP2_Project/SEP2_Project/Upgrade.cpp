#include "Upgrade.h"
#include "Main.h"


void Upgrade_Load(void) 
{

}

void Upgrade_Init(void) 
{

}
void Upgrade_Update(void) 
{
	if (AEInputCheckTriggered(AEVK_LBUTTON))
	{
		std::cout << "Play\n";
		gGameStateNext = PLAY;
	}

}
void Upgrade_Draw(void) 
{

}
void Upgrade_Free(void) 
{

}
void Upgrade_Unload(void) 
{

}