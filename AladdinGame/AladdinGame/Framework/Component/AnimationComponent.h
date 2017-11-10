#pragma once
#include "Component.h"
#include "PhysicsComponent.h"
#include <map>
#include "../animation.h"
using namespace std;

class AnimationComponent : public Component
{
public:
	AnimationComponent();
	AnimationComponent(PhysicsComponent* physicsComponent);
	~AnimationComponent();
	virtual void update(float deltatime);
	virtual Animation* getCurrentAnimation();
	virtual void setAnimation(int status);
	virtual void draw(LPD3DXSPRITE spriteHander, Viewport* viewport);
	virtual void setOpacity(float opacity);
	virtual float getOpacity();
	virtual void setColor(D3DXCOLOR color);
	virtual D3DXCOLOR getColor();
	virtual GVector2 getAnchorPoint();
	virtual Sprite * getSprite();
	virtual RECT getBounding();
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
protected:
	Sprite* _sprite;
	map<int, Animation*> _animations;
	int _index;
	int _preindex;
	LPD3DXSPRITE _spriteHandle;
	PhysicsComponent* _physicsComponent;
};
