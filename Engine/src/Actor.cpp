#include "Actor.h"

#include "World.h"


Actor::Actor()
{
	LOG("Constructor Actor");
	isActive = true;
}

Actor::~Actor()
{
	LOG("Destroy Actor");
	for(int i=0;i<components.size();i++)
	{
		delete components[i];
	}
}

void Actor::SetActive(bool value)
{
	if(value == isActive) return;
	isActive = value;
	if(isActive == false)
	{
		for (Component* c: components)
		{
			c->isEnabled = false;
		}	
	}
}

bool Actor::IsActive()
{
	return isActive;
}

Transform& Actor::GetTransform()
{
	return transform;
}

Actor* Actor::Clone() const
{
	return new Actor(*this);
}
