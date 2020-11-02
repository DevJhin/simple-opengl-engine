#include "Circle.h"

#include "../Mathf.h"

Circle::Circle(): center(Vector2(0,0)), radius(0)
{
	
}

Circle::Circle(Vector2 center, float radius): center(center), radius(radius)
{
	
}

List<Vector2> Circle::findIntersectPoints(const Vector2& p1, const Vector2& p2)
{
	float a = p2.x - p1.x;
	float b = p1.x;
	float c = p2.y - p1.y;
	float d = p1.y;

	float e = center.x;
	float f = center.y;

	float r = radius;

	float A = a*a + c *c;
	float B = 2* (a*b - a*e + c*d - c*f);
	float C = b*b + d*d + e*e + f*f -r*r - 2*(b*e + d*f);

	float D = B*B - 4*A*C;

	List<Vector2> intersectPoints;
	
	//Have two intersection points
	if(D>0)
	{
		float t1 = (-B + sqrt(D))/(2*A);
		float t2 = (-B - sqrt(D)) / (2 * A);

		if(t1 >= 0 && t1 <=1)
			intersectPoints.emplace_back(a * t1 + b, c*t1 +d);
		if(t2 >= 0 && t2 <=1)
			intersectPoints.emplace_back(a * t2 + b, c * t2 + d);
	}
	else if(D==0)
	{
		float t1 = -b / (2*a);
		if (t1 >= 0 && t1 <= 1)
			intersectPoints.emplace_back(a * t1 + b, c * t1 + d);
	}

	return intersectPoints;
}

std::vector<Vector3> Circle::createVertices(int precision, Vector3 color)
{
	List<Vector3> circleVertices;

	float interval = 360 / static_cast<float>(precision);

	for (int i = 0; i < precision; i++)
	{
		float angle = (i * interval) * Mathf::PI / 180.0f;

		float x = sin(angle)*radius + center.x;
		float y = cos(angle)*radius + center.y;

		circleVertices.emplace_back(x,y,0);
	}
	return circleVertices;
}
