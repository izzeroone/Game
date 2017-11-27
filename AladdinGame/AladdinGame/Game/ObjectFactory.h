﻿#ifndef __OBJECT_FACTORY_H__
#define __OBJECT_FACTORY_H__
#include "../Framework/define.h"
#include "../Framework/GameObject.h"
#include "Player\Aladdin.h"
#include "Object\Apple.h"
#include "Object\Land.h"
#include "Object\Rope.h"
#include "Enemy\Hakim.h"
#include "Object\Sword.h"
#include "Object\Flame.h"
#include "../../pugixml/src/pugixml.hpp"
#include <functional>
using namespace pugi;

class ObjectFactory
{
public:
	ObjectFactory();
	~ObjectFactory();
	static map<string, GameObject*>* getMapObjectFromFile(const string path);
	static map<string, std::function<GameObject * () >>* getMapObjectFunctionFromFile(const string path);
	static GameObject* getAladdin();
	static GameObject* getApple(GVector2 pos, GVector2 velocity);
	static GameObject* getSword(GVector2 pos, float width, float height, bool canSlashEnemy);
	static GameObject* getLand(xml_node node);
	static GameObject* getRope(xml_node node);
	static GameObject* getHakim(GVector2 pos, float rangeXStart, float rangeXEnd);
	static GameObject* getFlame(GVector2 pos);
private:
	static map<string, string> ObjectFactory::getObjectProperties(xml_node node);
	static GameObject* getObjectById(xml_node node, eObjectID id);
	static std::function<GameObject * () > getFunctionById(xml_node node, eObjectID id);
};
#endif // !__OBJECT_FACTORY_H__