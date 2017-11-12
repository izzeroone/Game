#include "Land.h"

void Land::init(int x, int y, int width, int height, eDirection physicBodyDirection, eLandType type)
{
	_id = eObjectID::LAND;
	// X là left. Y là top
	RECT bounding;
	bounding.top = y;
	bounding.left = x;
	bounding.bottom = y - height;
	bounding.right = x + width;
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
