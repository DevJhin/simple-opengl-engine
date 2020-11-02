#pragma once
struct ColliderInfo
{
	Vector3 center;
	float radius;
};


class Physics
{

public:

	static bool CheckCollision(ColliderInfo col1, ColliderInfo col2)
	{
		float distance = Vec3Math::Distance(col1.center, col2.center);

		return distance<= col1.radius + col2.radius;
	
	}
};

