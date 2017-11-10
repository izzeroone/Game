#include "spriteresource.h"
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


	// Đọc file xml để tạo đối tượng sprite
	//sp = loadXMLDoc(spriteHandle, L"Resources//Map//stage1.xml");
	//sp->setOrigin(VECTOR2ZERO);
	//this->_listSprite[eObjectID::MAPSTAGE1] = sp;

}

Sprite* SpriteResource::getSprite(eObjectID id)
{
	Sprite *it = this->_listSprite.find(id)->second;
	return new Sprite(*it);			// get the copy version of Sprite
}

RECT SpriteResource::getSourceRect(eObjectID id, string name)
{
	//return _sourceRectList[id].at(name);
	return _sourceRectList[id][name];
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
			char name[100];
			fgets(name, 100, file);

			fscanf(file, "%s %d %d %d %d", &name, &rect.left, &rect.top, &rect.right, &rect.bottom);

			_sourceRectList[id][string(name)] = rect;
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
