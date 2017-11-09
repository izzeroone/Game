#pragma once
#include "../define.h"
#include "Component.h"
class BehaviorComponent
{
public:
	virtual void update(float deltatime) = 0;
};
