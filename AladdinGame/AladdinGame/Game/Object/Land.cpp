#include "Land.h"

void Land::init(int x, int y, int width, int height, eDirection physicBodyDirection, eLandType type)
{
	GameObject::init();
	_id = eObjectID::LAND;
	// X l� left. Y l� top
	RECT bounding;
	bounding.top = y;
	bounding.left = x;
	bounding.bottom = y - height;
	bounding.right = x + width;
	_physicsComponent->setBounding(bounding);
	_landType = type;
	_physicsComponent->setPhysicsBodySide(physicBodyDirection);
}

void Land::init()
{
	_id = eObjectID::LAND;
}

void Land::setLandType(eLandType landType)
{
	_landType = landType;
}

eLandType Land::getLandType()
{
	return _landType;
}

void LandPhysiscsComponent::init()
{
	_componentList["Collision"] = new CollisionComponent();
}
