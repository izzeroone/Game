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
	checkCollision(deltatime);

	//done landing, get destroyed
	if (_status == eStatus::LANDING && _obj->getAnimationComponent()->getCurrentAnimation()->getCount() >= 1)
	{
		setStatus(eStatus::DESTROY);
	}
}

void ExplosionPotBehaviorComponent::checkCollision(float deltatime)
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
				setStatus(eStatus::LANDING);
				standing();
			}
			break;
		case ALADDIN:
			if (_collisionComponent->checkCollision(obj, deltatime, false))
			{
				if (_status != eStatus::LANDING)
				{
					setStatus(eStatus::LANDING);
					standing();
					PlayerBehaviorComponent * encom = (PlayerBehaviorComponent *)obj->getBehaviorComponent();
					encom->dropHitpoint(20);
				}
			}

			break;
		default:
			break;
		}
	}
}

void ExplosionPotBehaviorComponent::updateAnimation()
{
	switch (_status)
	{
	case NORMAL:
		_obj->getAnimationComponent()->setAnimation(eStatus::NORMAL);
		break;
	case LANDING:
		_obj->getAnimationComponent()->setAnimation(eStatus::LANDING);
		break;
	}
}
