#pragma once

#include "Mathematics.h"

enum class Space
{
	Local,
	World
};

#pragma once
class Transform:Object
{

public:
	Transform();
	~Transform() = default;

	void SetPosition(const Vector3& position);
	Vector3 GetPosition();
	
	void LocalPosition(const Vector3& position);
	Vector3 LocalPosition();
	
	void SetRotation(const Quaternion& rotation);
	Quaternion GetRotation();

	void SetLocalRotation(const Quaternion& rotation);
	Quaternion GetLocalRotation();
	
	void SetEulerAngles(Vector3 eulerAngles);
	Vector3 GetEulerAngles();
	
	void SetScale(const Vector3& scale);
	Vector3 GetScale();
	
	void Translate(const Vector3& translation);
	
	void Rotate(const Vector3& axis, float angle);
	void RotateAround(const Vector3& center, const Vector3& axis, float angle);

	Vector3 GetForward();
	Vector3 GetUp();
	Vector3 GetRight();

	void LookAt(const Vector3& center, const Vector3& up);
	
	void SetParent(Transform* parent);

	const Matrix4x4& GetWorldMatrix();

	String ToString() override;
	
private:
	Vector3 position;
	Vector3 localPosition;
	
	Vector3 eulerAngles;
	Vector3 localEulerAngles;

	Quaternion rotation;
	Quaternion localRotation;
	
	Vector3 scale;

	Vector3 up;
	Vector3 right;
	Vector3 forward;
	
	Vector3 localScale;
	

	bool hasTransformChanged;

	Matrix4x4 worldMatrix;
	Matrix4x4 localMatrix;

	Transform* parent;
	List<Transform*> children;

	void updateTRS();
};

 