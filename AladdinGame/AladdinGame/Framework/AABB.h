#pragma once
#include "define.h"
#include <cmath>
#include "VectorHelper.h"
//Bottom lelf - rectangle for collision detection
class AABB
{
public:
	AABB();
	AABB(const RECT &rect);
	AABB(const GVector2 &center, const GVector2 &extents);
	~AABB();
	AABB& operator= (const RECT& rect);
	operator RECT();
	RECT rect;
	GVector2 getMin();
	GVector2 getMax();
	GVector2 getSize();
	void move(GVector2 moveVector);
	AABB minkowskiDifference(AABB other);
	GVector2 cloestPointOnBoundsToPoint(GVector2 point);
	float getRayIntersectionFractionOffFirstRay(GVector2 originA, GVector2 endA, GVector2 originB, GVector2 endB);
	float getRayIntersectionFraction(GVector2 origin, GVector2 direction);
private:

};

