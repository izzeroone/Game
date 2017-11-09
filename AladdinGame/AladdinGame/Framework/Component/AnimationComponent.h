#pragma once
#include "Component.h"
#include <map>
#include "../animation.h"
using namespace std;

class AnimationComponent
{
public:
	void update(float deltatime);
	Animation* getCurrentAnimation();
	void setAnimation(int status);
private:
	map<int, Animation*> _animations;
	int _index;
	int _preindex;
};
