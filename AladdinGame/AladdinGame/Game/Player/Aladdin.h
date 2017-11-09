
#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__
#include "../../Framework/define.h"
#include "../../Framework/Component/AnimationComponent.h"
#include "../../Framework/Component/BehaviorComponent.h"
#include "../../Framework/Component/PhysicsComponent.h"

#define ALADDIN_MOVE_SPEED 300
#define ALADDIN_CLIMB_SPEED 100
#define ALADDIN_JUMP_VEL 400
#define GRAVITY 800
#define PROTECT_TIME 3000
#define ALADDIN_BORING_TIME 3000

LINK_FRAMEWORK
class AladdinPhysicsComponent : public PhysicsComponent
{
	void init();
};

class AladdinAnimationComponent : public AnimationComponent
{
	void init();
};

class AladdinBehaviorComponent : public BehaviorComponent
{
private:

};

#endif // !__GameObject_H__
