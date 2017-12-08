#include "CollisionComponent.h"

//set update position for y only

CollisionComponent::CollisionComponent(eDirection side)
{
	_physicsSide = side;
}


CollisionComponent::~CollisionComponent()
{
	_physicsSide = eDirection::ALL;
}

void CollisionComponent::setTargerGameObject(GameObject * gameObject)
{
	_target = gameObject;
}

bool CollisionComponent::checkCollision(GameObject * otherObject, float dt, bool updatePosition)
{
	//check if other game object has physiscs component
	if (otherObject->getPhysicsComponent() == nullptr)
		return false;


	RECT myRect = _target->getPhysicsComponent()->getBounding();
	RECT otherRect = otherObject->getPhysicsComponent()->getBounding();
	return checkCollision(otherObject, myRect, otherRect, dt, updatePosition);
}

bool CollisionComponent::checkCollision(GameObject * otherObject, RECT myBound, float dt, bool updatePosition)
{
	//check if other game object has physiscs component
	if (otherObject->getPhysicsComponent() == nullptr)
		return false;

	RECT otherRect = otherObject->getPhysicsComponent()->getBounding();
	return checkCollision(otherObject, myBound, otherRect, dt, updatePosition);
}

bool CollisionComponent::checkCollision(GameObject * otherObject, RECT myBound, RECT otherBound, float dt, bool updatePosition)
{
	bool result = false;
	// sử dụng Broadphase rect để kt vùng tiếp theo có va chạm ko
	RECT broadphaseRect = getBroadphaseRect(myBound ,dt);	// là bound của object được mở rộng ra thêm một phần bằng với vận tốc (dự đoán trước bound)
	if (!isColliding(broadphaseRect, otherBound))				// kiểm tra tính chồng lắp của 2 hcn
	{
		return false; // doesn't have any chance to collision
	}
	GVector2 boxAVelo = _target->getPhysicsComponent()->getVelocity();
	GVector2 boxBVelo = otherObject->getPhysicsComponent()->getVelocity();

	//construct the aabb box
	AABB boxA = myBound;
	AABB boxB = otherBound;
	// construct the relative velocity ray
	GVector2 rvRay = (boxAVelo - boxBVelo) * dt / 1000;

	//targer physics side
	eDirection targetSide;
	if (otherObject->getBehaviorComponent() != nullptr)
		targetSide = otherObject->getBehaviorComponent()->getCollisionComponent()->getPhysicsSide();
	else
		targetSide = eDirection::ALL;
	// see if there is already a collision
	eDirection colliSide = eDirection::NONE;
	GVector2 rvRayIntersection;
	AABB md = boxB.minkowskiDifference(boxA);
	GVector2 penetrationVector;
	if (md.getMin().x <= 0 &&
		md.getMax().x >= 0 &&
		md.getMin().y <= 0 &&
		md.getMax().y >= 0)
	{
		// collision is occurring!
		result = true;
		_listColliding[otherObject] = true;
		penetrationVector = md.cloestPointOnBoundsToPoint(VECTOR2ZERO, targetSide, colliSide);
		_listColliside[otherObject] = colliSide;
		_listPenetrationVector[otherObject] = penetrationVector;
		if (updatePosition)
		{
			//zero out the box's velocity in the direction of the penetration
			if (penetrationVector != VECTOR2ZERO)
			{
				GVector2 tangent = VectorHelper::normalized(penetrationVector);
				tangent = VectorHelper::tangent(tangent);
				boxAVelo = VectorHelper::dotProduct(boxAVelo, tangent) * tangent;
				boxBVelo = VectorHelper::dotProduct(boxBVelo, tangent) * tangent;
				auto move = (Movement*)_target->getPhysicsComponent()->getComponent("Movement");
				if (move != nullptr)
				{
					move->setVelocity(boxAVelo);
					move->setAddPos(penetrationVector);
				}
				move = (Movement*)otherObject->getPhysicsComponent()->getComponent("Movement");
				if (move != nullptr)
				{
					move->setVelocity(boxBVelo);
				}
			}
		}
	}
	else
	{
		// see if there WILL be a collision
		float intersectFraction = md.getRayIntersectionFraction(VECTOR2ZERO, rvRay, targetSide, colliSide);

		if (intersectFraction < std::numeric_limits<float>::infinity())
		{
			result = true;
			_listColliding[otherObject] = true;
			_listColliside[otherObject] = colliSide;
			_listPenetrationVector[otherObject] = rvRay * intersectFraction;
			if (updatePosition)
			{
				// yup, there WILL be a collision this frame
				rvRayIntersection = rvRay * intersectFraction;

				// zero out the normal of the collision
				GVector2 nrvRay = VectorHelper::normalized(rvRay);
				GVector2 tangent = GVector2(-nrvRay.y, nrvRay.x);
				boxAVelo = VectorHelper::dotProduct(boxAVelo, tangent) * tangent;
				boxBVelo = VectorHelper::dotProduct(boxBVelo, tangent) * tangent;
				auto move = (Movement*)_target->getPhysicsComponent()->getComponent("Movement");
				if (move != nullptr)
				{
					move->setAddPos(boxAVelo * dt * intersectFraction / 1000);
					move->setVelocity(boxAVelo);

				}
				move = (Movement*)otherObject->getPhysicsComponent()->getComponent("Movement");
				if (move != nullptr)
				{
					move->setAddPos(boxBVelo * dt * intersectFraction / 1000);
					move->setVelocity(boxBVelo);
				}
			}
		}
	}
	return result;
}


