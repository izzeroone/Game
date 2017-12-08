#include "AnimationComponent.h"
#include "PhysicsComponent.h"
#include "../GameObject.h"
AnimationComponent::AnimationComponent()
{
	_transitionPlayed = true;
	_tempIndex = -1;
}

AnimationComponent::AnimationComponent(GameObject * gameObject)
{
	_transitionPlayed = true;
	_obj = gameObject;
	_tempIndex = -1;
}


AnimationComponent::~AnimationComponent()
{
}

void AnimationComponent::update(float deltatime)
{
	_sprite->setPosition(_obj->getPhysicsComponent()->getPosition());

	if (updateTempAnimation(deltatime) == true)
		return;
	if (_transition[_preindex][_index] != nullptr)
	{
		if (_transition[_preindex][_index]->getCount() < 1)
		{
			_transition[_preindex][_index]->update(deltatime);
			return;
		}
		else
		{
			_transitionPlayed = true;
		}
	}
	if (_animations[_index] != nullptr)
	{
		_animations[_index]->update(deltatime);
	}
}

Animation * AnimationComponent::getCurrentAnimation()
{
	return _animations[_index];
}

void AnimationComponent::setAnimation(int status)
{
	if (_index != status)
	{
		_preindex = _index;
		if(_animations[_index] != nullptr)
			_animations[_index]->restart();
		_index = status;
		if (_transition[_preindex][_index] != nullptr)
		{
			_transition[_preindex][_index]->restart();
		}
		_transitionPlayed = false;
	}
}

void AnimationComponent::setAnimationNoRestart(int status)
{
	if (_index != status)
	{
		_preindex = _index;
		_index = status;
		if (_transition[_preindex][_index] != nullptr)
		{
			_transition[_preindex][_index]->restart();
		}
		_transitionPlayed = false;
	}
}

void AnimationComponent::setTempAnimation(int status, int count)
{

	//if (_tempIndex != -1)
	//	return;

	if (_tempIndex == status)
		return;

	_tempIndex = status;
	_tempCount = count;
	_animations[_tempIndex]->restart();
}

bool AnimationComponent::isTempAnimationEmpty()
{
	return _tempIndex == -1 || _animations[_tempIndex]->getCount() >= _tempCount;
}

bool AnimationComponent::updateTempAnimation(float deltatime)
{
	if (_tempIndex == -1)
		return false;
	
	if (_animations[_tempIndex]->getCount() >= _tempCount)
	{
		_tempIndex = -1;
		return false;
	}

	_animations[_tempIndex]->update(deltatime);
	return true;
}

bool AnimationComponent::drawTempAnimation(LPD3DXSPRITE spriteHandle, Viewport * viewport)
{
	if (_tempIndex == -1)
		return false;

	if (_animations[_tempIndex]->getCount() >= _tempCount)
	{
		_tempIndex = -1;
		return false;
	}
	
	_animations[_tempIndex]->draw(spriteHandle, viewport);
	return true;
}

Animation * AnimationComponent::getAnimation(int status)
{
	return _animations[status];
}

int AnimationComponent::getAnimationStatus()
{
	return _index;
}

void AnimationComponent::draw(LPD3DXSPRITE spriteHandle, Viewport * viewport)
{
	if (drawTempAnimation(spriteHandle, viewport) == true)
		return;

	if (_transitionPlayed == false && _transition[_preindex][_index] != nullptr)
	{
		_transition[_preindex][_index]->draw(spriteHandle, viewport);
	}
	else
	{
		_animations[_index]->draw(spriteHandle, viewport);
	}
}

GVector2 AnimationComponent::getScale()
{
	return _sprite->getScale();
}

void AnimationComponent::setScale(GVector2 scale)
{
	_sprite->setScale(scale);
}

void AnimationComponent::setScale(float scale)
{
	_sprite->setScale(scale);
}

void AnimationComponent::setScaleX(float sx)
{
	_sprite->setScaleX(sx);
}

void AnimationComponent::setScaleY(float sy)
{
	_sprite->setScaleY(sy);
}

GVector2 AnimationComponent::getTranslate()
{
	return _sprite->getTranslate();
}

void AnimationComponent::setTranslate(GVector2 Translate)
{
	_sprite->setTranslate(Translate);
}

void AnimationComponent::setTranslate(float Translate)
{
	_sprite->setTranslate(GVector2(Translate, Translate));
}

void AnimationComponent::setTranslateX(float sx)
{
	_sprite->setTranslateX(sx);
}

void AnimationComponent::setTranslateY(float sy)
{
	_sprite->setTranslateY(sy);
}
GVector2 AnimationComponent::getOrigin()
{
	return _sprite->getOrigin();
}

void AnimationComponent::setOrigin(GVector2 origin)
{
	_sprite->setOrigin(origin);
}

float AnimationComponent::getRotate()
{
	return _sprite->getRotate();
}

void AnimationComponent::setRotate(float degree)
{
	_sprite->setRotate(degree);
}

void AnimationComponent::setZIndex(float z)
{
	_sprite->setZIndex(z);
}

float AnimationComponent::getZIndex()
{
	return _sprite->getZIndex();
}

void AnimationComponent::setGameObject(GameObject * gameObject)
{
	_obj = gameObject;
}

void AnimationComponent::setOpacity(float opacity)
{
	_sprite->setOpacity(opacity);
}

float AnimationComponent::getOpacity()
{
	return _sprite->getOpacity();
}



void AnimationComponent::setColor(D3DXCOLOR color)
{
	_sprite->setColor(color);
}

D3DXCOLOR AnimationComponent::getColor()
{
	return _sprite->getColor();
}

GVector2 AnimationComponent::getAnchorPoint()
{
	return _sprite->getAnchorPoint();
}

Sprite * AnimationComponent::getSprite()
{
	return _sprite;
}

RECT AnimationComponent::getBounding()
{
	_sprite->setPosition(_obj->getPhysicsComponent()->getPosition());
	RECT newRect = _animations[_index]->getCurrentBounding();
	RECT oldRect = _sprite->getFrameRect();
	_sprite->setFrameRect(newRect);
	RECT bound = _sprite->getBounding();
	_sprite->setFrameRect(oldRect);

	return bound;

}

