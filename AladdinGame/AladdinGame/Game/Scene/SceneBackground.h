#ifndef __SCENEBACKGROUND_H__
#define __SCENEBACKGROUND_H__

#include "../../Framework/define.h"
#include "../../Framework/viewport.h"
#include "../../Framework/GameObject.h"

#include<vector>
LINK_FRAMEWORK
class SceneBackground
{
public:
	SceneBackground();
	virtual ~SceneBackground();

	bool virtual init() = 0;
	void virtual update(float dt, Viewport*) = 0;
	void virtual draw(LPD3DXSPRITE spriteHandle) = 0;
	void virtual release() = 0;

protected:
};

#endif // !__SCENEBACKGROUND_H__

