#include "Component.h"

Component::Component(Actor* actor)
{
	this->actor = actor;
	transform = &actor->GetTransform();
	isEnabled = true;
	//World::GetInstance()->RegisterComponent(this);
}

Component::~Component()
{
	
}

Actor* Component::GetActor()
{
	return actor;
}
