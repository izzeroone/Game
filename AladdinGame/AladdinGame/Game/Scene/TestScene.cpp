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

void TestScene::writeXMLQuadTree()
{
	_root->writeXML("Resources//Maps//stage1_quadtree.xml");
}

bool TestScene::init()
{

	_Aladdin = ObjectFactory::getAladdin();
	_Aladdin->getPhysicsComponent()->setPosition(2000, 1000);

	auto aladdinBehavior = (AladdinBehaviorComponent*)_Aladdin->getBehaviorComponent();
	aladdinBehavior->setRespawnPosition(GVector2(200, 1000));
	aladdinBehavior->moveViewport.Connect(this, &TestScene::moveViewport);
	aladdinBehavior->addToScene.Connect(this, &TestScene::addToScene);
	_listobject.push_back(_Aladdin);

	BehaviorComponent::addToScene.Connect(this, &TestScene::addToScene);

	_background = new TestSceneBackground();
	_background->init();

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

	RECT mapRECT = SpriteResource::getInstance()->getSourceRect(eObjectID::MAP1, "back");
	rootRect;
	rootRect.left = 0;
	rootRect.bottom = 0;
	rootRect.right = mapRECT.right * SCALE_FACTOR;
	rootRect.top = mapRECT.bottom * SCALE_FACTOR;

	QuadTreeNode::buildXMLfromXML("Resources//Maps//stage1.xml", "Resources//Maps//stage1_test.xml", mapRECT.right, mapRECT.bottom);
	_root = new QuadTreeNode(rootRect, 0);
	_root->readXML("Resources//Maps//stage1_test.xml");
	
	map<string, GameObject*>* maptemp = ObjectFactory::getMapObjectFromFile("Resources//Maps//stage1.xml");
	_mapobject.insert(maptemp->begin(), maptemp->end());


	_updateViewport = true;
	SoundManager::getInstance()->PlayLoop(eSoundId::BACKGROUND_STAGE1);
	return true;
}


void TestScene::update(float dt)
{
	updateViewport(_Aladdin, dt);
	_background->update(dt, _viewport);
	GVector2 viewport_position = _viewport->getPositionWorld();
	RECT viewport_in_transform = _viewport->getBounding();

	RECT screen;
	//hệ bot-left
	screen.left = viewport_in_transform.left;
	screen.right = viewport_in_transform.right ;
	screen.top = viewport_position.y;
	screen.bottom = screen.top - _viewport->getHeight();

	// getlistobject

	// [Bước 1]
	this->destroyobject();

	//OutputDebugStringW(L"Object list count : ");
	//__debugoutput(_listobject.size());

	// [Bước 2]
	_active_object.clear();

	// [Bước 3]
	auto listobjectname = _root->getActiveObject(screen);

	// [Bước 4]
	//OutputDebugStringW(L"Object in screen : ");
	for (auto name : listobjectname)
	{
		auto obj = _mapobject.find(name);
		if (obj == _mapobject.end() || obj._Ptr == nullptr)
			continue;
		//OutputDebugStringA(obj->first.c_str());
		//OutputDebugStringW(L" ");
		_active_object.push_back(obj->second);
	}
	//OutputDebugStringW(L"\n ");

	// [Bước 5]
	_active_object.insert(_active_object.end(), _listobject.begin(), _listobject.end());

	for (GameObject* obj : _active_object)
	{
		obj->update(dt);
	}
}

void TestScene::draw(LPD3DXSPRITE spriteHandle)
{
	_background->draw(spriteHandle);
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
	//TODO : Destroy các phần tử ngoài màn hình
	for (auto object : _listobject)
	{
		if (object->getBehaviorComponent() != nullptr && object->getBehaviorComponent()->getStatus() == eStatus::DESTROY)	// kiểm tra nếu là destroy thì loại khỏi list
		{
			object->release();
			// http://www.cplusplus.com/reference/algorithm/remove/
			auto rs1 = std::remove(_listobject.begin(), _listobject.end(), object);
			_listobject.pop_back();	
			delete object;
			break;		
		}
	}
	for (auto name : QuadTreeNode::ActiveObject)
	{
		auto object = _mapobject.find(name);
		if (object == _mapobject.end() || object._Ptr == nullptr)
			continue;
		if (object->second->getBehaviorComponent() != nullptr && object->second->getBehaviorComponent()->getStatus() == eStatus::DESTROY)	// kiểm tra nếu là destroy thì loại khỏi list
		{
			object->second->release();
			delete object->second;
			object->second = NULL;
			_mapobject.erase(name);

		}
	}
}

void TestScene::updateViewport(GameObject * objTracker, float deltatime)
{
	if (_updateViewport == false)
	{
		return;
	}
	float lerp = 5.0f;
	// Vị trí hiện tại của viewport. 
	GVector2 current_position = _viewport->getPositionWorld();
	GVector2 worldsize;
	worldsize.x = _mapBack->getFrameWidth();
	worldsize.y = _mapBack->getFrameHeight();
	// Bám theo object.

	float trackerX = max(objTracker->getPhysicsComponent()->getPositionX() - 260, 0);
	float trackerY = max(objTracker->getPhysicsComponent()->getPositionY() + 300, WINDOW_HEIGHT);

	//Không cho vượt quá bên trái
	if (trackerX + _viewport->getWidth() > worldsize.x)
	{
		trackerX = worldsize.x - _viewport->getWidth();
	}

	//Không vượt quá trên
	if (trackerY > worldsize.y)
	{
		trackerY = worldsize.y;
	}

	current_position.x += (trackerX - current_position.x) * lerp * deltatime / 1000;
	current_position.y += (trackerY - current_position.y) * lerp * deltatime / 1000;


	_viewport->setPositionWorld(current_position);
}


void TestScene::addToScene(GameObject * obj, sigcxx::SLOT slot)
{
	_listobject.push_back(obj);
}

void TestScene::updateInput(float dt)
{

}

vector<GameObject*> TestScene::getActiveObject()
{
	return _active_object;
}
