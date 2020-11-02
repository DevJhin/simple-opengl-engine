#include "Camera.h"

#include "Mathf.h"

Camera::Camera():Actor()
{
	fov = 60;
	
	transform.SetPosition(Vector3(0.0f, 0.0f, 10.0f));
	//transform.Rotate(Vector3(0, 1, 0), 180);
	
	Vector3 eulerAngles = transform.GetEulerAngles();

	zNear = 0.1f;
	zFar = 1000.0f;
}

Camera::~Camera()=default;


void Camera::Update()
{
	
}

void Camera::setFOV(float value)
{
	fov = value;
}

Actor* Camera::Clone() const
{
	return new Camera(*this);
}

Matrix4x4 Camera::getProjectionMatrix()
{
	Vector2Int screenSize = Window::getScreenSize();
	float aspect = float(screenSize.x) / float(screenSize.y);
	
	projection = glm::perspective(Mathf::deg2Rad(fov),aspect, zNear, zFar);
	
	
	return projection;
}

Matrix4x4 Camera::getViewMatrix()
{
	// camera/view transformation
	Vector3 cameraPos = transform.GetPosition();
	view = glm::lookAt(cameraPos, cameraPos + transform.GetForward(), transform.GetUp());
	return view;
}