RECT CollisionComponent::getBroadphaseRect(float dt)
{
	// vận tốc mỗi frame
	auto velocity = GVector2(_target->getPhysicsComponent()->getVelocity().x * dt / 1000, _target->getPhysicsComponent()->getVelocity().y * dt / 1000);
	auto myRect = _target->getPhysicsComponent()->getBounding();

	RECT rect;
	rect.top = velocity.y > 0 ? myRect.top + velocity.y : myRect.top;
	rect.bottom = velocity.y > 0 ? myRect.bottom : myRect.bottom + velocity.y;
	rect.left = velocity.x > 0 ? myRect.left : myRect.left + velocity.x;
	rect.right = velocity.y > 0 ? myRect.right + velocity.x : myRect.right;

	return rect;
}

RECT CollisionComponent::getBroadphaseRect(RECT myBound, float dt)
{
	// vận tốc mỗi frame
	auto velocity = GVector2(_target->getPhysicsComponent()->getVelocity().x * dt / 1000, _target->getPhysicsComponent()->getVelocity().y * dt / 1000);

	RECT rect;
	rect.top = velocity.y > 0 ? myBound.top + velocity.y : myBound.top;
	rect.bottom = velocity.y > 0 ? myBound.bottom : myBound.bottom + velocity.y;
	rect.left = velocity.x > 0 ? myBound.left : myBound.left + velocity.x;
	rect.right = velocity.y > 0 ? myBound.right + velocity.x : myBound.right;

	return rect;
}

eDirection CollisionComponent::getSide(GameObject* otherObject)
{
	auto myRect = _target->getPhysicsComponent()->getBounding();
	auto otherRect = otherObject->getPhysicsComponent()->getBounding();

	float left = otherRect.left - myRect.right;
	float top = otherRect.top - myRect.bottom;
	float right = otherRect.right - myRect.left;
	float bottom = otherRect.bottom - myRect.top;

	// kt va chạm
	if (left > 0 || right < 0 || top < 0 || bottom > 0)
		return eDirection::NONE;

	float minX;
	float minY;
	eDirection sideY;
	eDirection sideX;

	if (top > abs(bottom))
	{
		minY = bottom;
		sideY = eDirection::BOTTOM;
	}
	else
	{
		minY = top;
		sideY = eDirection::TOP;
	}


	if (abs(left) > right)
	{
		minX = right;
		sideX = eDirection::RIGHT;
	}
	else
	{
		minX = left;
		sideX = eDirection::LEFT;
	}


	if (abs(minX) < abs(minY))
	{
		return sideX;
	}
	else
	{
		return sideY;
	}
}

