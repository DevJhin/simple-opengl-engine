#include "LightTypes.h"

#pragma once
class Light:public Component
{
public:
	Light(Actor* actor);
	LightMode lightMode;

	Vector3 color;
	float intensity;
	float range;
	
	float angle;
	

private:
	
};

