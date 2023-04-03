#pragma once
/******************************************************************************/
/*!
\file       GameStateList.h
\project    Among Them
\authors	Angus Tan Yit Hoe, tan.a (100%)

\par        tan.a@digipen.edu

\brief      This .h file contains the enumerations for Main.cpp and 
			GameStateMgr.cpp to use

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
 */
 /******************************************************************************/




enum
{
	// list of all game states 
	MAINMENU = 0,

	//Start Game
	PLAY,
	// special game state. Do not change
	SPLASHPAGE,
	UPGRADE,
	RESTART,
	SETTINGS,
	HOWTOPLAY,
	CREDITS,
	AUGMENTS,
	GAMEOVER,
	QUIT

};