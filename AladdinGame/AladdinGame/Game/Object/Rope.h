#ifndef __ROPE_H__
#define __ROPE_H__
#include "../../Framework/define.h"
#include "../../Framework/GameObject.h"
#include "../../Framework/Component/NullComponent.h"
#include "../../Framework/Component/CollisionComponent.h"

LINK_FRAMEWORK

class RopePhysiscsComponent : public NullPhysicsComponent
{
	void init() override;
};

class Rope : public GameObject
{
public:
	void init(int x, int y, int width, int height, eDirection physicBodyDirection, eRopeType type);
	void init() override;
	void setRopeType(eRopeType ropeType);
	eRopeType getRopeType();
protected:
	eRopeType _ropeType;
};

#endif

