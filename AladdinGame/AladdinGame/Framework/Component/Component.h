#pragma once
#ifndef __COMPONENT_H__
#define __COMPONENT_H__
class Component
{
public:
	virtual void init() = 0;
	virtual void update(float deltatime) = 0;
};
#endif //__COMPONENT_H__
