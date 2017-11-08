#include "Viewport.h"



Viewport::Viewport()
{
}

Viewport::Viewport(float x, float y)
{
	_positionWorld.x = x;
	_positionWorld.y = y;
}

Viewport::Viewport(float x, float y, float width, float height)
{
	_positionWorld.x = x;
	_positionWorld.y = y;
	_width = width;
	_height = height;
}

void Viewport::setPositionWorld(GVector2 position)
{
	_positionWorld = position;
}

GVector2 Viewport::getPositionWorld()
{
	return _positionWorld;
}

float Viewport::getWidth()
{
	return _width;
}

float Viewport::getHeight()
{
	return _height;
}

GVector3 Viewport::getPositionInViewport(GVector3 * position)
{
	D3DXMATRIX mt; // ma tran 4x4
	D3DXVECTOR4 posViewport; // vector 4d
	
	D3DXMatrixIdentity(&mt); // tao ma tran don vi
	mt._22 = -1.0f;
	mt._41 = (-1) * _positionWorld.x;
	mt._42 = _positionWorld.y;

	D3DXVec3Transform(&posViewport, position, &mt);
	return GVector3(posViewport.x, posViewport.y, posViewport.z);
}

bool Viewport::isContain(RECT rect)
{
	if (rect.right < _positionWorld.x || rect.bottom > _positionWorld.y || rect.left > _positionWorld.x + _width || rect.top < _positionWorld.y - _height)
		return false;
	return true;
}

RECT Viewport::getBounding()
{
	RECT rect;

	rect.left = _positionWorld.x;
	rect.top = _positionWorld.y;
	rect.bottom = rect.top - _height;
	rect.right = rect.left + _width;

	return rect;
}




Viewport::~Viewport()
{
}
