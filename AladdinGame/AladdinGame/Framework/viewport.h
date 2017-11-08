#pragma once
#include "define.h"
//What to see in big game world :>
class Viewport
{
public:
	Viewport();
	Viewport(float x, float y);
	Viewport(float x, float y, float width, float height);
	~Viewport();
	
	void setPositionWorld(GVector2 position);
	GVector2 getPositionWorld();

	float getWidth();
	float getHeight();

	GVector3 getPositionInViewport(GVector3* position);
	bool isContain(RECT rect);
	/*
		Lay ve hinh chu nhat chua Viewport
	*/
	RECT getBounding();
private:
	GVector2 _positionWorld;
	float _width;
	float _height;
	
};

