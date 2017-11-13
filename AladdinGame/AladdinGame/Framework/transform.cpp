#include "Transform.h"

Transform::Transform()
{
	_scale = GVector2(1.0f, 1.0f);
}

Transform::~Transform()
{
}

GVector2 Transform::getPosition()
{
	return _position;
}

float Transform::getPositionX()
{
	return _position.x;
}

float Transform::getPositionY()
{
	return _position.y;
}

void Transform::setPosition(float x, float y, float z)
{
	GVector3 v(x, y, z);
	this->setPosition(v);
}

void Transform::setPosition(GVector3 vector)
{
	this->_position = GVector2(vector.x, vector.y);
}

void Transform::setPosition(GVector2 position)
{
	this->_position = GVector2(position.x, position.y);
}

void Transform::setPosition(float x, float y)
{
	this->setPositionX(x);
	this->setPositionY(y);
}

void Transform::setPositionX(float x)
{
	if (x != _position.x)
		_position.x = x;
}

void Transform::setPositionY(float y)
{
	if (y != _position.y)
		_position.y = y;
}


GVector2 Transform::getTranslate()
{
	return _translate;
}

float Transform::getTranslateX()
{
	return _translate.x;
}

float Transform::getTranslateY()
{
	return _translate.y;
}

void Transform::setTranslate(float x, float y, float z)
{
	GVector3 v(x, y, z);
	this->setTranslate(v);
}

void Transform::setTranslate(GVector3 vector)
{
	this->_translate = GVector2(vector.x, vector.y);
}

void Transform::setTranslate(GVector2 Translate)
{
	this->_translate = GVector2(Translate.x, Translate.y);
}

void Transform::setTranslate(float x, float y)
{
	this->setTranslateX(x);
	this->setTranslateY(y);
}

void Transform::setTranslateX(float x)
{
	if (x != _translate.x)
		_translate.x = x;
}

void Transform::setTranslateY(float y)
{
	if (y != _translate.y)
		_translate.y = y;
}
GVector2 Transform::getScale()
{
	return _scale;
}

void Transform::setScale(GVector2 scale)
{
	if (scale == _scale)
		return;

	_scale = scale;
}

void Transform::setScale(float scale)
{
	if (scale != _scale.x || scale != _scale.y)
	{
		_scale.x = scale;
		_scale.y = scale;
	}
}

void Transform::setScaleX(float sx)
{
	if (sx != _scale.x)
		_scale.x = sx;
}

void Transform::setScaleY(float sy)
{
	if (sy != _scale.y)
		_scale.y = sy;
}

float Transform::getRotate()
{
	return _rotate;
}

void Transform::setRotate(float degree)
{
	if (degree == _rotate)
		return;

	_rotate = degree;
}

GVector2 Transform::getOrigin()
{
	return _origin;
}

void Transform::setOrigin(GVector2 origin)
{
	if (origin != _origin)
		_origin = origin;
}

void Transform::setZIndex(float z)
{
	if (z != _zIndex)
		_zIndex = z;
}

float Transform::getZIndex()
{
	return _zIndex;
}

GVector2 Transform::getAnchorPoint()
{
	return _anchorPoint;
}
