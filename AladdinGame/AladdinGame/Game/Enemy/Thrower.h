
#ifndef __THROWER_H__
#define __THROWER_H__
#include "../../Framework/define.h"
#include "../../Framework/GameObject.h"
#include "../../Framework/Component/AnimationComponent.h"
#include "../../Framework/Component/BehaviorComponent.h"
#include "../../Framework/Component/PhysicsComponent.h"
#include "../../Framework/Component/CollisionComponent.h"
#include "../../Framework/Component/EnemyComponent.h"
#include "../ObjectFactory.h"
#include "../Scene/SceneManager.h"

#define THROW_INTERVAL 1500

class ThrowerPhysicsComponent : public NullPhysicsComponent
{
public:
	void init();
protected:
};

class ThrowerAnimationComponent : public AnimationComponent
{
public:
	void init();
private:

};

//he is invisible so no HP xD
class ThrowerBehaviorComponent : public EnemyBehaviorComponent
{
public:
	void init();
	void update(float detatime);
protected:
	bool _toThrow;
	float _timer;
	void throwPot();
};


#endif

