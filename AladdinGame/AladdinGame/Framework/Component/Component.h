#pragma once

class Component
{
public:
	virtual void init() = 0;
	virtual void update(float deltatime) = 0;
};
