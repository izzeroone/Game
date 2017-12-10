#include "Camel.h"

void CamelPhysicsComponent::init()
{

}


RECT CamelPhysicsComponent::getBounding()
{
	return _obj->getAnimationComponent()->getBounding();
}

void CamelAnimationComponent::init()
{
	_sprite = SpriteResource::getInstance()->getSprite(eObjectID::CAMEL);
	_sprite->setFrameRect(SpriteResource::getInstance()->getSourceRect(eObjectID::CAMEL, "camel_1"));
	_sprite->setZIndex(0.0f);

	setOrigin(GVector2(0.5f, 0.0f));
	setScale(SCALE_FACTOR);

	_animations[eStatus::NORMAL] = new Animation(_sprite, 0.07f);
	_animations[eStatus::NORMAL]->addFrameRect(eObjectID::CAMEL, "camel_1", "camel_2", "camel_3", "camel_4", "camel_5","camel_6","camel_7", NULL);

	for (auto animate : _animations)
	{
		animate.second->setColorFlash(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
}

void CamelBehaviorComponent::init()
{
	_obj->getAnimationComponent()->setAnimation(eStatus::NORMAL);
	setStatus(eStatus::NORMAL);
	_collisionComponent = new CollisionComponent(eDirection::ALL);
	_collisionComponent->setTargerGameObject(_obj);
}

void CamelBehaviorComponent::update(float deltatime)
{
	if (_obj->getAnimationComponent()->getCurrentAnimation()->getCount() >= 1)
	{
		setStatus(eStatus::DESTROY);
		return;
	}

	checkCollision(deltatime);
}

void CamelBehaviorComponent::puffApple()
{
	if (_weapon == eStatus::NORMAL)
		return;

	setWeapon(eStatus::NORMAL);
	_obj->getAnimationComponent()->setTempAnimation(eStatus::NORMAL, 1);
	auto pos = _obj->getPhysicsComponent()->getPosition();
	pos.y += _obj->getAnimationComponent()->getSprite()->getFrameHeight() * 2 / 3;
	GVector2 velocity(-600, 50);
	if (_facingDirection == eStatus::RIGHTFACING)
	{
		pos += GVector2(_obj->getAnimationComponent()->getSprite()->getFrameWidth(), 0);
		velocity.x = -velocity.x;

	}
	auto apple = ObjectFactory::getDagger(pos, velocity);
	addToScene.Emit(apple);

}

void CamelBehaviorComponent::checkCollision(float deltatime)
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
				puffApple();
			}
			break;
		}
	}
}