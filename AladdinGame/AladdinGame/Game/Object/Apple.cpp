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
}

GVector2 ApplePhysicsComponent::getVelocity()
{
	auto move = (Movement*)getComponent("Movement");
	return move->getVelocity();
}



RECT ApplePhysicsComponent::getBounding()
{
	return _obj->getAnimationComponent()->getBounding();
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
	_obj->getAnimationComponent()->setAnimation(eStatus::NORMAL);
	_collisionComponent = new CollisionComponent(eDirection::ALL);
	_collisionComponent->setTargerGameObject(_obj);
}

void AppleBehaviorComponent::update(float detatime)
{
	GameObject * object;
	
	object = _collisionComponent->isColliding(eObjectID::LAND);
	
	if (object != nullptr)
	{
		setStatus(eStatus::LANDING);
		standing();
	}
	auto isEnemyFunc = [](GameObject* obj) {
		auto id = obj->getID();
		return id == eObjectID::HAKIM || id == eObjectID::NAHBI || id == eObjectID::FALZA;
	};
	object = _collisionComponent->isColliding(isEnemyFunc);

	if (object != nullptr && _status != eStatus::LANDING)
	{
		setStatus(eStatus::LANDING);
		standing();
		EnemyBehaviorComponent * encom = (EnemyBehaviorComponent *)object->getBehaviorComponent();
		encom->dropHitpoint(20);
	}

	//done animation, get destroyed
	if (_obj->getAnimationComponent()->getCurrentAnimation()->getCount() >= 1)
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
		_obj->getAnimationComponent()->getCurrentAnimation()->canAnimate(false);
		break;
	case LANDING:
		_obj->getAnimationComponent()->getCurrentAnimation()->canAnimate(true);
		break;
	default:
		_obj->getAnimationComponent()->getCurrentAnimation()->canAnimate(false);
		break;
	}
}

void AppleBehaviorComponent::standing()
{
	auto move = (Movement*)_obj->getPhysicsComponent()->getComponent("Movement");
	move->setVelocity(GVector2(0, 0));

	auto gravity = (Gravity*)_obj->getPhysicsComponent()->getComponent("Gravity");
	gravity->setStatus(eGravityStatus::LANDED);

}
//Kiểm tra xem va chạm vs aladdin ko
//object = collisionComponent->isColliding(isEnemyFunc);
//
//if (object != nullptr)
//{
//	switch(item_type)
//{
//	case LifeUP:
// tăng aladdin lên 1
// setStatus(destroy)
//}
//}
