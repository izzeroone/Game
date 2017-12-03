
#include "PlayerComponent.h"

int PlayerBehaviorComponent::getHitpoint()
{
	return _hitpoint;
}

void PlayerBehaviorComponent::setHitpoint(int hitpoint)
{
	_hitpoint = hitpoint;
}

int PlayerBehaviorComponent::getLife()
{
	return _life;
}

void PlayerBehaviorComponent::setLife(int life)
{
	_life = life;
}

void PlayerBehaviorComponent::dropLife()
{
	_life--;
}

bool PlayerBehaviorComponent::dropHitpoint()
{
	_hitpoint--;
	return true;
}

bool PlayerBehaviorComponent::dropHitpoint(int damage)
{
	_hitpoint -= damage;
	return true;
}

