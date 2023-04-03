/******************************************************************************/
/*!
\file		MainMenu.h
\author		Ang Jun Sheng Aloysius, a.junshengaloysius, 2201807
\par		a.junshengaloysius@digipen.edu
\brief		Starting point of the game, where all the buttons to lead to other states are at.
			Contains the declarations of functions for the main menu to change its state, such as to the play state or settings state.

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
 */
 /******************************************************************************/

#pragma once


void Menu_Load(void);
void Menu_Init(void);
void Menu_Update(void);
void Menu_Draw(void);
void Menu_Free(void);
void Menu_Unload(void);