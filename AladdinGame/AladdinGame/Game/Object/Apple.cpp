#include "Apple.h"



Apple::Apple()
{
}


Apple::~Apple()
{
}

void ApplePhysicsComponent::init()
{
	auto movement = new Movement(GVector2(0, 0), GVector2(0, 0), this);
	_componentList["Movement"] = movement;
	_componentList["Gravity"] = new Gravity(GVector2(0, -GRAVITY), movement);
	_componentList["Collision"] = new CollisionComponent();
	setPhysicsBodySide(eDirection::ALL);
}

GVector2 ApplePhysicsComponent::getVelocity()
{
	auto move = (Movement*)getComponent("Movement");
	return move->getVelocity();
}

void ApplePhysicsComponent::setAnimationComponent(AnimationComponent * animationComponent)
{
	_animationComponent = animationComponent;
}

RECT ApplePhysicsComponent::getBounding()
{
	return _animationComponent->getBounding();
}

void AppleAnimationComponent::init()
{
	_sprite = SpriteResource::getInstance()->getSprite(eObjectID::ALADDIN);
	_sprite->setFrameRect(SpriteResource::getInstance()->getSourceRect(eObjectID::ALADDIN, "normal_01"));
	_sprite->setZIndex(0.0f);

	setOrigin(GVector2(0.5f, 0.5f));
	setScale(SCALE_FACTOR);

	_animations[eStatus::NORMAL] = new Animation(_sprite, 0.07f);
	_animations[eStatus::NORMAL]->addFrameRect(eObjectID::ALADDIN, "apple_01", "apple_02", "apple_03", "apple_04", "apple_05", "apple_06", NULL);

	for (auto animate : _animations)
	{
		animate.second->setColorFlash(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
}

void AppleBehaviorComponent::init()
{
	setStatus(eStatus::NORMAL);
	_animationComponent->setAnimation(eStatus::NORMAL);
}

void AppleBehaviorComponent::update(float detatime)
{

	auto collisionComponent = (CollisionComponent*)_physicsComponent->getComponent("Collision");
	GameObject * object;
	
	object = collisionComponent->isColliding(eObjectID::LAND);
	
	if (object != nullptr)
	{
		setStatus(eStatus::LANDING);
		standing();
	}

	object = collisionComponent->isColliding(eObjectID::HAKIM);

	if (object != nullptr && _status != eStatus::LANDING)
	{
		setStatus(eStatus::LANDING);
		standing();
		EnemyBehaviorComponent * encom = (EnemyBehaviorComponent *)object->getBehaviorComponent();
		encom->dropHitpoint(20);
	}

	//done animation, get destroyed
	if (_animationComponent->getCurrentAnimation()->getCount() >= 1)
	{
		setStatus(eStatus::DESTROY);
	}
}

void AppleBehaviorComponent::setStatus(eStatus status)
{
	BehaviorComponent::setStatus(status);
	updateAnimation();
}


void AppleBehaviorComponent::updateAnimation()
{
	switch (_status)
	{
	case NORMAL:
		_animationComponent->getCurrentAnimation()->canAnimate(false);
		break;
	case LANDING:
		_animationComponent->getCurrentAnimation()->canAnimate(true);
		break;
	default:
		_animationComponent->getCurrentAnimation()->canAnimate(false);
		break;
	}
}

void AppleBehaviorComponent::standing()
{
	auto move = (Movement*)_physicsComponent->getComponent("Movement");
	move->setVelocity(GVector2(0, 0));

	auto gravity = (Gravity*)_physicsComponent->getComponent("Gravity");
	gravity->setStatus(eGravityStatus::LANDED);

}
