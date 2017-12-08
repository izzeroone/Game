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
}

GVector2 DaggerPhysicsComponent::getVelocity()
{
	auto move = (Movement*)getComponent("Movement");
	return move->getVelocity();
}


RECT DaggerPhysicsComponent::getBounding()
{
	return _obj->getAnimationComponent()->getBounding();
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
	_obj->getAnimationComponent()->setAnimation(eStatus::NORMAL);
	_collisionComponent = new CollisionComponent(eDirection::ALL);
	_collisionComponent->setTargerGameObject(_obj);
}

void DaggerBehaviorComponent::update(float detatime)
{
	checkCollision(detatime);
}

void DaggerBehaviorComponent::setStatus(eStatus status)
{
	BehaviorComponent::setStatus(status);
	updateAnimation();
}

void DaggerBehaviorComponent::checkCollision(float deltatime)
{
	auto active_object = SceneManager::getInstance()->getCurrentScene()->getActiveObject();
	_collisionComponent->reset();
	for (auto obj : active_object)
	{
		eObjectID id = obj->getID();
		switch (id)
		{
		case LAND:
			if (_collisionComponent->checkCollision(obj, deltatime, true))
			{
				setStatus(eStatus::DESTROY);
			}
			break;
		case ALADDIN:
			if (_collisionComponent->checkCollision(obj, deltatime, false))
			{
				PlayerBehaviorComponent * encom = (PlayerBehaviorComponent *)obj->getBehaviorComponent();
				encom->dropHitpoint(20);
				setStatus(eStatus::DESTROY);
			}

			break;
		default:
			break;
		}
	}
}


void DaggerBehaviorComponent::updateAnimation()
{
	switch (_status)
	{
	case NORMAL:
		_obj->getAnimationComponent()->getCurrentAnimation()->canAnimate(true);
		break;
	}
}

void DaggerBehaviorComponent::standing()
{
	auto move = (Movement*)_obj->getPhysicsComponent()->getComponent("Movement");
	move->setVelocity(GVector2(0, 0));

	auto gravity = (Gravity*)_obj->getPhysicsComponent()->getComponent("Gravity");
	gravity->setStatus(eGravityStatus::LANDED);

}
