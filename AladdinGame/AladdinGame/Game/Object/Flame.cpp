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
	
	checkCollision(deltatime);
}

void FlameBehaviorComponent::checkCollision(float deltatime)
{
	auto active_object = SceneManager::getInstance()->getCurrentScene()->getActiveObject();
	_collisionComponent->reset();
	for (auto obj : active_object)
	{
		eObjectID id = obj->getID();
		switch (id)
		{
			case ALADDIN:
			if (_collisionComponent->checkCollision(obj, deltatime, false))
			{
				((PlayerBehaviorComponent*)obj->getBehaviorComponent())->dropHitpoint(10);
			}
			break;
		}
	}
}
