#pragma once
#ifndef __PHYSICSCOMPONENT_H__
#define __PHYSICSCOMPONENT_H__
#include "../define.h"
#include "Component.h"

//forward declarations
class MovingComponent;

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

	virtual void update(float deltatime);
	virtual void addMovingComponent(string name, MovingComponent* movingComponent);
	virtual void removeMovingComponent(string name, MovingComponent* movingComponent);
	virtual MovingComponent* getMovingComponent(string name);

	virtual GVector2 getVelocity();

	virtual int getMovingSpeed();
	virtual void setMovingSpeed(int movingSpeed);

	virtual void setPhysicsBodySide(eDirection side);
	virtual eDirection getPhysicsBodySide();


protected:
	int					_movingSpeed;
	GVector2			_position;
	float				_zIndex;
	map<string, MovingComponent*> _componentList;
	eDirection _physicsSide;

};
#endif // !__PHYSICSCOMPONENT_H__
