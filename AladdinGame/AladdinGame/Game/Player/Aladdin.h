
#ifndef __ALADDIN_H__
#define __ALADDIN_H__
#include "../../Framework/define.h"
#include "../../Framework/GameObject.h"
#include "../../Framework/Component/AnimationComponent.h"
#include "../../Framework/Component/BehaviorComponent.h"
#include "../../Framework/Component/PhysicsComponent.h"
#include "../../Framework/Component/CollisionComponent.h"
#include "../../Framework/Component/PlayerComponent.h"
#include "../../Framework/Singleton/SoundManager.h"
#include "../../Game/Object/Land.h"
#include "../../Game/Object/Rope.h"
#include "../../../sigcxx/include/sigcxx/sigcxx.hpp"
#include "../ObjectFactory.h"

#define ALADDIN_MOVE_SPEED 300
#define ALADDIN_CLIMB_SPEED 100
#define ALADDIN_JUMP_VEL 500
#define GRAVITY 800
#define ALADDIN_PROTECT_TIME 3000
#define ALADDIN_BORING_TIME 3.0f
#define ALADDIN_WIDTH 37 * SCALE_FACTOR
#define ALADDIN_HEIGHT 56 * SCALE_FACTOR
#define ALADDIN_CLIMB_HEIGHT 75 * SCALE_FACTOR
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
	RECT getBounding() override;
protected:
};

class AladdinAnimationComponent : public AnimationComponent
{
public:
	void init();
};

class AladdinBehaviorComponent : public PlayerBehaviorComponent
{
public:
	void init();
	void update(float detatime);
	void setStatus(eStatus status) override;
	void setRespawnPosition(GVector2 respawnPosition);
	bool dropHitpoint(int damage);
	sigcxx::Signal<float, bool> moveViewport; //float is offset, bool: true move up, false: revert back
	sigcxx::Signal<GameObject*> addToScene; // add some thing to scene
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
	void climbVertical();
	void climbHorizon();


	void respawn();

	//weapon action
	void slash();
	void throwApple();
	void updateWeaponAnimation(eStatus status);
	//hp
	

	//movement helper
	void removeGravity();
	void removeMovementX();
	// Inherited via BehaviorComponent
	virtual void executeCommand(eCommand command) override;
	// Collision check 
	void checkCollision(float deltatime);
	void handleCollisionLand(GameObject* otherObject, float deltatime);
	void handleCollisionRope(GameObject* otherObject, float deltatime);
	void handleCollisionWall(GameObject* otherObject, float deltatime);
	float _protectTime;
	bool _isBoring; // flag set not to update animation when boring
	bool _climbingLadder;
	GVector2 _respawnPostion;
};



#endif // !__ALADDIN_H__
