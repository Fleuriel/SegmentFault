#pragma once


#include "AEEngine.h"



struct AABB
{
	//AEVec2	c; // center
	//float  r[2]; // holds half width and half height

	AEVec2	min;
	AEVec2	max;
};

bool CollisionIntersection_RectRect(const AABB& aabb1, const AEVec2& vel1,
	const AABB& aabb2, const AEVec2& vel2);

bool CollisionCircleCircle(const AEVec2& center1, f32 radius1, const AEVec2& center2, f32 radius2);