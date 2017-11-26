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
	_animationComponent->setAnimation(eStatus::NORMAL);
	auto collisionComponent = (CollisionComponent*)_physicsComponent->getComponent("Collision");

	if (getStatus() == eStatus::FALLING)
	{
		_timer += deltatime;
		if (_timer >= FALLING_DESTROYED_TIME)
			setStatus(eStatus::DESTROY);
	}

	GameObject * aladdin = collisionComponent->isColliding(eObjectID::ALADDIN);
	if (aladdin == nullptr)
	{
		return;
	}

	auto g = (Gravity*)this->_physicsComponent->getComponent("Gravity");
	g->setStatus(eGravityStatus::FALLING__DOWN);

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
	_timer = 0;
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

void FallingLandAnimationComponent::draw(LPD3DXSPRITE spriteHander, Viewport * viewport)
{
	OutputDebugStringW(L"Position");
	__debugoutput(_physicsComponent->getPositionX());
	__debugoutput(_physicsComponent->getPositionY());
	AnimationComponent::draw(spriteHander, viewport);
}
