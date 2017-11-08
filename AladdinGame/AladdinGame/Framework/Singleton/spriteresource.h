#pragma once
#ifndef __SPRITERESOURCE_H__
#define __SPRITERESOURCE_H__


#include <fstream>

#include "../define.h"
#include "../sprite.h"

DEFINE_FRAMEWORK_START

class SpriteResource
{
public:
	static SpriteResource* getInstance();
	static void release();

	void loadResource(LPD3DXSPRITE spritehandle);
	Sprite* getSprite(eObjectID  id);

	RECT getSourceRect(eObjectID id, string name);
	void loadSpriteInfo(eObjectID id, const char* fileInfoPath);

	// release Sprite, dont release Texture, keep Texture to use in another Sprite.
	void releaseSprite(eObjectID id);

	// release Texture, and Sprite, only use releaseTexture if this is the last sprite.
	// - cẩn thận khi dùng hàm này. nhiều sprite có thể tham chiếu đến cùng một texture
	// - nếu release texture mà vẫn còn thể hiện nào đó tham chiếu đến thì sẽ bị lỗi.
	void releaseTexture(eObjectID id);	// dù dễ bị lỗi nhưng hàm này vẫn cần thiết để giải phóng texture khi không còn đối tượng nào nữa.

	~SpriteResource(void);
private:
	SpriteResource(void);
	static SpriteResource* _instance;
	map<eObjectID, Sprite*> _listSprite;
	map<eObjectID, map<string, RECT> > _sourceRectList;

};

DEFINE_FRAMEWORK_END
#endif // !__SpriteResource_H__
