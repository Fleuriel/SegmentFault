#include "GameStateMgr.h"
#include "main.h"

unsigned int	gGameStateInit;
unsigned int	gGameStateCurr;
unsigned int	gGameStatePrev;
unsigned int	gGameStateNext;

// pointer to functions for game state life cycles functions
void (*GameStateLoad)() = 0;
void (*GameStateInit)() = 0;
void (*GameStateUpdate)() = 0;
void (*GameStateDraw)() = 0;
void (*GameStateFree)() = 0;
void (*GameStateUnload)() = 0;


void GameStateMgrInit(unsigned int gameStateInit)
{
	// set the initial game state
	gGameStateInit = gameStateInit;

	// reset the current, previoud and next game
	gGameStateCurr = gGameStateInit;
	gGameStatePrev = gGameStateInit;
	gGameStateNext = gGameStateInit;

	// call the update to set the function pointers
	GameStateMgrUpdate();

}

void GameStateMgrUpdate()
{
	if ((gGameStateCurr == RESTART) || (gGameStateCurr == QUIT))
		return;

	switch (gGameStateCurr)
	{
	case MAINMENU:
		GameStateLoad   = Menu_Load;
		GameStateInit   = Menu_Init;
		GameStateUpdate = Menu_Update;
		GameStateDraw   = Menu_Draw;
		GameStateFree   = Menu_Free;
		GameStateUnload = Menu_Unload;
		break;
	case PLAY:
		GameStateLoad   = Level_1_Load;
		GameStateInit   = Level_1_Init;
		GameStateUpdate = Level_1_Update;
		GameStateDraw   = Level_1_Draw;
		GameStateFree   = Level_1_Free;
		GameStateUnload = Level_1_Unload;
		break;
		// no need for GS RESTART/GS_QUIT because if statement.
	case UPGRADE:
		GameStateLoad	= Upgrade_Load;
		GameStateInit	= Upgrade_Init;
		GameStateUpdate = Upgrade_Update;
		GameStateDraw	= Upgrade_Draw;
		GameStateFree	= Upgrade_Free;
		GameStateUnload = Upgrade_Unload;
		break;

	case SETTINGS:
		GameStateLoad = Settings_Load;
		GameStateInit = Settings_Init;
		GameStateUpdate = Settings_Update;
		GameStateDraw = Settings_Draw;
		GameStateFree = Settings_Free;
		GameStateUnload = Settings_Unload;
		break;

	case PAUSE:
		GameStateLoad = Pause_Load;
		GameStateInit = Pause_Init;
		GameStateUpdate = Pause_Update;
		GameStateDraw = Pause_Draw;
		GameStateFree = Pause_Free;
		GameStateUnload = Pause_Unload;
		break;

	default:
		AE_FATAL_ERROR("invalid state!!");
	}
}