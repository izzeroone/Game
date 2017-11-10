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