#include "BehaviorComponent.h"
#include "AnimationComponent.h"
#include "PhysicsComponent.h"
#include "../Singleton/gamecontroller.h"

BehaviorComponent::BehaviorComponent()
{
}

BehaviorComponent::BehaviorComponent(AnimationComponent * animationComponent, PhysicsComponent * physicsComponent, GameController * input)
{
	_animationComponent = animationComponent;
	_physicsComponent = physicsComponent;
	_input = input;
}


BehaviorComponent::~BehaviorComponent()
{
}

eStatus BehaviorComponent::getStatus()
{
	return _status;
}

void BehaviorComponent::setStatus(eStatus status)
{
	_preStatus = _status;
	_status = status;
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



void BehaviorComponent::executeCommand(eCommand command)
{
}

void BehaviorComponent::updateAnimation()
{
}

