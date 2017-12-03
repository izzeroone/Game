#include "Dagger.h"



Dagger::Dagger()
{
}


Dagger::~Dagger()
{
}

void DaggerPhysicsComponent::init()
{
	auto movement = new Movement(GVector2(0, 0), GVector2(0, 0), this);
	_componentList["Movement"] = movement;
	_componentList["Gravity"] = new Gravity(GVector2(0, -DAGGER_GRAVITY), movement);
	_componentList["Collision"] = new CollisionComponent(eDirection::ALL);
}

GVector2 DaggerPhysicsComponent::getVelocity()
{
	auto move = (Movement*)getComponent("Movement");
	return move->getVelocity();
}

void DaggerPhysicsComponent::setAnimationComponent(AnimationComponent * animationComponent)
{
	_animationComponent = animationComponent;
}

RECT DaggerPhysicsComponent::getBounding()
{
	return _animationComponent->getBounding();
}

void DaggerAnimationComponent::init()
{
	_sprite = SpriteResource::getInstance()->getSprite(eObjectID::GUARD);
	_sprite->setFrameRect(SpriteResource::getInstance()->getSourceRect(eObjectID::GUARD, "dagger_1"));
	_sprite->setZIndex(0.0f);

	setOrigin(GVector2(0.5f, 0.5f));
	setScale(SCALE_FACTOR);

	_animations[eStatus::NORMAL] = new Animation(_sprite, 0.07f);
	_animations[eStatus::NORMAL]->addFrameRect(eObjectID::GUARD, "dagger_1", "dagger_2", "dagger_3", "dagger_4", "dagger_5", "dagger_6", "dagger_7", NULL);

	for (auto animate : _animations)
	{
		animate.second->setColorFlash(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
}

void DaggerBehaviorComponent::init()
{
	setStatus(eStatus::NORMAL);
	_animationComponent->setAnimation(eStatus::NORMAL);
}

void DaggerBehaviorComponent::update(float detatime)
{

	auto collisionComponent = (CollisionComponent*)_physicsComponent->getComponent("Collision");
	GameObject * object;
	
	object = collisionComponent->isColliding(eObjectID::LAND);
	
	if (object != nullptr)
	{
		setStatus(eStatus::DESTROY);
	}

	object = collisionComponent->isColliding(eObjectID::ALADDIN);

	if (object != nullptr && _status != eStatus::LANDING)
	{
		PlayerBehaviorComponent * encom = (PlayerBehaviorComponent *)object->getBehaviorComponent();
		encom->dropHitpoint(20);
		setStatus(eStatus::DESTROY);
	}
}

void DaggerBehaviorComponent::setStatus(eStatus status)
{
	BehaviorComponent::setStatus(status);
	updateAnimation();
}


void DaggerBehaviorComponent::updateAnimation()
{
	switch (_status)
	{
	case NORMAL:
		_animationComponent->getCurrentAnimation()->canAnimate(true);
		break;
	}
}

void DaggerBehaviorComponent::standing()
{
	auto move = (Movement*)_physicsComponent->getComponent("Movement");
	move->setVelocity(GVector2(0, 0));

	auto gravity = (Gravity*)_physicsComponent->getComponent("Gravity");
	gravity->setStatus(eGravityStatus::LANDED);

}
