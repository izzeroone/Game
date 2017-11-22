#ifndef __COLLISION_COMPONENT__
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

	void checkCollision(GameObject* otherObject, float dt, bool updatePosition = true);

	bool checkCollision(GameObject* otherObject, eDirection& direction, float dt, bool updatePosition = true);

	bool isColliding(GameObject* otherObject);
		GameObject * isColliding(eObjectID eid);
	eDirection getCollidingDirection(GameObject * otherObject);

	void update(float dt);


	RECT getCollisionRect();

	void updateTargetPosition(GameObject* otherObject, eDirection direction, bool withVelocity, GVector2 move = GVector2(0, 0));

	float isCollide(GameObject* otherObject, eDirection& direction, float dt);
	bool isColliding(RECT myRect, RECT otherRect);
	bool isColliding(GameObject* otherObject, float& moveX, float& moveY, float dt);

	RECT getSweptBroadphaseRect(GameObject* object, float dt);
	eDirection getSide(GameObject* otherObject);

	void reset();

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
