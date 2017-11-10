#include "PhysicsComponent.h"
#include "MovingComponent.h"
PhysicsComponent::PhysicsComponent()
{
}

PhysicsComponent::~PhysicsComponent()
{
}

GVector2 PhysicsComponent::getPosition()
{
	return _position;
}

float PhysicsComponent::getPositionX()
{
	return _position.x;
}

float PhysicsComponent::getPositionY()
{
	return _position.y;
}

void PhysicsComponent::setPosition(float x, float y, float z)
{
	GVector3 v(x, y, z);
	this->setPosition(v);
}

void PhysicsComponent::setPosition(GVector3 vector)
{
	this->_position = GVector2(vector.x, vector.y);
}

void PhysicsComponent::setPosition(GVector2 position)
{
	this->_position = GVector2(position.x, position.y);
}

void PhysicsComponent::setPosition(float x, float y)
{
	this->setPositionX(x);
	this->setPositionY(y);
}

void PhysicsComponent::setPositionX(float x)
{
	if (x != _position.x)
		_position.x = x;
}

void PhysicsComponent::setPositionY(float y)
{
	if (y != _position.y)
		_position.y = y;
}


void PhysicsComponent::setZIndex(float z)
{
	if (z != _zIndex)
		_zIndex = z;
}

float PhysicsComponent::getZIndex()
{
	return _zIndex;
}

void PhysicsComponent::update(float deltatime)
{
	for (auto it = _componentList.begin(); it != _componentList.end(); it++)
	{
		it->second->update(deltatime);
	}
}

void PhysicsComponent::addMovingComponent(string name, MovingComponent * movingComponent)
{
	_componentList.emplace(name, movingComponent);
}

void PhysicsComponent::removeMovingComponent(string name, MovingComponent * movingComponent)
{
	_componentList.erase(name);
}

MovingComponent * PhysicsComponent::getMovingComponent(string name)
{
	return _componentList[name];
}

GVector2 PhysicsComponent::getVelocity()
{
	return VECTOR2ZERO;
}

int PhysicsComponent::getMovingSpeed()
{
	return _movingSpeed;
}

void PhysicsComponent::setMovingSpeed(int movingSpeed)
{
	_movingSpeed = movingSpeed;
}

void PhysicsComponent::setPhysicsBodySide(eDirection side)
{
	_physicsSide = side;
}

eDirection PhysicsComponent::getPhysicsBodySide()
{
	return _physicsSide;
}
