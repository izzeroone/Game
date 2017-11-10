
#ifndef __ALADDIN_H__
#define __ALADDIN_H__
#include "../../Framework/define.h"
#include "../../Framework/GameObject.h"
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
	void init();
	void update(float detatime);
private:
	void updateTimeOut(float deltaTime);
	void updateAnimation();
	//
	void faceLeft();
	void faceRight();
	//character action
	void standing();
	void moveLeft();
	void moveRight();
	void moveUp(); //for climbing
	void moveDown(); // for climbing
	void jump();
	void slash();
	void falling();
	void climbvertical();
	void climbhorizon();
	void climbJump();

	// Inherited via BehaviorComponent
	virtual void executeCommand(eCommand command) override;
};



#endif // !__ALADDIN_H__
