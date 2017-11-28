#ifndef __COLLISION_COMPONENT__
#define __COLLISION_COMPONENT__

#include "../GameObject.h"
#include "../AABB.h"
#include "Component.h"
#include "../../Game/Scene/SceneManager.h"
#include <functional>
#include <queue>
#include <cmath>

class CollisionComponent : public Component
{
public:
	CollisionComponent(eDirection side = eDirection::NONE);

	~CollisionComponent();

	void setTargerGameObject(GameObject * gameObject);

	void checkCollision(GameObject* otherObject, float dt, bool updatePosition = false);

	bool isColliding(GameObject* otherObject);
	GameObject * isColliding(eObjectID eid);
	GameObject * isColliding(std::function<bool(GameObject*)> predicate);
	eDirection getCollidingDirection(GameObject * otherObject);

	void update(float dt);


	RECT getCollisionRect();
	bool isColliding(RECT myRect, RECT otherRect);

	RECT getBroadphaseRect(GameObject* object, float dt);
	eDirection getSide(GameObject* otherObject);

	void setPhysicsSide(eDirection side);
	eDirection getPhysicsSide();

	void reset();

private:
	GameObject* _target;
	RECT _collisionComponentRect;
	eDirection _physicsSide; //which side should be check for update position

	map<GameObject*, bool> _listColliding;
	map<GameObject*, GVector2> _listPenetrationVector; // direction colliding


	// Do nothing 
	virtual void init() override;

};

#endif // !__COLLISION_COMPONENT__
