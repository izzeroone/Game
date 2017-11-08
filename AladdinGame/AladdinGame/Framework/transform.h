#pragma once
#ifndef __TRANSFORM_H__
#define __TRANSFORM_H__

#include "define.h"

class Transform
{
public:
	Transform();
	~Transform();

	virtual GVector2 getPosition();
	virtual float getPositionX();
	virtual float getPositionY();

	virtual void setPosition(GVector3 vector);
	virtual void setPosition(float x, float y, float z);
	virtual void setPosition(GVector2 position);
	virtual void setPosition(float x, float y);
	virtual void setPositionX(float x);
	virtual void setPositionY(float y);

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

	GVector2 getAnchorPoint();

protected:
	GVector2			_position;
	GVector2			_scale;
	float				_rotate;				// theo độ a từ 0 đến 360 (ko phải rad)
	GVector2			_origin;				// gốc của Transform, dùng để xoay, scale (anchor: điểm neo)
	GVector2			_anchorPoint;	
	float				_zIndex;
};

#endif // !__TRANSFORM_H__
