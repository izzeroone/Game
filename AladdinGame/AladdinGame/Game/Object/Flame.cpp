#include "Flame.h"

void FlamePhysicsComponent::init()
{
	_componentList["Collision"] = new CollisionComponent();
}

void FlamePhysicsComponent::setAnimationComponent(AnimationComponent * animationComponent)
{
	_animationComponent = animationComponent;
}

RECT FlamePhysicsComponent::getBounding()
{
	return _animationComponent->getBounding();
}

void FlameAnimationComponent::init()
{
	_sprite = SpriteResource::getInstance()->getSprite(eObjectID::FLAME);
	_sprite->setFrameRect(SpriteResource::getInstance()->getSourceRect(eObjectID::FLAME, "flame_01"));
	_sprite->setZIndex(0.0f);

	setOrigin(GVector2(0.5f, 0.0f));
	setScale(SCALE_FACTOR);

	_animations[eStatus::NORMAL] = new Animation(_sprite, 0.07f);
	_animations[eStatus::NORMAL]->addFrameRect(eObjectID::FLAME, "flame_01", "flame_02", "flame_03", "flame_04", "flame_05", "flame_06", "flame_07", "flame_08", NULL);

	for (auto animate : _animations)
	{
		animate.second->setColorFlash(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
}

void FlameBehaviorComponent::init()
{
	_animationComponent->setAnimation(eStatus::NORMAL);
	setStatus(eStatus::NORMAL);
}

void FlameBehaviorComponent::update(float deltatime)
{
	if (_animationComponent->getCurrentAnimation()->getCount() >= 1)
	{
		setStatus(eStatus::DESTROY);
		return;
	}
	auto collisionComponent = (CollisionComponent*)_physicsComponent->getComponent("Collision");

	GameObject * obj = collisionComponent->isColliding(eObjectID::ALADDIN);
	if (obj != nullptr)
	{
		((PlayerBehaviorComponent*)obj->getBehaviorComponent())->dropHitpoint(10);
	}
}
