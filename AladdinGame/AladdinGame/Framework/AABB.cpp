#include "AABB.h"



AABB::AABB()
{
}

AABB::AABB(const RECT &rect)
{
	this->rect = rect;
}

AABB::AABB(const GVector2 & center, const GVector2 & extents)
{
	rect.left = center.x - extents.x;
	rect.right = center.x + extents.x;
	rect.top = center.y + extents.y;
	rect.bottom = center.y - extents.y;
}


AABB::~AABB()
{
}

AABB & AABB::operator=(const RECT & rect)
{
	this->rect = rect;
	return (*this);
}

AABB::operator RECT()
{
	return rect;
}

GVector2 AABB::getMin()
{
	return GVector2(rect.left, rect.bottom);
}

GVector2 AABB::getMax()
{
	return GVector2(rect.right, rect.top);
}

GVector2 AABB::getSize()
{
	return GVector2(rect.right - rect.left, rect.top - rect.bottom);
}

void AABB::move(GVector2 moveVector)
{
	rect.left += moveVector.x;
	rect.right += moveVector.x;
	rect.top += moveVector.y;
	rect.bottom += moveVector.y;
}
//https://hamaluik.com/posts/simple-aabb-collision-using-minkowski-difference/
AABB AABB::minkowskiDifference(AABB other)
{
	//GVector2 topLeft = getMin() - other.getMax();
	//GVector2 fullSize = getSize() + other.getSize();
	//return AABB(topLeft + (fullSize / 2), fullSize / 2);
	RECT minkow;
	minkow.left = rect.left - other.rect.right;
	minkow.bottom = rect.bottom - other.rect.top;
	minkow.right = minkow.left + (rect.right - rect.left) + (other.rect.right - other.rect.left);
	minkow.top = minkow.bottom + (rect.top - rect.bottom) + (other.rect.top - other.rect.bottom);
	return minkow;

}

//tìm điểm trên viền gần nhất
GVector2 AABB::cloestPointOnBoundsToPoint(GVector2 point)
{
	//bug here need to reserve

	//test on left border
	float minDist = abs(point.x - rect.left);
	GVector2 boundsPoint(rect.left, point.y);
	//test on right border
	if (abs(rect.right - point.x) < minDist)
	{
		minDist = abs(rect.right - point.x);
		//boundsPoint = new Vector(getMax().x, point.y);
		boundsPoint.x = rect.right;
		boundsPoint.y = point.y;
	}
	//test on top border
	if (abs(rect.top - point.y) < minDist)
	{
		minDist = abs(rect.top - point.y);
		//boundsPoint = new Vector(point.x, getMax().y);
		boundsPoint.x = point.x;
		boundsPoint.y = rect.top;
	}
	//test on bottom border
	if (abs(rect.bottom - point.y) < minDist)
	{
		minDist = abs(rect.bottom - point.y);
		//boundsPoint = new Vector(point.x, min.y);
		boundsPoint.x = point.x;
		boundsPoint.y = rect.bottom;
	}
	return boundsPoint;
}
//tìm giao điển của 2 đoạn thẳng A và B (origin : điểm xuất phát, end : điểm kết thúc)
//ref https://stackoverflow.com/questions/563198/how-do-you-detect-where-two-line-segments-intersect
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
	//test on left line
	float minT = getRayIntersectionFractionOffFirstRay(origin, end, getMin(), GVector2(getMin().x, getMax().y));

	//test on top line
	float x = getRayIntersectionFractionOffFirstRay(origin, end, GVector2(getMin().x, getMax().y), GVector2(getMax().x, getMax().y));
	if (x < minT)
		minT = x;

	//test on right line
	x = getRayIntersectionFractionOffFirstRay(origin, end, GVector2(getMax().x, getMax().y), GVector2(getMax().x, getMin().y));
	if (x < minT)
		minT = x;

	//test bottom line
	x = getRayIntersectionFractionOffFirstRay(origin, end, GVector2(getMax().x, getMin().y), GVector2(getMin().x, getMin().y));
	if (x < minT)
		minT = x;

	// ok, now we should have found the fractional component along the ray where we collided
	return minT;
}

