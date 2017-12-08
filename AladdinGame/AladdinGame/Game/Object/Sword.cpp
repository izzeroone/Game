#include "Sword.h"

void SwordPhysicsComponent::init()
{

}

void SwordBehaviorComponent::init()
{
	_canSlashEnemy = false;
	_livingTime = 0;
	_collisionComponent = new CollisionComponent(eDirection::ALL);
	_collisionComponent->setTargerGameObject(_obj);
}

void SwordBehaviorComponent::update(float detatime)
{
	_livingTime += detatime;
	if (_livingTime >= LIVING_TIME)
	{
		setStatus(eStatus::DESTROY);
		return;
	}
	checkCollision(detatime);
	//auto isEnemyFunc = [](GameObject* obj) {
	//	auto id = obj->getID();
	//	return id == eObjectID::HAKIM || id == eObjectID::NAHBI || id == eObjectID::FALZA;
	//};

	//GameObject * obj;
	//if (_canSlashEnemy)
	//{
	//	obj = _collisionComponent->isColliding(isEnemyFunc);
	//	if (obj != nullptr)
	//	{
	//		auto it = std::find(_slashObject.begin(), _slashObject.end(), obj);
	//		if (it == _slashObject.end() || it._Ptr == nullptr)
	//		{
	//			((EnemyBehaviorComponent*)obj->getBehaviorComponent())->dropHitpoint(10);
	//			_slashObject.push_back(obj);
	//		}
	//	}
	//}
	//else
	//{
	//	obj = _collisionComponent->isColliding(eObjectID::ALADDIN);
	//	if (obj != nullptr)
	//	{
	//		auto it = std::find(_slashObject.begin(), _slashObject.end(), obj);
	//		if (it == _slashObject.end() || it._Ptr == nullptr)
	//		{
	//			((PlayerBehaviorComponent*)obj->getBehaviorComponent())->dropHitpoint(10);
	//			_slashObject.push_back(obj);
	//		}
	//	}
	//}
}

void SwordBehaviorComponent::canSlashEnemy(bool result)
{
	_canSlashEnemy = result;
}

void SwordBehaviorComponent::checkCollision(float deltatime)
{
	auto active_object = SceneManager::getInstance()->getCurrentScene()->getActiveObject();
	_collisionComponent->reset();
	for (auto obj : active_object)
	{
		eObjectID id = obj->getID();
		if (_canSlashEnemy)
		{
			switch (id)
			{
			case HAKIM: case NAHBI: case FALZA:
				auto it = std::find(_slashObject.begin(), _slashObject.end(), obj);
				if (it == _slashObject.end() || it._Ptr == nullptr)
				{
					((EnemyBehaviorComponent*)obj->getBehaviorComponent())->dropHitpoint(10);
					_slashObject.push_back(obj);
				}
				break;

			}
		}
		else
		{
			switch (id)
			{
			case ALADDIN:
				auto it = std::find(_slashObject.begin(), _slashObject.end(), obj);
				if (it == _slashObject.end() || it._Ptr == nullptr)
				{
					((PlayerBehaviorComponent*)obj->getBehaviorComponent())->dropHitpoint(10);
					_slashObject.push_back(obj);
				}
				break;
			}
		}
	}
}


void Sword::init(int x, int y, int width, int height, eDirection side, bool canSlashEnemy)
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
	((SwordBehaviorComponent*)(_behaviorComponent))->canSlashEnemy(canSlashEnemy);
}

Sword::Sword()
{
}

Sword::~Sword()
{
}
