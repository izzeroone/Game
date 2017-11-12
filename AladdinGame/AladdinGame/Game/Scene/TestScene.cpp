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

bool TestScene::init()
{

	auto Aladdin = ObjectFactory::getAladdin();
	Aladdin->getPhysicsComponent()->setPosition(300, 200);

	this->_Aladdin = Aladdin;
	_listobject.push_back(Aladdin);
	
	_map = SpriteResource::getInstance()->getSprite(eObjectID::MAP1);
	_map->setFrameRect(0.0f, _map->getFrameWidth(), (float)_map->getFrameHeight(), 0.0f);
	_map->setPositionX(_map->getFrameWidth());
	_map->setPositionY(_map->getFrameHeight());
	_map->setScale(2.0f);

	//SoundManager::getInstance()->PlayLoop(eSoundId::BACKGROUND_STAGE1);
	return true;
}


void TestScene::update(float dt)
{
	updateViewport(_Aladdin);
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
	screen.top = this->_map->getTextureHeight() - viewport_position.y;
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
		if (obj == nullptr  || obj->getID() == eObjectID::LAND)
			continue;

		for (GameObject* passiveobj : _active_object)
		{
			if (passiveobj == nullptr || passiveobj == obj)
				continue;
			auto collisionComponent = (CollisionComponent*)obj->getPhysicsComponent()->getComponent("Collision");
			if (collisionComponent != nullptr)
			{
				collisionComponent->checkCollision(passiveobj, dt);
			}
			
		}
	}
}

void TestScene::draw(LPD3DXSPRITE spriteHandle)
{
	_map->render(spriteHandle, _viewport);
	for (GameObject* object : _active_object)
	{
		object->draw(spriteHandle, _viewport);
	}
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

void TestScene::updateViewport(GameObject * objTracker)
{
	// Vị trí hiện tại của viewport. 
	GVector2 current_position = _viewport->getPositionWorld();
	GVector2 worldsize;
	worldsize.x = _map->getTextureWidth();
	worldsize.y = _map->getTextureHeight();
	// Bám theo object.
	GVector2 new_position = GVector2(max(objTracker->getPhysicsComponent()->getPositionX() - 260, 0), WINDOW_HEIGHT);		// 200 khoảng cách tối đa giữa object và map -> hardcode

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
