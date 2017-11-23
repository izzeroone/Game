#pragma once
#include "define.h"
#include <cmath>
class VectorHelper
{
public:
	VectorHelper();
	~VectorHelper();
	static float crossProduct(const GVector2 &a, const GVector2 &b);
	static float dotProduct(const GVector2 &a, const GVector2 &b);
	static float getLength(const GVector2 &a);
	static GVector2 normalized(const GVector2 &a);
	static GVector2 tangent(const GVector2 &a);

};

