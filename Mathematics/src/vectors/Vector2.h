#pragma once
#include <glm/vec2.hpp>

using Vector2Int = glm::uvec2;
using Vector2 = glm::vec2;

namespace Vec2Math
{
	
	inline List<Vector2> ToList(float* arr, int size)
	{
		List<Vector2> list;
		int vSize = size / 2;
		for (int i = 0; i < vSize; i++)
		{
			int offset = i * 2;
			list.emplace_back(arr[offset], arr[offset + 1]);
		}
		return list;
	}
}
