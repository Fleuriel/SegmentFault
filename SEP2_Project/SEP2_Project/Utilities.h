#pragma once
/******************************************************************************/
/*!
\file        Utilities.h
\project    Among Them
\authors    Liu Xujie, l.xujie,  (25%)
			Ang Jun Sheng Aloysius, a.junshengaloysius, 2201807 (35%)
			Lim Zhan Peng, zhanpeng.lim, 2203452 (25%)
			Angus Tan Yit Hoe, tan.a, 2200711 (15%)
\par        l.xujie@digipen.edu
			a.junshengaloysius@digipen.edu
			zhanpeng.lim@digipen.edu
			tan.a@digipen.edu
\brief        Definition of function helpers

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
/*!*****************************************************************
  \author
   Angus
  \brief
   This function checks for the collision between two Circles
  \param[in] center1
   center of circle1
  \param[in] radius1
  radius of circle 1
  \param[in] center2
   center of circle 2
  \param[in] radius2
   radius of cicle 2
  \return
   true if colliding false if not colliding
********************************************************************/

bool CollisionCircleCircle(const AEVec2& center1, f32 radius1, const AEVec2& center2, f32 radius2);

/*!*****************************************************************
  \author
   Ang Jun Sheng Aloysius
  \brief
   This function checks for the collision in a rectangle.
   object
  \param[in] area_center_x
   Center of the rectangle's X position
  \param[in] area_center_y
   Center of the rectangle's Y position
  \param[in] area_width
   Width of the rectangle
  \param[in] area_height
   Height of the rectangle
  \param[in] click_x
   X-coordinate of mouse cursor
  \param[in] click_y
   Y-coordinate of mouse cursor
  \return
   1 if true, 0 if false
********************************************************************/
int IsAreaClicked(float area_center_x, float area_center_y, float area_width, float area_height, int click_x, int click_y);

/*!*****************************************************************
  \author
   Ang Jun Sheng Aloysius
  \brief
   This function gets the width of the window.
  \param[in] none
  \return
   Width of the window
********************************************************************/
float getWinWidth();

/*!*****************************************************************
  \author
   Ang Jun Sheng Aloysius
  \brief
   This function gets the height of the window.
  \param[in] none
  \return
   Height of the window
********************************************************************/
float getWinHeight();

/*!*****************************************************************
\author
Lim Zhan Peng
\brief
This function returns the angle between the cursor and player drone
\param[in] pos
Player position
\return
angle in radian
********************************************************************/
double getCursorRad(AEVec2 pos);
