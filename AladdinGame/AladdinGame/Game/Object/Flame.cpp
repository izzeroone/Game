#include "Flame.h"

void FlamePhysicsComponent::init()
{

}


RECT FlamePhysicsComponent::getBounding()
{
	return _obj->getAnimationComponent()->getBounding();
}

void FlameAnimationComponent::init()
{
	_sprite = SpriteResource::getInstance()->getSprite(eObjectID::JAFAR);
	_sprite->setFrameRect(SpriteResource::getInstance()->getSourceRect(eObjectID::JAFAR, "flame_1"));
	_sprite->setZIndex(0.0f);

	setOrigin(GVector2(0.5f, 0.0f));
	setScale(SCALE_FACTOR);

	_animations[eStatus::NORMAL] = new Animation(_sprite, 0.07f);
	_animations[eStatus::NORMAL]->addFrameRect(eObjectID::JAFAR, "flame_1", "flame_2", "flame_3", "flame_4", "flame_5", NULL);

	for (auto animate : _animations)
	{
		animate.second->setColorFlash(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
}

void FlameBehaviorComponent::init()
{
	_obj->getAnimationComponent()->setAnimation(eStatus::NORMAL);
	setStatus(eStatus::NORMAL);
	_collisionComponent = new CollisionComponent(eDirection::ALL);
	_collisionComponent->setTargerGameObject(_obj);
}

void FlameBehaviorComponent::update(float deltatime)
{
	if (_obj->getAnimationComponent()->getCurrentAnimation()->getCount() >= 1)
	{
		setStatus(eStatus::DESTROY);
		return;
	}

	GameObject * obj = _collisionComponent->isColliding(eObjectID::ALADDIN);
	if (obj != nullptr)
	{
		((PlayerBehaviorComponent*)obj->getBehaviorComponent())->dropHitpoint(10);
	}
}
