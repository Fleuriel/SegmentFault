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
	case SPLASHPAGE:
		GameStateLoad = SplashPage_Load;
		GameStateInit = SplashPage_Init;
		GameStateUpdate = SplashPage_Update;
		GameStateDraw = SplashPage_Draw;
		GameStateFree = SplashPage_Free;
		GameStateUnload = SplashPage_Unload;
		break;
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
	case CREDITS:
		GameStateLoad = Credits_Load;
		GameStateInit = Credits_Init;
		GameStateUpdate = Credits_Update;
		GameStateDraw = Credits_Draw;
		GameStateFree = Credits_Free;
		GameStateUnload = Credits_Unload;
		break;
	case GAMEOVER:
		GameStateLoad = GameOver_Load;
		GameStateInit = GameOver_Init;
		GameStateUpdate = GameOver_Update;
		GameStateDraw = GameOver_Draw;
		GameStateFree = GameOver_Free;
		GameStateUnload = GameOver_Unload;
		break;


	default:
		AE_FATAL_ERROR("invalid state!!");
	}
}