
#include "GameObject.h"


GameObject::GameObject(eObjectID id)
{
	this->_id = id;
	this->setStatus(eStatus::NORMAL);
}

GameObject::~GameObject()
{
}

eObjectID GameObject::getId()
{
	return this->_id;
}
