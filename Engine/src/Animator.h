#pragma once
#include "Animation.h"
#include "Component.h"



class Animator : public Component
{
public:
	Animation* animation;

	bool isPlaying;
	bool isPaused;
	float time;
	
	Animator(Actor* actor) :Component(actor)
	{
		animation = nullptr;
		isPlaying  = false;
		isPaused= false;
		time=0;
	}

	
	void Awake() override
	{
		LOG("Animator Awake");
		
	}

	
	void Start() override
	{
		Play();
		isPlaying=false;
	}

	void Reset()
	{
		Vector3 position = animation->GetPos(0);
		Quaternion rotation = animation->GetRotation(0);

		transform->SetPosition(position);
		transform->SetRotation(rotation);
	}

	void Play()
	{
		if(animation == nullptr)
		{
			isPlaying = false;
			LOG_ERROR("Animation does not exist.");
			return;
		}
		time = 0;

		Reset();
		isPaused = false;
		isPlaying = true;		
	}

	void Stop()
	{
		isPlaying = false;
		isPaused = false;
	}

	void Pause()
	{
		isPaused= true;
	}

	void Resume()
	{
		isPaused = false;
	}
	
	
	void Update() override
	{
		if(!isPlaying || isPaused) return;

		if(animation->IsFinished(time))
		{
			Stop();
			return;
		}
		
		time+=Time::getDeltaTime();
		
		Vector3 position = animation->GetPos(time);
		Quaternion rotation = animation->GetRotation(time);

		transform->SetPosition(position);
		transform->SetRotation(rotation);
	}

	bool IsFinished()
	{
		return animation->IsFinished(time);
	}
	

};

