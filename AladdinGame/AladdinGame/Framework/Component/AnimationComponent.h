#pragma once
#include "Component.h"
#include "PhysicsComponent.h"
#include <map>
#include "../animation.h"
using namespace std;

class AnimationComponent
{
public:
	AnimationComponent();
	AnimationComponent(PhysicsComponent* physicsComponent);
	~AnimationComponent();
	void update(float deltatime);
	Animation* getCurrentAnimation();
	virtual void setAnimation(int status);
	virtual void draw(Viewport* viewport);
	virtual void setOpacity(float opacity);
	virtual float getOpacity();
	void setColor(D3DXCOLOR color);
	D3DXCOLOR getColor();
	GVector2 getAnchorPoint();
	Sprite * getSprite();
	RECT getBounding();
	virtual GVector2 getScale();
	virtual void setScale(GVector2 scale);
	virtual void setScale(float scale);
	virtual void setScaleX(float sx);
	virtual void setScaleY(float sy);

	virtual float getRotate();
	virtual void setRotate(float degree);

	virtual GVector2 getOrigin();
	virtual void setOrigin(GVector2 origin);

	virtual void setZIndex(float z);
	virtual float getZIndex();

	virtual void setOpacity(float opacity);
	virtual float getOpacity();

	virtual void setSpriteHandle(LPD3DXSPRITE spriteHandle);
private:
	Sprite* _sprite;
	map<int, Animation*> _animations;
	int _index;
	int _preindex;
	LPD3DXSPRITE _spriteHandle;
	PhysicsComponent* _physicsComponent;
};
