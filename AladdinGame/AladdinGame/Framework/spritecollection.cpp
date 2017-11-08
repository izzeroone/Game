﻿/*
HOW TO USE:
spritemanager is basic class to manage load and release sprite and texture.
It load all image you have, if you want to use sprite any where, just getSprite from SpriteManager.
if you dont want you use this image any more, you can call release.

everytime use this, you have to call SpriteManager::getInstance() first.
this is Singleton format.
Seemore about Singleton: http://www.stdio.vn/articles/read/224/singleton-pattern

you can call directly: SpriteManager::getInstance()->DOSOMETHING()
or reference it:
SpriteManager* _spritemanager;
...
_spritemanager = SpriteManager::getInstance();
...
_spritemanager->DOSOMETHING()

Next, you should call loadresource(LPD3DXSPRITE spriteHandle) in Game::loadresource().
It will load all your image from file to memory.
Remember: Insert your code to loadresource to load image from file.

If you want object reference to Sprite. call:
SpriteManager::getInstance()->getSprite(eID::OBJECT_ID)
what is eID::OBJECT_ID ?
in define.h you can insert element to eID.

OK. Now you have sprite to draw.

If you dont want to use this sprite any more, call releaseSprite or releaseTexture
they often are called in object::release

Call SpriteManager::release() in game:release() to clean all memory.
*/
#include "SpriteManager.h"
US_FRAMEWORK

SpriteManager* SpriteManager::_instance = nullptr;
SpriteManager::SpriteManager(void)
{
	// do nothing.
}

SpriteManager::~SpriteManager(void)
{
	for (auto spr = _listSprite.begin(); spr != _listSprite.end(); ++spr)
	{
		spr->second->release();		// release image
		delete spr->second;			// delete sprite
	}
	if (_listSprite.empty() == false)
		_listSprite.clear();		// remove all from MAP
}

void SpriteManager::loadResource(LPD3DXSPRITE spriteHandle)
{
	/* if you have any image, load them with this format */
	// [psedue code]
	// sp = new SPRITE(...)
	// this->_listSprite.insert(pair<eID, Sprite*>(eID::ENUMOBJECT, sp));

	//Sprite* sp = new Sprite(spriteHandle, L"Flower.png", 4, 4);
	//this->_listSprite.insert(pair<eID, Sprite*>(eID::FLOWER, sp));


	Sprite* sp = NULL;


	Sprite* bill = new Sprite(spriteHandle, L"Resources//Images//aladdin_animation_genesis.png");
	this->_listSprite[eID::ALADDIN] = bill;
	this->loadSpriteInfo(eID::ALADDIN, "Resources//Images//aladdin_animation_genesis.txt");

	Sprite* map = new Sprite(spriteHandle, L"Resources//Images//map1.png");
	this->_listSprite[eID::MAP1] = map;

	//Sprite* aladdin = new Sprite(spriteHandle, L"Resources//Images//aladdin_animation.png");
	//this->_listSprite[eID::ALADDIN] = aladdin;
	//this->loadSpriteInfo(eID::ALADDIN, "Resources//Images//aladdin_animation.txt");

	// Đọc file xml để tạo đối tượng sprite
	//sp = loadXMLDoc(spriteHandle, L"Resources//Map//stage1.xml");
	//sp->setOrigin(VECTOR2ZERO);
	//this->_listSprite[eID::MAPSTAGE1] = sp;

}

Sprite* SpriteManager::loadXMLDoc(LPD3DXSPRITE spritehandle, LPWSTR path)
{
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(path, pugi::parse_default | pugi::parse_pi);
	if (result == false)
	{
		OutputDebugString(L"Khong tim thay file xml");
		return nullptr;
	}
	pugi::xml_node root = doc.first_child();
	pugi::xml_node tileset_node = root.child("TileSet");
	// Tìm tên file.
	// Cắt từ chuỗi path ra để tìm thư mục.
	// Sau đó ghép với tên file ảnh được lấy từ file xml để load ảnh.
	string filename = tileset_node.attribute("FileName").as_string();   // get filename from xml node
	wstring L_filename = wstring(filename.begin(), filename.end());		// convert to wstring.

	wstring strpath = wstring(path);									// convert to wstring.
	int index = strpath.find_last_of(L'//');							// cut to find path
	strpath = strpath.substr(0, index);
	strpath += L"/" + L_filename;										// concat string.  Final string is strpath.
																		// Tìm số dòng
	int rows = tileset_node.attribute("Rows").as_int();
	int columns = tileset_node.attribute("Columns").as_int();
	return new Sprite(spritehandle, (LPWSTR)strpath.c_str(), rows * columns, columns);
}
Sprite* SpriteManager::getSprite(eID id)
{
	Sprite *it = this->_listSprite.find(id)->second;
	return new Sprite(*it);			// get the copy version of Sprite
}

RECT SpriteManager::getSourceRect(eID id, string name)
{
	//return _sourceRectList[id].at(name);
	return _sourceRectList[id][name];
}

void SpriteManager::loadSpriteInfo(eID id, const char* fileInfoPath)
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

void SpriteManager::releaseSprite(eID id)
{
	Sprite *it = this->_listSprite.find(id)->second;
	delete it;							// delete the sprite only, dont relase image
	this->_listSprite.erase(id);		// erase funciotn only remove the pointer from MAP, dont delete it.
}
void SpriteManager::releaseTexture(eID id)
{
	Sprite *spr = this->_listSprite.find(id)->second;
	spr->release();						// release image
	delete spr;
	this->_listSprite.erase(id);		// erase funciotn only remove the pointer from MAP, dont delete it.
}
SpriteManager* SpriteManager::getInstance()
{
	if (_instance == nullptr)
		_instance = new SpriteManager();
	return _instance;
}

void SpriteManager::release()
{
	delete _instance;			// _instance is static attribute, only static function can delete it.
	_instance = nullptr;
}
