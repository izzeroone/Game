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
		OutputDebugStringW(L"Status : ");
		__debugoutput(status);
		OutputDebugStringW(L"\n");
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

