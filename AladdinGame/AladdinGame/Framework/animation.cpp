#include "Animation.h"
#include "../debug.h"
Animation::Animation(Sprite * spriteSheet, float timeAnimate, bool loop)
{
	_spriteSheet = spriteSheet;
	_timeAnimate = timeAnimate;

	_canAnimate = true;
	_totalFrames = 0;
	_index = 0;
	_timer = 0;
	_totalTimeAnimate = 0;
	_isCustom = false;
	_isReserve = false;
	_valueFlashes = 0.5f;
	_count = 0;

	_startFrame = 0;
	_startLoopFrame = 0;
	_endFrame = _totalFrames - 1;

	this->setIndex(0);
	this->setLoop(loop);
	_canFlashes = false;
	_flashColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
}

Animation::Animation(Sprite * spriteSheet, int totalFrames, int cols, float timeAnimate)
{
	_spriteSheet = spriteSheet;
	_timeAnimate = timeAnimate;
	_canAnimate = true;
	_totalFrames = totalFrames;
	_totalTimeAnimate = 0;
	_index = 0;
	_timer = 0;
	_isCustom = 0;
	_isReserve = false;
	_valueFlashes = 0.5f;
	_count = 0;

	_startFrame = 0;
	_startLoopFrame = 0;
	_endFrame = _totalFrames - 1;

	int frameW = spriteSheet->getTextureWidth() / cols;
	int frameH = spriteSheet->getTextureHeight() * cols / totalFrames;

	for (int i = 0; i < totalFrames; i++)
	{
		int x = i % cols;
		int y = i / cols;

		this->addFrameRect(x * frameW, y * frameH, frameW, frameH);
	}

	_currentRect = _frameRectList[_index];

	_flashColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
}

Animation::~Animation()
{
	// dont release sprite
}

void Animation::nextFrame()
{
	setIndex(_index + 1);
}
void Animation::prevFrame()
{
	setIndex(_index - 1);
}
int Animation::getIndex()
{
	return _index;
}
int Animation::getCount()
{
	return _count;
}
float Animation::getTotalTimeAnimation()
{
	return _totalTimeAnimate;
}
void Animation::setIndex(int index)
{
	if (index == _index || _totalFrames == 0)
		return;

	_index = index;

	if (_index > _endFrame)
	{
		_count++;
		//_index = _startFrame;
		_index = _startLoopFrame;
	}

	if (_index < _startFrame)
	{
		_count++;
		_index = _endFrame;
	}

	//if (_index < _startLoopFrame)
	//{
	//	_count++;
	//	_index = _endFrame;
	//}

	_currentRect = _frameRectList[_index];

	if (!_isLoop && _index == _endFrame)
	{
		this->stop();
	}
}

void Animation::setCustomTime(vector<float> customTimes)
{
		_customTimeAnimate = customTimes;
		_isCustom = true;
}

void Animation::update(float dt)
{
	if (!_canFlashes && !_canAnimate)
		return;
	_totalTimeAnimate += dt / 1000;
	_timer += dt / 1000;
	float timeAnimate = _timeAnimate;
	if (_isCustom)
	{
		timeAnimate = _customTimeAnimate[_index];
	}
	if (_timer >= timeAnimate)
	{
		if (_canAnimate)
		{
			if (_isReserve == false)
			{
				this->nextFrame();
			}
			else
			{
				this->prevFrame();
			}
		}

		_timer -= timeAnimate;				// không thể gán bằng 0. vì như vậy là làm tròn. sẽ có sai số

		if (_canFlashes)
		{
			if (_spriteSheet->getOpacity() != _valueFlashes)
			{
				_spriteSheet->setOpacity(_valueFlashes);
				_spriteSheet->setColor(D3DXCOLOR(_flashColor.r, _flashColor.g, _flashColor.b, _valueFlashes));
			}
			else
			{
				_spriteSheet->setOpacity(1.0f);
				_spriteSheet->setColor(D3DXCOLOR(_flashColor.r, _flashColor.g, _flashColor.b, 1.0f));
			}
		}
	}
}

void Animation::setTimeAnimate(float time)
{
	_timeAnimate = time;
}

float Animation::getTimeAnimate()
{
	return _timeAnimate;
}

void Animation::start()
{
	if (_canAnimate == false)
		_canAnimate = true;
}

void Animation::stop()
{
	if (_canAnimate == true)
		_canAnimate = false;
}

void Animation::canAnimate(bool can)
{
	if (_canAnimate != can)
		_canAnimate = can;
}
bool Animation::isAnimate()
{
	return _canAnimate;
}
bool Animation::isLastAnimation()
{
	return false;
}

RECT Animation::getCurrentBounding()
{
	return _frameRectList[_index];
}

void Animation::init()
{
}

void Animation::addFrameRect(RECT rect)
{
	//nếu là rect đầu tiên thì set current luôn
	if (_frameRectList.empty())
	{
		_currentRect = rect;
	}


	_frameRectList.push_back(rect);
	_totalFrames = _frameRectList.size();

	_endFrame = _totalFrames - 1;
}

void Animation::addFrameTransition(GVector2 transition)
{
	_frameTransition.push_back(transition);
}

void Animation::addFrameRect(float left, float top, int width, int height)
{
	RECT rect;
	rect.left = left;
	rect.top = top;
	rect.right = left + width;
	rect.bottom = top + height;

	this->addFrameRect(rect);
}

void Animation::addFrameRect(float left, float top, float right, float bottom)
{
	RECT rect;
	rect.left = left;
	rect.top = top;
	rect.right = right;
	rect.bottom = bottom;

	this->addFrameRect(rect);
}

void Animation::addFrameRect(eObjectID id, char* firstRectName, ...)
{
	va_list vl;
	char* name;

	va_start(vl, firstRectName);

	name = firstRectName;

	while (name != NULL)
	{
		this->addFrameRect(SpriteResource::getInstance()->getSourceRect(id, name));
		this->addFrameTransition(SpriteResource::getInstance()->getSourceTransition(id, name));
		name = va_arg(vl, char*);
	}

	va_end(vl);
}

void Animation::setLoop(bool isLoop)
{
	if (isLoop != _isLoop)
		_isLoop = isLoop;
}

void Animation::setReserve(bool isReserve)
{
	_isReserve = isReserve;
}

bool Animation::isLoop()
{
	return _isLoop;
}

void Animation::restart(int from)
{
	setIndex(from);

	if (_canAnimate == false)
		_canAnimate = true;
	
	_count = 0;
	_totalTimeAnimate = 0;
}

void Animation::enableFlashes(bool enable)
{
	if (_canFlashes == enable)
		return;

	_canFlashes = enable;
	_spriteSheet->setColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
}

void Animation::setValueFlashes(float value)
{
	if (_valueFlashes != value)
		_valueFlashes = value;
}

void Animation::animateFromTo(int from, int to, bool loop)
{
	if (from <= to)
	{
		_startLoopFrame = from;
		_endFrame = to;
	}
	else
	{
		_startLoopFrame = to;
		_endFrame = from;
	}

	this->setIndex(0);
	_isLoop = loop;
	_timer = 0.0f;

	if (_canAnimate == false)
		_canAnimate = true;
}

void Animation::setColorFlash(D3DXCOLOR color)
{
	_flashColor = color;
}

D3DXCOLOR Animation::getColorFlash()
{
	return _flashColor;
}

void Animation::draw(LPD3DXSPRITE spriteHandle, Viewport* viewport)
{
	_spriteSheet->setFrameRect(_currentRect);
	_spriteSheet->render(spriteHandle, viewport, _frameTransition[_index]);
}
