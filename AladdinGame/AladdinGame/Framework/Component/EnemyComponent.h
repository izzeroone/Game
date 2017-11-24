#pragma once
#ifndef __ENEMYCOMPONENT_H__
#define __ENEMYCOMPONENT_H__
#include "../define.h"
#include "PhysicsComponent.h"
#include "AnimationComponent.h"
#include "BehaviorComponent.h"


class EnemyBehaviorComponent : public BehaviorComponent
{
public:
	virtual void init() override;
	int getHitpoint();
	void setHitpoint(int);
    int getScore();
	void setScore(int);
	virtual void dropHitpoint();
	virtual void dropHitpoint(int damage);
	void setStatus(eStatus status) override;
protected:
	void gainScore();
	int _hitpoint;
	int _score;
};
#endif // !__ENEMYCOMPONENT_H__
