#pragma once
#include "Actor.h"

class Scene:public Object
{
public:

	virtual void LoadSceneObjects() = 0;
	virtual void OnSceneStart(){};
	
	List<Actor*>& GetPrefabs()
	{
		return sceneObjects;
	}

	List<Actor*>& GetSceneActors()
	{
		return actors;
	}

	void AddSceneObject(Actor* prefab);


private:
	List<Actor*> sceneObjects;
	
	List<Actor*> actors;
	
};

