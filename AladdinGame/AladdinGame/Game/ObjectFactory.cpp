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

	animationComponent->setPhysiscComponent(physicsComponent);
	behaviorComponent->setPhysicsComponent(physicsComponent);
	behaviorComponent->setAnimationComponent(animationComponent);
	behaviorComponent->setGameController(GameController::getInstance());

	auto aladdin = new GameObject(eObjectID::ALADDIN, animationComponent, behaviorComponent, physicsComponent);
	aladdin->init();
	auto collisionComponent = (CollisionComponent*)aladdin->getPhysicsComponent()->getComponent("Collision");
	collisionComponent->setTargerGameObject(aladdin);

	return aladdin;
}
