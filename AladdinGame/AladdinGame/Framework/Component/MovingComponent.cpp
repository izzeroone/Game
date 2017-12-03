#include "MovingComponent.h"
#include "PhysicsComponent.h"
#include "../../debug.h"

#pragma region Movement
Movement::Movement(GVector2 accel, GVector2 veloc, PhysicsComponent* physicsComponent )
{
	this->_accelerate = accel;
	this->_velocity = veloc;
	this->_physicsComponent = physicsComponent;
	_addPos = VECTOR2ZERO;
	_doNotMove = false;

}
void Movement::update(float deltatime)
{
	if (_physicsComponent == NULL)
		return;

	auto position = _physicsComponent->getPosition();
	this->_velocity += this->_accelerate * deltatime / 1000;
	if (_addPos != VECTOR2ZERO)
	{
		position += _addPos;
		_addPos = VECTOR2ZERO;
	}
	if (_doNotMove == true)
		_doNotMove = false;
	else
		position += this->_velocity * deltatime / 1000;
	
	this->_physicsComponent->setPosition(position);

	
}
void Movement::setAccelerate(GVector2 accel)
{
	this->_accelerate = accel;
}
void Movement::setVelocity(GVector2 veloc)
{
	this->_velocity = veloc;
}
GVector2 Movement::getAccelerate()
{
	return this->_accelerate;
}

GVector2 Movement::getVelocity()
{
	return this->_velocity;
}

void Movement::setAddPos(GVector2 addPos)
{
	_addPos += addPos;
}

void Movement::setDoNotMove(bool result)
{
	_doNotMove = result;
}

void Movement::init()
{
}
#pragma endregion

#pragma region Gravity
void Gravity::update(float deltatime)
{
	switch (_status)
	{
	case FALLING__DOWN:
		this->_additionalVeloc = this->_gravity * deltatime / 1000;
		break;
	case LANDED:
		this->_additionalVeloc = VECTOR2ZERO;
	default:
		break;
	}
	auto veloc = this->_refmovement->getVelocity();
	this->_refmovement->setVelocity(veloc + _additionalVeloc);
}

void Gravity::setStatus(eGravityStatus status)
{
	this->_status = status;
}
void Gravity::setGravity(GVector2 gravity)
{
	this->_gravity = gravity;
}
void Gravity::init()
{
}
Gravity::Gravity(GVector2 gravity, Movement *movement)
{
	this->_gravity = gravity;
	this->_refmovement = movement;
	this->_status = FALLING__DOWN;
}
#pragma endregion

