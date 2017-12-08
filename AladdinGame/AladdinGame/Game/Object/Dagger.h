
#ifndef __DAGGER_H__
#define __DAGGER_H__
#include "../../Framework/define.h"
#include "../../Framework/GameObject.h"
#include "../../Framework/Component/AnimationComponent.h"
#include "../../Framework/Component/BehaviorComponent.h"
#include "../../Framework/Component/PhysicsComponent.h"
#include "../../Framework/Component/CollisionComponent.h"
#include "../../Framework/Component/EnemyComponent.h"
#include "../../Framework/Component/PlayerComponent.h"

#define DAGGER_GRAVITY 400

class DaggerPhysicsComponent : public PhysicsComponent
{
public:
	void init();

	GVector2 getVelocity();
	RECT getBounding() override;
protected:
};

class DaggerAnimationComponent : public AnimationComponent
{
public:
	void init();
};

class DaggerBehaviorComponent : public BehaviorComponent
{
public:
	void init();
	void update(float detatime);
	void setStatus(eStatus status) override;
protected:
	vector<GameObject*> _hitObject;// the object get slash do don't get slash again
	virtual void updateAnimation();
	void standing();
};

class Dagger : GameObject
{
public:
	Dagger();
	~Dagger();
};

#endif

