#include "TestScene.h"

TestScene::TestScene()
{
	_viewport = new Viewport(0, WINDOW_HEIGHT, WINDOW_WIDTH, WINDOW_HEIGHT);
}

TestScene::~TestScene()
{
	delete _viewport;
	_viewport = nullptr;
}

void TestScene::setViewport(Viewport * viewport)
{
	if (_viewport != viewport)
		_viewport = viewport;
}

void TestScene::moveViewport(float offset, bool moveup, sigcxx::SLOT slot)
{
	GVector2 position = _viewport->getPositionWorld();
	if (moveup == true)
	{
		position.y += offset;
		_updateViewport = false;
	}
	else
	{
		position.y -= offset;
		_updateViewport = true;
	}
	_viewport->setPositionWorld(position);
}

bool TestScene::init()
{

	_Aladdin = ObjectFactory::getAladdin();
	_Aladdin->getPhysicsComponent()->setPosition(100, 200);
	auto aladdinBehavior = (AladdinBehaviorComponent*)_Aladdin->getBehaviorComponent();
	aladdinBehavior->setRespawnPosition(GVector2(100, 200));
	aladdinBehavior->move_viewport.Connect(this, &TestScene::moveViewport);

	_listobject.push_back(_Aladdin);

	map<string, GameObject*>* maptemp = ObjectFactory::getMapObjectFromFile("Resources//Maps//stage1.xml");
	_mapobject.insert(maptemp->begin(), maptemp->end());

	for (auto it = _mapobject.begin(); it != _mapobject.end(); it++)
	{
		_listobject.push_back(it->second);
	}


	_mapBack = SpriteResource::getInstance()->getSprite(eObjectID::MAP1);
	_mapBack->setFrameRect(SpriteResource::getInstance()->getSourceRect(eObjectID::MAP1, "back"));
	_mapBack->setPositionX(0);
	_mapBack->setPositionY(0);
	_mapBack->setOrigin(GVector2(0.f, 0.f));
	_mapBack->setScale(SCALE_FACTOR);
	_mapBack->setZIndex(0.f);

	_mapFront = SpriteResource::getInstance()->getSprite(eObjectID::MAP1);
	_mapFront->setFrameRect(SpriteResource::getInstance()->getSourceRect(eObjectID::MAP1, "front"));
	_mapFront->setPositionX(0);
	_mapFront->setPositionY(0);
	_mapFront->setOrigin(GVector2(0.f, 0.f));
	_mapFront->setScale(SCALE_FACTOR);
	_mapFront->setZIndex(0.f);


	_updateViewport = true;
	//SoundManager::getInstance()->PlayLoop(eSoundId::BACKGROUND_STAGE1);
	return true;
}


void TestScene::update(float dt)
{
	updateViewport(_Aladdin, dt);
	_active_object.clear();
	_active_object.push_back(_Aladdin);
	for (GameObject* obj : _active_object)
	{
		obj->update(dt);
	}
	GVector2 viewport_position = _viewport->getPositionWorld();
	RECT viewport_in_transform = _viewport->getBounding();

	RECT screen;
	// left right không đổi dù hệ top-left hay hệ bot-left
	screen.left = viewport_in_transform.left;
	screen.right = viewport_in_transform.right;
	screen.top = this->_mapFront->getTextureHeight() - viewport_position.y;
	screen.bottom = screen.top + _viewport->getHeight();
	// getlistobject

	// [Bước 1]
	this->destroyobject();

	// [Bước 2]
	_active_object.clear();


	// [Bước 5]
	_active_object.insert(_active_object.end(), _listobject.begin(), _listobject.end());

	// [Bước 6]
	for (GameObject* obj : _active_object)
	{
		// một vài trạng thái không cần thiết phải check hàm va chạm
		if (obj == nullptr  || obj->getID() == eObjectID::LAND || obj->getID() == eObjectID::ROPE)
			continue;

		for (GameObject* passiveobj : _active_object)
		{
			if (passiveobj == nullptr || passiveobj == obj)
				continue;
			auto collisionComponent = (CollisionComponent*)obj->getPhysicsComponent()->getComponent("Collision");
			if (collisionComponent != nullptr)
			{
				if (passiveobj->getID() != eObjectID::ROPE) // aladdin can overlap rope so don't update target postion. Let aladdin behavior do it instead
					collisionComponent->checkCollision(passiveobj, dt);
				else
					collisionComponent->checkCollision(passiveobj, dt, false);
			}
			
		}
	}
}

void TestScene::draw(LPD3DXSPRITE spriteHandle)
{
	_mapBack->render(spriteHandle, _viewport);
	for (GameObject* object : _active_object)
	{
		object->draw(spriteHandle, _viewport);
	}
	_mapFront->render(spriteHandle, _viewport);
}

void TestScene::release()
{
}


GameObject * TestScene::getObject(eObjectID id)
{
	if (id == eObjectID::ALADDIN)
		return getAladdin();
	eObjectID objectID;
	if (_active_object.size() == 0)
	{
		return nullptr;
	}
	for (GameObject* object : _active_object)
	{
		objectID = object->getID();
		if (objectID == id)
			return object;
	}
	return nullptr;
}

GameObject * TestScene::getAladdin()
{
	return _Aladdin;
}

void TestScene::destroyobject()
{
}

void TestScene::updateViewport(GameObject * objTracker, float deltatime)
{
	if (_updateViewport == false)
	{
		return;
	}
	// Vị trí hiện tại của viewport. 
	GVector2 current_position = _viewport->getPositionWorld();
	GVector2 worldsize;
	worldsize.x = _mapBack->getTextureWidth();
	worldsize.y = _mapBack->getTextureHeight();
	// Bám theo object.
	GVector2 new_position;
	float trackerX = max(objTracker->getPhysicsComponent()->getPositionX() - 260, 0);
	float trackerY = max(objTracker->getPhysicsComponent()->getPositionY() + 300, WINDOW_HEIGHT);
	new_position.x = trackerX;
	new_position.y = trackerY;
	//if (trackerX > current_position.x + deltatime / 1000 * VIEWPORT_VELOCITY)
	//{
	//	new_position.x = current_position.x + deltatime / 1000 * VIEWPORT_VELOCITY;
	//}
	//else if (trackerX < current_position.x - deltatime / 1000 * VIEWPORT_VELOCITY)
	//{
	//	new_position.x = current_position.x - deltatime / 1000 * VIEWPORT_VELOCITY;
	//}
	//else
	//{
	//	new_position.x = current_position.x;
	//}

	//if (trackerY > current_position.y + deltatime / 1000 * VIEWPORT_VELOCITY)
	//{
	//	new_position.y = current_position.y + deltatime / 1000 * VIEWPORT_VELOCITY;
	//}
	//else if (trackerY < current_position.y - deltatime / 1000 * VIEWPORT_VELOCITY)
	//{
	//	new_position.y = current_position.y - deltatime / 1000 * VIEWPORT_VELOCITY;
	//}
	//else
	//{
	//	new_position.y = current_position.y;
	//}


	// Không cho đi quá map.
	if (new_position.x + WINDOW_WIDTH > worldsize.x)
	{
		new_position.x = worldsize.x - WINDOW_WIDTH;
	}

	_viewport->setPositionWorld(new_position);
}

void TestScene::updateInput(float dt)
{

}
