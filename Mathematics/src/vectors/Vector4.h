#pragma once

#include <glm/vec4.hpp>

using Vector4 = glm::vec4;

namespace Vec4Math
{
	inline List<Vector4> ToList(float* arr, int size)
	{
		List<Vector4> list;
		int vSize = size / 4;
		for (int i = 0; i < vSize; i++)
		{
			int offset = i * 4;
			list.emplace_back(arr[offset], arr[offset + 1], arr[offset + 2], arr[offset+3]);
		}
		return list;
	}
}
