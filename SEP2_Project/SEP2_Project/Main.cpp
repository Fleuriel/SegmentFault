/******************************************************************************/
/*!
\file       Main.cpp
\project    Among Them

\authors    Angus Tan Yit Hoe, tan.a, 2200711 (20%)
			Liu Xujie, l.xujie,  (20%)
			Ang Jun Sheng Aloysius, a.junshengaloysius, 2201807 (20%)
			Lim Zhan Peng, zhanpeng.lim, 2203452 (20%)
			Emery Quek Cheng Kwang, c.quek, 2201955 (20%)

\par        tan.a@digipen.edu
\brief      This .cpp file contains the main function of the program.


Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
 */
 /******************************************************************************/

#include "main.h"
#include <memory>



// ---------------------------------------------------------------------------
// Globals
float	 g_dt;
double	 g_appTime;
int		 FPS = 144;
s8       fontID;


//Game World Dimensions
AEVec2	Game_Dimension{ 1600.0f, 900.0f };


//Game World Parameters
int		Currency = 0;
int		ShipModel;
int		MaximumPlayerHealth;
int	    ProjectileSpeed_upgrade;
int	    CD_upgrade;
int	    Regen_upgrade;

float	currHighScoreMin = 0.f;
float	currHighScoreSec = 0.f;

// Pre-definition of scaling
float	scaleX;
float	scaleY;

f32		BGtransX, BGtransY;

/******************************************************************************/
/*!
	Starting point of the application
*/
/******************************************************************************/
_Use_decl_annotations_ int WINAPI WinMain(HINSTANCE instanceH, HINSTANCE prevInstanceH, LPSTR command_line, int show)
{
	SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);


	// Enable run-time memory check for debug builds.
#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif



	// Initialize the system
	AESysInit(instanceH, show, static_cast<s32>(Game_Dimension.x), static_cast<s32>(Game_Dimension.y), 1, FPS, false, NULL);
	//AESysInit(instanceH, show, 160, 90, 1, FPS, false, NULL);
	

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

			if (AESysDoesWindowExist() == false)
				gGameStateNext = QUIT;

			AESysFrameEnd();

			g_dt = (f32)AEFrameRateControllerGetFrameTime();
			g_appTime += g_dt;
		}

		GameStateFree();

		if (gGameStateNext != RESTART)
			GameStateUnload();

		gGameStatePrev = gGameStateCurr;
		gGameStateCurr = gGameStateNext;
	}

	AEGfxDestroyFont(fontID);

	// free the system
	AESysExit();
}