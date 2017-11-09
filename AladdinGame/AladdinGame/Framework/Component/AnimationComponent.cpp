#include "AnimationComponent.h"

AnimationComponent::AnimationComponent()
{
}

AnimationComponent::AnimationComponent(PhysicsComponent * physicsComponent)
{
	_physicsComponent = physicsComponent;
}


AnimationComponent::~AnimationComponent()
{
}

void AnimationComponent::update(float deltatime)
{
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
	_preindex = _index;
	_animations[_index]->restart();
	_index = status;
}

void AnimationComponent::draw(Viewport * viewport)
{
	_animations[_index]->setPosition(_physicsComponent->getPosition());
	_animations[_index]->draw(_spriteHandle, viewport);
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

void AnimationComponent::setOpacity(float opacity)
{
	_sprite->setOpacity(opacity);
}

float AnimationComponent::getOpacity()
{
	return _sprite->getOpacity();
}

void AnimationComponent::setSpriteHandle(LPD3DXSPRITE spriteHandle)
{
	_spriteHandle = spriteHandle;
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
	return _sprite->getBounding();
}

