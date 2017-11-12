#ifndef __OBJECT_FACTORY_H__
#define __OBJECT_FACTORY_H__
#include "../Framework/define.h"
#include "../Framework/GameObject.h"
#include "Player\Aladdin.h"
#include "Object\Land.h"

class ObjectFactory
{
public:
	ObjectFactory();
	~ObjectFactory();
	static GameObject* getAladdin();
	static GameObject* getLand(int x, int y, int width, int height, eDirection physicBodyDirection, eLandType type);
};
#endif // !__OBJECT_FACTORY_H__