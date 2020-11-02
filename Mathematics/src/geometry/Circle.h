#pragma once
#include "../Collections.h"
#include "../Vectors.h"

class Circle
{
public:
	Circle();
	Circle(Vector2 center, float radius);

	
	List<Vector2> findIntersectPoints(const Vector2& p1, const Vector2& p2);
	
	List<Vector3> createVertices(int precision, Vector3 color);
private:
	Vector2 center;
	float radius;
};

