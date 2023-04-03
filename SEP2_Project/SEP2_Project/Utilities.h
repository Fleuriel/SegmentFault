#pragma once
/******************************************************************************/
/*!
\file		Utilities.h
\author		Liu Xujie, l.xujie, 2203183
\par		l.xujie@digipen.edu
\brief		This is a header file for Utilities.cpp which contain the function 
			declarations

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
 */
 /******************************************************************************/

#include "AEEngine.h"



struct AABB
{
	//AEVec2	c; // center
	//float  r[2]; // holds half width and half height

	AEVec2	min;
	AEVec2	max;
};
/*!*****************************************************************
  \brief
	This function checks for the collision between two rectangular
	object
  \param[in] aabb1
   struct of the min and max x y values for object 1
  \param[in] vel1
  velocity vector for object 1
  \param[in] aabb2
   struct of the min and max x y values for object 2
  \param[in] aabb2
  velocity vector for object 2
  \return
  true if colliding false if not colliding
********************************************************************/
bool CollisionIntersection_RectRect(const AABB& aabb1, const AEVec2& vel1,
	const AABB& aabb2, const AEVec2& vel2);

bool CollisionCircleCircle(const AEVec2& center1, f32 radius1, const AEVec2& center2, f32 radius2);

// Function to check if the area is being touched/clicked
int IsAreaClicked(float area_center_x, float area_center_y, float area_width, float area_height, int click_x, int click_y);

// Function to get window width
float getWinWidth();

// Function to get window width
float getWinHeight();

// Function to get angle of cursor to player in radian
double getCursorRad(AEVec2 pos);
