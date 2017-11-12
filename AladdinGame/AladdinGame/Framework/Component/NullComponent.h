#pragma once
#ifndef __NULLCOMPONENT_H__
#define __NULLCOMPONENT_H__
#include "../define.h"
#include "PhysicsComponent.h"
#include "AnimationComponent.h"
#include "BehaviorComponent.h"

class NullPhysicsComponent: public PhysicsComponent
{
	// Inherited via PhysicsComponent
	virtual void init() override;
	GVector2 getPosition();
	float getPositionX();
	float getPositionY();
	void setPosition(GVector3 vector);
	void setPosition(float x, float y, float z);
	void setPosition(GVector2 position);
	void setPosition(float x, float y);
	void setPositionX(float x);
	void setPositionY(float y);
};



class NullAnimationComponent : public AnimationComponent
{
	// Inherited via AnimationComponent
	virtual void init() override;
};
#endif // !__NULLCOMPONENT_H__
