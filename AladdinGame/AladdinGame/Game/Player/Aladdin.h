
#ifndef __ALADDIN_H__
#define __ALADDIN_H__
#include "../../Framework/define.h"
#include "../../Framework/GameObject.h"
#include "../../Framework/Component/AnimationComponent.h"
#include "../../Framework/Component/BehaviorComponent.h"
#include "../../Framework/Component/PhysicsComponent.h"
#include "../../Framework/Component/CollisionComponent.h"
#include "../../Game/Object/Land.h"
#include "../../Game/Object/Rope.h"
#include "../../../sigcxx/include/sigcxx/sigcxx.hpp"

#define ALADDIN_MOVE_SPEED 300
#define ALADDIN_CLIMB_SPEED 100
#define ALADDIN_JUMP_VEL 450
#define GRAVITY 800
#define PROTECT_TIME 3000
#define ALADDIN_BORING_TIME 3.0f
#define ALADDIN_WIDTH 37 * SCALE_FACTOR
#define ALADDIN_HEIGHT 56 * SCALE_FACTOR
#define ALADDIN_CLIMB_HEIGHT 78 * SCALE_FACTOR
#define RUNNING_BRAKE_TIME 2.0f
#define JUMP_OFFSET 10 // trick to allow burning land to collide
#define VIEWPORT_MOVEUP_OFFSET 30 // use when aladdin lookup

#define BT_LEFT DIK_LEFT
#define BT_RIGHT DIK_RIGHT
#define	BT_UP DIK_UP
#define BT_DOWN DIK_DOWN
#define BT_JUMP DIK_X
#define BT_SLASH DIK_C
#define BT_THROW DIK_Z
#define BT_BOUND DIK_A


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
	virtual void setStatus(eStatus status) override;
	void setRespawnPosition(GVector2 respawnPosition);
	sigcxx::Signal<float, bool> move_viewport; //float is offset, bool: true move up, false: revert back
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


	void respawn();

	//weapon action
	void slash();
	void throwApple();
	void checkAndAddWeaponAnimation();
	void checkAndAddWeaponAnimation(eStatus status);
	void removeWeaponAnimation();
	void checkAndRemoveWeapon();

	//movement helper
	void removeGravity();
	void removeMovementX();
	// Inherited via BehaviorComponent
	virtual void executeCommand(eCommand command) override;

	bool _isBoring; // flag set not to update animation when boring
	GVector2 _respawnPostion;
};



#endif // !__ALADDIN_H__
