#ifndef __TESTSCENEBACKGROUND_H__
#define __TESTSCENEBACKGROUND_H__

#include "SceneBackground.h"
#include "../../Framework/sprite.h"
#include<vector>
LINK_FRAMEWORK

#define _1_SCALE -1
#define _2_SCALE -0.8
#define _3_SCALE -0.6
#define _4_SCALE -0.4
#define _5_SCALE -0.2
#define _6_VELOCITY -10
#define _7_VELOCITY -50
#define _8_VELOCITY -75
#define _9_VELOCITY -100

class TestSceneBackground : public SceneBackground
{
public:
	TestSceneBackground();
	~TestSceneBackground();

	virtual bool init() override;
	virtual void update(float dt, Viewport *) override;
	virtual void draw(LPD3DXSPRITE spriteHandle) override;
	virtual void release() override;


protected:
	Sprite * _sprite1_first;
	Sprite * _sprite2_first;
	Sprite * _sprite3_first;
	Sprite * _sprite4_first;
	Sprite * _sprite5_first;
	Sprite * _sprite6_first;
	Sprite * _sprite7_first;
	Sprite * _sprite8_first;
	Sprite * _sprite9_first;

	Sprite * _sprite1_second;
	Sprite * _sprite2_second;
	Sprite * _sprite3_second;
	Sprite * _sprite4_second;
	Sprite * _sprite5_second;
	Sprite * _sprite6_second;
	Sprite * _sprite7_second;
	Sprite * _sprite8_second;
	Sprite * _sprite9_second;

	float _oldViewportX;
	float _frameWidth;

	Sprite * makeSprite(string name, float x, float y);
	void addPositionSprite(Sprite * first, Sprite * second, float diffirent);


};

#endif // !__SCENEBACKGROUND_H__

