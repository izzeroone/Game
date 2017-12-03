#include "ObjectFactory.h"

ObjectFactory::ObjectFactory()
{
}

ObjectFactory::~ObjectFactory()
{
}


map<string, GameObject*>* ObjectFactory::getMapObjectFromFile(const string path)
{
	pugi::xml_document doc;
	map<string, GameObject*>* listobject = new map<string, GameObject*>();

	// Mở file và đọc
	xml_parse_result result = doc.load_file(path.data(), pugi::parse_default | pugi::parse_pi);
	if (result == false)
	{
		return listobject;
	}

	xml_node objects = doc.child("Objects");
	auto list = objects.children();

	// Lấy id từ file xml. so sánh với eID, tuỳ theo eID nào mà gọi đến đúng hàm load cho riêng object đó.
	for (auto item : list)
	{
		int id = item.attribute("Id").as_int();
		string name = item.attribute("Name").as_string();
		eObjectID enumID;
		try {
			enumID = (eObjectID)id;
		}
		catch (exception e) {
			continue;
		}
		GameObject* obj = getObjectById(item, enumID);
		if (obj != NULL)
			(*listobject)[name] = obj;
	}
	return listobject;
}

map<string, std::function<GameObject*()>>* ObjectFactory::getMapObjectFunctionFromFile(const string path)
{
	pugi::xml_document doc;
	map<string, std::function<GameObject*()>>* listobject = new map<string, std::function<GameObject*()>>();

	// Mở file và đọc
	xml_parse_result result = doc.load_file(path.data(), pugi::parse_default | pugi::parse_pi);
	if (result == false)
	{
		return listobject;
	}

	xml_node objects = doc.child("Objects");
	auto list = objects.children();

	// Lấy id từ file xml. so sánh với eID, tuỳ theo eID nào mà gọi đến đúng hàm load cho riêng object đó.
	for (auto item : list)
	{
		int id = item.attribute("Id").as_int();
		string name = item.attribute("Name").as_string();
		eObjectID enumID;
		try {
			enumID = (eObjectID)id;
		}
		catch (exception e) {
			continue;
		}
		auto obj = getFunctionById(item, enumID);
		if (obj != NULL)
			(*listobject)[name] = obj;
	}
	return listobject;
}

GameObject* ObjectFactory::getObjectById(xml_node node, eObjectID id)
{
	switch (id)
	{
	case LAND:
		return getLand(node);
	case ROPE:
		return getRope(node);
	case THROWER:
		return getThrower(node);
	case HAKIM:
		return getHakim(node);
	case FALZA:
		return getFalza(node);
	case NAHBI:
		return getNahbi(node);
	default:
		break;
	}
}

