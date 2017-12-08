
#ifndef __NAHBI_H__
#define __NAHBI_H__
#include"../../Framework/define.h"
#include "../../Framework/GameObject.h"
#include "../../Framework/Component/AnimationComponent.h"
#include "../../Framework/Component/BehaviorComponent.h"
#include "../../Framework/Component/PhysicsComponent.h"
#include "../../Framework/Component/CollisionComponent.h"
#include "../../Framework/Component/EnemyComponent.h"
#include "../ObjectFactory.h"
#include "../Scene/SceneManager.h"

#define STAND_TIME 500

class NahbiPhysicsComponent : public PhysicsComponent
{
public:
	void init();

	GVector2 getVelocity();
	RECT getBounding() override;
protected:
};

class NahbiAnimationComponent : public AnimationComponent
{
public:
	void init();
private:

};

class NahbiBehaviorComponent : public EnemyBehaviorComponent
{
public:
	void init();
	void update(float detatime);
	void setStatus(eStatus status) override;
	void dropHitpoint(int damage) override;
private:
	void checkCollision(float deltatime);
	void updateAnimation();
	void faceLeft();
	void faceRight();
	void standing();
	void moveLeft();
	void moveRight();
	void slash();

	float _standTime; // sau khi bị đánh phải đứng lại một khoảng thời gian


};


#endif


