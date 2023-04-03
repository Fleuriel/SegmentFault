/******************************************************************************/
/*!
\file		Utilities.cpp
\author		Liu Xujie, l.xujie, 2203183
\par		l.xujie@digipen.edu
\brief		Definition of function helpers

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
 */
 /******************************************************************************/

#include "Main.h"

/*!*****************************************************************
  \author
   Liu Xujie
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
    const AABB& aabb2, const AEVec2& vel2)
{
    // Check static collision

    if (aabb1.max.x > aabb2.min.x && aabb1.max.y > aabb2.min.y && aabb2.max.x > aabb1.min.x && aabb2.max.y > aabb1.min.y) {
        return true;
    }

    AEVec2 veloVec{};
    veloVec.x = vel2.x - vel1.x;
    veloVec.y = vel2.y - vel1.y;
    AEVec2 tFirst{ 0 };
    AEVec2 tLast{ (float)AEFrameRateControllerGetFrameTime(), (float)AEFrameRateControllerGetFrameTime() };
    AEVec2 tFirsttemp{ 0 };
    AEVec2 tLasttemp{ (float)AEFrameRateControllerGetFrameTime(), (float)AEFrameRateControllerGetFrameTime() };

    // Check if the rectangles are moving towards each other on X axis
    if (veloVec.x < 0) {
        if (aabb1.min.x > aabb2.max.x) {
            return false;
        }
        else {
            tFirsttemp.x = (aabb1.max.x - aabb2.min.x) / veloVec.x;
            if (tFirsttemp.x > tFirst.x)
                tFirst.x = tFirsttemp.x;
            tLasttemp.x = (aabb1.min.x - aabb2.max.x) / veloVec.x;
            if (tLast.x > tLasttemp.x)
                tFirst.x = tFirsttemp.x;
        }
    }
    else {
        if (aabb1.min.x > aabb2.max.x) {
            tFirsttemp.x = (aabb1.max.x - aabb2.min.x) / veloVec.x;
            if (tFirsttemp.x > tFirst.x)
                tFirst.x = tFirsttemp.x;
            tLasttemp.x = (aabb1.min.x - aabb2.max.x) / veloVec.x;
            if (tLast.x > tLasttemp.x)
                tFirst.x = tFirsttemp.x;
        }
        else {
            return false;
        }
    }
    // Check if the rectangles are moving towards each other on Y axis
    if (veloVec.y < 0) {
        if (aabb1.min.y > aabb2.max.y) {
            return false;
        }
        else {
            tFirsttemp.y = (aabb1.max.y - aabb2.min.y) / veloVec.y;
            if (tFirsttemp.y > tFirst.y)
                tFirst.y = tFirsttemp.y;
            tLasttemp.y = (aabb1.min.y - aabb2.max.y) / veloVec.y;
            if (tLast.y > tLasttemp.y)
                tFirst.y = tFirsttemp.y;
        }
    }
    else {
        if (aabb1.min.y > aabb2.max.y) {
            tFirsttemp.y = (aabb1.max.y - aabb2.min.y) / veloVec.y;
            if (tFirsttemp.y > tFirst.y)
                tFirst.y = tFirsttemp.y;
            tLasttemp.y = (aabb1.min.y - aabb2.max.y) / veloVec.y;
            if (tLast.y > tLasttemp.y)
                tFirst.y = tFirsttemp.y;
        }
        else {
            return false;
        }
    }

    // Check if the time of collision is within the frame time
    if (tFirst.y > tLast.x || tFirst.x > tLast.y)
    {
        return false;
    }

    if (tFirst.x > tFirst.y)
    {
        if (tFirst.x < 0 || tFirst.x >(float)AEFrameRateControllerGetFrameTime())
        {
            return false;
        }
    }
    else
    {
        if (tFirst.y < 0 || tFirst.y >(float)AEFrameRateControllerGetFrameTime())
        {
            return false;
        }
    }

    return true;
}


bool CollisionCircleCircle(const AEVec2& center1, f32 radius1, const AEVec2& center2, f32 radius2)
{
	float dx = center2.x - center1.x;
	float dy = center2.y - center1.y;
	float distanceSquared = dx * dx + dy * dy;

	// Calculate the sum of the radii
	float radiusSum = radius1 + radius2;

	// Check if the distance is less than or equal to the sum of the radii
	return distanceSquared <= radiusSum * radiusSum;
}

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
int IsAreaClicked(float area_center_x, float area_center_y, float area_width, float area_height, int click_x, int click_y)
{
	// TODO
	if (click_x > area_center_x - (area_width / 2) && click_x < area_center_x + (area_width / 2)
		&& click_y < area_center_y + (area_height / 2) && click_y > area_center_y - (area_height / 2))
	{
		return 1;
	}

	return 0;
}

/*!*****************************************************************
  \author
   Ang Jun Sheng Aloysius
  \brief
   This function gets the width of the window.
  \param[in] none
  \return
   Width of the window
********************************************************************/
float getWinWidth() {
	return AEGfxGetWinMaxX() - AEGfxGetWinMinX();
}

/*!*****************************************************************
  \author
   Ang Jun Sheng Aloysius
  \brief
   This function gets the height of the window.
  \param[in] none
  \return
   Height of the window
********************************************************************/
float getWinHeight() {
	return AEGfxGetWinMaxY() - AEGfxGetWinMinY();
}

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
double getCursorRad(AEVec2 pos) {
    s32 cX, cY;                     //Mouse position
    double rad = 0;                 //radian value to be returned
    const double pi = 3.1415926;    //define pi
    float sumx = 0, sumy = 0;
    pos.y += 75;

    AEInputGetCursorPosition(&cX, &cY);
    AEVec2 MP = { (f32)cX - (Game_Dimension.x / 2), -((f32)cY - (Game_Dimension.y / 2)) }; //Mouse pos with reference to window size

    //mouse position - player pos
    sumx = MP.x - pos.x;
    sumy = MP.y - pos.y;

    //for each quadrant
    if (MP.x > pos.x && MP.y > pos.y) { rad = pi + atan(sumy / sumx); }          //Quad1
    else if (MP.x < pos.x && MP.y > pos.y) { rad = pi + atan(sumy / sumx); }     //Quad2
    else if (MP.x < pos.x && MP.y < pos.y) { rad = pi + atan(sumy / sumx); }     //Quad3
    else if (MP.x > pos.x && MP.y < pos.y) { rad = pi + atan(sumy / sumx); }     //Quad4

    return rad; //Return radian value
}