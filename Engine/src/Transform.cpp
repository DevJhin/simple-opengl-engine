#include "Transform.h"

Transform::Transform()
{
	position = Vec3Math::ZERO;
	localPosition = Vec3Math::ZERO;
	
	worldMatrix = Matrix4x4(1.0f);
	localMatrix = Matrix4x4(1.0f);
	
	rotation = QuatMath::identity;
	localRotation = QuatMath::identity;
	localEulerAngles = Vec3Math::ZERO;
	
	scale = Vec3Math::ONE;
	localScale = Vec3Math::ONE;

	hasTransformChanged = true;
	
}

void Transform::SetPosition(const Vector3& position)
{
	this->position = position;
	hasTransformChanged = true;
}

Vector3 Transform::GetPosition()
{
	return position;
}

void Transform::SetParent(Transform* parent)
{
	this->parent = parent;
	parent->children.push_back(this);
	hasTransformChanged = true;
}

void Transform::LocalPosition(const Vector3& position)
{
	localPosition = position;
}

Vector3 Transform::LocalPosition()
{
	return localPosition;
}

void Transform::SetRotation(const Quaternion& rotation)
{
	this->rotation = rotation;
	hasTransformChanged = true;
}

Quaternion Transform::GetRotation()
{
	return rotation;
}

void Transform::SetLocalRotation(const Quaternion& rotation)
{
	localRotation = rotation;
}

Quaternion Transform::GetLocalRotation()
{
	return Quaternion();
}

void Transform::SetEulerAngles(Vector3 eulerAngles)
{
	rotation = QuatMath::euler(eulerAngles);
}

Vector3 Transform::GetEulerAngles()
{
	return eulerAngles;
}

void Transform::SetScale(const Vector3& scale)
{
	this->scale = scale;
	hasTransformChanged = true;
}

Vector3 Transform::GetScale()
{
	return scale;
}

void Transform::Translate(const Vector3& translation)
{
	position +=translation;
	hasTransformChanged = true;
	
}

void Transform::updateTRS()
{
	worldMatrix = QuatMath::TRS(position, rotation, scale);
	hasTransformChanged = false;
}

Vector3 Transform::GetRight()
{
	return rotation * Vec3Math::RIGHT;	
}


void Transform::Rotate(const Vector3& axis, float angle)
{	
	rotation = QuatMath::angleAxis(normalize(axis), angle) * rotation;
	eulerAngles = glm::eulerAngles(rotation);
	
	hasTransformChanged= true;
}


void Transform::RotateAround(const Vector3& center, const Vector3& axis, float angle)
{
	
}

Vector3 Transform::GetForward()
{
	return rotation* Vec3Math::FORWARD;
}

Vector3 Transform::GetUp()
{
	return rotation* Vec3Math::UP;
}

void Transform::LookAt(const Vector3& center, const Vector3& up)
{
	Vector3 forwardVector = Vec3Math::normalize(center - position);

	float dot = Vec3Math::dot(Vec3Math::FORWARD, forwardVector);

	if (Mathf::abs(dot - (-1.0f)) < 0.000001f)
	{
		rotation = Quaternion(Mathf::PI, 0, 1,  0);
	}
	if (Mathf::abs(dot - (1.0f)) < 0.000001f)
	{
		rotation =  QuatMath::identity;
	}

	float rotAngle = Mathf::acos(dot);
	Vector3 rotAxis = Vec3Math::cross(Vec3Math::FORWARD, forwardVector);
	
	rotAxis = Vec3Math::normalize(rotAxis);
	rotation = QuatMath::angleAxis(rotAxis, rotAngle);


	Vector3 proj = Vec3Math::dot(up, forwardVector)*forwardVector;
	Vector3 reject = Vec3Math::UP - proj;

	reject = Vec3Math::normalize(reject);
	Vector3 localUp = rotation * Vec3Math::UP;
	float rotAngleY = Vec3Math::dot(localUp, reject);

	Rotate(forwardVector, Mathf::acos(rotAngleY)*Mathf::Rad2Deg);
	hasTransformChanged = true;
}

const Matrix4x4& Transform::GetWorldMatrix()
{
	if(hasTransformChanged)
	{
		updateTRS();
	}
	
	return worldMatrix;
}

String Transform::ToString()
{
	/*
	String str = "position: " + position.x + "_" << position.y << "_" << position.z;
	LOG("position: " << position.x << "_" << position.y << "_" << position.z);
	LOG("EulerAngles: " << eulerAngles.x << "_" << eulerAngles.y << "_" << eulerAngles.z);
	LOG("scale: " << scale.x << "_" << scale.y << "_" << scale.z);
	*/
	return String();
}
