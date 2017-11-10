#include "Aladdin.h"

void AladdinPhysicsComponent::init()
{
	_movingSpeed = ALADDIN_MOVE_SPEED;
	auto movement = new Movement(GVector2(0, 0), GVector2(0, 0), this);
	_componentList["Movement"] = movement;
	_componentList["Gravity"] = new Gravity(GVector2(0, -GRAVITY), movement);
}

void AladdinAnimationComponent::init()
{

	_animations[eStatus::NORMAL] = new Animation(_sprite, 1000.0f);
	_animations[eStatus::NORMAL]->addFrameRect(eObjectID::ALADDIN, "normal_01", NULL);

	_animations[eStatus::NORMAL | eStatus::SWORD] = new Animation(_sprite, 0.1f);
	_animations[eStatus::NORMAL | eStatus::SWORD]->addFrameRect(eObjectID::ALADDIN, "slash_stand_01", "slash_stand_02", "slash_stand_03", "slash_stand_04", "slash_stand_05", NULL);

	_animations[eStatus::RUNNING] = new Animation(_sprite, 0.1f);
	_animations[eStatus::RUNNING]->addFrameRect(eObjectID::ALADDIN, "run_01", "run_02", "run_03", "run_04", "run_05", "run_06", "run_07", "run_08", "run_09", "run_10", "run_11", "run_12", "run_13", NULL);

	_animations[eStatus::RUNNING | eStatus::SWORD] = _animations[eStatus::NORMAL | eStatus::SWORD];

	_animations[eStatus::JUMPING] = new Animation(_sprite, 0.1f);
	_animations[eStatus::JUMPING]->addFrameRect(eObjectID::ALADDIN, "jump_stand_01", "jump_stand_02", "jump_stand_03", "jump_stand_04", "jump_stand_05", "jump_stand_06", "jump_stand_07", "jump_stand_08", "jump_stand_09", "jump_stand_10", "jump_stand_11", "jump_stand_12", NULL);
	_animations[eStatus::JUMPING]->animateFromTo(0, 10, false);

	_animations[eStatus::JUMPING | eStatus::SWORD] = new Animation(_sprite, 0.1f);
	_animations[eStatus::JUMPING | eStatus::SWORD]->addFrameRect(eObjectID::ALADDIN, "slash_jump_01", "slash_jump_02", "slash_jump_03", "slash_jump_04", "slash_jump_05", "slash_jump_06", NULL);

	_animations[eStatus::MOVINGJUMPING] = new Animation(_sprite, 0.1f);
	_animations[eStatus::MOVINGJUMPING]->addFrameRect(eObjectID::ALADDIN, "jump_moving_01", "jump_moving_02", "jump_moving_03", "jump_moving_04", "jump_moving_05", "jump_moving_06", "jump_moving_07", "jump_moving_08", "jump_moving_09", NULL);
	_animations[eStatus::MOVINGJUMPING]->animateFromTo(0, 7, false);

	_animations[eStatus::MOVINGJUMPING | eStatus::SWORD] = _animations[eStatus::JUMPING | eStatus::SWORD];


	_animations[eStatus::FALLING] = new Animation(_sprite, 0.1f);
	_animations[eStatus::FALLING]->addFrameRect(eObjectID::ALADDIN, "jump_stand_13", NULL);

	_animations[eStatus::LAYING_DOWN] = new Animation(_sprite, 0.1f);
	_animations[eStatus::LAYING_DOWN]->addFrameRect(eObjectID::ALADDIN, "laydown_01", "laydown_02", "laydown_03", "laydown_04", NULL);
	_animations[eStatus::LAYING_DOWN]->animateFromTo(0, 2, false);

	_animations[eStatus::LAYING_DOWN | eStatus::SWORD] = new Animation(_sprite, 0.1f);
	_animations[eStatus::LAYING_DOWN | eStatus::SWORD]->addFrameRect(eObjectID::ALADDIN, "slash_laydown_01", "slash_laydown_02", "slash_laydown_03", "slash_laydown_04", "slash_laydown_05", "slash_laydown_06", "slash_laydown_07", NULL);

	_animations[eStatus::LOOKING_UP] = new Animation(_sprite, 0.1f);
	_animations[eStatus::LOOKING_UP]->addFrameRect(eObjectID::ALADDIN, "lookup_01", "lookup_02", "lookup_03", NULL);
	_animations[eStatus::LOOKING_UP]->animateFromTo(0, 1, false);

	_animations[eStatus::CLIMBVERTICAL] = new Animation(_sprite, 0.1f);
	_animations[eStatus::CLIMBVERTICAL]->addFrameRect(eObjectID::ALADDIN, "climb_horizon_01", "climb_horizon_02", "climb_horizon_03", "climb_horizon_04", "climb_horizon_05", "climb_horizon_06", "climb_horizon_07", "climb_horizon_08", "climb_horizon_09", "climb_horizon_10", NULL);

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

	setOrigin(GVector2(0.0f, 0.0f));
	setScale(SCALE_FACTOR);


	for (auto animate : _animations)
	{
		animate.second->setColorFlash(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
}

void AladdinBehaviorComponent::init()
{
	_preStatus = NORMAL;
	_status = NORMAL;
}

void AladdinBehaviorComponent::update(float detatime)
{
	switch (_status)
	{
	case NORMAL:
		if (_input->isKeyDown(DIK_LEFT))
		{
			moveLeft();
		}
		if (_input->isKeyDown(DIK_RIGHT))
		{
			moveRight();
		}
		if (_input->isKeyPressed(DIK_X))
		{
			jump();
		}
		break;
	case JUMPING:
		break;
	case LAYING_DOWN:
		if(_input->isKeyRelease())
		break;
	case RUNNING:
		break;
	case LOOKING_UP:
		break;
	case THROWING:
		break;
	case MOVING:
		break;
	case FALLING:
		break;
	case MOVINGJUMPING:
		break;
	case SWORD:
		break;
	case CLIMBVERTICAL:
		break;
	case CLIMBHORIZON:
		break;
	case MOVE_UP:
		break;
	case MOVE_DOWN:
		break;
	case BORING1:
		break;
	case BORING2:
		break;
	case BORING3:
		break;
	default:
		break;
	}
}

void AladdinBehaviorComponent::updateTimeOut(float deltaTime)
{
}

void AladdinBehaviorComponent::updateAnimation()
{
	switch (_status)
	{
	case NORMAL:
		_animationComponent->setAnimation(eStatus::NORMAL);
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
		break;
	case LAYING_DOWN:
		_animationComponent->setAnimation(eStatus::LAYING_DOWN);
		break;
	case RUNNING:
		_animationComponent->setAnimation(eStatus::RUNNING);
		break;
	case LOOKING_UP:
		_animationComponent->setAnimation(eStatus::LOOKING_UP);
		break;
	case FALLING:
		_animationComponent->setAnimation(eStatus::FALLING);
		break;
	case CLIMBVERTICAL:
		_animationComponent->setAnimation(eStatus::RUNNING);
		break;
	case BORING1:
		_animationComponent->setAnimation(eStatus::BORING1);
		break;
	case BORING2:
		_animationComponent->setAnimation(eStatus::BORING2);
		break;
	case BORING3:
		_animationComponent->setAnimation(eStatus::BORING3);
		break;
	default:
		break;
	}
}

void AladdinBehaviorComponent::faceLeft()
{
	if (_animationComponent->getScale().x > 0)
	{
		_animationComponent->setScaleX(_animationComponent->getScale().x * (-1));
	}
	setFacingDirection(eStatus::LEFT);
}

void AladdinBehaviorComponent::faceRight()
{
	if (_animationComponent->getScale().x < 0)
	{
		_animationComponent->setScaleX(_animationComponent->getScale().x * (-1));
	}
	setFacingDirection(eStatus::RIGHT);
}

void AladdinBehaviorComponent::standing()
{
	auto move = (Movement*)_physicsComponent->getMovingComponent("movement");
	move->setVelocity(GVector2(0, 0));
	setStatus(eStatus::NORMAL);
}

void AladdinBehaviorComponent::moveLeft()
{
	faceLeft();
	auto move = (Movement*)_physicsComponent->getMovingComponent("Movement");
	move->setVelocity(GVector2(-_physicsComponent->getMovingSpeed(), move->getVelocity().y));
	setStatus(eStatus::MOVING);
	setFacingDirection(eStatus::RUNNING);
}

void AladdinBehaviorComponent::moveRight()
{
	faceRight();
	auto move = (Movement*)_physicsComponent->getMovingComponent("Movement");
	move->setVelocity(GVector2(_physicsComponent->getMovingSpeed(), move->getVelocity().y));
	setStatus(eStatus::MOVING);
	setFacingDirection(eStatus::RUNNING);
}

void AladdinBehaviorComponent::moveUp()
{
	auto move = (Movement*)_physicsComponent->getMovingComponent("Movement");
	move->setVelocity(GVector2(0, ALADDIN_CLIMB_SPEED));
}

void AladdinBehaviorComponent::moveDown()
{
	auto move = (Movement*)_physicsComponent->getMovingComponent("Movement");
	move->setVelocity(GVector2(0, -ALADDIN_CLIMB_SPEED));
}

void AladdinBehaviorComponent::jump()
{
	auto move = (Movement*)this->_physicsComponent->getMovingComponent("Movement");
	move->setVelocity(GVector2(move->getVelocity().x, ALADDIN_JUMP_VEL));

	auto g = (Gravity*)this->_physicsComponent->getMovingComponent("Gravity");
	g->setStatus(eGravityStatus::FALLING__DOWN);

	setStatus(eStatus::JUMPING);
}

void AladdinBehaviorComponent::slash()
{
	setWeapon(eStatus::SWORD);
}

void AladdinBehaviorComponent::falling()
{
	auto g = (Gravity*)this->_physicsComponent->getMovingComponent("Gravity");
	g->setStatus(eGravityStatus::FALLING__DOWN);

	setStatus(eStatus::FALLING);
}

void AladdinBehaviorComponent::climbvertical()
{
}

void AladdinBehaviorComponent::climbhorizon()
{
	auto move = (Movement*)this->_physicsComponent->getMovingComponent("Movement");
	move->setVelocity(GVector2(0, 0));
}


void AladdinBehaviorComponent::climbJump()
{
	jump();
}

