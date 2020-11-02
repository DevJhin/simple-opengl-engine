#pragma once
#include <string>
#include <glm/gtx/norm.hpp>
#include <glm/vec3.hpp>

using Vector3Int = glm::uvec3;
using Vector3 = glm::vec3;

inline glm::vec3 bt2glm(const Vector3& vec)
{
    return { vec.x, vec.y, vec.z };
}


namespace Vec3Math
{
	const static Vector3 ZERO = Vector3(0, 0, 0);
	const static Vector3 ONE = Vector3(1, 1, 1);

	const static Vector3 FORWARD = Vector3(0, 0, -1);
	const static Vector3 UP = Vector3(0, 1, 0);
	const static Vector3 RIGHT = Vector3(1, 0, 0);

	inline Vector3 normalize(const Vector3& value)
	{
		return glm::normalize(value);
	}

	inline float magnitude(const Vector3& value)
	{
		return glm::length(value);
	}

	inline float Distance(const Vector3& a, const Vector3& b)
	{
		return glm::distance(a, b);
	}

	inline float dot(const Vector3& a, const Vector3& b)
	{
		return glm::dot(a,b);
	}

	inline Vector3 cross(const Vector3& a, const Vector3& b)
	{
		return glm::cross(a, b);
	}
	inline std::string print(const Vector3& v)
	{
		std::string str;
		str += std::to_string(v.x) + "_" + std::to_string(v.y) + "_" + std::to_string(v.z);
		return str;
	}


	inline List<Vector3> ToList(float* arr, int size)
	{
		List<Vector3> list;
		int vSize = size/3;
		for(int i=0;i<vSize;i++)
		{
			int offset = i*3;
			list.emplace_back(arr[offset], arr[offset+1], arr[offset+2]);
		}
		return list;
	}


	inline List<Vector3Int> ToList(int* arr, int size)
	{
		List<Vector3Int> list;
		int vSize = size / 3;
		for (int i = 0; i < vSize; i++)
		{
			int offset = i * 3;
			list.emplace_back(arr[offset], arr[offset + 1], arr[offset + 2]);
		}
		return list;
	}
}
