#pragma once
#include "Object.h"
#include "Transform.h"


class Actor;

class Component:public Object
{
public:
	Component(Actor* actor);
	virtual ~Component();

	virtual void Awake(){};
	virtual void Start(){};
	virtual void Update(){};

	Actor* GetActor();
	Transform* transform;

	bool isEnabled;
private:
	Actor* actor;
};

