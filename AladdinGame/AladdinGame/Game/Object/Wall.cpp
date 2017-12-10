#include "Wall.h"

void Wall::init(int x, int y, int width, int height, eDirection physicBodyDirection)
{
	GameObject::init();
	_id = eObjectID::WALL;
	// X là left. Y là top
	RECT bounding;
	bounding.top = y;
	bounding.left = x;
	bounding.bottom = y - height;
	bounding.right = x + width;
	_physicsComponent->setBounding(bounding);
}

void Wall::init()
{
	_id = eObjectID::WALL;
}


void WallPhysiscsComponent::init()
{

}
