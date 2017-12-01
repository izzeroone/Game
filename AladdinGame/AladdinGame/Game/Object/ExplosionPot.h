
#ifndef __EXPLOSIONPOT_H__
#define __EXPLOSIONPOT_H__
#include "../../Framework/define.h"
#include "../../Framework/GameObject.h"
#include "../Player/Aladdin.h"
#include "Apple.h"


#define POT_GRAVITY 1600

class ExplosionPotPhysicsComponent : public ApplePhysicsComponent
{
};

class ExplosionPotAnimationComponent : public AnimationComponent
{
public:
	void init();
};

class ExplosionPotBehaviorComponent : public AppleBehaviorComponent
{
public:
	void update(float deltatime);
private:
	void updateAnimation();
};

class ExplosionPot : GameObject
{
public:
	ExplosionPot();
	~ExplosionPot();
};

#endif

