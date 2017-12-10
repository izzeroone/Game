#ifndef __WALL_H__
#define __WALL_H__
#include "../../Framework/define.h"
#include "../../Framework/GameObject.h"
#include "../../Framework/Component/NullComponent.h"
#include "../../Framework/Component/CollisionComponent.h"

LINK_FRAMEWORK

class WallPhysiscsComponent : public NullPhysicsComponent
{
	void init() override;
};

class Wall : public GameObject
{
public:
	void init(int x, int y, int width, int height, eDirection physicBodyDirection);
	void init() override;
protected:
};

#endif

