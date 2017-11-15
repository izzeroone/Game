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
	physicsComponent->setAnimationComponent(animationComponent);

	auto aladdin = new GameObject(eObjectID::ALADDIN, animationComponent, behaviorComponent, physicsComponent);
	aladdin->init();
	auto collisionComponent = (CollisionComponent*)aladdin->getPhysicsComponent()->getComponent("Collision");
	collisionComponent->setTargerGameObject(aladdin);

	return aladdin;
}

GameObject * ObjectFactory::getLand(int x, int y, int width, int height, eDirection physicBodyDirection, eLandType type)
{
	auto physicsComponent = new LandPhysiscsComponent();

	auto land = new Land();
	land->setPhysicsComponent(physicsComponent);
	land->init(x, y, width, height, physicBodyDirection, type);

	auto collisionComponent = (CollisionComponent*)land->getPhysicsComponent()->getComponent("Collision");
	collisionComponent->setTargerGameObject(land);
	return land;
}

GameObject * ObjectFactory::getRope(int x, int y, int width, int height, eDirection physicBodyDirection, eRopeType type)
{
	auto physicsComponent = new RopePhysiscsComponent();

	auto rope = new Rope();
	rope->setPhysicsComponent(physicsComponent);
	rope->init(x, y, width, height, physicBodyDirection, type);

	auto collisionComponent = (CollisionComponent*)rope->getPhysicsComponent()->getComponent("Collision");
	collisionComponent->setTargerGameObject(rope);
	return rope;
}
