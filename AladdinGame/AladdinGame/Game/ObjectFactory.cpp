#include "ObjectFactory.h"

ObjectFactory::ObjectFactory()
{
}

ObjectFactory::~ObjectFactory()
{
}

GameObject * ObjectFactory::getAladdin()
{
	auto physicsComponent = new AladdinPhysicsComponent();
	auto animationComponent = new AladdinAnimationComponent();
	auto behaviorComponent = new AladdinBehaviorComponent();
	auto aladdin = new GameObject(eObjectID::ALADDIN, animationComponent, behaviorComponent, physicsComponent);
	return aladdin;
}
