#include "BehaviorComponent.h"

BehaviorComponent::BehaviorComponent()
{
}

BehaviorComponent::BehaviorComponent(AnimationComponent * animationComponent, PhysicsComponent * physicsComponent, GameController *input)
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
}

eStatus BehaviorComponent::getFacingDirection()
{
	return _facingDirection;
}

void BehaviorComponent::setFacingDirection(eStatus status)
{
	_facingDirection = status;
}



void BehaviorComponent::executeCommand(eCommand command)
{
}

void BehaviorComponent::updateAnimation()
{
}
