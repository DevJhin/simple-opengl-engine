#pragma once

namespace Mathf
{
	const float PI = 3.14159265358979323846f;
	const float Deg2Rad = (PI * 2) / 360;
	const float Rad2Deg = 360/(2*PI);

	inline float deg2Rad(float degree);

	inline float rad2Deg(float radian);

	inline float abs(float value);

	inline float clamp01(float value);

	inline float lerp(float s, float e, float t);

	inline float clamp(float value, float min, float max);

	inline float acos(float rad);

	inline float Cos(float rad);

	inline float Sin(float rad);

	inline float asin(float rad);

	inline float tan(float rad);

	inline int pow(int a, int b);

	inline float atan(float y, float x);
}

