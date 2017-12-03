#ifndef __LAND_H__
#define __LAND_H__
#include "../../Framework/define.h"
#include "../../Framework/GameObject.h"
#include "../../Framework/Component/NullComponent.h"
#include "../../Framework/Component/CollisionComponent.h"
#include "../Scene/SceneManager.h"
#include "../ObjectFactory.h"

#define FLAME_INTEVAL 300 // 0,3s sau khi chạm flameland
#define FALLING_DESTROYED_TIME 500 // thời gian tính từ lúc rơi xuống tới lúc bể
#define FALLING_LAND_HOLD_TIME 1000 // thời gian từ khi chạm tới bắt đầu rớt
LINK_FRAMEWORK

class LandPhysiscsComponent : public NullPhysicsComponent
{
public:
	void init() override;
};

class FallingLandPhysiscsComponent : public LandPhysiscsComponent
{
public:
	void init() override;
};

class FallingLandAnimationComponent : public AnimationComponent
{
public:
	void init() override;
};

class LandBehaviorComponent : public BehaviorComponent
{
public:
	void init();
	void update(float deltatime);
	void setLandType(eLandType type);
	eLandType getLandType();
protected:
	void updateFlameLand(float deltatime);
	void updateFallingLand(float deltatime);

	GVector2 _flamePos;
	eLandType _landType;
	float _width;
	float _timer;
	float _holdTimer;

	
};

class Land : public GameObject
{
public:
	void init(int x, int y, int width, int height, eDirection physicBodyDirection, eLandType type);
	void init() override;
	void setLandType(eLandType landType);
	eLandType getLandType();
protected:
};

#endif

