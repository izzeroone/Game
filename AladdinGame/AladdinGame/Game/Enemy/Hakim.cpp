#include "Hakim.h"


void HakimPhysicsComponent::init()
{
	_movingSpeed = 50;
	auto movement = new Movement(GVector2(10, 0), GVector2(0, 0), this);
	_componentList["Movement"] = movement;
}

GVector2 HakimPhysicsComponent::getVelocity()
{
	auto move = (Movement*)getComponent("Movement");
	return move->getVelocity();
}


RECT HakimPhysicsComponent::getBounding()
{
	return _obj->getAnimationComponent()->getBounding();
}

void HakimAnimationComponent::init()
{
	_sprite = SpriteResource::getInstance()->getSprite(eObjectID::GUARD);
	_sprite->setFrameRect(SpriteResource::getInstance()->getSourceRect(eObjectID::GUARD, "nakim_running_1"));
	_sprite->setZIndex(0.0f);

	setOrigin(GVector2(0.0f, 0.0f));
	setScale(SCALE_FACTOR);

	_animations[eStatus::NORMAL] = new Animation(_sprite, 0.07f);
	_animations[eStatus::NORMAL]->addFrameRect(eObjectID::GUARD, "nakim_running_1", NULL);;

	_animations[eStatus::RUNNING] = new Animation(_sprite, 0.07f);
	_animations[eStatus::RUNNING]->addFrameRect(eObjectID::GUARD,"nakim_running_1", "nakim_running_2", "nakim_running_3", "nakim_running_4", "nakim_running_5", "nakim_running_6", "nakim_running_7", "nakim_running_8", NULL);

	_animations[eStatus::SLASH] = new Animation(_sprite, 0.07f);
	_animations[eStatus::SLASH]->addFrameRect(eObjectID::GUARD, "nakim_slash_1", "nakim_slash_2", "nakim_slash_3", "nakim_slash_4", "nakim_slash_5", "nakim_slash_6", NULL);

	_animations[eStatus::BEATEN] = new Animation(_sprite, 0.07f);
	_animations[eStatus::BEATEN]->addFrameRect(eObjectID::GUARD, "nakim_beaten_1", "nakim_beaten_2", "nakim_beaten_3", "nakim_beaten_4", "nakim_beaten_5", "nakim_beaten_6", "nakim_beaten_7", "nakim_beaten_8", NULL);

	for (auto animate : _animations)
	{
		animate.second->setColorFlash(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
}

void HakimBehaviorComponent::init()
{
	setStatus(eStatus::NORMAL);
	_hitpoint = 100;
	_standTime = 0;
	_collisionComponent = new CollisionComponent(eDirection::ALL);
	_collisionComponent->setTargerGameObject(_obj);
}

void HakimBehaviorComponent::update(float detatime)
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
		slash();
	}


	if (_obj->getAnimationComponent()->isTempAnimationEmpty() == true)
	{
		setWeapon(eStatus::NORMAL);
	}

}

void HakimBehaviorComponent::setStatus(eStatus status)
{
	BehaviorComponent::setStatus(status);
	updateAnimation();
}

void HakimBehaviorComponent::dropHitpoint(int damage)
{
	EnemyBehaviorComponent::dropHitpoint(damage);
	_obj->getAnimationComponent()->setTempAnimation(eStatus::BEATEN, 1);
	_standTime = STAND_TIME;
}

void HakimBehaviorComponent::updateAnimation()
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


void HakimBehaviorComponent::faceLeft()
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

void HakimBehaviorComponent::faceRight()
{
	if (_obj->getAnimationComponent()->getScale().x < 0)
	{
		_obj->getAnimationComponent()->setScaleX(_obj->getAnimationComponent()->getScale().x * (-1));

		_obj->getAnimationComponent()->setTranslateX(0);
	}
	setFacingDirection(eStatus::RIGHTFACING);
}

void HakimBehaviorComponent::standing()
{
	auto move = (Movement*)_obj->getPhysicsComponent()->getComponent("Movement");
	move->setVelocity(GVector2(0, 0));
}

void HakimBehaviorComponent::moveLeft()
{
	faceLeft();
	auto move = (Movement*)_obj->getPhysicsComponent()->getComponent("Movement");
	move->setVelocity(GVector2(-_obj->getPhysicsComponent()->getMovingSpeed(), move->getVelocity().y));
	setFacingDirection(eStatus::LEFTFACING);
}

void HakimBehaviorComponent::moveRight()
{
	faceRight();
	auto move = (Movement*)_obj->getPhysicsComponent()->getComponent("Movement");
	move->setVelocity(GVector2(_obj->getPhysicsComponent()->getMovingSpeed(), move->getVelocity().y));
	setFacingDirection(eStatus::RIGHTFACING);
}

void HakimBehaviorComponent::slash()
{
	if (_weapon == eStatus::SLASH)
		return;

	setWeapon(eStatus::SLASH);
	_obj->getAnimationComponent()->setTempAnimation(eStatus::SLASH, 1);
	auto pos = _obj->getPhysicsComponent()->getPosition();
	pos.y += _obj->getAnimationComponent()->getSprite()->getFrameHeight();
	float width = _obj->getAnimationComponent()->getSprite()->getFrameWidth() * 4 / 3;
	float height = _obj->getAnimationComponent()->getSprite()->getFrameHeight();
	if (_facingDirection == eStatus::RIGHTFACING)
	{
		pos += GVector2(_obj->getAnimationComponent()->getSprite()->getFrameWidth(), 0);
	}
	else
	{
		pos -= GVector2(_obj->getAnimationComponent()->getSprite()->getFrameWidth(), 0);
	}
	auto sword = ObjectFactory::getSword(pos, width, height, false);
	addToScene.Emit(sword);

}
