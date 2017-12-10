
#ifndef __APPLE_H__
#define __APPLE_H__
#include "../../Framework/define.h"
#include "../../Framework/GameObject.h"
#include "../../Framework/Component/AnimationComponent.h"
#include "../../Framework/Component/BehaviorComponent.h"
#include "../../Framework/Component/PhysicsComponent.h"
#include "../../Framework/Component/CollisionComponent.h"
#include "../../Framework/Component/EnemyComponent.h"
#include "../../Framework/Component/PlayerComponent.h"

#define GRAVITY 1600

class ApplePhysicsComponent : public PhysicsComponent
{
public:
	void init();

	GVector2 getVelocity();
	RECT getBounding() override;
protected:
};

class AppleAnimationComponent : public AnimationComponent
{
public:
	void init();
};

class AppleBehaviorComponent : public BehaviorComponent
{
public:
	void init();
	void update(float detatime);
	void setStatus(eStatus status) override;
protected:
	void checkCollision(float deltatime);
	vector<GameObject*> _hitObject;// the object get slash do don't get slash again
	virtual void updateAnimation();
	void standing();
};

class Apple : GameObject
{
public:
	Apple();
	~Apple();

};

#endif

