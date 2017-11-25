
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

void PlayerBehaviorComponent::dropHitpoint()
{
	_hitpoint--;
}

void PlayerBehaviorComponent::dropHitpoint(int damage)
{
	_hitpoint += damage;
}

