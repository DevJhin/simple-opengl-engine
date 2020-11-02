#pragma once

class Camera final: public Actor
{
public:
	Camera();
	~Camera();

	void Update() override;

	Matrix4x4 getProjectionMatrix();

	Matrix4x4 getViewMatrix();

	void setFOV(float value);


	Actor* Clone() const override;
private:
	float fov;

	float zNear;
	float zFar;
	
	Matrix4x4 view = Matrix4x4(1.0f);
	Matrix4x4 projection = Matrix4x4(1.0f);

};

