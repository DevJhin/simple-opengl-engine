#pragma once

#include "Actor.h"
#include "Transform.h"

class AArcBall:public Actor
{
public:
	
	Transform* modelTransform;
	Transform* camTransform;

	float sensitivity;
	
	void OnResetKeyPressed();
	void OnToggleKeyPressed();
	
	void Start() override;
	void Update() override;

	Actor* Clone() const override;
	bool isCameraMode;
private:
	Vector2 prevMousePos;
	
	Vector3 camAxis;
	Vector3 camInitpos;
	
	float camDistance;
};

