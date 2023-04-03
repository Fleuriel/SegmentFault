#pragma once

/******************************************************************************/
/*!
\file       Level1.cpp
\project    Among Them
\authors	Liu Xujie, l.xujie,  (20%)
            Ang Jun Sheng Aloysius, a.junshengaloysius, 2201807 (20%)
            Lim Zhan Peng, zhanpeng.lim, 2203452 (20%)
            Angus Tan Yit Hoe, tan.a, 2200711 (20%)
            Emery Quek Cheng Kwang, c.quek

\par        tan.a@digipen.edu
\brief      This .cpp file contains the functions necessary for the game to run
			namely, Load, Initialize, Update,Free,Unload...

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
 */
 /******************************************************************************/




// includes
#include <iostream>
#include <fstream>
#include <math.h>

#include "GameStateMgr.h"

#include "Level1.h"
#include "Upgrade.h"
#include "MainMenu.h"
#include "SettingsMenu.h"
#include "HowToPlay.h"
#include "Credits.h"
#include "GameOverMenu.h"
#include "SplashPage.h"

//Utilities.h contains AEngine.h
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
extern int	    ProjectileSpeed_upgrade; 
extern int	    CD_upgrade;
extern int	    Regen_upgrade;


// Pre-definition of scaling
extern float	scaleX;
extern float	scaleY;

extern f32 BGtransX, BGtransY;



// ---------------------------------------------------------------------------
