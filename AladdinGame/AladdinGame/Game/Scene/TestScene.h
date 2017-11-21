
#ifndef __TEST_SCENE_H__
#define __TEST_SCENE_H__

#include "Scene.h"

#include "../../Framework/define.h"
#include "../../Framework/sprite.h"
#include "../../Framework/Singleton/spriteresource.h"
#include "../../Framework/Singleton/SoundManager.h"
#include "../../Framework/animation.h"
#include "../ObjectFactory.h"
#include "../../debug.h"
#include "../Player/Aladdin.h"

using namespace std;
LINK_FRAMEWORK


class TestScene : public Scene, public sigcxx::Trackable
{
public:
	TestScene();
	~TestScene();

	bool init() override;
	void update(float dt) override;
	void draw(LPD3DXSPRITE spriteHandle) override;
	void release() override;


	void setViewport(Viewport* viewport);
	void moveViewport(float offset, bool moveup, sigcxx::SLOT slot = nullptr);

	// Trả về một đối tượng theo id.
	// id: kiểu enum eID, định danh một đối tượng.
	// return: đối tượng cần tìm.
	GameObject* getObject(eObjectID id);

	// Lấy đối tượng bill.
	GameObject* getAladdin();
private:
	void destroyobject();				// kiển tra nếu object hết hạn sử dụng thì phá huỷ đối tượng

	// Danh sách đối tượng dùng để tạo spatical hashing.
	map <string, GameObject*> _mapobject;

	// Danh sách các đối tượng hoạt động rộng không thể đưa vào quadtree.
	// (Ví dụ main character) Spactial hashing 
	vector<GameObject*> _listobject;

	// Danh sách đối tượng nằm trong vùng active.
	// Mỗi vòng lặp sẽ được kiểm tra chỉnh sửa tại update, và sử dụng lại tại draw.
	vector<GameObject*>   _active_object;


	// Trỏ đến bill, một số đối tượng cần truyền bill vào để xử lý, lấy ở đây.
	GameObject* _Aladdin;
	//Map background
	Sprite* _mapBack;
	Sprite* _mapFront;

	void updateViewport(GameObject* objTracker);

	// Check if need to update viewport
	bool _updateViewport;
	RECT _rect;
	// Inherited via Scene
	virtual void updateInput(float dt) override;

};

#endif // !__TEST_SCENE_H__
