#ifndef __FLAME_H__
#define __FLAME_H__
#include "../../Framework/define.h"
#include "../../Framework/GameObject.h"
#include "../../Framework/Component/NullComponent.h"
#include "../../Framework/Component/CollisionComponent.h"
#include "../../Framework/Component/PlayerComponent.h"


LINK_FRAMEWORK

class FlamePhysicsComponent : public PhysicsComponent
{
public:
	void init() override;
	RECT getBounding();
protected:
};

class FlameAnimationComponent : public AnimationComponent
{
public:
	void init() override;
};

class FlameBehaviorComponent : public BehaviorComponent
{
public:
	void init();
	void update(float deltatime) override;
protected:
};


#endif

