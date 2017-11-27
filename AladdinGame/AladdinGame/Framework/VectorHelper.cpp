#include "VectorHelper.h"



VectorHelper::VectorHelper()
{
}


VectorHelper::~VectorHelper()
{
}

float VectorHelper::crossProduct(const GVector2 & a, const GVector2 & b)
{
	return (a.x * b.y - a.y * b.x);
}

float VectorHelper::dotProduct(const GVector2 & a, const GVector2 & b)
{
	return 1.0f * a.x * b.x + a.y * b.y;
}


float VectorHelper::getLength(const GVector2 & a)
{
	return sqrtf(a.x * a.x + a.y * a.y);
}

GVector2 VectorHelper::normalized(const GVector2 & a)
{
	float l = getLength(a);
	if (l != 0.f)
	{
		return GVector2(a.x / l, a.y / l);
	}
	return VECTOR2ZERO;
}

GVector2 VectorHelper::tangent(const GVector2 & a)
{
	return GVector2(-a.y, a.x);
}
