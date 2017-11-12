#include "Aladdin.h"
#include <ctime>;

void AladdinPhysicsComponent::init()
{
	_movingSpeed = ALADDIN_MOVE_SPEED;
	auto movement = new Movement(GVector2(0, 0), GVector2(0, 0), this);
	_componentList["Movement"] = movement;
	_componentList["Gravity"] = new Gravity(GVector2(0, -GRAVITY), movement);
	_componentList["Collision"] = new CollisionComponent();
	setPhysicsBodySide(eDirection::ALL);
}

void AladdinAnimationComponent::init()
{
	_sprite = SpriteResource::getInstance()->getSprite(eObjectID::ALADDIN);
	_sprite->setFrameRect(SpriteResource::getInstance()->getSourceRect(eObjectID::ALADDIN, "normal_01"));
	_sprite->setZIndex(0.0f);
	setOrigin(GVector2(0.0f, 0.0f));
	setScale(SCALE_FACTOR);
	

	_animations[eStatus::NORMAL] = new Animation(_sprite, 1000.0f);
	_animations[eStatus::NORMAL]->addFrameRect(eObjectID::ALADDIN, "normal_01", NULL);

	_animations[eStatus::NORMAL | eStatus::SLASH] = new Animation(_sprite, 0.1f);
	_animations[eStatus::NORMAL | eStatus::SLASH]->addFrameRect(eObjectID::ALADDIN, "slash_stand_01", "slash_stand_02", "slash_stand_03", "slash_stand_04", "slash_stand_05", NULL);

	_animations[eStatus::NORMAL | eStatus::THROW] = new Animation(_sprite, 0.1f);
	_animations[eStatus::NORMAL | eStatus::THROW]->addFrameRect(eObjectID::ALADDIN, "stand_throw_01", "stand_throw_02", "stand_throw_03", "stand_throw_04", "stand_throw_05","stand_throw_06", NULL);

	_animations[eStatus::RUNNING] = new Animation(_sprite, 0.1f);
	_animations[eStatus::RUNNING]->addFrameRect(eObjectID::ALADDIN, "run_01", "run_02", "run_03", "run_04", "run_05", "run_06", "run_07", "run_08", "run_09", "run_10", "run_11", "run_12", "run_13", NULL);

	_animations[eStatus::RUNNING | eStatus::SLASH] = _animations[eStatus::NORMAL | eStatus::SLASH];

	_animations[eStatus::JUMPING] = new Animation(_sprite, 0.1f);
	_animations[eStatus::JUMPING]->addFrameRect(eObjectID::ALADDIN, "jump_stand_01", "jump_stand_02", "jump_stand_03", "jump_stand_04", "jump_stand_05", "jump_stand_06", "jump_stand_07", "jump_stand_08", "jump_stand_09", "jump_stand_10", "jump_stand_11", "jump_stand_12", NULL);
	_animations[eStatus::JUMPING]->animateFromTo(0, 10, false);

	_animations[eStatus::JUMPING | eStatus::SLASH] = new Animation(_sprite, 0.1f);
	_animations[eStatus::JUMPING | eStatus::SLASH]->addFrameRect(eObjectID::ALADDIN, "slash_jump_01", "slash_jump_02", "slash_jump_03", "slash_jump_04", "slash_jump_05", "slash_jump_06", NULL);

	_animations[eStatus::MOVINGJUMPING] = new Animation(_sprite, 0.1f);
	_animations[eStatus::MOVINGJUMPING]->addFrameRect(eObjectID::ALADDIN, "jump_moving_01", "jump_moving_02", "jump_moving_03", "jump_moving_04", "jump_moving_05", "jump_moving_06", "jump_moving_07", "jump_moving_08", "jump_moving_09", NULL);

	//_animations[eStatus::MOVINGJUMPING | eStatus::SLASH] = _animations[eStatus::JUMPING | eStatus::SLASH];


	_animations[eStatus::FALLING] = new Animation(_sprite, 0.1f);
	_animations[eStatus::FALLING]->addFrameRect(eObjectID::ALADDIN, "jump_stand_13", NULL);

	_animations[eStatus::LANDING] = new Animation(_sprite, 0.1f);
	_animations[eStatus::LANDING]->addFrameRect(eObjectID::ALADDIN, "landing_01", "landing_02", "landing_03", "landing_04", "landing_05", "landing_06", "landing_07", "landing_08", "landing_09", "landing_10", "landing_11", "landing_12", NULL);

	_animations[eStatus::LAYING_DOWN] = new Animation(_sprite, 0.1f);
	_animations[eStatus::LAYING_DOWN]->addFrameRect(eObjectID::ALADDIN, "laydown_01", "laydown_02", "laydown_03", "laydown_04", NULL);
	_animations[eStatus::LAYING_DOWN]->animateFromTo(0, 2, false);

	_animations[eStatus::LAYING_DOWN | eStatus::SLASH] = new Animation(_sprite, 0.1f);
	_animations[eStatus::LAYING_DOWN | eStatus::SLASH]->addFrameRect(eObjectID::ALADDIN, "slash_laydown_01", "slash_laydown_02", "slash_laydown_03", "slash_laydown_04", "slash_laydown_05", "slash_laydown_06", "slash_laydown_07", NULL);

	_animations[eStatus::LAYING_DOWN | eStatus::THROW] = new Animation(_sprite, 0.1f);
	_animations[eStatus::LAYING_DOWN | eStatus::THROW]->addFrameRect(eObjectID::ALADDIN, "throw_laydown_01", "throw_laydown_02", "throw_laydown_03", "throw_laydown_04", "throw_laydown_05", "throw_laydown_06", "throw_laydown_07", NULL);

	_animations[eStatus::LOOKING_UP] = new Animation(_sprite, 0.1f);
	_animations[eStatus::LOOKING_UP]->addFrameRect(eObjectID::ALADDIN, "lookup_01", "lookup_02", "lookup_03", NULL);
	_animations[eStatus::LOOKING_UP]->animateFromTo(0, 1, false);

	_animations[eStatus::LOOKING_UP | eStatus::SLASH] = new Animation(_sprite, 0.1f);
	_animations[eStatus::LOOKING_UP | eStatus::SLASH]->addFrameRect(eObjectID::ALADDIN, "lookup_slash_01", "lookup_slash_02", "lookup_slash_03", "lookup_slash_04", "lookup_slash_05", "lookup_slash_06", "lookup_slash_07", "lookup_slash_08", "lookup_slash_09", "lookup_slash_10", "lookup_slash_11", "lookup_slash_12", NULL);

	_animations[eStatus::CLIMBVERTICAL] = new Animation(_sprite, 0.1f);
	_animations[eStatus::CLIMBVERTICAL]->addFrameRect(eObjectID::ALADDIN, "climb_vertical_01", "climb_vertical_02", "climb_vertical_03", "climb_vertical_04", "climb_vertical_05", "climb_vertical_06", "climb_vertical_07", "climb_vertical_08", "climb_vertical_09", "climb_vertical_10", NULL);


	_animations[eStatus::CLIMBHORIZON] = new Animation(_sprite, 0.1f);
	_animations[eStatus::CLIMBHORIZON]->addFrameRect(eObjectID::ALADDIN, "climb_horizon_01", "climb_horizon_02", "climb_horizon_03", "climb_horizon_04", "climb_horizon_05", "climb_horizon_06", "climb_horizon_07", "climb_horizon_08","climb_horizon_09","climb_horizon_10", NULL);

	_animations[eStatus::CLIMBHORIZON | eStatus::BORING1] = new Animation(_sprite, 0.1f);
	_animations[eStatus::CLIMBHORIZON | eStatus::BORING1]->addFrameRect(eObjectID::ALADDIN, "climb_horizon_boring_01", "climb_horizon_boring_02", "climb_horizon_boring_03", "climb_horizon_boring_04", "climb_horizon_boring_05", NULL);

	_animations[eStatus::CLIMBHORIZON | eStatus::JUMPING] = new Animation(_sprite, 0.1f);
	_animations[eStatus::CLIMBHORIZON | eStatus::JUMPING]->addFrameRect(eObjectID::ALADDIN, "tumble_01", "tumble_02", "tumble_03", "tumble_04", "tumble_05", "tumble_06", "tumble_07", "tumble_08", NULL);

	_animations[eStatus::CLIMBHORIZON | eStatus::THROW] = new Animation(_sprite, 0.1f);
	_animations[eStatus::CLIMBHORIZON | eStatus::THROW]->addFrameRect(eObjectID::ALADDIN, "throw_climb_01", "throw_climb_02", "throw_climb_03", "throw_climb_04", "throw_climb_05", NULL);

	_animations[eStatus::CLIMBHORIZON | eStatus::SLASH] = new Animation(_sprite, 0.1f);
	_animations[eStatus::CLIMBHORIZON | eStatus::SLASH]->addFrameRect(eObjectID::ALADDIN, "slash_climb_01", "slash_climb_02", "slash_climb_03", "slash_climb_04", "slash_climb_05", NULL);

	_animations[eStatus::JUMPOUT] = new Animation(_sprite, 0.1f);
	_animations[eStatus::JUMPOUT]->addFrameRect(eObjectID::ALADDIN, "jump_out_01", "jump_out_02", "jump_out_03", "jump_out_04", "jump_out_05", "jump_out_06", "jump_out_07", "jump_out_08", "jump_out_09", NULL);

	_animations[eStatus::PUSH] = new Animation(_sprite, 0.1f);
	_animations[eStatus::PUSH]->addFrameRect(eObjectID::ALADDIN, "push_01", "push_02", "push_03", "push_04", "push_05", "push_06", "push_07", "push_08", "push_09", NULL);

	_animations[eStatus::BURNED] = new Animation(_sprite, 0.1f);
	_animations[eStatus::BURNED]->addFrameRect(eObjectID::ALADDIN, "burned_01", "burned_02", "burned_03", "burned_04", "burned_05", "burned_06", NULL);

	_animations[eStatus::DYING] = new Animation(_sprite, 0.1f);
	_animations[eStatus::DYING]->addFrameRect(eObjectID::ALADDIN, "die_01", "die_02", "die_03", "die_04", "die_05", "die_06", "die_07", "die_08", "die_09", "die_10", "die_11", "die_12", "die_13", NULL);

	_animations[eStatus::CARE] = new Animation(_sprite, 0.1f);
	_animations[eStatus::CARE]->addFrameRect(eObjectID::ALADDIN, "care_01", "care_02", "care_03", "care_04", "care_05", "care_06", "care_07", "care_08", "care_09", "care_10", "care_11", "care_12", "care_13", "care_14", "care_15", NULL);

	_animations[eStatus::REVIVE] = new Animation(_sprite, 0.1f);
	_animations[eStatus::REVIVE]->addFrameRect(eObjectID::ALADDIN, "revive_01", "revive_02", "revive_03", "revive_04", "revive_05", "revive_06", "revive_07", "revive_08", "revive_09", "revive_10", "revive_11", "revive_12", "revive_13", "revive_14", NULL);

	_animations[eStatus::REVIVE] = new Animation(_sprite, 0.1f);
	_animations[eStatus::REVIVE]->addFrameRect(eObjectID::ALADDIN, "jealous_01", "jealous_02", "jealous_03", "jealous_04", "jealous_05", "jealous_06", "jealous_07", "jealous_08", NULL);

	_animations[eStatus::BRAKING] = new Animation(_sprite, 0.1f);
	_animations[eStatus::BRAKING]->addFrameRect(eObjectID::ALADDIN, "braking_01", "braking_02", "braking_03", "braking_04", "braking_05", "braking_06", "braking_07", "braking_08", "braking_09", NULL);

	_animations[eStatus::BORING1] = new Animation(_sprite, 0.1f);
	_animations[eStatus::BORING1]->addFrameRect(eObjectID::ALADDIN, "normal_01", "normal_02", "normal_03", "normal_04", "normal_05", "normal_06", "normal_07", NULL);
	vector<float> customTime(7, 0.1f);
	customTime[3] = 0.5f;
	customTime[6] = 0.5f;
	_animations[eStatus::BORING1]->setCustomTime(customTime);
	_animations[eStatus::BORING1]->setLoop(true);


	_animations[eStatus::BORING2] = new Animation(_sprite, 0.1f);
	_animations[eStatus::BORING2]->addFrameRect(eObjectID::ALADDIN, "boring_01", "boring_02", "boring_03", "boring_04", "boring_05", "boring_06", "boring_07", "boring_08", "boring_09", "boring_10", "boring_11", "boring_12", "boring_13", "boring_14", "boring_15", NULL);
	_animations[eStatus::BORING2]->animateFromTo(5, 14, true);

	_animations[eStatus::BORING3] = new Animation(_sprite, 0.1f);
	_animations[eStatus::BORING3]->addFrameRect(eObjectID::ALADDIN, "boring_circus_01", "boring_circus_02", "boring_circus_03", "boring_circus_04", "boring_circus_05", "boring_circus_06", "boring_circus_07", "boring_circus_08", "boring_circus_09", "boring_circus_10", "boring_circus_11", "boring_circus_12", "boring_circus_13", "boring_circus_14", "boring_circus_15", "boring_circus_16", "boring_circus_17", NULL);


	for (auto animate : _animations)
	{
		animate.second->setColorFlash(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
}


GVector2 AladdinPhysicsComponent::getVelocity()
{
	auto move = (Movement*)getComponent("Movement");
	return move->getVelocity();
}

void AladdinPhysicsComponent::setAnimationComponent(AnimationComponent * animationComponent)
{
	_animationComponent = animationComponent;
}

RECT AladdinPhysicsComponent::getBounding()
{
	return _animationComponent->getBounding();
}


void AladdinBehaviorComponent::init()
{
	_isBoring = false;
	_preStatus = eStatus::NORMAL;
	_preObject = new GameObject();
	_preObject->setID(eObjectID::LAND);
	setWeapon(eStatus::NORMAL);
	moveLeft();
	moveRight();
	jump();
	srand(time(0));
}

void AladdinBehaviorComponent::update(float detatime)
{
	auto collisionComponent = (CollisionComponent*)_physicsComponent->getComponent("Collision");
	GameObject * object;
	eDirection direction;
	switch (_status)
	{
	case NORMAL:
		if (_animationComponent->getCurrentAnimation()->getTotalTimeAnimation() >= 3.0f)
		{
			_isBoring = true;
			_animationComponent->setAnimation(eStatus::BORING1);
			setBoringAnimation();
		}
		if (_input->isKeyDown(BT_LEFT))
		{
			_isBoring = false;
			setStatus(eStatus::RUNNING);
			moveLeft();
		}
		if (_input->isKeyDown(BT_RIGHT))
		{
			_isBoring = false;
			setStatus(eStatus::RUNNING);
			moveRight();
		}
		if (_input->isKeyPressed(BT_JUMP))
		{
			_isBoring = false;
			jump();
		}
		if (_input->isKeyDown(BT_UP))
		{
			_isBoring = false;
			setStatus(eStatus::LOOKING_UP);
		}
		if (_input->isKeyDown(BT_DOWN))
		{
			_isBoring = false;
			setStatus(eStatus::LAYING_DOWN);
		}
		if (_input->isKeyPressed(BT_SLASH))
		{
			_isBoring = false;
			if (getWeapon() == eStatus::NORMAL)
			{
				slash();
			}
		}
		if (_input->isKeyPressed(BT_THROW))
		{
			_isBoring = false;
			if (getWeapon() == eStatus::NORMAL)
			{
				throwApple();
			}
		}
		break;
	case JUMPING:
		object = collisionComponent->isColliding(eObjectID::LAND);
		if ( object != nullptr)
		{
			standing();
			_preObject = object;
		}
		if (_input->isKeyDown(BT_LEFT))
		{
			moveLeft();
		}
		if (_input->isKeyDown(BT_RIGHT))
		{
			moveRight();
		}
		if (_input->isKeyPressed(BT_SLASH))
		{
			if (getWeapon() == eStatus::NORMAL)
			{
				setWeapon(eStatus::SLASH);
			}
		}
		break;
	case LAYING_DOWN:
		if (_input->isKeyRelease(BT_DOWN))
		{
			setStatus(eStatus::NORMAL);
		}
		if (_input->isKeyPressed(BT_SLASH))
		{
			if (getWeapon() == eStatus::NORMAL)
			{
				setWeapon(eStatus::SLASH);
			}
		}
		if (_input->isKeyPressed(BT_THROW))
		{
			if (getWeapon() == eStatus::NORMAL)
			{
				setWeapon(eStatus::THROW);
			}
		}
		break;
	case RUNNING:
		if (_input->isKeyDown(BT_LEFT))
		{
			moveLeft();
		}
		if (_input->isKeyDown(BT_RIGHT))
		{
			moveRight();
		}
		if (_input->isKeyPressed(BT_JUMP))
		{
			jump();
		}
		if (!_input->isKeyDown(BT_LEFT) && !_input->isKeyDown(BT_RIGHT))
		{
			standing();
		}
		if (_input->isKeyPressed(BT_SLASH))
		{
			if (getWeapon() == eStatus::NORMAL)
			{
				setWeapon(eStatus::SLASH);
			}
		}
		if (_input->isKeyPressed(BT_THROW))
		{
			if (getWeapon() == eStatus::NORMAL)
			{
				setWeapon(eStatus::THROW);
			}
		}
		break;
	case LOOKING_UP:
		if (_input->isKeyRelease(BT_UP))
		{
			setStatus(eStatus::NORMAL);
		}
		if (_input->isKeyPressed(BT_SLASH))
		{
			if (getWeapon() == eStatus::NORMAL)
			{
				setWeapon(eStatus::SLASH);
			}
		}
		break;
	case FALLING:
		break;
	case CLIMBVERTICAL:
		if (_input->isKeyDown(BT_UP))
		{
			moveUp();
		}
		if (_input->isKeyDown(BT_DOWN))
		{
			moveDown();
		}
		break;
	case CLIMBHORIZON:
		if (_input->isKeyPressed(BT_SLASH))
		{
			if (getWeapon() == eStatus::NORMAL)
			{
				setWeapon(eStatus::SLASH);
			}
		}
		if (_input->isKeyPressed(BT_THROW))
		{
			if (getWeapon() == eStatus::NORMAL)
			{
				setWeapon(eStatus::THROW);
			}
		}
		break;
	default:
		break;
	}
	updateAnimation();
}

void AladdinBehaviorComponent::updateTimeOut(float deltaTime)
{
}

void AladdinBehaviorComponent::updateAnimation()
{
	switch (_status)
	{
	case NORMAL:
		if (_isBoring == false)
		{
			checkAndAddWeaponAnimation();
		}
		break;
	case JUMPING:
		if (_preStatus == eStatus::RUNNING)
		{
			_animationComponent->setAnimation(eStatus::MOVINGJUMPING);
		}
		else
		{
			_animationComponent->setAnimation(eStatus::JUMPING);
		}
		checkAndAddWeaponAnimation();
		break;
	case LAYING_DOWN:
		checkAndAddWeaponAnimation();
		break;
	case RUNNING:
		checkAndAddWeaponAnimation();
		break;
	case LOOKING_UP:
		checkAndAddWeaponAnimation();
		break;
	case FALLING:
		_animationComponent->setAnimation(eStatus::FALLING);
		break;
	case CLIMBVERTICAL:
		_animationComponent->setAnimation(eStatus::CLIMBVERTICAL);
		break;
	default:
		break;
	}
	checkAndRemoveWeapon();
}

void AladdinBehaviorComponent::setBoringAnimation()
{
	if (_animationComponent->getCurrentAnimation()->getCount() >= 1)
	{
		int random = rand() % 3;
		switch (random)
		{
		case 0:
			_animationComponent->setAnimation(eStatus::BORING1);
			break;
		case 1:
			_animationComponent->setAnimation(eStatus::BORING2);
			break;
		case 2:
			_animationComponent->setAnimation(eStatus::BORING3);
			break;
		default:
			_animationComponent->setAnimation(eStatus::BORING1);
			break;
		}
	}
}

void AladdinBehaviorComponent::faceLeft()
{
	if (_animationComponent->getScale().x > 0)
	{
		_animationComponent->setScaleX(_animationComponent->getScale().x * (-1));
		_animationComponent->setOrigin(GVector2(0.5f, 0.0f));
	}
	setFacingDirection(eStatus::LEFTFACING);
}

void AladdinBehaviorComponent::faceRight()
{
	if (_animationComponent->getScale().x < 0)
	{
		_animationComponent->setScaleX(_animationComponent->getScale().x * (-1));
		_animationComponent->setOrigin(GVector2(0.5f, 0.0f));
	}
	setFacingDirection(eStatus::RIGHTFACING);
}

void AladdinBehaviorComponent::standing()
{
	auto move = (Movement*)_physicsComponent->getComponent("Movement");
	move->setVelocity(GVector2(0, 0));

	auto gravity = (Gravity*)_physicsComponent->getComponent("Gravity");
	gravity->setStatus(eGravityStatus::LANDED);

	setStatus(eStatus::NORMAL);
}

void AladdinBehaviorComponent::moveLeft()
{
	faceLeft();
	auto move = (Movement*)_physicsComponent->getComponent("Movement");
	move->setVelocity(GVector2(-_physicsComponent->getMovingSpeed(), move->getVelocity().y));
	setFacingDirection(eStatus::LEFTFACING);
}

void AladdinBehaviorComponent::moveRight()
{
	faceRight();
	auto move = (Movement*)_physicsComponent->getComponent("Movement");
	move->setVelocity(GVector2(_physicsComponent->getMovingSpeed(), move->getVelocity().y));
	setFacingDirection(eStatus::RIGHTFACING);
}

void AladdinBehaviorComponent::moveUp()
{
	auto move = (Movement*)_physicsComponent->getComponent("Movement");
	move->setVelocity(GVector2(0, ALADDIN_CLIMB_SPEED));
}

void AladdinBehaviorComponent::moveDown()
{
	auto move = (Movement*)_physicsComponent->getComponent("Movement");
	move->setVelocity(GVector2(0, -ALADDIN_CLIMB_SPEED));
}

void AladdinBehaviorComponent::jump()
{
	auto move = (Movement*)this->_physicsComponent->getComponent("Movement");
	move->setVelocity(GVector2(move->getVelocity().x, ALADDIN_JUMP_VEL));

	auto g = (Gravity*)this->_physicsComponent->getComponent("Gravity");
	g->setStatus(eGravityStatus::FALLING__DOWN);

	setStatus(eStatus::JUMPING);
}

void AladdinBehaviorComponent::slash()
{
	setWeapon(eStatus::SLASH);
}

void AladdinBehaviorComponent::throwApple()
{
	setWeapon(eStatus::THROW);
}

void AladdinBehaviorComponent::checkAndAddWeaponAnimation()
{
	if (getWeapon() != eStatus::NORMAL)
	{
		_animationComponent->setAnimation(_status | getWeapon());
	}
	else
	{
		_animationComponent->setAnimation(_status);
	}
}

void AladdinBehaviorComponent::removeWeaponAnimation()
{
	int status = _animationComponent->getAnimationStatus();
	status = (status & ~eStatus::SLASH); // remove slash
	status = (status & ~eStatus::THROW); // remove throw
	_animationComponent->setAnimation(status);
}

void AladdinBehaviorComponent::checkAndRemoveWeapon()
{
	if (getWeapon() != eStatus::NORMAL && _animationComponent->getCurrentAnimation()->getCount() >= 1 )
	{
		removeWeaponAnimation();
		setWeapon(eStatus::NORMAL);
	}
}


void AladdinBehaviorComponent::falling()
{
	auto g = (Gravity*)this->_physicsComponent->getComponent("Gravity");
	g->setStatus(eGravityStatus::FALLING__DOWN);

	setStatus(eStatus::FALLING);
}

void AladdinBehaviorComponent::climbvertical()
{
}

void AladdinBehaviorComponent::climbhorizon()
{
	auto move = (Movement*)this->_physicsComponent->getComponent("Movement");
	move->setVelocity(GVector2(0, 0));
}


void AladdinBehaviorComponent::climbJump()
{
	jump();
}

void AladdinBehaviorComponent::executeCommand(eCommand command)
{

}

