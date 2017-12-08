
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
	GameObject(eObjectID eid, AnimationComponent* animationComponent = nullptr, BehaviorComponent* behaviorComponent = nullptr, PhysicsComponent* physicsComponent = nullptr);
	virtual ~GameObject();

	virtual void init();
	virtual void update(float deltatime);
	virtual void draw(LPD3DXSPRITE, Viewport*);
	virtual void release();

	virtual AnimationComponent* getAnimationComponent();
	virtual void setAnimationComponent(AnimationComponent* animationComponent);

	virtual PhysicsComponent* getPhysicsComponent();
	virtual void setPhysicsComponent(PhysicsComponent* PhysicsComponent);

	virtual BehaviorComponent* getBehaviorComponent();
	virtual void setBehaviorComponent(BehaviorComponent* BehaviorComponent);


	eObjectID getID();
	void setID(eObjectID eid);

protected:
	eObjectID _id;
	AnimationComponent* _animationComponent;
	BehaviorComponent* _behaviorComponent;
	PhysicsComponent* _physicsComponent;

};
typedef GameObject* pGameObject;

#endif // !__GameObject_H__
