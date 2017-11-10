#ifndef __OBJECT_FACTORY_H__
#define __OBJECT_FACTORY_H__
#include "../Framework/define.h"
#include "../Framework/GameObject.h"
#include "Player\Aladdin.h"

class ObjectFactory
{
public:
	ObjectFactory();
	~ObjectFactory();
	static GameObject* getAladdin();
};
#endif // !__OBJECT_FACTORY_H__