#include "CollisionComponent.h"

//set update position for y only

CollisionComponent::CollisionComponent()
{
}


CollisionComponent::~CollisionComponent()
{

}

void CollisionComponent::setTargerGameObject(GameObject * gameObject)
{
	_target = gameObject;
}

void CollisionComponent::checkCollision(GameObject * otherObject, float dt, bool updatePosition)
{
	//check if other game object has physiscs component
	if (otherObject->getPhysicsComponent() == nullptr)
		return;

	RECT myRect = _target->getPhysicsComponent()->getBounding();
	RECT otherRect = otherObject->getPhysicsComponent()->getBounding();



	// sử dụng Broadphase rect để kt vùng tiếp theo có va chạm ko
	RECT broadphaseRect = getBroadphaseRect(_target, dt);	// là bound của object được mở rộng ra thêm một phần bằng với vận tốc (dự đoán trước bound)
	if (!isColliding(broadphaseRect, otherRect))				// kiểm tra tính chồng lắp của 2 hcn
	{
		return; // doesn't have any chance to collision
	}
	GVector2 boxAVelo = _target->getPhysicsComponent()->getVelocity();
	GVector2 boxBVelo = otherObject->getPhysicsComponent()->getVelocity();

	//construct the aabb box
	AABB boxA = myRect;
	AABB boxB = otherRect;
	// construct the relative velocity ray
	GVector2 rvRay = (boxAVelo - boxBVelo) * dt / 1000;

	// see if there is already a collision
	GVector2 rvRayIntersection;
	AABB md = boxB.minkowskiDifference(boxA);
	GVector2 penetrationVector;
	if (md.getMin().x <= 0 &&
		md.getMax().x >= 0 &&
		md.getMin().y <= 0 &&
		md.getMax().y >= 0)
	{
		// collision is occurring!
		_listColliding[otherObject] = true;
		penetrationVector = md.cloestPointOnBoundsToPoint(VECTOR2ZERO);
	
		_listPenetrationVector[otherObject] = penetrationVector;
		if (updatePosition)
		{
			//zero out the box's velocity in the direction of the penetration
			if (penetrationVector != VECTOR2ZERO)
			{
				penetrationVector.x = floor(penetrationVector.x);
				penetrationVector.y = floor(penetrationVector.y);
				GVector2 tangent = VectorHelper::normalized(penetrationVector);
				tangent = VectorHelper::tangent(tangent);
				boxAVelo = VectorHelper::dotProduct(boxAVelo, tangent) * tangent;
				boxBVelo = VectorHelper::dotProduct(boxBVelo, tangent) * tangent;
				auto move = (Movement*)_target->getPhysicsComponent()->getComponent("Movement");
				if (_target->getID() == eObjectID::ALADDIN && otherObject->getID() == eObjectID::LAND && move != nullptr)
				{
					OutputDebugStringW(L"Penetration vector : ");
					__debugoutput(penetrationVector.x);
					__debugoutput(penetrationVector.y);
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
			float intersectFraction = md.getRayIntersectionFraction(VECTOR2ZERO, rvRay);
			_listPenetrationVector[otherObject] = penetrationVector;
			if (intersectFraction < std::numeric_limits<float>::infinity())
			{
				_listColliding[otherObject] = true;
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
					if (_target->getID() == eObjectID::ALADDIN && move != nullptr)
					{
						//move->setAddPos(boxAVelo * dt * intersectFraction / 1000);
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
	}


RECT CollisionComponent::getBroadphaseRect(GameObject* object, float dt)
{
	// vận tốc mỗi frame
	auto velocity = GVector2(object->getPhysicsComponent()->getVelocity().x * dt / 1000, object->getPhysicsComponent()->getVelocity().y * dt / 1000);
	auto myRect = object->getPhysicsComponent()->getBounding();

	RECT rect;
	rect.top = velocity.y > 0 ? myRect.top + velocity.y : myRect.top;
	rect.bottom = velocity.y > 0 ? myRect.bottom : myRect.bottom + velocity.y;
	rect.left = velocity.x > 0 ? myRect.left : myRect.left + velocity.x;
	rect.right = velocity.y > 0 ? myRect.right + velocity.x : myRect.right;

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

eDirection CollisionComponent::getCollidingDirection(GameObject * otherObject)
{
	return eDirection::TOP;
}

void CollisionComponent::update(float dt)
{
}

