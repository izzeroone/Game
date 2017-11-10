#pragma once
#ifndef __BEHAVIORCOMPONENT_H__
#define __BEHAVIORCOMPONENT_H__
#include "../define.h"
#include "Component.h"

//forward declarations
class AnimationComponent;
class PhysicsComponent;

class BehaviorComponent: public Component
{
public:
	BehaviorComponent();
	BehaviorComponent(AnimationComponent* animationComponent, PhysicsComponent* physicsComponent, GameController* input);
	~BehaviorComponent();
	
	virtual void update(float deltatime) = 0;

	virtual eStatus getStatus();
	virtual void setStatus(eStatus status);

	virtual eStatus getFacingDirection();
	virtual void setFacingDirection(eStatus status);

	virtual eStatus getWeapon();
	virtual void setWeapon(eStatus weapon);

	virtual void executeCommand(eCommand command) = 0;
	virtual void updateAnimation() = 0;

protected:
	eStatus _status;
	eStatus _preStatus;
	eStatus _facingDirection;

	eStatus _weapon;

	GameController * _input;

	AnimationComponent * _animationComponent;
	PhysicsComponent* _physicsComponent;
};

#endif //__BEHAVIORCOMPONENT_H__
