#pragma once
#ifndef __SPRITECOLLECTION_H__
#define __SPRITECOLLECTION_H__


#include <fstream>

#include "define.h"
#include "sprite.h"

DEFINE_FRAMEWORK_START

class SpriteCollection
{
public:
	static SpriteCollection* getInstance();
	static void release();

	void loadResource(LPD3DXSPRITE spritehandle);
	Sprite* getSprite(eID id);

	RECT getSourceRect(eID id, string name);
	void loadSpriteInfo(eID id, const char* fileInfoPath);

	// release Sprite, dont release Texture, keep Texture to use in another Sprite.
	void releaseSprite(eID id);

	// release Texture, and Sprite, only use releaseTexture if this is the last sprite.
	// - cẩn thận khi dùng hàm này. nhiều sprite có thể tham chiếu đến cùng một texture
	// - nếu release texture mà vẫn còn thể hiện nào đó tham chiếu đến thì sẽ bị lỗi.
	void releaseTexture(eID id);	// dù dễ bị lỗi nhưng hàm này vẫn cần thiết để giải phóng texture khi không còn đối tượng nào nữa.

	~SpriteCollection(void);
private:
	SpriteCollection(void);
	static SpriteCollection* _instance;
	map<eID, Sprite*> _listSprite;
	map<eID, map<string, RECT> > _sourceRectList;

	Sprite* loadXMLDoc(LPD3DXSPRITE spritehandle, LPWSTR path);
};

DEFINE_FRAMEWORK_END
#endif // !__SpriteCollection_H__
