#include "Rope.h"

void Rope::init(int x, int y, int width, int height, eDirection physicBodyDirection, eRopeType type)
{
	GameObject::init();
	_id = eObjectID::ROPE;
	// X là left. Y là top
	RECT bounding;
	bounding.top = y;
	bounding.left = x;
	bounding.bottom = y - height;
	bounding.right = x + width;
	_physicsComponent->setBounding(bounding);
	_ropeType = type;
	_physicsComponent->setPhysicsBodySide(physicBodyDirection);
}

void Rope::init()
{
	_id = eObjectID::ROPE;
}

void Rope::setRopeType(eRopeType ropeType)
{
	_ropeType = ropeType;
}

eRopeType Rope::getRopeType()
{
	return _ropeType;
}


void RopePhysiscsComponent::init()
{
	_componentList["Collision"] = new CollisionComponent();
}
