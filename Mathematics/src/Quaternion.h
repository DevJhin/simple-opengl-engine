#pragma once
#include "../../../../External Libs/GLM/glm/gtx/quaternion.hpp"

#include "Matrix4x4.h"

using Quaternion = glm::quat;

namespace QuatMath
{
	const static Quaternion identity = glm::quat(Vector3(0.0f, 0.0f, 0.0f));

	inline Quaternion angleAxis(const Vector3& axis, float angle)
	{
		return glm::angleAxis(angle * Mathf::Deg2Rad, axis);
	}

	inline Quaternion euler(const Vector3& axis)
	{
		return Quaternion(axis*Mathf::Deg2Rad);
	}

	inline Quaternion inverseRotation(const Quaternion& quat)
	{
		return glm::inverse(quat);
	}
	
	inline Matrix4x4 toMatrix4x4(const Quaternion& q)
	{	
		return glm::toMat4(q);
	}

	inline Quaternion FromToRotation(const Vector3& from, const Vector3& to)
	{
		return glm::rotation(from, to);
	}

	inline Matrix4x4 TRS(const Vector3& position, const Quaternion& rotation, const Vector3& scale)
	{
		Matrix4x4 worldMatrix(1.0f);
		worldMatrix = glm::translate(worldMatrix, position);
		worldMatrix *= QuatMath::toMatrix4x4(rotation);
		worldMatrix = glm::scale(worldMatrix, scale);
		return worldMatrix;
	}

	inline Matrix4x4 SRT(const Vector3& position, const Quaternion& rotation, const Vector3& scale)
	{
		Matrix4x4 matrix = Matrix4x4(1.0f);
		matrix = glm::scale(matrix, scale);
		matrix *= QuatMath::toMatrix4x4(rotation);
		matrix = glm::translate(matrix, position);
		return matrix;
	}

}