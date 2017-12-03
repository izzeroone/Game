#include "spriteresource.h"
#include "../../debug.h"
LINK_FRAMEWORK

SpriteResource* SpriteResource::_instance = nullptr;
SpriteResource::SpriteResource(void)
{
	// do nothing.
}

SpriteResource::~SpriteResource(void)
{
	for (auto spr = _listSprite.begin(); spr != _listSprite.end(); ++spr)
	{
		spr->second->release();		// release image
		delete spr->second;			// delete sprite
	}
	if (_listSprite.empty() == false)
		_listSprite.clear();		// remove all from MAP
}

void SpriteResource::loadResource(LPD3DXSPRITE spriteHandle)
{
	Sprite* sp = NULL;


	Sprite* aladdin = new Sprite(spriteHandle, L"Resources//Images//aladdin_animation_genesis.png");
	this->_listSprite[eObjectID::ALADDIN] = aladdin;
	this->loadSpriteInfo(eObjectID::ALADDIN, "Resources//Images//aladdin_animation_genesis.txt");

	Sprite* map = new Sprite(spriteHandle, L"Resources//Images//map1.png");
	this->_listSprite[eObjectID::MAP1] = map;
	this->loadSpriteInfo(eObjectID::MAP1, "Resources//Images//map1.txt");

	Sprite* guard = new Sprite(spriteHandle, L"Resources//Images//guard.png");
	this->_listSprite[eObjectID::GUARD] = guard;
	this->loadSpriteInfo(eObjectID::GUARD, "Resources//Images//guard.txt");

	Sprite* flame = new Sprite(spriteHandle, L"Resources//Images//jafar.png");
	this->_listSprite[eObjectID::JAFAR] = flame;
	this->loadSpriteInfo(eObjectID::JAFAR, "Resources//Images//jafar.txt");

	Sprite* map1background = new Sprite(spriteHandle, L"Resources//Images//map1_background.png");
	this->_listSprite[eObjectID::MAP1BACKGROUND] = map1background;
	this->loadSpriteInfo(eObjectID::MAP1BACKGROUND, "Resources//Images//map1_background.txt");

	Sprite* civilian = new Sprite(spriteHandle, L"Resources//Images//civilian_enemies.png");
	this->_listSprite[eObjectID::CIVILIAN] = civilian;
	this->loadSpriteInfo(eObjectID::CIVILIAN, "Resources//Images//civilian_enemies.txt");


}

Sprite* SpriteResource::getSprite(eObjectID id)
{
	Sprite *it = this->_listSprite.find(id)->second;
	return new Sprite(*it);			// get the copy version of Sprite
}

RECT SpriteResource::getSourceRect(eObjectID id, string name)
{
	return _sourceRectList[id][name];
}

GVector2 SpriteResource::getSourceTransition(eObjectID id, string name)
{
	return _sourceTransitionList[id][name];
}

void SpriteResource::loadSpriteInfo(eObjectID id, const char* fileInfoPath)
{
	FILE* file;
	file = fopen(fileInfoPath, "r");

	if (file)
	{
		while (!feof(file))
		{
			RECT rect;
			GVector2 transition;
			char name[100];
			fgets(name, 100, file);

			fscanf(file, "%s %d %d %d %d %f %f", &name, &rect.left, &rect.top, &rect.right, &rect.bottom, &transition.x, &transition.y);

			_sourceRectList[id][string(name)] = rect;
			_sourceTransitionList[id][string(name)] = transition;
		}
	}

	fclose(file);
}

void SpriteResource::releaseSprite(eObjectID id)
{
	Sprite *it = this->_listSprite.find(id)->second;
	delete it;							// delete the sprite only, dont relase image
	this->_listSprite.erase(id);		// erase funciotn only remove the pointer from MAP, dont delete it.
}
void SpriteResource::releaseTexture(eObjectID id)
{
	Sprite *spr = this->_listSprite.find(id)->second;
	spr->release();						// release image
	delete spr;
	this->_listSprite.erase(id);		// erase funciotn only remove the pointer from MAP, dont delete it.
}
SpriteResource* SpriteResource::getInstance()
{
	if (_instance == nullptr)
		_instance = new SpriteResource();
	return _instance;
}

void SpriteResource::release()
{
	delete _instance;			// _instance is static attribute, only static function can delete it.
	_instance = nullptr;
}
