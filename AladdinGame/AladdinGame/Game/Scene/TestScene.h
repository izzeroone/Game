
#ifndef __PLAY_SCENE_H__
#define __PLAY_SCENE_H__

#include "Sprite.h"
#include "SpriteManager.h"
#include "SoundManager.h"
#include "Animation.h"
#include "debug.h"

#include "Aladdin.h"
#include "Land.h"
#include "Scene.h"


using namespace std;
US_FRAMEWORK

ACTOR_SCENARIO


class TestScene : public Scene
{
public:
	TestScene();
	~TestScene();

	bool init() override;
	void updateInput(float dt) override;
	void update(float dt) override;
	void draw(LPD3DXSPRITE spriteHandle) override;
	void release() override;


	void setViewport(Viewport* viewport);
	//static Viewport* getViewport();

	// Trả về một đối tượng theo id.
	// id: kiểu enum eID, định danh một đối tượng.
	// return: đối tượng cần tìm.
	BaseObject* getObject(eID id);

	// Lấy đối tượng bill.
	Aladdin* getAladdin();
private:
	void destroyobject();				// kiển tra nếu object hết hạn sử dụng thì phá huỷ đối tượng

	// Danh sách đối tượng dùng để tạo spatical hashing.
	map <string, BaseObject*> _mapobject;

	// Danh sách các đối tượng hoạt động rộng không thể đưa vào quadtree.
	// (Ví dụ main character) Spactial hashing 
	vector<BaseObject*> _listobject;

	// Danh sách đối tượng nằm trong vùng active.
	// Mỗi vòng lặp sẽ được kiểm tra chỉnh sửa tại update, và sử dụng lại tại draw.
	vector<BaseObject*>   _active_object;

	vector<IControlable*> _listControlObject;

	// Trỏ đến bill, một số đối tượng cần truyền bill vào để xử lý, lấy ở đây.
	BaseObject* _bill;
	//Map background
	Sprite* _map;
	void updateViewport(BaseObject* objTracker);


};

#endif // !__PLAY_SCENE_H__
