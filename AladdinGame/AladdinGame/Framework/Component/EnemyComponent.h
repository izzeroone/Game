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
	virtual int getHitpoint();
	virtual void setHitpoint(int);
    virtual int getScore();
	virtual void setScore(int);
	virtual void dropHitpoint();
	virtual void dropHitpoint(int damage);
	virtual void setStatus(eStatus status) override;
	virtual void setRange(float rangeXStart, float rangeXEnd);
protected:
	void gainScore();
	int _hitpoint;
	int _score;
	//Tầm hoạt động chỉ trong khoản này ko được vượt quá
	float _rangeXStart;
	float _rangeXEnd;
};
#endif // !__ENEMYCOMPONENT_H__
