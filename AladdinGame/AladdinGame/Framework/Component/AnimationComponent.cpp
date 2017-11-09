#include "AnimationComponent.h"

void AnimationComponent::update(float deltatime)
{
	if (_animations[_index] != nullptr)
	{
		_animations[_index]->update(deltatime);
	}
}

Animation * AnimationComponent::getCurrentAnimation()
{
	return _animations[_index];
}

void AnimationComponent::setAnimation(int status)
{
	_preindex = _index;
	_animations[_index]->restart();
	_index = status;
}
