
#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__
#include "define.h"
#include "Singleton/spriteresource.h"
#include "sprite.h"
#include "Component/AnimationComponent.h"
#include "Component/BehaviorComponent.h"
#include "Component/PhysicsComponent.h"
#include "Singleton/gamecontroller.h"


LINK_FRAMEWORK
class GameObject
{
public:
	GameObject();
	GameObject(eObjectID eid, AnimationComponent* animationComponent, BehaviorComponent* behaviorComponent, PhysicsComponent* physicsComponent);
	virtual ~GameObject();

	virtual void init() = 0;
	virtual void update(float deltatime) = 0;
	virtual void draw(LPD3DXSPRITE, Viewport*) = 0;
	virtual void release() = 0;


protected:
	eObjectID _id;
	AnimationComponent* _animationComponent;
	BehaviorComponent* _behaviorComponent;
	PhysicsComponent* _physicsComponent;

};
typedef GameObject* pGameObject;

#endif // !__GameObject_H__
