
#include "GameObject.h"



GameObject::GameObject()
{
}

GameObject::GameObject(eObjectID eid, AnimationComponent * animationComponent, BehaviorComponent * behaviorComponent, PhysicsComponent * physicsComponent)
{
	_id = eid;
	_animationComponent = animationComponent;
	_behaviorComponent = behaviorComponent;
	_physicsComponent = physicsComponent;
}

GameObject::~GameObject()
{
}

void GameObject::init()
{
	if (_physicsComponent != nullptr)
	{
		_physicsComponent->init();
	}
	if (_animationComponent != nullptr)
	{
		_animationComponent->init();
	}
	if (_behaviorComponent != nullptr)
	{
		_behaviorComponent->init();
	}
}

void GameObject::update(float deltatime)
{
	if (_physicsComponent != nullptr)
	{
		_physicsComponent->update(deltatime);
	}
	if (_animationComponent != nullptr)
	{
		_animationComponent->update(deltatime);
	}
	if (_behaviorComponent != nullptr)
	{
		_behaviorComponent->update(deltatime);
	}
}

void GameObject::draw(LPD3DXSPRITE spriteHandle, Viewport *viewport)
{
	if (_animationComponent != nullptr)
	{
		_animationComponent->draw(spriteHandle, viewport);
	}
}


void GameObject::release()
{
	SAFE_DELETE(_behaviorComponent)
	SAFE_DELETE(_physicsComponent)
	SAFE_DELETE(_animationComponent)
}

AnimationComponent * GameObject::getAnimationComponent()
{
	return _animationComponent;
}

void GameObject::setAnimationComponent(AnimationComponent * animationComponent)
{
	_animationComponent = animationComponent;
}

PhysicsComponent * GameObject::getPhysicsComponent()
{
	return  _physicsComponent;
}

void GameObject::setPhysicsComponent(PhysicsComponent * PhysicsComponent)
{
	_physicsComponent = PhysicsComponent;
}

BehaviorComponent * GameObject::getBehaviorComponent()
{
	return _behaviorComponent;
}

void GameObject::setBehaviorComponent(BehaviorComponent * BehaviorComponent)
{
	_behaviorComponent = BehaviorComponent;
}

eObjectID GameObject::getID()
{
	return this->_id;
}

void GameObject::setID(eObjectID eid)
{
	_id = eid;
}
