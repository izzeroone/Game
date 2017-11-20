﻿#ifndef __COLLISION_COMPONENT__
#define __COLLISION_COMPONENT__

#include "../GameObject.h"
#include "Component.h"
#include <queue>

class CollisionComponent : public Component
{
public:
	CollisionComponent();
	CollisionComponent(GameObject* target);

	~CollisionComponent();

	void setTargerGameObject(GameObject * gameObject);
	/*
	kiểm tra va chạm với object khác, gọi event Begin, End.
	@otherObject: object cần kt va chạm
	@dt: delta time của mỗi frame
	@updatePosition: collision body sẽ cập nhật vị trí object lại nếu object chồng lấp lên object khác khi set = true
	*/
	void checkCollision(GameObject* otherObject, float dt, bool updatePosition = true);

	/*
	kiểm tra va chạm với object khác lấy được hướng va chạm
	@otherObject: object cần kt va chạm
	@direction: lấy hướng va chạm của otherObject
	@dt: delta time của mỗi frame
	@updatePosition: collision body sẽ cập nhật vị trí object lại nếu object chồng lấp lên object khác khi set = true
	*/
	bool checkCollision(GameObject* otherObject, eDirection& direction, float dt, bool updatePosition = true);

	bool isColliding(GameObject* otherObject);
		GameObject * isColliding(eObjectID eid);
	eDirection getCollidingDirection(GameObject * otherObject);

	void update(float dt);


	/*
	lấy collision rect trong world, tính theo gốc tọa độ bottom-left
	*/
	RECT getCollisionRect();

	/*
	Cập nhật target position khi va chạm
	@otherObject: đối tượng va chạm
	@direction: hướng bị va chạm của otherObject
	@withVelocity: TRUE khi kt va chạm với vận tốc, tham số move ko cần. FALSE khi va chạm bằng kt RECT
	@move: khoảng chồng lấp của 2 object.
	*/
	void updateTargetPosition(GameObject* otherObject, eDirection direction, bool withVelocity, GVector2 move = GVector2(0, 0));

	float isCollide(GameObject* otherObject, eDirection& direction, float dt);
	bool isColliding(RECT myRect, RECT otherRect);
	bool isColliding(GameObject* otherObject, float& moveX, float& moveY, float dt);

	RECT getSweptBroadphaseRect(GameObject* object, float dt);
	eDirection getSide(GameObject* otherObject);

private:
	GameObject* _target;
	RECT _collisionComponentRect;

	float _dxEntry, _dyEntry, _dxExit, _dyExit;
	float _txEntry, _tyEntry, _txExit, _tyExit;

	map<GameObject*, bool> _listColliding;
	map<GameObject*, eDirection> _listDirection; // direction colliding

	// Do nothing 
	virtual void init() override;

};

#endif // !__COLLISION_COMPONENT__
