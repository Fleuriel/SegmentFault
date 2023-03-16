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
#include "PauseMenu.h"
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
<<<<<<< Updated upstream
extern int   Currency;
extern float currHighScoreMin;
extern float currHighScoreSec;
//<<<<<<< Updated upstream
=======
extern double   Currency;
extern int		ShipModel;
>>>>>>> Stashed changes

// Pre-definition of scaling
extern double scaleX;
extern double scaleY;


<<<<<<< Updated upstream
extern int		ShipModel;
=======

// ---------------------------------------------------------------------------
>>>>>>> Stashed changes
