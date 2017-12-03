#include "Nahbi.h"


void NahbiPhysicsComponent::init()
{
	_movingSpeed = 50;
	auto movement = new Movement(GVector2(10, 0), GVector2(0, 0), this);
	_componentList["Movement"] = movement;
	_componentList["Collision"] = new CollisionComponent();
}

GVector2 NahbiPhysicsComponent::getVelocity()
{
	auto move = (Movement*)getComponent("Movement");
	return move->getVelocity();
}

void NahbiPhysicsComponent::setAnimationComponent(AnimationComponent * animationComponent)
{
	_animationComponent = animationComponent;
}

RECT NahbiPhysicsComponent::getBounding()
{
	return _animationComponent->getBounding();
}

void NahbiAnimationComponent::init()
{
	_sprite = SpriteResource::getInstance()->getSprite(eObjectID::GUARD);
	_sprite->setFrameRect(SpriteResource::getInstance()->getSourceRect(eObjectID::GUARD, "nahbi_running_8"));
	_sprite->setZIndex(0.0f);

	setOrigin(GVector2(0.0f, 0.0f));
	setScale(SCALE_FACTOR);

	//_animations[eStatus::NORMAL] = new Animation(_sprite, 0.07f);
	//_animations[eStatus::NORMAL]->addFrameRect(eObjectID::GUARD, "nahbi_running_8", NULL);

	_animations[eStatus::RUNNING] = new Animation(_sprite, 0.07f);
	_animations[eStatus::RUNNING]->addFrameRect(eObjectID::GUARD, "nahbi_running_8", "nahbi_running_7", "nahbi_running_6", "nahbi_running_5", "nahbi_running_4", "nahbi_running_3", "nahbi_running_2", "nakim_running_1", NULL);

	_animations[eStatus::TAUGHT] = new Animation(_sprite, 0.07f);
	_animations[eStatus::TAUGHT]->addFrameRect(eObjectID::GUARD, "nahbi_taught_6", "nahbi_taught_5", "nahbi_taught_4", "nahbi_taught_3", "nahbi_taught_2", "nahbi_taught_1", NULL);

	_animations[eStatus::SLASH1] = new Animation(_sprite, 0.07f); 
	_animations[eStatus::SLASH1]->addFrameRect(eObjectID::GUARD, "nahbi_slash1_6", "nahbi_slash1_5", "nahbi_slash1_4", "nahbi_slash1_3", "nahbi_slash1_2", "nahbi_slash1_1", NULL);

	_animations[eStatus::SLASH2] = new Animation(_sprite, 0.07f);
	_animations[eStatus::SLASH2]->addFrameRect(eObjectID::GUARD, "nahbi_slash2_5", "nahbi_slash2_4", "nahbi_slash2_3", "nahbi_slash2_2", "nahbi_slash2_1", NULL);

	_animations[eStatus::BEATEN] = new Animation(_sprite, 0.07f);
	_animations[eStatus::BEATEN]->addFrameRect(eObjectID::GUARD, "nahbi_beaten_6", "nahbi_beaten_5", "nahbi_beaten_4", "nahbi_beaten_3", "nahbi_beaten_2", "nahbi_beaten_1", NULL);

	_animations[eStatus::BURNED] = new Animation(_sprite, 0.07f);
	_animations[eStatus::BURNED]->addFrameRect(eObjectID::GUARD, "nahbi_burned_9", "nahbi_burned_8", "nahbi_burned_7", "nahbi_burned_6", "nahbi_burned_5", "nahbi_burned_4", "nahbi_burned_3", "nahbi_burned_2", "nahbi_burned_1", NULL);

	for (auto animate : _animations)
	{
		animate.second->setColorFlash(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
}

void NahbiBehaviorComponent::init()
{
	setStatus(eStatus::TAUGHT);
	_hitpoint = 100;
	_standTime = 0;
}

void NahbiBehaviorComponent::update(float detatime)
{
	if (_hitpoint <= 0)
	{
		setStatus(eStatus::DESTROY);
		return;
	}

	_standTime -= detatime;
	if (_standTime > 0)
	{
		setStatus(eStatus::TAUGHT);
		standing();
		return;
	}

	auto aladdin = SceneManager::getInstance()->getCurrentScene()->getObject(eObjectID::ALADDIN);
	auto aladdinPos = aladdin->getPhysicsComponent()->getPosition();

	float diffirent = _physicsComponent->getPosition().x - aladdinPos.x;
	RECT bound = _physicsComponent->getBounding();
	float width = bound.right - bound.left;

	if (diffirent > width && _physicsComponent->getPositionX() >= _rangeXStart) // aladdin ở bến trái
	{
		setStatus(eStatus::RUNNING);
		moveLeft();
	}
	else if (diffirent < -width && _physicsComponent->getPositionX() <= _rangeXEnd)
	{
		setStatus(eStatus::RUNNING);
		moveRight();
	}
	else
	{
		standing();
		setStatus(eStatus::TAUGHT);
		slash();
	}


	if (_animationComponent->isTempAnimationEmpty() == true)
	{
		setWeapon(eStatus::NORMAL);
	}

}

void NahbiBehaviorComponent::setStatus(eStatus status)
{
	BehaviorComponent::setStatus(status);
	updateAnimation();
}

void NahbiBehaviorComponent::dropHitpoint(int damage)
{
	EnemyBehaviorComponent::dropHitpoint(damage);
	_animationComponent->setTempAnimation(eStatus::BEATEN, 1);
	_standTime = STAND_TIME;
}

void NahbiBehaviorComponent::updateAnimation()
{
	switch (_status)
	{
	case TAUGHT:
		_animationComponent->setAnimation(eStatus::TAUGHT);
		break;
	case RUNNING:
		_animationComponent->setAnimation(eStatus::RUNNING);
		break;
	default:
		break;
	}
}


void NahbiBehaviorComponent::faceLeft()
{
	if (_animationComponent->getScale().x > 0)
	{
		_animationComponent->setScaleX(_animationComponent->getScale().x * (-1));

		RECT bound = _physicsComponent->getBounding();
		float width = bound.right - bound.left;
		_animationComponent->setTranslateX(width);
	}
	setFacingDirection(eStatus::LEFTFACING);
}

void NahbiBehaviorComponent::faceRight()
{
	if (_animationComponent->getScale().x < 0)
	{
		_animationComponent->setScaleX(_animationComponent->getScale().x * (-1));

		_animationComponent->setTranslateX(0);
	}
	setFacingDirection(eStatus::RIGHTFACING);
}

void NahbiBehaviorComponent::standing()
{
	auto move = (Movement*)_physicsComponent->getComponent("Movement");
	move->setVelocity(GVector2(0, 0));
}

void NahbiBehaviorComponent::moveLeft()
{
	faceLeft();
	auto move = (Movement*)_physicsComponent->getComponent("Movement");
	move->setVelocity(GVector2(-_physicsComponent->getMovingSpeed(), move->getVelocity().y));
	setFacingDirection(eStatus::LEFTFACING);
}

void NahbiBehaviorComponent::moveRight()
{
	faceRight();
	auto move = (Movement*)_physicsComponent->getComponent("Movement");
	move->setVelocity(GVector2(_physicsComponent->getMovingSpeed(), move->getVelocity().y));
	setFacingDirection(eStatus::RIGHTFACING);
}

void NahbiBehaviorComponent::slash()
{
	int random = rand() % 3;
	switch (random)
		{
		case 1:
			_animationComponent->setTempAnimation(eStatus::SLASH1, 1);
			break;
		case 2:
			_animationComponent->setTempAnimation(eStatus::SLASH2, 1);
			break;
		}
	auto pos = _physicsComponent->getPosition();
	pos.y += _animationComponent->getSprite()->getFrameHeight();
	float width = _animationComponent->getSprite()->getFrameWidth() * 4 / 3;
	float height = _animationComponent->getSprite()->getFrameHeight();
	if (_facingDirection == eStatus::RIGHTFACING)
	{
		pos += GVector2(_animationComponent->getSprite()->getFrameWidth(), 0);
	}
	else
	{
		pos -= GVector2(_animationComponent->getSprite()->getFrameWidth(), 0);
	}
	auto sword = ObjectFactory::getSword(pos, width, height, false);
	addToScene.Emit(sword);

}
