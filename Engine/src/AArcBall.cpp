#include "AArcBall.h"


#include "World.h"


void AArcBall::Start()
{
	LOG("ArcBall start")
	Camera* camera = World::GetInstance()->camera;

	camTransform = &camera->GetTransform();
	camInitpos = camTransform->GetPosition();
	camTransform->SetPosition(camInitpos);
	//camTransform->LookAt(Vec3Math::ZERO, Vec3Math::UP);

	camAxis = Vec3Math::normalize(camInitpos);
	camDistance = Vec3Math::magnitude(camInitpos);
	sensitivity = 180;
	
	/*
	 * Add actionListener of for reset key 'R'
	 */
	Input::addOnKeyPressAction(KeyCode::R, [this] { OnResetKeyPressed(); });
	//Input::addOnKeyPressAction(KeyCode::A, [this] { OnToggleKeyPressed(); });


	isCameraMode = true;
}

void AArcBall::Update()
{
	float mouseScrollDelta = -Input::mouseScrollDelta().y;
	if(Mathf::abs(mouseScrollDelta)>0.01f)
	{
		camDistance += mouseScrollDelta * 2;
		camTransform->SetPosition(camAxis * camDistance);
	}
	
	bool isCliking = Input::getMouseButton(0);
	
	if(!isCliking)
	{
		prevMousePos = Input::getMousePosition();
		return;
	}

	
	/*Get current Mouse pos*/
	Vector2 currentMousePos = Input::getMousePosition();
	
	/*Get delta Mouse position*/
	Vector2 deltaMousePos = currentMousePos - prevMousePos;

	
	float deltaX = deltaMousePos.x * sensitivity;
	float deltaY = deltaMousePos.y * sensitivity;

	//Rotate modelTransform object.

	if(isCameraMode)
	{	
		Quaternion camPosRotation = QuatMath::euler(Vector3(-deltaY, deltaX,0));

		camAxis = camAxis*camPosRotation;
	
		Quaternion invRotation = QuatMath::inverseRotation(camPosRotation);
		camTransform->SetPosition(camAxis*camDistance);
		camTransform->SetRotation(invRotation * camTransform->GetRotation());
	}
	else
	{
		modelTransform->Rotate(Vec3Math::RIGHT, -deltaY);
		modelTransform->Rotate(Vec3Math::UP, deltaX);
	}
	
	prevMousePos = currentMousePos;
}

Actor* AArcBall::Clone() const
{
	return new AArcBall(*this);
}


void AArcBall::OnResetKeyPressed()
{
	LOG("Reset Arcball");
	if(modelTransform !=nullptr)
		modelTransform->SetRotation(QuatMath::identity);

	camTransform->SetPosition(Vec3Math::normalize(camInitpos)*camDistance);
	camTransform->SetRotation(QuatMath::identity);
	//camTransform->LookAt(Vec3Math::ZERO, Vec3Math::UP);
	
	camAxis = Vec3Math::normalize(camTransform->GetPosition());
}

void AArcBall::OnToggleKeyPressed()
{
	isCameraMode = !isCameraMode;
	if(isCameraMode) 
	{
		LOG("Toggle Key Pressed::Camera Rotation Mode");
	}
	else
	{
		LOG("Toggle Key Pressed::Model Rotation Mode");
	}
}
