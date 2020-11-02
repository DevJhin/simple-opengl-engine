#pragma once
#include "Camera.h"
#include "RenderObject.h"

/*
 * Arc-ball based camera controller.
 */

struct CameraState
{
	Vector3 position;
	Quaternion rotation;

	float fov;
};


class CameraController: public RenderObject
{
private:
	
	float distance;
	float angle;
	float rollSpeed;
	float axis;

	float mouseSensitivity;
	float scrollSensitivity;

	CameraState initState;
	
	CameraState currentState;
	CameraState targetState;

	Vector2 prevMousePos;

	Vector3 camAxis;
	
	void interpolateStates();
	void applyCurrentState();
	void updateTargetState();
public:
	CameraController();
	~CameraController() override;
	
	Camera* camera;
	Transform* camTransform;

	void start() override;
	void reset();
	void update() override;
};

