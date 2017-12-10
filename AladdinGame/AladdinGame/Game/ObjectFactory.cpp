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
	case WALL:
		return getWall(node);
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
	auto aladdin = new GameObject(eObjectID::ALADDIN);

	auto physicsComponent = new AladdinPhysicsComponent();
	physicsComponent->setGameObject(aladdin);

	auto animationComponent = new AladdinAnimationComponent();
	animationComponent->setGameObject(aladdin);

	auto behaviorComponent = new AladdinBehaviorComponent();
	behaviorComponent->setGameObject(aladdin);
	behaviorComponent->setGameController(GameController::getInstance());

	aladdin->setPhysicsComponent(physicsComponent);
	aladdin->setAnimationComponent(animationComponent);
	aladdin->setBehaviorComponent(behaviorComponent);

	aladdin->init();

	return aladdin;
}

GameObject * ObjectFactory::getApple(GVector2 pos, GVector2 velocity)
{
	auto Apple = new GameObject(eObjectID::APPLE);

	auto physicsComponent = new ApplePhysicsComponent();
	physicsComponent->setGameObject(Apple);
	physicsComponent->setPosition(pos);

	auto animationComponent = new AppleAnimationComponent();
	animationComponent->setGameObject(Apple);

	auto behaviorComponent = new AppleBehaviorComponent();
	behaviorComponent->setGameObject(Apple);
	behaviorComponent->setGameController(GameController::getInstance());

	Apple->setPhysicsComponent(physicsComponent);
	Apple->setAnimationComponent(animationComponent);
	Apple->setBehaviorComponent(behaviorComponent);

	Apple->init();
	auto move = (Movement*)physicsComponent->getComponent("Movement");
	move->setVelocity(velocity);

	return Apple;
}

GameObject * ObjectFactory::getDagger(GVector2 pos, GVector2 velocity)
{
	auto Dagger = new GameObject(eObjectID::DAGGER);

	auto physicsComponent = new DaggerPhysicsComponent();
	physicsComponent->setGameObject(Dagger);
	physicsComponent->setPosition(pos);

	auto animationComponent = new DaggerAnimationComponent();
	animationComponent->setGameObject(Dagger);

	auto behaviorComponent = new DaggerBehaviorComponent();
	behaviorComponent->setGameObject(Dagger);
	behaviorComponent->setGameController(GameController::getInstance());

	Dagger->setPhysicsComponent(physicsComponent);
	Dagger->setAnimationComponent(animationComponent);
	Dagger->setBehaviorComponent(behaviorComponent);

	Dagger->init();
	auto move = (Movement*)physicsComponent->getComponent("Movement");
	move->setVelocity(velocity);

	return Dagger;
}

GameObject * ObjectFactory::getSword(GVector2 pos, float width, float height, bool canSlashEnemy)
{
	auto sword = new Sword();
	sword->setID(eObjectID::SWORD);

	auto physicsComponent = new SwordPhysicsComponent();
	physicsComponent->setGameObject(sword);

	auto behaviorComponent = new SwordBehaviorComponent();
	behaviorComponent->setGameObject(sword);

	sword->setPhysicsComponent(physicsComponent);
	sword->setBehaviorComponent(behaviorComponent);

	sword->setAnimationComponent(nullptr);
	sword->init(pos.x, pos.y, width, height, eDirection::ALL, canSlashEnemy);

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
	auto land = new Land();

	auto behaviorComponent = new LandBehaviorComponent();
	PhysicsComponent * physicsComponent;
	AnimationComponent * animationComponent = nullptr;
	if (type == eLandType::lFALLING)
	{
		physicsComponent = new FallingLandPhysiscsComponent();
		animationComponent = new FallingLandAnimationComponent();
		animationComponent->setGameObject(land);
		physicsComponent->setPosition(GVector2(x, y));
	}
	else
	{
		physicsComponent = new LandPhysiscsComponent();
	}
	behaviorComponent->setGameObject(land);

	
	land->setPhysicsComponent(physicsComponent);
	land->setBehaviorComponent(behaviorComponent);
	land->setAnimationComponent(animationComponent);
	land->init(x, y, width, height, dir, type);

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

	return rope;
}

