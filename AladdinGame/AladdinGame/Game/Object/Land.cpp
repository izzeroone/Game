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
	_physicsComponent->setPosition(GVector2(x, y));
	setLandType(type);
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
	if (_timer != 0)
	{
		_timer += deltatime;
		if (_timer >= FLAME_INTEVAL)
		{
			addToScene.Emit(ObjectFactory::getFlame(_flamePos));
			_timer = 0;
		}
		else
		{
			return;
		}
	}
	auto collisionComponent = (CollisionComponent*)_physicsComponent->getComponent("Collision");

	GameObject * aladdin = collisionComponent->isColliding(eObjectID::ALADDIN);

	if (aladdin != nullptr && _timer == 0)
	{
		RECT landBound = _physicsComponent->getBounding();
		_width = landBound.right - landBound.left;
		float landX = _physicsComponent->getPositionX();
		RECT aladdinBound = aladdin->getPhysicsComponent()->getBounding();
		float aladdinPosX = aladdin->getPhysicsComponent()->getPositionX();
		float width = (aladdinBound.right - aladdinBound.left);
		if (aladdinPosX + width / 2 > landX && aladdinPosX  < landX + _width)
		{
			_timer += deltatime;
			_flamePos = GVector2(aladdinPosX + width / 2, _physicsComponent->getPositionY());
		}
	}
}

void LandBehaviorComponent::updateFallingLand(float deltatime)
{
	_animationComponent->setAnimation(eStatus::NORMAL);
	auto collisionComponent = (CollisionComponent*)_physicsComponent->getComponent("Collision");

	if (getStatus() == eStatus::FALLING)
	{
		_timer += deltatime;
		if (_timer >= FALLING_DESTROYED_TIME)
		{
			setStatus(eStatus::DESTROY);
			return;
		}
	}

	if (_holdTimer != 0)
	{
		_holdTimer += deltatime;
		if (_holdTimer >= FALLING_LAND_HOLD_TIME)
		{
			setStatus(eStatus::FALLING);
			auto g = (Gravity*)this->_physicsComponent->getComponent("Gravity");
			g->setStatus(eGravityStatus::FALLING__DOWN);
		}
	}

	GameObject * aladdin = collisionComponent->isColliding(eObjectID::ALADDIN);
	if (aladdin != nullptr && _holdTimer == 0)
	{
		_holdTimer += deltatime;
	}


}


void LandBehaviorComponent::init()
{
	_timer = 0;
	_holdTimer = 0;
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
		updateFallingLand(deltatime);
		break;
	default:
		break;
	}
}

void FallingLandPhysiscsComponent::init()
{
	LandPhysiscsComponent::init();
	auto movement = new Movement(GVector2(0, 0), GVector2(0, 0), this);
	_componentList["Movement"] = movement;
	auto gravity = new Gravity(GVector2(0, -GRAVITY), movement);
	gravity->setStatus(eGravityStatus::LANDED);
	_componentList["Gravity"] = gravity;

}

void FallingLandAnimationComponent::init()
{
	_sprite = SpriteResource::getInstance()->getSprite(eObjectID::MAP1);
	_sprite->setFrameRect(SpriteResource::getInstance()->getSourceRect(eObjectID::MAP1, "falling_land"));
	_sprite->setZIndex(0.0f);

	setOrigin(GVector2(0.0f, 0.0f));
	setScale(SCALE_FACTOR);

	_animations[eStatus::NORMAL] = new Animation(_sprite, 100.f);
	_animations[eStatus::NORMAL]->addFrameRect(eObjectID::MAP1, "falling_land", NULL);

	_index = eStatus::NORMAL;

	for (auto animate : _animations)
	{
		animate.second->setColorFlash(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}


}

