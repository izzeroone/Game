
#include "EnemyComponent.h"


void EnemyBehaviorComponent::init()
{
}

int EnemyBehaviorComponent::getHitpoint()
{
	return _hitpoint;
}

void EnemyBehaviorComponent::setHitpoint(int hitpoint)
{
	_hitpoint = hitpoint;
}

int EnemyBehaviorComponent::getScore()
{
	return _score;
}

void EnemyBehaviorComponent::setScore(int score)
{
	_score = score;
}

void EnemyBehaviorComponent::dropHitpoint()
{
	_hitpoint--;
	if (_hitpoint <= 0)
		gainScore();
}

void EnemyBehaviorComponent::dropHitpoint(int damage)
{
	_hitpoint -= damage;
	OutputDebugStringW(L"Enemy hit point : ");
	__debugoutput(_hitpoint);
	if (_hitpoint <= 0)
		gainScore();
}

void EnemyBehaviorComponent::setStatus(eStatus status)
{
	if (status == eStatus::DESTROY)
	{
		//SoundManager::getInstance()->Play(eSoundId::DESTROY_ENEMY);
	}
	BehaviorComponent::setStatus(status);
}

void EnemyBehaviorComponent::setRange(float rangeXStart, float rangeXEnd)
{
	if (rangeXStart <= rangeXEnd)
	{
		_rangeXStart = rangeXStart;
		_rangeXEnd = rangeXEnd;
	}
	else
	{
		_rangeXStart = rangeXEnd;
		_rangeXEnd = rangeXStart;
	}
}

void EnemyBehaviorComponent::gainScore()
{
	//add score
}
