#pragma once
#include <string>
#include <glm/detail/type_mat4x4.hpp>

#include "Mathf.h"


using Matrix4x4 = glm::mat4x4;

namespace Mat4Math
{
	inline Matrix4x4 perspective(float fov, float aspect, float zNear, float zFar)
	{
		return glm::perspective(Mathf::deg2Rad(fov), aspect, zNear, zFar);
	}
	inline std::string print(const Matrix4x4& matrix)
	{
		std::string str;
		for (int i = 0; i < 4; i++)
		{
			std::string row;
			for (int j = 0; j < 4; j++)
			{
				row += std::to_string(matrix[i][j]);
				row += ' ';
			}
			str += row + "\n";
		}
		return str;
		}
}