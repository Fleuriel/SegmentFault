#include "Main.h"



bool CollisionIntersection_RectRect(const AABB& aabb1, const AEVec2& vel1,
	const AABB& aabb2, const AEVec2& vel2)
{
	UNREFERENCED_PARAMETER(aabb1);
	UNREFERENCED_PARAMETER(vel1);
	UNREFERENCED_PARAMETER(aabb2);
	UNREFERENCED_PARAMETER(vel2);

	// Check for static collision
	if (aabb1.max.x < aabb2.min.x || aabb2.max.x < aabb1.min.x)
		return false;
	if (aabb1.max.y < aabb2.min.y || aabb2.max.y < aabb1.min.y)
		return false;

	float tFirst = 0;
	float tLast = g_dt;



	// Calculate the new velocity of the second rectangle
	float Vb_x = vel2.x - vel1.x;
	float Vb_y = vel2.y - vel1.y;

	// Check the x-axis


	//if vRel (x) < 0...
	if (Vb_x < 0)
	{
		//Case 1
		if (aabb1.min.x > aabb2.max.x) ///
			return 0;
		//Case 4 (1/2)
		if (aabb1.max.x < aabb2.min.x)
			tFirst = max((aabb1.max.x - aabb2.min.x) / Vb_x, tFirst);
		//Case 4 (2/2)
		if (aabb1.min.x < aabb2.max.x)
			tLast = min((aabb1.min.x - aabb2.max.x) / Vb_x, tLast);
	}

	//if vRel (x) > 0...
	if (Vb_x > 0)
	{
		//Case 2 (1/2)
		if (aabb1.min.x > aabb2.max.x)
			tFirst = max((aabb1.min.x - aabb2.max.x) / Vb_x, tFirst);
		//Case 2 (2/2)
		if (aabb1.max.x > aabb2.min.x)
			tLast = min((aabb1.max.x - aabb2.min.x) / Vb_x, tLast);
		//Case 3
		if (aabb1.max.x < aabb2.min.x)
			return 0;
	}

	//Intersection
	if (tFirst > tLast)
		return 0;

	//if vRel (y) < 0...
	if (Vb_y < 0)
	{
		//Case 1
		if (aabb1.min.y > aabb2.max.y)
			return 0;
		//Case 4 (1/2)
		if (aabb1.max.y < aabb2.min.y)
			tFirst = max((aabb1.max.y - aabb2.min.y) / Vb_y, tFirst);
		//Case 4 (2/2)
		if (aabb1.min.y < aabb2.max.y)
			tLast = min((aabb1.min.y - aabb2.max.y) / Vb_y, tLast);
	}

	//if vRel (y) > 0...
	if (Vb_y > 0)
	{
		//Case 2 (1/2)
		if (aabb1.min.y > aabb2.max.y)
			tFirst = max((aabb1.min.y - aabb2.max.y) / Vb_y, tFirst);
		//Case 2 (2/2)
		if (aabb1.max.y > aabb2.min.y)
			tLast = min((aabb1.max.y - aabb2.min.y) / Vb_y, tLast);
		//Case 3
		if (aabb1.max.y < aabb2.min.y)
			return 0;
	}

	//No Intersection
	if (tFirst > tLast)
		return 0;

	// The rectangles intersect
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