#pragma once
#include "../define.h"
#include "Component.h"
#include "AnimationComponent.h"
#include "PhysicsComponent.h"
#include "../Singleton/gamecontroller.h"
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

	virtual void executeCommand(eCommand command) = 0;
	virtual void updateAnimation() = 0;

protected:
	eStatus _status;
	eStatus _preStatus;
	eStatus _facingDirection;

	GameController* _input;

	AnimationComponent* _animationComponent;
	PhysicsComponent* _physicsComponent;


	
};
