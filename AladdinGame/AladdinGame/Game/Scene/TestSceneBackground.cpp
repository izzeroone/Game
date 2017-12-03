#include "TestSceneBackground.h"

TestSceneBackground::TestSceneBackground()
{
	_oldViewportX = 0;
}

TestSceneBackground::~TestSceneBackground()
{
}

bool TestSceneBackground::init()
{
	_sprite1_first = makeSprite("part_09", 0, WINDOW_HEIGHT);
	_sprite2_first = makeSprite("part_08", 0, _sprite1_first->getPositionY() - _sprite1_first->getFrameHeight());
	_sprite3_first = makeSprite("part_07", 0, _sprite2_first->getPositionY() - _sprite2_first->getFrameHeight());
	_sprite4_first = makeSprite("part_06", 0, _sprite3_first->getPositionY() - _sprite3_first->getFrameHeight());
	_sprite5_first = makeSprite("part_05", 0, _sprite4_first->getPositionY() - _sprite4_first->getFrameHeight());
	_sprite6_first = makeSprite("part_04", 0, _sprite5_first->getPositionY() - _sprite5_first->getFrameHeight());
	_sprite7_first = makeSprite("part_03", 0, _sprite6_first->getPositionY() - _sprite6_first->getFrameHeight());
	_sprite8_first = makeSprite("part_02", 0, _sprite7_first->getPositionY() - _sprite7_first->getFrameHeight());
	_sprite9_first = makeSprite("part_01", 0, _sprite8_first->getPositionY() - _sprite8_first->getFrameHeight());

	_sprite1_first->setOrigin(GVector2(1.f, 0.f));
	_sprite2_first->setOrigin(GVector2(1.f, 0.f));
	_sprite3_first->setOrigin(GVector2(1.f, 0.f));
	_sprite4_first->setOrigin(GVector2(1.f, 0.f));
	_sprite5_first->setOrigin(GVector2(1.f, 0.f));
	_sprite6_first->setOrigin(GVector2(1.f, 0.f));
	_sprite7_first->setOrigin(GVector2(1.f, 0.f));
	_sprite8_first->setOrigin(GVector2(1.f, 0.f));
	_sprite9_first->setOrigin(GVector2(1.f, 0.f));

	_sprite1_second = makeSprite("part_09", 0, WINDOW_HEIGHT);
	_sprite2_second = makeSprite("part_08", 0, _sprite1_second->getPositionY() - _sprite1_second->getFrameHeight());
	_sprite3_second = makeSprite("part_07", 0, _sprite2_second->getPositionY() - _sprite2_second->getFrameHeight());
	_sprite4_second = makeSprite("part_06", 0, _sprite3_second->getPositionY() - _sprite3_second->getFrameHeight());
	_sprite5_second = makeSprite("part_05", 0, _sprite4_second->getPositionY() - _sprite4_second->getFrameHeight());
	_sprite6_second = makeSprite("part_04", 0, _sprite5_second->getPositionY() - _sprite5_second->getFrameHeight());
	_sprite7_second = makeSprite("part_03", 0, _sprite6_second->getPositionY() - _sprite6_second->getFrameHeight());
	_sprite8_second = makeSprite("part_02", 0, _sprite7_second->getPositionY() - _sprite7_second->getFrameHeight());
	_sprite9_second = makeSprite("part_01", 0, _sprite8_second->getPositionY() - _sprite8_second->getFrameHeight());


	_frameWidth = _sprite1_first->getFrameWidth();
	return true;
}

void TestSceneBackground::update(float dt, Viewport * viewport)
{
	float diffi = viewport->getPositionWorld().x - _oldViewportX;
	_oldViewportX = viewport->getPositionWorld().x;

	addPositionSprite(_sprite1_first, _sprite1_second, diffi * _1_SCALE);
	addPositionSprite(_sprite2_first, _sprite2_second, diffi * _2_SCALE);
	addPositionSprite(_sprite3_first, _sprite3_second, diffi * _3_SCALE);
	addPositionSprite(_sprite4_first, _sprite4_second, diffi * _4_SCALE);
	addPositionSprite(_sprite5_first, _sprite5_second, diffi * _5_SCALE);

	addPositionSprite(_sprite6_first, _sprite6_second, dt * _6_VELOCITY / 1000);
	addPositionSprite(_sprite7_first, _sprite7_second, dt * _7_VELOCITY / 1000);
	addPositionSprite(_sprite8_first, _sprite8_second, dt * _8_VELOCITY / 1000);
	addPositionSprite(_sprite9_first, _sprite9_second, dt * _9_VELOCITY / 1000);
}

void TestSceneBackground::draw(LPD3DXSPRITE spriteHandle)
{
	_sprite1_first->render(spriteHandle);
	_sprite2_first->render(spriteHandle);
	_sprite3_first->render(spriteHandle);
	_sprite4_first->render(spriteHandle);
	_sprite5_first->render(spriteHandle);
	_sprite6_first->render(spriteHandle);
	_sprite7_first->render(spriteHandle);
	_sprite8_first->render(spriteHandle);
	_sprite9_first->render(spriteHandle);

	_sprite1_second->render(spriteHandle);
	_sprite2_second->render(spriteHandle);
	_sprite3_second->render(spriteHandle);
	_sprite4_second->render(spriteHandle);
	_sprite5_second->render(spriteHandle);
	_sprite6_second->render(spriteHandle);
	_sprite7_second->render(spriteHandle);
	_sprite8_second->render(spriteHandle);
	_sprite9_second->render(spriteHandle);
}

void TestSceneBackground::release()
{
}

Sprite * TestSceneBackground::makeSprite(string name, float x, float y)
{
	Sprite * result;
	result = SpriteResource::getInstance()->getSprite(eObjectID::MAP1BACKGROUND);
	result->setFrameRect(SpriteResource::getInstance()->getSourceRect(eObjectID::MAP1BACKGROUND, name));
	result->setPositionX(0);
	result->setPositionY(y);
	result->setOrigin(GVector2(0.f, 0.f));
	result->setScale(SCALE_FACTOR);
	result->setColor(C_WHITE);
	result->setZIndex(0.f);
	return result;
}

void TestSceneBackground::addPositionSprite(Sprite * first, Sprite * second, float diffirent)
{
	first->setPositionX(first->getPositionX() + diffirent);
	second->setPositionX(second->getPositionX() + diffirent);
	if (first->getPositionX() > _frameWidth)
	{
		first->setPositionX(0);
		second->setPositionX(0);
	}
	if (first->getPositionX() < 0)
	{
		first->setPositionX(_frameWidth - 1);
		second->setPositionX(_frameWidth - 1);
	}
}
