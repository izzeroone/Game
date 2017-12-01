#include "Thrower.h"

void ThrowerPhysicsComponent::init()
{

}

void ThrowerAnimationComponent::init()
{
	_sprite = SpriteResource::getInstance()->getSprite(eObjectID::CIVILIAN);
	_sprite->setFrameRect(SpriteResource::getInstance()->getSourceRect(eObjectID::CIVILIAN, "pot_1"));
	_sprite->setZIndex(0.0f);

	setOrigin(GVector2(0.0f, 0.0f));
	setScale(SCALE_FACTOR);

	_animations[eStatus::NORMAL] = new Animation(_sprite, 0.07f);
	_animations[eStatus::NORMAL]->addFrameRect(eObjectID::CIVILIAN, "pot_1", "pot_2", "pot_3", "pot_4", "pot_5", "pot_6", "pot_7", NULL);

	_index = eStatus::NORMAL;
}

void ThrowerBehaviorComponent::init()
{
	_timer = 0;
}

void ThrowerBehaviorComponent::update(float detatime)
{
	//Nếu aladdin ở gần thì ném, ko thì reset lại
	//Xét thời gian chạy cần đủ 1 vòng thì mới ném, ko thì thôi
	auto aladdin = SceneManager::getInstance()->getCurrentScene()->getObject(eObjectID::ALADDIN);
	auto aladdinPos = aladdin->getPhysicsComponent()->getPosition();

	//aladdin ở gần
	if (abs(aladdinPos.y - _physicsComponent->getPositionY()) <= 50 * SCALE_FACTOR)
	{
		_timer += detatime;
		if (_timer >= THROW_INTERVAL)
		{
			_timer -= THROW_INTERVAL;
		}
		else
			return;
		throwPot();
	}
	else
	{
		_timer = 0;
	}
}


void ThrowerBehaviorComponent::throwPot()
{
	GVector2 pos = _physicsComponent->getPosition();
	pos.x += 10 * SCALE_FACTOR; // code cứng
	pos.y -= 5 * SCALE_FACTOR;
	auto explosionPot = ObjectFactory::getApple(pos, GVector2(0, 0));
	addToScene.Emit(explosionPot);
}
