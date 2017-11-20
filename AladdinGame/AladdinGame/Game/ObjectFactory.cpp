﻿#include "ObjectFactory.h"

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

GameObject* ObjectFactory::getObjectById(xml_node node, eObjectID id)
{
	switch (id)
	{
	case LAND:
		return getLand(node);
	case ROPE:
		return getRope(node);
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

	auto physicsComponent = new LandPhysiscsComponent();

	auto land = new Land();
	land->setPhysicsComponent(physicsComponent);
	land->init(x, y, width, height, dir, type);

	auto collisionComponent = (CollisionComponent*)land->getPhysicsComponent()->getComponent("Collision");
	collisionComponent->setTargerGameObject(land);
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
	return rope;
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