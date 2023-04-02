#pragma once



// includes
#include <chrono>
#include <ctime>
#include <iostream>
#include <fstream>

#include "AEEngine.h"
#include "Math.h"

#include "GameStateMgr.h"
#include "GameStateList.h"

#include "Level1.h"
#include "Upgrade.h"
#include "MainMenu.h"
#include "SettingsMenu.h"
#include "Credits.h"
#include "GameOverMenu.h"
#include "SplashPage.h"

#include "Utilities.h"


//------------------------------------
// Globals
extern float	g_dt;
extern double	g_appTime;
extern s8       fontID;

//Game Dimensions
extern AEVec2	Game_Dimension;


//Game World Parameters
extern int		Currency;
extern int		ShipModel;
extern int		MaximumPlayerHealth;
extern float	currHighScoreMin;
extern float	currHighScoreSec;


// Pre-definition of scaling
extern float	scaleX;
extern float	scaleY;

extern f32 BGtransX, BGtransY;



// ---------------------------------------------------------------------------
