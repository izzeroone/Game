#ifndef __OBJECT_FACTORY_H__
#define __OBJECT_FACTORY_H__
#include "../Framework/define.h"
#include "../Framework/GameObject.h"
#include "Player\Aladdin.h"
#include "Object\Land.h"
#include "Object\Rope.h"
#include "../../pugixml/src/pugixml.hpp"

using namespace pugi;

class ObjectFactory
{
public:
	ObjectFactory();
	~ObjectFactory();
	static map<string, GameObject*>* getMapObjectFromFile(const string path);
	static GameObject* getObjectById(xml_node node, eObjectID id);
	static GameObject* getAladdin();
	static GameObject* getLand(xml_node node);
	static GameObject* getRope(xml_node node);
private:
	static map<string, string> ObjectFactory::getObjectProperties(xml_node node);
};
#endif // !__OBJECT_FACTORY_H__