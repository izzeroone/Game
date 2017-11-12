#ifndef __LAND_H__
#define __LAND_H__
#include "../../Framework/define.h"
#include "../../Framework/GameObject.h"
#include "../../Framework/Component/NullComponent.h"
#include "../../Framework/Component/CollisionComponent.h"

LINK_FRAMEWORK

class LandPhysiscsComponent : public NullPhysicsComponent
{
	void init() override;
};

class Land : public GameObject
{
public:
	void init(int x, int y, int width, int height, eDirection physicBodyDirection, eLandType type);
	void init() override;
	void setLandType(eLandType landType);
	eLandType getLandType();
protected:
	eLandType _landType;
};

#endif

