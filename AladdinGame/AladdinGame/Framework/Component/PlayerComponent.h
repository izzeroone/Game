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
	virtual bool dropHitpoint(); // drop complete = true, is invisible = false
	virtual bool dropHitpoint(int damage);
protected:
	int _hitpoint;
	int _life;
};
#endif // !__PLAYERCOMPONENT_H__
