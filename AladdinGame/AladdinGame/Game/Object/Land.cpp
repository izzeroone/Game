#include "Land.h"

void Land::init(int x, int y, int width, int height, eDirection physicBodyDirection, eLandType type)
{
	GameObject::init();
	_id = eObjectID::LAND;
	// X là left. Y là top
	RECT bounding;
	bounding.top = y;
	bounding.left = x;
	bounding.bottom = y - height;
	bounding.right = x + width;
	_physicsComponent->setBounding(bounding);
	setLandType(type);
	_physicsComponent->setPhysicsBodySide(physicBodyDirection);
}

void Land::init()
{
	_id = eObjectID::LAND;
}

void Land::setLandType(eLandType landType)
{
	((LandBehaviorComponent *)_behaviorComponent)->setLandType(landType);
}

eLandType Land::getLandType()
{
	return ((LandBehaviorComponent *)_behaviorComponent)->getLandType();
}

void LandPhysiscsComponent::init()
{
	_componentList["Collision"] = new CollisionComponent();
}

void LandBehaviorComponent::setLandType(eLandType type)
{
	_landType = type;
}

eLandType LandBehaviorComponent::getLandType()
{
	return _landType;
}

void LandBehaviorComponent::updateFlameLand(float deltatime)
{
	_timer += deltatime;
	if (_timer >= FLAME_INTEVAL)
		_timer -= FLAME_INTEVAL;
	else
		return;
	auto collisionComponent = (CollisionComponent*)_physicsComponent->getComponent("Collision");

	GameObject * aladdin = collisionComponent->isColliding(eObjectID::ALADDIN);
	if (aladdin == nullptr)
	{
		return;
	}

	
	RECT bound = _physicsComponent->getBounding();
	_width = bound.right - bound.left;
	GVector2 pos = _physicsComponent->getPosition() + GVector2(_width / FLAME_PER_LAND * (_index + 0.5f), 0);

	addToScene.Emit(ObjectFactory::getFlame(pos));

	GVector2 aladdinPos = aladdin->getPhysicsComponent()->getPosition();
	if (aladdinPos.x > pos.x)
	{
		setIndex(_index + 1);
	}
	else
	{
		setIndex(_index - 1);
	}

}

void LandBehaviorComponent::updateFallingLand(float deltatime)
{
}

void LandBehaviorComponent::setIndex(int index)
{
	_index = index;
	if (_index >= FLAME_PER_LAND)
		_index = FLAME_PER_LAND - 1;
	else if (_index < 0)
		_index = 0;

}

void LandBehaviorComponent::init()
{
	_index = 0;
}

void LandBehaviorComponent::update(float deltatime)
{
	switch (_landType)
	{
	case lNORMAL:
		break;
	case lFLAME:
		updateFlameLand(deltatime);
		break;
	case lFALLING:
		break;
	default:
		break;
	}
}
