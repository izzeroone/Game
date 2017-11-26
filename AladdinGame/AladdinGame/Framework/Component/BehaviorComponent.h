#pragma once
#ifndef __BEHAVIORCOMPONENT_H__
#define __BEHAVIORCOMPONENT_H__
#include "../define.h"
#include "Component.h"
#include "../Singleton/gamecontroller.h"
#include "../../../pugixml/src/pugixml.hpp"
#include "../../../sigcxx/include/sigcxx/sigcxx.hpp"
using namespace pugi;
LINK_FRAMEWORK
//forward declarations
class AnimationComponent;
class PhysicsComponent;
class GameObject;

class BehaviorComponent: public Component
{
public:
	BehaviorComponent();
	BehaviorComponent(AnimationComponent* animationComponent, PhysicsComponent* physicsComponent);
	~BehaviorComponent();
	
	virtual void update(float deltatime);

	virtual eStatus getStatus();
	virtual void setStatus(eStatus status);

	virtual eStatus getFacingDirection();
	virtual void setFacingDirection(eStatus status);

	virtual eStatus getWeapon();
	virtual void setWeapon(eStatus weapon);
	virtual void checkWeaponAnimation();

	virtual void executeCommand(eCommand command);
	virtual void updateAnimation();

	virtual void setGameController(GameController * input);
	virtual void setAnimationComponent(AnimationComponent * animationComponent);
	virtual void setPhysicsComponent(PhysicsComponent * physicsComponent);

	wstring getStatusString(eStatus status);

	static sigcxx::Signal<GameObject * > addToScene;
protected:
	eStatus _status;
	eStatus _preStatus;
	eStatus _facingDirection;
	eStatus _weapon;

	GameController * _input;
	GameObject * _preObject;
	AnimationComponent * _animationComponent;
	PhysicsComponent* _physicsComponent;
};

#endif //__BEHAVIORCOMPONENT_H__
