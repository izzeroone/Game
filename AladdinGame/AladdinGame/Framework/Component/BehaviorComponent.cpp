#include "BehaviorComponent.h"
#include "AnimationComponent.h"
#include "PhysicsComponent.h"
#include "../GameObject.h"
#include "../Singleton/gamecontroller.h"

BehaviorComponent::BehaviorComponent()
{
}

BehaviorComponent::BehaviorComponent(AnimationComponent * animationComponent, PhysicsComponent * physicsComponent)
{
	_animationComponent = animationComponent;
	_physicsComponent = physicsComponent;
}


BehaviorComponent::~BehaviorComponent()
{
}

void BehaviorComponent::update(float deltatime)
{
}

eStatus BehaviorComponent::getStatus()
{
	return _status;
}

void BehaviorComponent::setStatus(eStatus status)
{
	if (_status != status)
	{
		_preStatus = _status;
		_status = status;
	}
}

eStatus BehaviorComponent::getFacingDirection()
{
	return _facingDirection;
}

void BehaviorComponent::setFacingDirection(eStatus status)
{
	_facingDirection = status;
}

eStatus BehaviorComponent::getWeapon()
{
	return _weapon;
}

void BehaviorComponent::setWeapon(eStatus weapon)
{
	_weapon = weapon;
}

void BehaviorComponent::checkWeaponAnimation()
{
}



void BehaviorComponent::executeCommand(eCommand command)
{
}

void BehaviorComponent::updateAnimation()
{
}

void BehaviorComponent::setGameController(GameController * input)
{
	_input = input;
}

void BehaviorComponent::setAnimationComponent(AnimationComponent * animationComponent)
{
	_animationComponent = animationComponent;
}

void BehaviorComponent::setPhysicsComponent(PhysicsComponent * physicsComponent)
{
	_physicsComponent = physicsComponent;
}

wstring BehaviorComponent::getStatusString(eStatus status)
{
	switch (status)
	{
	case NORMAL:
		return L"normal";
		break;
	case JUMPING:
		return L"jumping";
		break;
	case LAYING_DOWN:
		return L"laying_down";
		break;
	case RUNNING:
		return L"running";
		break;
	case LOOKING_UP:
		return L"look_up";
		break;
	case THROW:
		return L"throw";
		break;
	case FALLING:
		return L"falling";
		break;
	case MOVING_JUMPING:
		return L"movingjumping";
		break;
	case SLASH:
		return L"slash";
		break;
	case CLIMB_VERTICAL:
		return L"climb vertical";
		break;
	case CLIMB_HORIZON:
		return L"climb horizon";
		break;
	case BORING1:
		return L"boring1";
		break;
	case BORING2:
		return L"boring2";
		break;
	case BORING3:
		return L"boring3";
		break;
	case LANDING:
		return L"landing";
		break;
	case BRAKING:
		return L"braking";
		break;
	case PUSH:
		return L"push";
		break;
	case BURNED:
		return L"burned";
		break;
	case DYING:
		return L"dying";
		break;
	case CARE:
		return L"care";
		break;
	case REVIVE:
		return L"revive";
		break;
	case JEALOUS:
		return L"jealous";
		break;
	default:
		return L"unknown";
		break;
	}
}

