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
	_animations[eStatus::NORMAL]->addFrameRect(eObjectID::CIVILIAN,"emply", "thrower_1", "thrower_2", "thrower_3", "thrower_4", "thrower_5", "thrower_6", "thrower_7", "thrower_8", "thrower_9", "thrower_10", NULL);

	_index = eStatus::NORMAL;
}

void ThrowerBehaviorComponent::init()
{
	_timer = 0;
	_toThrow = false;
}

void ThrowerBehaviorComponent::update(float detatime)
{
	//Nếu aladdin ở gần thì ném, ko thì reset lại
	//Xét thời gian chạy cần đủ 1 vòng thì mới ném, ko thì thôi
	auto aladdin = SceneManager::getInstance()->getCurrentScene()->getObject(eObjectID::ALADDIN);
	auto aladdinPos = aladdin->getPhysicsComponent()->getPosition();

	if (_toThrow == true)
	{
		if (_animationComponent->getCurrentAnimation()->getCount() >= 1)
		{
			throwPot();
			_animationComponent->getCurrentAnimation()->restart();
			_animationComponent->getCurrentAnimation()->canAnimate(false);
			_toThrow = false;
		}
	}
	//aladdin ở gần
	if (abs(aladdinPos.x - _physicsComponent->getPositionX()) <= 50 * SCALE_FACTOR)
	{
		_timer += detatime;
		if (_timer >= THROW_INTERVAL)
		{
			_timer -= THROW_INTERVAL;
		}
		else
			return;
		_toThrow = true;
		_animationComponent->setAnimation(eStatus::NORMAL);
		_animationComponent->getCurrentAnimation()->canAnimate(true);
	}
	else
	{
		if (_toThrow == false)
		{
			_timer = 0;
			_animationComponent->getCurrentAnimation()->canAnimate(false);
		}
	}
}


void ThrowerBehaviorComponent::throwPot()
{
	GVector2 pos = _physicsComponent->getPosition();
	pos.x += 15 * SCALE_FACTOR; // code cứng
	pos.y -= 5 * SCALE_FACTOR;
	auto explosionPot = ObjectFactory::getExlplosionPot(pos);
	addToScene.Emit(explosionPot);
}
