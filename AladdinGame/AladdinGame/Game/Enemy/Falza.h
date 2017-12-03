#ifndef __FALZA_H__
#define __FALZA_H__

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

class FalzaPhysicsComponent : public PhysicsComponent
{
public:
	void init();

	GVector2 getVelocity();
	void setAnimationComponent(AnimationComponent * animationComponent);
	RECT getBounding() override;
protected:
	AnimationComponent * _animationComponent;
};

class FalzaAnimationComponent : public AnimationComponent
{
public:
	void init();
private:

};

class FalzaBehaviorComponent : public EnemyBehaviorComponent
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
	void throwApple();

	float _standTime; // sau khi bị đánh phải đứng lại một khoảng thời gian


};


#endif
