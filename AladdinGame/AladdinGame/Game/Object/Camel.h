#ifndef __CAMEL_H__
#define __CAMEL_H__
#include "../../Framework/define.h"
#include "../../Framework/GameObject.h"
#include "../../Framework/Component/AnimationComponent.h"
#include "../../Framework/Component/BehaviorComponent.h"
#include "../../Framework/Component/PhysicsComponent.h"
#include "../../Framework/Component/CollisionComponent.h"
#include "../../Framework/Component/EnemyComponent.h"
#include "../../Framework/Component/PlayerComponent.h"
#include "../ObjectFactory.h"

#define GRAVITY 1600

class CamelPhysicsComponent : public PhysicsComponent
{
public:
	void init() override;
	RECT getBounding();
protected:
};

class CamelAnimationComponent : public AnimationComponent
{
public:
	void init() override;
};

class CamelBehaviorComponent : public BehaviorComponent
{
public:
	void init();
	void update(float deltatime) override;
protected:
	void checkCollision(float deltatime);
private:
	void puffApple();
};


#endif


