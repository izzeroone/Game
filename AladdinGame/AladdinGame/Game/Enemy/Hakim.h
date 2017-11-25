
#ifndef __HAKIM_H__
#define __HAKIM_H__
#include "../../Framework/define.h"
#include "../../Framework/GameObject.h"
#include "../../Framework/Component/AnimationComponent.h"
#include "../../Framework/Component/BehaviorComponent.h"
#include "../../Framework/Component/PhysicsComponent.h"
#include "../../Framework/Component/CollisionComponent.h"
#include "../../Framework/Component/EnemyComponent.h"
#include "../ObjectFactory.h"
#include "../Scene/SceneManager.h"


class HakimPhysicsComponent : public PhysicsComponent
{
public:
	void init();

	GVector2 getVelocity();
	void setAnimationComponent(AnimationComponent * animationComponent);
	RECT getBounding() override;
protected:
	AnimationComponent * _animationComponent;
};

class HakimAnimationComponent : public AnimationComponent
{
public:
	void init();
private:

};

class HakimBehaviorComponent : public EnemyBehaviorComponent
{
public:
	void init();
	void update(float detatime);
	void setStatus(eStatus status) override;
	void dropHitpoint(int damage) override;
private:
	void updateAnimation();
	void faceLeft();
	void faceRight();
	void standing();
	void moveLeft();
	void moveRight();
	void slash();


};


#endif

