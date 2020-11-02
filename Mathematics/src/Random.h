#pragma once
#include <random>

#include "vectors/Vector3.h"

static std::random_device rd;

static std::mt19937 gen(rd());
static std::uniform_real_distribution<float> dis(0, 1);

class Random
{
	
public:
	static float randomRange(float min, float max)
	{
		
		return dis(gen)*(max-min) + min;
	}

	static Vector3 randomRange(const Vector3& min, const Vector3& max)
	{
		Vector3 rlt;
		for(int i=0;i<3;i++)
		{
			rlt[i] = randomRange(min[i], max[i]);
		}
		return rlt;
	}

};
