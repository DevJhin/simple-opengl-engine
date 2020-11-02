#include "Mathf.h"
#include "glm/glm.hpp"

float Mathf::deg2Rad(float degree)
{
	return glm::radians(degree);
}

float Mathf::rad2Deg(float radian)
{
	return glm::degrees(radian);
}

float Mathf::abs(float value)
{
	return glm::abs(value);
}

float Mathf::clamp01(float value)
{
	if (value > 1) return 1;
	if (value < 0) return 0;
	return value;
}

float Mathf::lerp(float s, float e, float t)
{
	return (e - s) * clamp01(t) + s;
}

float Mathf::clamp(float value, float min, float max)
{
	return glm::clamp(value, min, max);
}

float Mathf::acos(float rad)
{
	return glm::acos(rad);
}

float Mathf::Cos(float rad)
{
	return glm::cos(rad);
}

float Mathf::Sin(float rad)
{
	return glm::sin(rad);
}

float Mathf::asin(float rad)
{
	return glm::asin(rad);
}

float Mathf::tan(float rad)
{
	return glm::tan(rad);
}

int Mathf::pow(int a, int b)
{
	return glm::pow(a,b);
}

float Mathf::atan(float y, float x)
{
	return glm::atan(y,x);
}
