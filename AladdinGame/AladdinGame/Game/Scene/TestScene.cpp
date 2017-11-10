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

	auto bill = new Aladdin(3);
	bill->init();
	bill->setPosition(100, 200);

	//InputController::getInstance()->keyPressedSig().Connect(bill, &Aladdin::onKeyPressed);

	this->_bill = bill;
	_listControlObject.push_back(bill);
	_listobject.push_back(bill);
	
	_map = SpriteManager::getInstance()->getSprite(eID::MAP1);
	_map->setFrameRect(0.0f, _map->getFrameWidth(), (float)_map->getFrameHeight(), 0.0f);
	_map->setPositionX(_map->getFrameWidth());
	_map->setPositionY(_map->getFrameHeight());
	_map->setScale(2.0f);

	//SoundManager::getInstance()->PlayLoop(eSoundId::BACKGROUND_STAGE1);

	auto land = new Land(0, 75, 3000, 5, eDirection::TOP, eLandType::GRASS);
	_listobject.push_back(land);

	auto rope = new Rope(464, 500, 5, 350, eDirection::ALL, eRopeType::HORIZONTAL);
	_listobject.push_back(rope);
	return true;
}

void TestScene::updateInput(float dt)
{
	for (IControlable* obj : _listControlObject)
	{
		obj->updateInput(dt);
	}
}

void TestScene::update(float dt)
{
	if (_bill->isInStatus(eStatus::DYING) == false)
	{
		this->updateViewport(_bill);
	}
	_active_object.clear();
	_active_object.push_back(_bill);
	for (BaseObject* obj : _active_object)
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
	for (BaseObject* obj : _active_object)
	{
		// một vài trạng thái không cần thiết phải check hàm va chạm
		if (obj == nullptr || obj->isInStatus(eStatus::DESTROY) || obj->getId() == eID::LAND || obj->getId() == eID::ROPE)
			continue;

		for (BaseObject* passiveobj : _active_object)
		{
			if (passiveobj == nullptr || passiveobj == obj || passiveobj->isInStatus(eStatus::DESTROY))
				continue;

			obj->checkCollision(passiveobj, dt);
		}
	}

}

void TestScene::draw(LPD3DXSPRITE spriteHandle)
{
	_map->render(spriteHandle, _viewport);
	for (BaseObject* object : _active_object)
	{
		object->draw(spriteHandle, _viewport);
	}
}

void TestScene::release()
{
}


BaseObject * TestScene::getObject(eID id)
{
	if (id == eID::ALADDIN)
		return getAladdin();
	eID objectID;
	if (_active_object.size() == 0)
	{
		return nullptr;
	}
	for (BaseObject* object : _active_object)
	{
		objectID = object->getId();
		if (objectID == id)
			return object;
	}
	return nullptr;
}

Aladdin * TestScene::getAladdin()
{
	return (Aladdin*)_bill;
}

void TestScene::destroyobject()
{
}

void TestScene::updateViewport(BaseObject * objTracker)
{
	// Vị trí hiện tại của viewport. 
	GVector2 current_position = _viewport->getPositionWorld();
	GVector2 worldsize;
	worldsize.x = _map->getTextureWidth();
	worldsize.y = _map->getTextureHeight();
	// Bám theo object.
	GVector2 new_position = GVector2(max(objTracker->getPositionX() - 260, 0), WINDOW_HEIGHT);		// 200 khoảng cách tối đa giữa object và map -> hardcode

	// Không cho đi quá map.
	if (new_position.x + WINDOW_WIDTH > worldsize.x)
	{
		new_position.x = worldsize.x - WINDOW_WIDTH;
	}

	_viewport->setPositionWorld(new_position);
}