GameObject * ObjectFactory::getHakim(GVector2 pos, float rangeXStart, float rangeXEnd)
{
	auto Hakim = new GameObject(eObjectID::HAKIM);

	auto physicsComponent = new HakimPhysicsComponent();
	physicsComponent->setGameObject(Hakim);
	physicsComponent->setPosition(pos);

	auto animationComponent = new HakimAnimationComponent();
	animationComponent->setGameObject(Hakim);

	EnemyBehaviorComponent* behaviorComponent = new HakimBehaviorComponent();
	behaviorComponent->setGameObject(Hakim);
	behaviorComponent->setGameController(GameController::getInstance());
	behaviorComponent->setRange(rangeXStart, rangeXEnd);

	Hakim->setPhysicsComponent(physicsComponent);
	Hakim->setAnimationComponent(animationComponent);
	Hakim->setBehaviorComponent(behaviorComponent);

	Hakim->init();

	return Hakim;
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
	auto Falza = new GameObject(eObjectID::FALZA);

	auto physicsComponent = new FalzaPhysicsComponent();
	physicsComponent->setGameObject(Falza);
	physicsComponent->setPosition(pos);

	auto animationComponent = new FalzaAnimationComponent();
	animationComponent->setGameObject(Falza);

	EnemyBehaviorComponent* behaviorComponent = new FalzaBehaviorComponent();
	behaviorComponent->setGameObject(Falza);
	behaviorComponent->setGameController(GameController::getInstance());
	behaviorComponent->setRange(rangeXStart, rangeXEnd);

	Falza->setPhysicsComponent(physicsComponent);
	Falza->setAnimationComponent(animationComponent);
	Falza->setBehaviorComponent(behaviorComponent);

	Falza->init();

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
	auto Nahbi = new GameObject(eObjectID::NAHBI);

	auto physicsComponent = new NahbiPhysicsComponent();
	physicsComponent->setGameObject(Nahbi);
	physicsComponent->setPosition(pos);

	auto animationComponent = new NahbiAnimationComponent();
	animationComponent->setGameObject(Nahbi);

	EnemyBehaviorComponent* behaviorComponent = new NahbiBehaviorComponent();
	behaviorComponent->setGameObject(Nahbi);
	behaviorComponent->setGameController(GameController::getInstance());
	behaviorComponent->setRange(rangeXStart, rangeXEnd);

	Nahbi->setPhysicsComponent(physicsComponent);
	Nahbi->setAnimationComponent(animationComponent);
	Nahbi->setBehaviorComponent(behaviorComponent);

	Nahbi->init();

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
	auto Flame = new GameObject(eObjectID::FLAME);

	auto physicsComponent = new FlamePhysicsComponent();
	physicsComponent->setGameObject(Flame);
	physicsComponent->setPosition(pos);

	auto animationComponent = new FlameAnimationComponent();
	animationComponent->setGameObject(Flame);

	auto behaviorComponent = new FlameBehaviorComponent();
	behaviorComponent->setGameObject(Flame);
	behaviorComponent->setGameController(GameController::getInstance());

	Flame->setPhysicsComponent(physicsComponent);
	Flame->setAnimationComponent(animationComponent);
	Flame->setBehaviorComponent(behaviorComponent);

	Flame->init();

	return Flame;
}

GameObject * ObjectFactory::getExlplosionPot(GVector2 pos)
{
	auto ExplosionPot = new GameObject(eObjectID::EXPLOSIONPOT);

	auto physicsComponent = new ExplosionPotPhysicsComponent();
	physicsComponent->setGameObject(ExplosionPot);
	physicsComponent->setPosition(pos);

	auto animationComponent = new ExplosionPotAnimationComponent();
	animationComponent->setGameObject(ExplosionPot);

	auto behaviorComponent = new ExplosionPotBehaviorComponent();
	behaviorComponent->setGameObject(ExplosionPot);
	behaviorComponent->setGameController(GameController::getInstance());

	ExplosionPot->setPhysicsComponent(physicsComponent);
	ExplosionPot->setAnimationComponent(animationComponent);
	ExplosionPot->setBehaviorComponent(behaviorComponent);

	ExplosionPot->init();

	return ExplosionPot;
}


GameObject * ObjectFactory::getThrower(GVector2 pos)
{
	auto Thrower = new GameObject(eObjectID::THROWER);

	auto physicsComponent = new ThrowerPhysicsComponent();
	physicsComponent->setGameObject(Thrower);
	physicsComponent->setPosition(pos);

	auto animationComponent = new ThrowerAnimationComponent();
	animationComponent->setGameObject(Thrower);

	auto behaviorComponent = new ThrowerBehaviorComponent();
	behaviorComponent->setGameObject(Thrower);
	behaviorComponent->setGameController(GameController::getInstance());

	Thrower->setPhysicsComponent(physicsComponent);
	Thrower->setAnimationComponent(animationComponent);
	Thrower->setBehaviorComponent(behaviorComponent);

	Thrower->init();

	return Thrower;
}

GameObject * ObjectFactory::getThrower(xml_node node)
{
	GVector2 pos;
	pos.x = node.attribute("X").as_float() * SCALE_FACTOR;
	pos.y = node.attribute("Y").as_float() * SCALE_FACTOR;

	return getThrower(pos);
}

GameObject * ObjectFactory::getWall(xml_node node)
{
	auto properties = getObjectProperties(node);
	if (properties.size() == 0)
		return nullptr;

	int x, y, width, height;
	eDirection dir;

	x = stoi(properties["X"]) * SCALE_FACTOR;
	y = stoi(properties["Y"]) * SCALE_FACTOR;
	width = stoi(properties["Width"]) * SCALE_FACTOR;
	height = stoi(properties["Height"]) * SCALE_FACTOR;


	if (properties.find("physicBodyDirection") != properties.end())
	{
		dir = (eDirection)(stoi(properties.find("physicBodyDirection")->second));
	}
	else
	{
		dir = eDirection::ALL;
	}

	auto physicsComponent = new RopePhysiscsComponent();

	auto wall = new Wall();
	wall->setPhysicsComponent(physicsComponent);
	wall->init(x, y, width, height, dir);

	return wall;
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