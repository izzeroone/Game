#ifndef __ANIMATION_H__
#define __ANIMATION_H__

/*
update 5/11/2015
Vy

- Thêm thời gian tùy chỉnh cho animation
*/

#include <vector>
#include <stdarg.h>
#include "define.h"
#include "Sprite.h"
#include "Component\MovingComponent.h"
#include "Singleton\spriteresource.h"

LINK_FRAMEWORK

class Animation : public Component
{
public:
	~Animation();


	Animation(Sprite* spriteSheet, float timeAnimate = 0.0f, bool loop = true);

	Animation(Sprite* spriteSheet, int totalFrames, int cols, float timeAnimate = 0.0f);

	/*
	Chuyển qua frame kế tiếp
	*/
	void nextFrame();

	/*
	Chuyển qua frame trước
	*/
	void prevFrame();

	/*
	Truyền thứ tự frame cụ thể
	*/
	void setIndex(int index);
	
	/*
	Lấy giá trị index hiện tại
	*/
	int getIndex();

	/*
	Lấy số lần animation đã chạy
	*/
	int getCount();

	/*
	Lấy tổng số thời gian animation đã chạy
	*/
	float getTotalTimeAnimation();

	/*
	Đặt giá trị animation tùy chọn mà thời gian chuyển cảnh không bằng nhau
	*/
	void setCustomTime(vector<float> customTimes);
	/*
	Update animation
	*/
	void update(float dt);

	/*
	Vẽ chuyển động
	*/
	void draw(LPD3DXSPRITE spriteHandle, Viewport* viewport);

	/*
	Đặt thời gian chuyển frame
		@time: thời gian tính theo giây
	*/
	void setTimeAnimate(float time);
	
	/*
	Lấy giá trị thời gian chuyển frame
	*/
	float getTimeAnimate();

	/*
	Bắt đầu chuyển frame
	*/
	void start();

	/*
	Dừng chuyển frame
	*/
	void stop();

	void canAnimate(bool can);
	bool isAnimate();
	void addFrameRect(RECT rect);
	void addFrameTransition(GVector2 transition);
	void addFrameRect(float left, float top, int width, int height);
	void addFrameRect(float left, float top, float right, float bottom);

	void addFrameRect(eObjectID id, char* firstRectName, ...);

	void setPosition(GVector2 p)
	{ 
	}

	void setLoop(bool isLoop);
	void setReserve(bool isReserve);
	bool isLoop();

	void restart(int from = 0);
	void enableFlashes(bool enable);

	void setValueFlashes(float value);

	void animateFromTo(int from, int to, bool loop = true);

	void setColorFlash(D3DXCOLOR color);
	D3DXCOLOR getColorFlash();
	bool isLastAnimation();
	RECT getCurrentBounding();
private:
	bool					_isAll;
	int						_startFrame;
	int						_startLoopFrame;						//Vị trí loop bắt đầu, vị trị loop kết thúc là _endFrame luôn
	int						_endFrame;
	int						_index;									// số thứ tự frame
	int						_totalFrames;
	int						_count;									// số lần animation chạy xong chu kì

	float					_timeAnimate;							// thời gian chuyển giữa các frame
	float					_timer;
	float					_totalTimeAnimate;

	vector<float>			_customTimeAnimate;
	bool					_isCustom;

	bool					_canAnimate;
	bool					_isLoop;
	bool					_isReserve; 

	Sprite*					_spriteSheet;							// ref to object's sprite
	vector<RECT>			_frameRectList;
	vector<GVector2>		_frameTransition;
	string					_nameAnimation;
	RECT					_currentRect;

	bool					_canFlashes;
	float					_valueFlashes;
	D3DXCOLOR				_flashColor;

	// Inherited via Component
	virtual void init() override;
};

#endif // !__ANIMATION_H__
