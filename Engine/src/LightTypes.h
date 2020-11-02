#pragma once
#include "Quaternion.h"
#include "vectors/Vector3.h"
#include "vectors/Vector4.h"

enum class LightMode
{
	Directional,
	Point,
	Spot
};


struct LinearColor
{
	float r;
	float g;
	float b;
	
	float intensity;
};


struct SpotLightData
{
	Vector3 position;
	Vector3 direction;
	
	float innerCutoffAngle;
	float outerCutoffAngle;

	LinearColor color;
};


struct PointLightData
{
	Vector3 position;
	
	Vector3 color;
	
	float range;
};


struct DirectionalLightData
{
	Vector3 direction;

	Vector3 color;

};