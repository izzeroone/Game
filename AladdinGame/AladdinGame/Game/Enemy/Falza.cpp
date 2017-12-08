#include "Falza.h"


void FalzaPhysicsComponent::init()
{
	_movingSpeed = 50;
	auto movement = new Movement(GVector2(10, 0), GVector2(0, 0), this);
	_componentList["Movement"] = movement;
}

GVector2 FalzaPhysicsComponent::getVelocity()
{
	auto move = (Movement*)getComponent("Movement");
	return move->getVelocity();
}


RECT FalzaPhysicsComponent::getBounding()
{
	return _obj->getAnimationComponent()->getBounding();
}

void FalzaAnimationComponent::init()
{
	_sprite = SpriteResource::getInstance()->getSprite(eObjectID::GUARD);
	_sprite->setFrameRect(SpriteResource::getInstance()->getSourceRect(eObjectID::GUARD, "falza_boring_7"));
	_sprite->setZIndex(0.0f);

	setOrigin(GVector2(0.0f, 0.0f));
	setScale(SCALE_FACTOR);

	_animations[eStatus::NORMAL] = new Animation(_sprite, 0.07f);
	_animations[eStatus::NORMAL]->addFrameRect(eObjectID::GUARD, "falza_boring_7", "falza_boring_6", "falza_boring_5", "falza_boring_4","falza_boring_3", "falza_boring_2", "falza_boring_1", NULL);

	_animations[eStatus::RUNNING] = new Animation(_sprite, 0.07f);
	_animations[eStatus::RUNNING]->addFrameRect(eObjectID::GUARD, "falza_running_8", "falza_running_7", "falza_running_6", "falza_running_5", "falza_running_4", "falza_running_3", "falza_running_2", "falza_running_1", NULL);

	_animations[eStatus::THROW] = new Animation(_sprite, 0.07f);
	_animations[eStatus::THROW]->addFrameRect(eObjectID::GUARD, "falza_throw_5", "falza_throw_4", "falza_throw_3", "falza_throw_2", "falza_throw_1", NULL);

	_animations[eStatus::BEATEN] = new Animation(_sprite, 0.07f);
	_animations[eStatus::BEATEN]->addFrameRect(eObjectID::GUARD, "falza_beaten_7", "falza_beaten_6", "falza_beaten_5", "falza_beaten_4", "falza_beaten_3", "falza_beaten_2", "falza_beaten_1", NULL);

	for (auto animate : _animations)
	{
		animate.second->setColorFlash(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
}

void FalzaBehaviorComponent::init()
{
	setStatus(eStatus::NORMAL);
	_hitpoint = 100;
	_throwTime = 0;
	_standTime = 0;
	_collisionComponent = new CollisionComponent(eDirection::ALL);
	_collisionComponent->setTargerGameObject(_obj);
}

void FalzaBehaviorComponent::update(float detatime)
{
	if (_hitpoint <= 0)
	{
		setStatus(eStatus::DESTROY);
		return;
	}

	_standTime -= detatime;
	if (_standTime > 0)
	{
		setStatus(eStatus::NORMAL);
		standing();
		return;
	}

	auto aladdin = SceneManager::getInstance()->getCurrentScene()->getObject(eObjectID::ALADDIN);
	auto aladdinPos = aladdin->getPhysicsComponent()->getPosition();

	float diffirent = _obj->getPhysicsComponent()->getPosition().x - aladdinPos.x;
	RECT bound = _obj->getPhysicsComponent()->getBounding();
	float width = bound.right - bound.left;

	if (diffirent > width && _obj->getPhysicsComponent()->getPositionX() >= _rangeXStart) // aladdin ở bến trái
	{
		setStatus(eStatus::RUNNING);
		moveLeft();
	}
	else if (diffirent < -width && _obj->getPhysicsComponent()->getPositionX() <= _rangeXEnd)
	{
		setStatus(eStatus::RUNNING);
		moveRight();
	}
	else
	{
		standing();
		setStatus(eStatus::NORMAL);
		throwApple();
	}


	if (_obj->getAnimationComponent()->isTempAnimationEmpty() == true)
	{
		setWeapon(eStatus::NORMAL);
	}

}

void FalzaBehaviorComponent::setStatus(eStatus status)
{
	BehaviorComponent::setStatus(status);
	updateAnimation();
}

void FalzaBehaviorComponent::dropHitpoint(int damage)
{
	EnemyBehaviorComponent::dropHitpoint(damage);
	_obj->getAnimationComponent()->setTempAnimation(eStatus::BEATEN, 1);
	_standTime = STAND_TIME;
}

void FalzaBehaviorComponent::updateAnimation()
{
	switch (_status)
	{
	case NORMAL:
		_obj->getAnimationComponent()->setAnimation(eStatus::NORMAL);
		break;
	case RUNNING:
		_obj->getAnimationComponent()->setAnimation(eStatus::RUNNING);
		break;
	default:
		break;
	}
}


void FalzaBehaviorComponent::faceLeft()
{
	if (_obj->getAnimationComponent()->getScale().x > 0)
	{
		_obj->getAnimationComponent()->setScaleX(_obj->getAnimationComponent()->getScale().x * (-1));

		RECT bound = _obj->getPhysicsComponent()->getBounding();
		float width = bound.right - bound.left;
		_obj->getAnimationComponent()->setTranslateX(width);
	}
	setFacingDirection(eStatus::LEFTFACING);
}

void FalzaBehaviorComponent::faceRight()
{
	if (_obj->getAnimationComponent()->getScale().x < 0)
	{
		_obj->getAnimationComponent()->setScaleX(_obj->getAnimationComponent()->getScale().x * (-1));

		_obj->getAnimationComponent()->setTranslateX(0);
	}
	setFacingDirection(eStatus::RIGHTFACING);
}

void FalzaBehaviorComponent::standing()
{
	auto move = (Movement*)_obj->getPhysicsComponent()->getComponent("Movement");
	move->setVelocity(GVector2(0, 0));
}

void FalzaBehaviorComponent::moveLeft()
{
	faceLeft();
	auto move = (Movement*)_obj->getPhysicsComponent()->getComponent("Movement");
	move->setVelocity(GVector2(-_obj->getPhysicsComponent()->getMovingSpeed(), move->getVelocity().y));
	setFacingDirection(eStatus::LEFTFACING);
}

void FalzaBehaviorComponent::moveRight()
{
	faceRight();
	auto move = (Movement*)_obj->getPhysicsComponent()->getComponent("Movement");
	move->setVelocity(GVector2(_obj->getPhysicsComponent()->getMovingSpeed(), move->getVelocity().y));
	setFacingDirection(eStatus::RIGHTFACING);
}

void FalzaBehaviorComponent::throwApple()
{
	if (_weapon == eStatus::THROW)
		return;

	setWeapon(eStatus::THROW);
	_obj->getAnimationComponent()->setTempAnimation(eStatus::THROW, 1);
	auto pos = _obj->getPhysicsComponent()->getPosition();
	pos.y += _obj->getAnimationComponent()->getSprite()->getFrameHeight() * 2 / 3;
	GVector2 velocity(-400, 100);
	if (_facingDirection == eStatus::RIGHTFACING)
	{
		pos += GVector2(_obj->getAnimationComponent()->getSprite()->getFrameWidth(), 0);
		velocity.x = -velocity.x;

	}
	auto apple = ObjectFactory::getDagger(pos, velocity);
	addToScene.Emit(apple);

}