void CollisionComponent::setPhysicsSide(eDirection side)
{
	_physicsSide = side;
}

eDirection CollisionComponent::getPhysicsSide()
{
	return _physicsSide;
}

void CollisionComponent::reset()
{
	_listColliding.clear();
}


void CollisionComponent::init()
{

}

RECT CollisionComponent::getCollisionRect()
{
	RECT rect;

	rect.top = _target->getPhysicsComponent()->getBounding().top - _collisionComponentRect.top;
	rect.left = _target->getPhysicsComponent()->getBounding().left + _collisionComponentRect.left;

	rect.bottom = rect.top - abs(_collisionComponentRect.top - _collisionComponentRect.bottom);
	rect.right = rect.left + abs(_collisionComponentRect.right - _collisionComponentRect.left);

	return rect;
}

bool CollisionComponent::isColliding(RECT myRect, RECT otherRect)
{
	float left = otherRect.left - myRect.right;
	float top = otherRect.top - myRect.bottom;
	float right = otherRect.right - myRect.left;
	float bottom = otherRect.bottom - myRect.top;

	return !(left > 0 || right < 0 || top < 0 || bottom > 0);
}

void CollisionComponent::updatePosition(GameObject * otherObject)
{
	GVector2 boxAVelo = _target->getPhysicsComponent()->getVelocity();
	GVector2 boxBVelo = otherObject->getPhysicsComponent()->getVelocity();

	GVector2 tangent = VectorHelper::normalized(_listPenetrationVector[otherObject]);
	tangent = VectorHelper::tangent(tangent);
	boxAVelo = VectorHelper::dotProduct(boxAVelo, tangent) * tangent;
	boxBVelo = VectorHelper::dotProduct(boxBVelo, tangent) * tangent;
	auto move = (Movement*)_target->getPhysicsComponent()->getComponent("Movement");
	if (move != nullptr)
	{
		move->setVelocity(boxAVelo);
		move->setAddPos(_listPenetrationVector[otherObject]);
	}
	move = (Movement*)otherObject->getPhysicsComponent()->getComponent("Movement");
	if (move != nullptr)
	{
		move->setVelocity(boxBVelo);
	}
}

bool CollisionComponent::isColliding(GameObject* otherObject)
{
	if (_listColliding.find(otherObject) != _listColliding.end())
		return true;
	else
		return false;
}

GameObject * CollisionComponent::isColliding(eObjectID eid)
{
	for (auto it = _listColliding.begin(); it != _listColliding.end(); it++)
	{
		if (it->first->getID() == eid)
		{
			return it->first;
		}
	}
	return nullptr;
}

GameObject * CollisionComponent::isColliding(eObjectID eid, eDirection side)
{
	for (auto it = _listColliding.begin(); it != _listColliding.end(); it++)
	{
		if (it->first->getID() == eid && _listColliside[it->first] & side == side)
		{
			return it->first;
		}
	}
	return nullptr;
}

GameObject * CollisionComponent::isColliding(std::function<bool(GameObject*)> predicate)
{
	for (auto it = _listColliding.begin(); it != _listColliding.end(); it++)
	{
		if (predicate(it->first))
		{
			return it->first;
		}
	}
	return nullptr;
}

vector<GameObject*> CollisionComponent::areColliding(eObjectID eid)
{
	vector<GameObject*> result;
	for (auto it = _listColliding.begin(); it != _listColliding.end(); it++)
	{
		if (it->first->getID() == eid)
		{
			result.push_back(it->first);
		}
	}
	return result;	
}

eDirection CollisionComponent::getCollidingDirection(GameObject * otherObject)
{
	return _listColliside[otherObject];
}

void CollisionComponent::update(float dt)
{
}

