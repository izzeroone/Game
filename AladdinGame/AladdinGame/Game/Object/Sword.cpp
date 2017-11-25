#include "Sword.h"

void SwordPhysicsComponent::init()
{
	_componentList["Collision"] = new CollisionComponent();
}

void SwordBehaviorComponent::init()
{
	_livingTime = 0;
}

void SwordBehaviorComponent::update(float detatime)
{
	_livingTime += detatime;
	if (detatime >= LIVING_TIME)
	{
		setStatus(eStatus::DESTROY);
		return;
	}

	auto collisionComponent = (CollisionComponent*)_physicsComponent->getComponent("Collision");
	auto isEnemyFunc = [](GameObject* obj) {
		auto id = obj->getID();
		return id == eObjectID::HAKIM;
	};
	GameObject * obj = collisionComponent->isColliding(isEnemyFunc);
	if (obj != nullptr)
	{
		auto it = std::find(_slashObject.begin(), _slashObject.end(), obj);
		if (it == _slashObject.end() || it._Ptr == nullptr)
		{
			((EnemyBehaviorComponent*)obj->getBehaviorComponent())->dropHitpoint(20);
			_slashObject.push_back(obj);
		}
	}

	obj = collisionComponent->isColliding(eObjectID::ALADDIN);
	if (obj != nullptr)
	{
		auto it = std::find(_slashObject.begin(), _slashObject.end(), obj);
		if (it == _slashObject.end() || it._Ptr == nullptr)
		{
			((PlayerBehaviorComponent*)obj->getBehaviorComponent())->dropHitpoint(20);
			_slashObject.push_back(obj);
		}
	}
}


void Sword::init(int x, int y, int width, int height, eDirection side)
{
	GameObject::init();
	_id = eObjectID::SWORD;
	// X là left. Y là top
	RECT bounding;
	bounding.top = y;
	bounding.left = x;
	bounding.bottom = y - height;
	bounding.right = x + width;
	_physicsComponent->setBounding(bounding);
	_physicsComponent->setPhysicsBodySide(side);
}

Sword::Sword()
{
}

Sword::~Sword()
{
}
