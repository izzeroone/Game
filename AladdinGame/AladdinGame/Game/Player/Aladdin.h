
#ifndef __ALADDIN_H__
#define __ALADDIN_H__
#include "../../Framework/define.h"
#include "../../Framework/GameObject.h"
#include "../../Framework/Component/AnimationComponent.h"
#include "../../Framework/Component/BehaviorComponent.h"
#include "../../Framework/Component/PhysicsComponent.h"
#include "../../Framework/Component/CollisionComponent.h"

#define ALADDIN_MOVE_SPEED 300
#define ALADDIN_CLIMB_SPEED 100
#define ALADDIN_JUMP_VEL 400
#define GRAVITY 800
#define PROTECT_TIME 3000
#define ALADDIN_BORING_TIME 3

#define BT_LEFT DIK_LEFT
#define BT_RIGHT DIK_RIGHT
#define	BT_UP DIK_UP
#define BT_DOWN DIK_DOWN
#define BT_JUMP DIK_X
#define BT_SLASH DIK_C
#define BT_THROW DIK_Z


LINK_FRAMEWORK
class AladdinPhysicsComponent : public PhysicsComponent
{
public:
	void init();

	GVector2 getVelocity();
	void setAnimationComponent(AnimationComponent * animationComponent);
	RECT getBounding() override;
protected:
	AnimationComponent * _animationComponent;
};

class AladdinAnimationComponent : public AnimationComponent
{
public:
	void init();
};

class AladdinBehaviorComponent : public BehaviorComponent
{
public:
	void init();
	void update(float detatime);
private:
	void updateTimeOut(float deltaTime);
	void updateAnimation();
	void setBoringAnimation();
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
	void falling();
	void climbvertical();
	void climbhorizon();
	void climbJump();
	//weapon action
	void slash();
	void throwApple();
	void checkAndAddWeaponAnimation();
	void removeWeaponAnimation();
	void checkAndRemoveWeapon();


	// Inherited via BehaviorComponent
	virtual void executeCommand(eCommand command) override;

	bool _isBoring; // flag set not to update animation when boring
};



#endif // !__ALADDIN_H__
