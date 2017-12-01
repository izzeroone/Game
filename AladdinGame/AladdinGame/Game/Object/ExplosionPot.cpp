#include "ExplosionPot.h"

void ExplosionPotAnimationComponent::init()
{
	_sprite = SpriteResource::getInstance()->getSprite(eObjectID::CIVILIAN);
	_sprite->setFrameRect(SpriteResource::getInstance()->getSourceRect(eObjectID::CIVILIAN, "pot_1"));
	_sprite->setZIndex(0.0f);

	setOrigin(GVector2(0.5f, 0.0f));
	setScale(SCALE_FACTOR);

	_animations[eStatus::NORMAL] = new Animation(_sprite, 0.07f);
	_animations[eStatus::NORMAL]->addFrameRect(eObjectID::CIVILIAN, "pot_1", "pot_2", "pot_3", "pot_4", "pot_5", "pot_6", "pot_7", NULL);

	_animations[eStatus::LANDING] = new Animation(_sprite, 0.07f);
	_animations[eStatus::LANDING]->addFrameRect(eObjectID::CIVILIAN, "pot_landing_1", "pot_landing_2", "pot_landing_3", "pot_landing_4", "pot_landing_5", "pot_landing_6", "pot_landing_7", NULL);

	_index = eStatus::NORMAL;
}

ExplosionPot::ExplosionPot()
{
}

ExplosionPot::~ExplosionPot()
{
}

void ExplosionPotBehaviorComponent::update(float deltatime)
{
	auto collisionComponent = (CollisionComponent*)_physicsComponent->getComponent("Collision");
	GameObject * object;

	object = collisionComponent->isColliding(eObjectID::LAND);

	if (object != nullptr)
	{
		setStatus(eStatus::LANDING);
		standing();
	}

	object = collisionComponent->isColliding(eObjectID::ALADDIN);

	if (object != nullptr && _status != eStatus::LANDING)
	{
		setStatus(eStatus::LANDING);
		standing();
		AladdinBehaviorComponent * encom = (AladdinBehaviorComponent *)object->getBehaviorComponent();
		encom->dropHitpoint(20);
	}

	//done landing, get destroyed
	if (_status == eStatus::LANDING && _animationComponent->getCurrentAnimation()->getCount() >= 1)
	{
		setStatus(eStatus::DESTROY);
	}
}

void ExplosionPotBehaviorComponent::updateAnimation()
{
	switch (_status)
	{
	case NORMAL:
		_animationComponent->setAnimation(eStatus::NORMAL);
		break;
	case LANDING:
		_animationComponent->setAnimation(eStatus::LANDING);
		break;
	}
}
