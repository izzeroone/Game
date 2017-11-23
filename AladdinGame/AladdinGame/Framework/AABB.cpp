#include "AABB.h"



AABB::AABB()
{
}

AABB::AABB(const RECT &rect)
{
	center.x = (rect.right + rect.left) / 2;
	center.y = (rect.bottom + rect.top) / 2;
	extents.x = (rect.right - rect.left) / 2;
	extents.y = (rect.top - rect.bottom) / 2;
}

AABB::AABB(const GVector2 & center, const GVector2 & extents)
{
	this->center = center;
	this->extents = extents;
}


AABB::~AABB()
{
}

AABB & AABB::operator=(const RECT & rect)
{
	center.x = (rect.right + rect.left) / 2;
	center.y = (rect.bottom + rect.top) / 2;
	extents.x = (rect.right - rect.left) / 2;
	extents.y = (rect.top - rect.bottom) / 2;
	return (*this);
}

AABB::operator RECT()
{
	RECT rect;
	rect.left = center.x - extents.x;
	rect.right = center.x + extents.x;
	rect.top = center.y + extents.y;
	rect.bottom = center.y - extents.y;
	return rect;
}

GVector2 AABB::getMin()
{
	return GVector2(center.x - extents.x, center.y - extents.y);
}

GVector2 AABB::getMax()
{
	return GVector2(center.x + extents.x, center.y + extents.y);
}

GVector2 AABB::getSize()
{
	return GVector2(extents.x * 2, extents.y * 2);
}

AABB AABB::minkowskiDifference(AABB other)
{
	GVector2 topLeft = getMin() - other.getMax();
	GVector2 fullSize = getSize() + other.getSize();
	return AABB(topLeft + (fullSize / 2), fullSize / 2);
}

GVector2 AABB::cloestPointOnBoundsToPoint(GVector2 point)
{
	float minDist = abs(point.x - getMin().x);
	GVector2 boundsPoint(getMin().x, point.y);
	if (abs(getMax().x - point.x) < minDist)
	{
		minDist = abs(getMax().x - point.x);
		//boundsPoint = new Vector(getMax().x, point.y);
		boundsPoint.x = getMax().x;
		boundsPoint.y = point.y;
	}
	if (abs(getMax().y - point.y) < minDist)
	{
		minDist = abs(getMax().y - point.y);
		//boundsPoint = new Vector(point.x, getMax().y);
		boundsPoint.x = point.x;
		boundsPoint.y = getMax().y;
	}
	if (abs(getMin().y - point.y) < minDist)
	{
		minDist = abs(getMin().y - point.y);
		//boundsPoint = new Vector(point.x, min.y);
		boundsPoint.x = point.x;
		boundsPoint.y = getMin().y;
	}
	return boundsPoint;
}

float AABB::getRayIntersectionFractionOffFirstRay(GVector2 originA, GVector2 endA, GVector2 originB, GVector2 endB)
{
	GVector2 r = endA - originA;
	GVector2 s = endB - originB;

	float numerator = VectorHelper::crossProduct(originB - originA, r);
	float denominator = VectorHelper::crossProduct(r, s);

	if (numerator == 0 && denominator == 0)
	{
		//the lines are co-linear
		return std::numeric_limits<float>::infinity();
	}

	if (denominator == 0)
	{
		// lines are parallel
		return std::numeric_limits<float>::infinity();
	}

	float u = numerator / denominator;
	float t = VectorHelper::crossProduct(originB - originA, s) / denominator;
	if ((t >= 0) && (t <= 1) && (u >= 0) && (u <= 1))
	{
		//return originA + (r * t);
		return t;
	}
	return std::numeric_limits<float>::infinity();
}

float AABB::getRayIntersectionFraction(GVector2 origin, GVector2 direction)
{
	GVector2 end = origin + direction;

	float minT = getRayIntersectionFractionOffFirstRay(origin, end, getMin(), GVector2(getMin().x, getMax().y));
	float x = getRayIntersectionFractionOffFirstRay(origin, end, GVector2(getMin().x, getMax().y), GVector2(getMax().x, getMax().y));
	if (x < minT)
		minT = x;
	x = getRayIntersectionFractionOffFirstRay(origin, end, GVector2(getMax().x, getMax().y), GVector2(getMax().x, getMin().y));
	if (x < minT)
		minT = x;
	x = getRayIntersectionFractionOffFirstRay(origin, end, GVector2(getMax().x, getMin().y), GVector2(getMin().x, getMin().y));
	if (x < minT)
		minT = x;

	// ok, now we should have found the fractional component along the ray where we collided
	return minT;
}

