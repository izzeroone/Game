﻿#pragma once
#include "../define.h"
#include "Component.h"
#include "MovingComponent.h"
class PhysicsComponent: public Component
{
public:

	PhysicsComponent();
	~PhysicsComponent();

	virtual GVector2 getPosition();
	virtual float getPositionX();
	virtual float getPositionY();

	virtual void setPosition(GVector3 vector);
	virtual void setPosition(float x, float y, float z);
	virtual void setPosition(GVector2 position);
	virtual void setPosition(float x, float y);
	virtual void setPositionX(float x);
	virtual void setPositionY(float y);

	virtual void setZIndex(float z);
	virtual float getZIndex();

	void update(float deltatime);
	void addMovingComponent(string name, MovingComponent *movingComponent);
	void removeMovingComponent(string name, MovingComponent *movingComponent);

	virtual GVector2 getVelocity();

	virtual void setPhysicsBodySide(eDirection side);
	virtual eDirection getPhysicsBodySide();


protected:
	GVector2			_position;
	float				_zIndex;
	map<string, MovingComponent*> _componentList;
	eDirection _physicsSide;

};
