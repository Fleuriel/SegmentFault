#include "main.h"
#include <memory>

// ---------------------------------------------------------------------------
// Globals
float	 g_dt;
double	 g_appTime;
int		 FPS = 144;
s8       fontID;
double	 Currency = 0;

/******************************************************************************/
/*!
	Starting point of the application
*/
/******************************************************************************/
int WINAPI WinMain(HINSTANCE instanceH, HINSTANCE prevInstanceH, LPSTR command_line, int show)
{
	UNREFERENCED_PARAMETER(prevInstanceH);
	UNREFERENCED_PARAMETER(command_line);

	// Enable run-time memory check for debug builds.
#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	int* pi = new int;
	delete pi;


	// Initialize the system
	AESysInit(instanceH, show, 1366, 768, 1, FPS, false, NULL);
	//AESysInit(instanceH, show, 1000, 563, 1, FPS, false, NULL);
	

	// Changing the window title
	AESysSetWindowTitle("Among Them!");

	//set background color
	//AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);

	// Initialize font
	fontID = AEGfxCreateFont("Assets\\Assets\\Minecraft.ttf", 50);

	//Set game state to GS_ASTEROIDS.
	GameStateMgrInit(MAINMENU);

	while (gGameStateCurr != QUIT)
	{
		// reset the system modules
		AESysReset();

		// If not RESTART, load the gamestate
		if (gGameStateCurr != QUIT)
		{
			GameStateMgrUpdate();
			GameStateLoad();
		}
		else
			gGameStateNext = gGameStateCurr = gGameStatePrev;

		// Initialize the gamestate
		GameStateInit();

		while (gGameStateCurr == gGameStateNext)
		{
			AESysFrameStart();

			AEInputUpdate();

			GameStateUpdate();

			GameStateDraw();

			AESysFrameEnd();

			// check if forcing the application to quit
			if ((AESysDoesWindowExist() == false) || AEInputCheckTriggered(AEVK_ESCAPE))
				gGameStateNext = QUIT;



			g_dt = (f32)AEFrameRateControllerGetFrameTime();
			g_appTime += g_dt;
		}

		GameStateFree();

		if (gGameStateNext != RESTART)
			GameStateUnload();

		gGameStatePrev = gGameStateCurr;
		gGameStateCurr = gGameStateNext;
	}

	// free the system
	AESysExit();
}