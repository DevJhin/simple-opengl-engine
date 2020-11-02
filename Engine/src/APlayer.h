#pragma once
#include "Animator.h"
#include "AObstacle.h"
#include "Component.h"

class AObstacle;

class APlayer : public Actor
{
public:
	Animator* animator;

	float radius;
	
	Vector3 direction;
	float speed;

	float MAX_PLAY_TIME;
	float playTime;

	int MAX_LIFE;
	int life;

	Actor* lifeBar;
	Actor* timeBar;

	Light* directionalLight;

	Quaternion targetQuaternion;

	Transform* environment1;
	Transform* environment2;
	
	bool isDied;
	bool isWin;

	bool isImmortal;
	float lastHitTime;

	bool isGameEnd;

	Renderer* renderer;

	Vector3 environmentOffset = Vector3(0, 70, -20);
	float environmentMinY = -70;
	
	void Start() override
	{
		LOG("Start Cube Controlller");
		radius = 1;
		playTime = 0;

		life = MAX_LIFE;

		environment1->SetPosition(environmentOffset);
		
	}

	void Move()
	{
		Vector2 axis = Input::getAxis();
		transform.Translate(Vector3(axis.x,axis.y,0)*(Time::getDeltaTime()* speed));

		Vector3 newPos = transform.GetPosition();
		newPos.x = glm::clamp(newPos.x, -8.3f, 8.3f);
		newPos.y = glm::clamp(newPos.y, -8.3f, 8.3f);

		transform.SetPosition(newPos);
		newPos.z -=1.0f;
		newPos.y += 1.0f;
		directionalLight->transform->SetPosition(newPos);
	}

	void Update() override
	{
		if(isGameEnd)
		{
			float delta = isDied? -1.0f:1.0f;
			directionalLight->intensity += delta*Time::getDeltaTime();
			return;
		}
		
		Move();

		playTime += Time::getDeltaTime();
		
		float timeRate = (MAX_PLAY_TIME- playTime)/MAX_PLAY_TIME;

		if(timeRate<=0)
		{
			isGameEnd = true;
			isWin = true;
		}

		float ems = Mathf::lerp(-8.0f, -15.0f, timeRate+0.2f);
		
		Vector3 environMoveSpeed= Vector3(0, ems, 0) * Time::getDeltaTime();

		
		if(environment1->GetPosition().y <environmentMinY)
		{
			environment1->SetPosition(environmentOffset);
		}
		if (environment2->GetPosition().y < environmentMinY)
		{
			environment2->SetPosition(environmentOffset);
		}
		environment1->Translate(environMoveSpeed);
		environment2->Translate(environMoveSpeed);

		
		
		timeRate = timeRate<0?0:timeRate;


		
		//Update Time bar
		Vector3 scale = timeBar->GetTransform().GetScale();
		scale.x = 5 * timeRate;
		timeBar->GetTransform().SetScale(scale);
		
	}

	void OnDamage(AObstacle& obstacle)
	{
		if(isDied || Time::getCurrentTime() - lastHitTime <= 2) return;
		
		LOG("Damage");
		life--;
		lastHitTime = Time::getCurrentTime();
		float lifeRate = life/(float)MAX_LIFE;
		Vector3 scale = lifeBar->GetTransform().GetScale();
		scale.x = 5 * lifeRate;
		lifeBar->GetTransform().SetScale(scale);
		LOG("Life Rate" << lifeRate);
		if(life == 0)
		{
			OnDeath();
			return;		
		}
		
		
	}

	void OnDeath()
	{
		isDied = true;
		isGameEnd = true;
		renderer->isEnabled = false;
	}
	
	Actor* Clone() const override
	{
		return new APlayer(*this);
	}

	ColliderInfo GetColliderInfo()
	{
		ColliderInfo colliderInfo;
		colliderInfo.radius = radius;
		colliderInfo.center = transform.GetPosition();

		return colliderInfo;
	}	
};

