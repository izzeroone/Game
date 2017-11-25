#pragma once
#ifndef __PLAYERCOMPONENT_H__
#define __PLAYERCOMPONENT_H__
#include "../define.h"
#include "PhysicsComponent.h"
#include "AnimationComponent.h"
#include "BehaviorComponent.h"


class PlayerBehaviorComponent : public BehaviorComponent
{
public:
	virtual int getHitpoint();
	virtual void setHitpoint(int);
	virtual int getLife();
	virtual void setLife(int);
	virtual void dropLife();
	virtual void dropHitpoint();
	virtual void dropHitpoint(int damage);
protected:
	int _hitpoint;
	int _life;
};
#endif // !__PLAYERCOMPONENT_H__
