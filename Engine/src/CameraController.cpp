#include "CameraController.h"
#include "World.h"

CameraController::CameraController():RenderObject()
{
	//get the transform of the camera.
	camera = World::getInstance()->camera;
	camTransform = &camera->getTransform();

	
	targetState.fov = 60;
	targetState.position = Vector3(0.0f, 5.0f, 0.0f);
	targetState.rotation = QuatMath::euler(Vector3(90,0,0));
	
	scrollSensitivity = 10;
	mouseSensitivity = 10;

	distance = 15;

	getRenderer().isEnabled = false;
	
}

void CameraController::start()
{
	currentState = targetState;
	applyCurrentState();

	camAxis = currentState.position;

	
}

void CameraController::reset()
{
	targetState.fov = 60;
	targetState.position = Vector3(0.0f, 5.0f, 0.0f);
	targetState.rotation = QuatMath::euler(Vector3(90, 0, 0));
}

void CameraController::update()
{
	updateTargetState();
	interpolateStates();
	applyCurrentState();

}

/*
 * Interpolate current & target State.
 */
void CameraController::interpolateStates()
{
	float t = Time::getDeltaTime();

	currentState.position = targetState.position;

		
	float fovDelta = targetState.fov - currentState.fov;
	float smoothDelta = Mathf::lerp(0, Mathf::abs(fovDelta), t);
	currentState.fov += fovDelta > 0 ? smoothDelta : -smoothDelta;
}


/*
 * Apply current state to camera.
 */
void CameraController::applyCurrentState()
{
	camTransform->setRotation(currentState.rotation);
	camTransform->setPosition(currentState.position);
	camera->setFOV(currentState.fov);
	
	camTransform->lookAt(Vec3Math::ZERO, transform.getUp());
}

/*
 * Update targetState
 */
void CameraController::updateTargetState()
{	
	Vector2 currentMousePos = Input::getMousePosition();
	Vector2 deltaMousePos = currentMousePos - prevMousePos;

	currentMousePos+= Vector2(1,1);
	currentMousePos *=0.5f;
	
	/*
	 * Update target Camera position & rotation.
	 */

	float theta = Mathf::lerp( -175,175, currentMousePos.x);
	float gamma = Mathf::lerp(0, 90, currentMousePos.y);

	theta *= Mathf::Deg2Rad;
	gamma *= Mathf::Deg2Rad;
	
	float x = Mathf::sin(theta)*Mathf::cos(gamma);
	float y = Mathf::sin(theta)*Mathf::sin(gamma);
	float z = Mathf::cos(theta);

	Vector3 coordinate(x,y,z);

	coordinate*=distance;

	targetState.position = coordinate;

	/*
	 * Update fov.
	 */
	float scrollValue = Input::mouseScrollDelta().y;

	if (Mathf::abs(scrollValue) > 0.03f)
	{
		targetState.fov -= scrollValue * scrollSensitivity;
		targetState.fov = Mathf::clamp(targetState.fov, 30, 90);
	}

	prevMousePos = currentMousePos;
}


CameraController::~CameraController()
{
	camera = nullptr;
}