std::function<GameObject*() > ObjectFactory::getFunctionById(xml_node node, eObjectID id)
{
	switch (id)
	{
	case LAND:
		return bind(getLand, node);
		break;
	case ROPE:
		return bind(getRope, node);
		break;
	default:
		break;
	}
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

GameObject * ObjectFactory::getApple(GVector2 pos, GVector2 velocity)
{
	auto physicsComponent = new ApplePhysicsComponent();
	auto animationComponent = new AppleAnimationComponent();
	auto behaviorComponent = new AppleBehaviorComponent();

	animationComponent->setPhysiscComponent(physicsComponent);
	behaviorComponent->setPhysicsComponent(physicsComponent);
	behaviorComponent->setAnimationComponent(animationComponent);
	behaviorComponent->setGameController(GameController::getInstance());
	physicsComponent->setAnimationComponent(animationComponent);


	physicsComponent->setPosition(pos);

	auto apple = new GameObject(eObjectID::APPLE, animationComponent, behaviorComponent, physicsComponent);
	apple->init();
	auto collisionComponent = (CollisionComponent*)apple->getPhysicsComponent()->getComponent("Collision");
	collisionComponent->setTargerGameObject(apple);


	auto move = (Movement*)physicsComponent->getComponent("Movement");
	move->setVelocity(velocity);

	return apple;
}

GameObject * ObjectFactory::getDagger(GVector2 pos, GVector2 velocity)
{
	auto physicsComponent = new DaggerPhysicsComponent();
	auto animationComponent = new DaggerAnimationComponent();
	auto behaviorComponent = new DaggerBehaviorComponent();

	animationComponent->setPhysiscComponent(physicsComponent);
	behaviorComponent->setPhysicsComponent(physicsComponent);
	behaviorComponent->setAnimationComponent(animationComponent);
	behaviorComponent->setGameController(GameController::getInstance());
	physicsComponent->setAnimationComponent(animationComponent);


	physicsComponent->setPosition(pos);

	auto Dagger = new GameObject(eObjectID::DAGGER, animationComponent, behaviorComponent, physicsComponent);
	Dagger->init();
	auto collisionComponent = (CollisionComponent*)Dagger->getPhysicsComponent()->getComponent("Collision");
	collisionComponent->setTargerGameObject(Dagger);


	auto move = (Movement*)physicsComponent->getComponent("Movement");
	move->setVelocity(velocity);

	return Dagger;
}

GameObject * ObjectFactory::getSword(GVector2 pos, float width, float height, bool canSlashEnemy)
{
	auto physicsComponent = new SwordPhysicsComponent();
	auto behaviorComponent = new SwordBehaviorComponent();

	behaviorComponent->setPhysicsComponent(physicsComponent);


	auto sword = new Sword();
	sword->setID(eObjectID::SWORD);
	sword->setPhysicsComponent(physicsComponent);
	sword->setBehaviorComponent(behaviorComponent);
	sword->setAnimationComponent(nullptr);
	sword->init(pos.x, pos.y, width, height, eDirection::ALL, canSlashEnemy);

	auto collisionComponent = (CollisionComponent*)sword->getPhysicsComponent()->getComponent("Collision");
	collisionComponent->setTargerGameObject(sword);
	collisionComponent->setPhysicsSide(eDirection::ALL);

	return sword;
}

GameObject * ObjectFactory::getLand(xml_node node)
{
	auto properties = getObjectProperties(node);
	if (properties.size() == 0)
		return nullptr;

	int x, y, width, height;
	eDirection dir;
	eLandType type;

	x = stoi(properties["X"]) * SCALE_FACTOR;
	y = stoi(properties["Y"]) * SCALE_FACTOR;
	width = stoi(properties["Width"]) * SCALE_FACTOR;
	height = stoi(properties["Height"]) * SCALE_FACTOR;

	if (properties.find("type") != properties.end())
	{
		type = (eLandType)(stoi(properties.find("type")->second));
	}
	else
	{
		type = eLandType::lNORMAL;
	}

	if (properties.find("physicBodyDirection") != properties.end())
	{
		dir = (eDirection)(stoi(properties.find("physicBodyDirection")->second));
	}
	else
	{
		dir = eDirection::TOP;
	}

	auto behaviorComponent = new LandBehaviorComponent();
	PhysicsComponent * physicsComponent;
	AnimationComponent * animationComponent = nullptr;
	if (type == eLandType::lFALLING)
	{
		physicsComponent = new FallingLandPhysiscsComponent();
		animationComponent = new FallingLandAnimationComponent();
		animationComponent->setPhysiscComponent(physicsComponent);
		physicsComponent->setPosition(GVector2(x, y));
	}
	else
	{
		physicsComponent = new LandPhysiscsComponent();
	}
	behaviorComponent->setPhysicsComponent(physicsComponent);
	behaviorComponent->setAnimationComponent(animationComponent);

	auto land = new Land();
	land->setPhysicsComponent(physicsComponent);
	land->setBehaviorComponent(behaviorComponent);
	land->setAnimationComponent(animationComponent);
	land->init(x, y, width, height, dir, type);

	auto collisionComponent = (CollisionComponent*)land->getPhysicsComponent()->getComponent("Collision");
	collisionComponent->setTargerGameObject(land);
	collisionComponent->setPhysicsSide(dir);
	return land;
}

GameObject * ObjectFactory::getRope(xml_node node)
{
	auto properties = getObjectProperties(node);
	if (properties.size() == 0)
		return nullptr;

	int x, y, width, height;
	eDirection dir;
	eRopeType type;

	x = stoi(properties["X"]) * SCALE_FACTOR;
	y = stoi(properties["Y"]) * SCALE_FACTOR;
	width = stoi(properties["Width"]) * SCALE_FACTOR;
	height = stoi(properties["Height"]) * SCALE_FACTOR;

	if (properties.find("type") != properties.end())
	{
		type = (eRopeType)(stoi(properties.find("type")->second));
	}
	else
	{
		type = eRopeType::rVERTICAL;
	}

	if (properties.find("physicBodyDirection") != properties.end())
	{
		dir = (eDirection)(stoi(properties.find("physicBodyDirection")->second));
	}
	else
	{
		dir = eDirection::ALL;
	}

	auto physicsComponent = new RopePhysiscsComponent();

	auto rope = new Rope();
	rope->setPhysicsComponent(physicsComponent);
	rope->init(x, y, width, height, dir, type);

	auto collisionComponent = (CollisionComponent*)rope->getPhysicsComponent()->getComponent("Collision");
	collisionComponent->setTargerGameObject(rope);
	collisionComponent->setPhysicsSide(dir);
	return rope;
}

GameObject * ObjectFactory::getHakim(GVector2 pos, float rangeXStart, float rangeXEnd)
{
	auto physicsComponent = new HakimPhysicsComponent();
	auto animationComponent = new HakimAnimationComponent();
	EnemyBehaviorComponent* behaviorComponent = new HakimBehaviorComponent();

	animationComponent->setPhysiscComponent(physicsComponent);
	behaviorComponent->setPhysicsComponent(physicsComponent);
	behaviorComponent->setAnimationComponent(animationComponent);
	behaviorComponent->setGameController(GameController::getInstance());
	physicsComponent->setAnimationComponent(animationComponent);

	physicsComponent->setPosition(pos);

	behaviorComponent->setRange(rangeXStart, rangeXEnd);

	auto hakim = new GameObject(eObjectID::HAKIM, animationComponent, behaviorComponent, physicsComponent);
	hakim->init();
	auto collisionComponent = (CollisionComponent*)hakim->getPhysicsComponent()->getComponent("Collision");
	collisionComponent->setTargerGameObject(hakim);
	collisionComponent->setPhysicsSide(eDirection::ALL);

	return hakim;
}

GameObject * ObjectFactory::getHakim(xml_node node)
{
	GVector2 pos;
	pos.x = node.attribute("X").as_float() * SCALE_FACTOR;
	pos.y = node.attribute("Y").as_float() * SCALE_FACTOR;
	auto bound = node.child("Bound");
	float rangeXStart = bound.attribute("Left").as_float() * SCALE_FACTOR;
	float rangeXEnd = bound.attribute("Right").as_float() * SCALE_FACTOR;
	return getHakim(pos, rangeXStart, rangeXEnd);
}

GameObject * ObjectFactory::getFalza(GVector2 pos, float rangeXStart, float rangeXEnd)
{
	auto physicsComponent = new FalzaPhysicsComponent();
	auto animationComponent = new FalzaAnimationComponent();
	EnemyBehaviorComponent* behaviorComponent = new FalzaBehaviorComponent();

	animationComponent->setPhysiscComponent(physicsComponent);
	behaviorComponent->setPhysicsComponent(physicsComponent);
	behaviorComponent->setAnimationComponent(animationComponent);
	behaviorComponent->setGameController(GameController::getInstance());
	physicsComponent->setAnimationComponent(animationComponent);

	physicsComponent->setPosition(pos);

	behaviorComponent->setRange(rangeXStart, rangeXEnd);

	auto Falza = new GameObject(eObjectID::FALZA, animationComponent, behaviorComponent, physicsComponent);
	Falza->init();
	auto collisionComponent = (CollisionComponent*)Falza->getPhysicsComponent()->getComponent("Collision");
	collisionComponent->setTargerGameObject(Falza);
	collisionComponent->setPhysicsSide(eDirection::ALL);

	return Falza;
}

GameObject * ObjectFactory::getFalza(xml_node node)
{
	GVector2 pos;
	pos.x = node.attribute("X").as_float() * SCALE_FACTOR;
	pos.y = node.attribute("Y").as_float() * SCALE_FACTOR;
	auto bound = node.child("Bound");
	float rangeXStart = bound.attribute("Left").as_float() * SCALE_FACTOR;
	float rangeXEnd = bound.attribute("Right").as_float() * SCALE_FACTOR;
	return getFalza(pos, rangeXStart, rangeXEnd);
}

GameObject * ObjectFactory::getNahbi(GVector2 pos, float rangeXStart, float rangeXEnd)
{
	auto physicsComponent = new NahbiPhysicsComponent();
	auto animationComponent = new NahbiAnimationComponent();
	EnemyBehaviorComponent* behaviorComponent = new NahbiBehaviorComponent();

	animationComponent->setPhysiscComponent(physicsComponent);
	behaviorComponent->setPhysicsComponent(physicsComponent);
	behaviorComponent->setAnimationComponent(animationComponent);
	behaviorComponent->setGameController(GameController::getInstance());
	physicsComponent->setAnimationComponent(animationComponent);

	physicsComponent->setPosition(pos);

	behaviorComponent->setRange(rangeXStart, rangeXEnd);

	auto Nahbi = new GameObject(eObjectID::NAHBI, animationComponent, behaviorComponent, physicsComponent);
	Nahbi->init();
	auto collisionComponent = (CollisionComponent*)Nahbi->getPhysicsComponent()->getComponent("Collision");
	collisionComponent->setTargerGameObject(Nahbi);
	collisionComponent->setPhysicsSide(eDirection::ALL);

	return Nahbi;
}

GameObject * ObjectFactory::getNahbi(xml_node node)
{
	GVector2 pos;
	pos.x = node.attribute("X").as_float() * SCALE_FACTOR;
	pos.y = node.attribute("Y").as_float() * SCALE_FACTOR;
	auto bound = node.child("Bound");
	float rangeXStart = bound.attribute("Left").as_float() * SCALE_FACTOR;
	float rangeXEnd = bound.attribute("Right").as_float() * SCALE_FACTOR;
	return getNahbi(pos, rangeXStart, rangeXEnd);
}

GameObject * ObjectFactory::getFlame(GVector2 pos)
{
	FlamePhysicsComponent * physicsComponent = new FlamePhysicsComponent();
	auto animationComponent = new FlameAnimationComponent();
	auto behaviorComponent = new FlameBehaviorComponent();

	animationComponent->setPhysiscComponent(physicsComponent);
	behaviorComponent->setPhysicsComponent(physicsComponent);
	behaviorComponent->setAnimationComponent(animationComponent);
	behaviorComponent->setGameController(GameController::getInstance());
	physicsComponent->setAnimationComponent(animationComponent);

	physicsComponent->setPosition(pos);


	auto Flame = new GameObject(eObjectID::FLAME, animationComponent, behaviorComponent, physicsComponent);
	Flame->init();
	auto collisionComponent = (CollisionComponent*)Flame->getPhysicsComponent()->getComponent("Collision");
	collisionComponent->setTargerGameObject(Flame);
	collisionComponent->setPhysicsSide(eDirection::ALL);

	return Flame;
}

GameObject * ObjectFactory::getExlplosionPot(GVector2 pos)
{
	auto physicsComponent = new ExplosionPotPhysicsComponent();
	auto animationComponent = new ExplosionPotAnimationComponent();
	auto behaviorComponent = new ExplosionPotBehaviorComponent();

	animationComponent->setPhysiscComponent(physicsComponent);
	behaviorComponent->setPhysicsComponent(physicsComponent);
	behaviorComponent->setAnimationComponent(animationComponent);
	behaviorComponent->setGameController(GameController::getInstance());
	physicsComponent->setAnimationComponent(animationComponent);


	physicsComponent->setPosition(pos);

	auto ExplosionPot = new GameObject(eObjectID::EXPLOSIONPOT, animationComponent, behaviorComponent, physicsComponent);
	ExplosionPot->init();
	auto collisionComponent = (CollisionComponent*)ExplosionPot->getPhysicsComponent()->getComponent("Collision");
	collisionComponent->setTargerGameObject(ExplosionPot);

	return ExplosionPot;
}


GameObject * ObjectFactory::getThrower(GVector2 pos)
{
	auto physicsComponent = new ThrowerPhysicsComponent();
	auto animationComponent = new ThrowerAnimationComponent();
	auto behaviorComponent = new ThrowerBehaviorComponent();

	animationComponent->setPhysiscComponent(physicsComponent);
	behaviorComponent->setPhysicsComponent(physicsComponent);
	behaviorComponent->setAnimationComponent(animationComponent);
	behaviorComponent->setGameController(GameController::getInstance());


	physicsComponent->setPosition(pos);

	auto thrower = new GameObject(eObjectID::THROWER, animationComponent, behaviorComponent, physicsComponent);
	thrower->init();

	return thrower;
}

GameObject * ObjectFactory::getThrower(xml_node node)
{
	GVector2 pos;
	pos.x = node.attribute("X").as_float() * SCALE_FACTOR;
	pos.y = node.attribute("Y").as_float() * SCALE_FACTOR;

	return getThrower(pos);
}

map<string, string> ObjectFactory::getObjectProperties(xml_node node)
{
	map<string, string> properties;

	// general
	properties["X"] = node.attribute("X").as_string();
	properties["Y"] = node.attribute("Y").as_string();
	properties["Width"] = node.attribute("Width").as_string();
	properties["Height"] = node.attribute("Height").as_string();

	// parameters
	xml_node params = node.child("Params");
	for (auto item : params)
	{
		auto key = item.attribute("Key").as_string();
		auto value = item.attribute("Value").as_string();
		properties[key] = value;
	}

	return properties;
}