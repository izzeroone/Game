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

}

void TestScene::draw(LPD3DXSPRITE spriteHandle)
{
	_map->render(spriteHandle, _viewport);
	_Aladdin->draw(spriteHandle, _viewport);
	//for (GameObject* object : _active_object)
	//{
	//	object->draw(spriteHandle, _viewport);
	//}
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
