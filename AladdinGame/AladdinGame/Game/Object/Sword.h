
#ifndef __SWORD_H__
#define __SWORD_H__
#include "../../Framework/define.h"
#include "../../Framework/GameObject.h"
#include "../../Framework/Component/AnimationComponent.h"
#include "../../Framework/Component/BehaviorComponent.h"
#include "../../Framework/Component/PhysicsComponent.h"
#include "../../Framework/Component/CollisionComponent.h"
#include "../../Framework/Component/NullComponent.h"
#include <vector>
#define LIVING_TIME 1000 // kiếm tồn tại 1 s

class SwordPhysicsComponent : public NullPhysicsComponent
{
public:
	void init();
protected:
};


class SwordBehaviorComponent : public BehaviorComponent
{
public:
	void init();
	void update(float detatime);
private:
	vector<GameObject*> _slashObject;// the object get slash do don't get slash again
	float _livingTime;
};

class Sword : GameObject
{
public:
	void init(int x, int y, int width, int height, eDirection side);
	Sword();
	~Sword();
};

#endif

