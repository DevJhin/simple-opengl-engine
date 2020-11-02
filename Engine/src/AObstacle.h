#pragma once
#include "Actor.h"
#include "Animator.h"
#include "Time.h"

#include "APlayer.h"
class APlayer;

enum class ObstacleState
{
	WAIT,
	MOVE,
	FINISH
};


class AObstacle : public Actor
{
public:
	Animator* animator;
	ObstacleState state;

	Vector3 direction;
	
	float radius;
	
	float speed;
	
	float startTime;
	float lifeTime;

	APlayer* player;
	
	void Start() override
	{
		LOG("Start Obstacle");
		waitingTime = 0;
		playingTime = 0;
		
		state = ObstacleState::WAIT;
		direction = -Vec3Math::UP;
		speed = 5;

		radius = 0.3f;
	}

	void Move()
	{
		transform.Translate(direction* (Time::getDeltaTime() * speed));
	}

	void Update() override
	{
		if(player->isWin)
		{
			SetActive(false);
		}
		switch (state)
		{
		case ObstacleState::WAIT:
			waitingTime += Time::getDeltaTime();
			if(waitingTime>= startTime)
			{
				state = ObstacleState::MOVE;
				animator->Play();
			}
			break;
		case ObstacleState::MOVE:
			playingTime += Time::getDeltaTime();
			//Move();
			if(Physics::CheckCollision(player->GetColliderInfo(), GetColliderInfo()))
			{
				player->OnDamage(*this);
			}			
			if(playingTime > lifeTime)
				state = state = ObstacleState::FINISH;
			break;
		case ObstacleState::FINISH:
			SetActive(false);
			break;
		default: ;
		}

	}

	ColliderInfo GetColliderInfo()
	{
		ColliderInfo colliderInfo;
		colliderInfo.radius = radius;
		colliderInfo.center = transform.GetPosition();
		
		return colliderInfo;
	}
	

	Actor* Clone() const override
	{
		return new AObstacle(*this);
	}

private:
	float waitingTime;
	float playingTime;
};

