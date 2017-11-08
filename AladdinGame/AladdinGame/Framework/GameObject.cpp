
#include "GameObject.h"

IControlable::IControlable()
{
	_input = GameController::getInstance();
}

GameObject::GameObject(eObjectID id)
{
	this->_id = id;
	this->setStatus(eStatus::NORMAL);
}

GameObject::~GameObject()
{
}

eObjectID GameObject::getId()
{
	return this->_id;
}

eStatus GameObject::getStatus()
{
	return this->_status;
}

void GameObject::setStatus(eStatus status)
{
	if (_status != status)
		_status = status;
}

void GameObject::addStatus(eStatus status)
{
	this->setStatus(eStatus(this->getStatus() | status));
}

void GameObject::removeStatus(eStatus status)
{
	this->setStatus(eStatus(this->getStatus() & ~status));
}

bool GameObject::isInStatus(eStatus status)
{
	return (this->getStatus() & status) == status;
}

GVector2 GameObject::getPosition()
{
	return _sprite->getPosition();
}

float GameObject::getPositionX()
{
	return _sprite->getPositionX();
}

float GameObject::getPositionY()
{
	return _sprite->getPositionY();
}

void GameObject::setPosition(GVector3 vector)
{
	_sprite->setPosition(vector);
}

void GameObject::setPosition(float x, float y, float z)
{
	_sprite->setPosition(x, y, z);
}

void GameObject::setPosition(GVector2 position)
{
	_sprite->setPosition(position);
}

void GameObject::setPosition(float x, float y)
{
	_sprite->setPosition(x, y);
}

void GameObject::setPositionX(float x)
{
	_sprite->setPositionX(x);
}

void GameObject::setPositionY(float y)
{
	_sprite->setPositionY(y);
}

GVector2 GameObject::getScale()
{
	return _sprite->getScale();
}

void GameObject::setScale(GVector2 scale)
{
	_sprite->setScale(scale);
}

void GameObject::setScale(float scale)
{
	_sprite->setScale(scale);
}

void GameObject::setScaleX(float sx)
{
	_sprite->setScaleX(sx);
}

void GameObject::setScaleY(float sy)
{
	_sprite->setScaleY(sy);
}

GVector2 GameObject::getOrigin()
{
	return _sprite->getOrigin();
}

void GameObject::setOrigin(GVector2 origin)
{
	_sprite->setOrigin(origin);
}

float GameObject::getRotate()
{
	return _sprite->getRotate();
}

void GameObject::setRotate(float degree)
{
	_sprite->setRotate(degree);
}

void GameObject::setZIndex(float z)
{
	_sprite->setZIndex(z);
}

float GameObject::getZIndex()
{
	return _sprite->getZIndex();
}

void GameObject::setOpacity(float opacity)
{
	_sprite->setOpacity(opacity);
}

float GameObject::getOpacity()
{
	return _sprite->getOpacity();
}

void GameObject::setColor(D3DXCOLOR color)
{
	_sprite->setColor(color);
}

D3DXCOLOR GameObject::getColor()
{
	return _sprite->getColor();
}

GVector2 GameObject::getAnchorPoint()
{
	return _sprite->getAnchorPoint();
}

Sprite * GameObject::getSprite()
{
	return _sprite;
}

RECT GameObject::getBounding()
{
	return _sprite->getBounding();
}

float GameObject::checkCollision(GameObject * object, float dt)
{
	return 0.0f;
}

GVector2 GameObject::getVelocity()
{
	return GVector2(0, 0);
}

void GameObject::setPhysicsBodySide(eDirection side)
{
	if (side != _physicsSide)
		_physicsSide = side;
}

eDirection GameObject::getPhysicsBodySide()
{
	return _physicsSide;
}
