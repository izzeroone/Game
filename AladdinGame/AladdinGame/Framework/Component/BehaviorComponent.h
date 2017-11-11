#pragma once
#ifndef __BEHAVIORCOMPONENT_H__
#define __BEHAVIORCOMPONENT_H__
#include "../define.h"
#include "Component.h"
#include "../Singleton/gamecontroller.h"
LINK_FRAMEWORK
//forward declarations
class AnimationComponent;
class PhysicsComponent;

class BehaviorComponent: public Component
{
public:
	BehaviorComponent();
	BehaviorComponent(AnimationComponent* animationComponent, PhysicsComponent* physicsComponent);
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

	virtual void setGameController(GameController * input);
	virtual void setAnimationComponent(AnimationComponent * animationComponent);
	virtual void setPhysicsComponent(PhysicsComponent * physicsComponent);

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