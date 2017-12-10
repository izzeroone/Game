#pragma once
#ifndef __BEHAVIORCOMPONENT_H__
#define __BEHAVIORCOMPONENT_H__
#include "../define.h"
#include "Component.h"
#include "../Singleton/gamecontroller.h"
#include "../../../pugixml/src/pugixml.hpp"
#include "../../../sigcxx/include/sigcxx/sigcxx.hpp"
using namespace pugi;
//forward declarations
class CollisionComponent;
class GameObject;

LINK_FRAMEWORK

class BehaviorComponent: public Component
{
public:
	BehaviorComponent();
	BehaviorComponent(GameObject* gameObject);
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

	wstring getStatusString(eStatus status);

	virtual void setGameObject(GameObject* gameObject);
	virtual CollisionComponent* getCollisionComponent();

	static sigcxx::Signal<GameObject * > addToScene;
protected:
	eStatus _status;
	eStatus _preStatus;
	eStatus _facingDirection;
	eStatus _weapon;

	GameController * _input;
	GameObject * _obj;
	GameObject * _colliseObject;
	CollisionComponent* _collisionComponent;
};

#endif //__BEHAVIORCOMPONENT_H__
