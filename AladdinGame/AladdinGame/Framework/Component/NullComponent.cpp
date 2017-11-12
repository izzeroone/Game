#include "NullComponent.h"
void NullPhysicsComponent::init()
{
}

GVector2 NullPhysicsComponent::getPosition()
{
	return GVector2(_bounding.left, _bounding.top);
}

float NullPhysicsComponent::getPositionX()
{
	return _bounding.left;
}

float NullPhysicsComponent::getPositionY()
{
	return _bounding.top;
}

void NullPhysicsComponent::setPosition(GVector3 vector)
{
	_bounding.left = vector.x;
	_bounding.top = vector.y;
}

void NullPhysicsComponent::setPosition(float x, float y, float z)
{
	_bounding.left = x;
	_bounding.top = y;
}

void NullPhysicsComponent::setPosition(GVector2 position)
{
	_bounding.left = position.x;
	_bounding.top = position.y;
}

void NullPhysicsComponent::setPosition(float x, float y)
{
	_bounding.left = x;
	_bounding.top = y;
}

void NullPhysicsComponent::setPositionX(float x)
{
	_bounding.left = x;
}

void NullPhysicsComponent::setPositionY(float y)
{
	_bounding.right = y;
}

void NullAnimationComponent::init()
{
}

