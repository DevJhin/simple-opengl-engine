#pragma once

#include "Actor.h"

#include "Camera.h"
#include "Input.h"
#include "Light.h"
#include "Scene.h"

class World{
public:
	Camera* camera;
	List<Light*> lights;
	
	/**
	 * \brief Terminates the main system. System resources will be released.
	 */
	~World();

	void Init();

	static World* GetInstance();
	/**
	 * \brief Run the main loop of this system (including rendering, input Update, etc).
	 */
	void Update();
	
	template<class T>
	T* SpawnActor(T* original);

	template<class T>
	void LoadActor(T* actor);
	
	void RegisterComponent(Component* component);
	void RegisterRenderer(Renderer* renderer);
	void RegisterLight(Light* light);

	

private:
	World();

	void RegisterActor(Actor* actor);

	void LoadScene(Scene* scene);

	static World* instance;
	
	List<Actor*> onStartActors;
	List<Actor*> onDestroyActors;

	List<Actor*> activeActors;

	List<Component*> onStartComponents;
	List<Component*> activeComponents;
	List<Renderer*> activeRenderers;

	Scene* activeScene;

	void UpdateActors();
	void UpdateComponents();
	void Render();


	void ProcessStartActors();
	void ProcessStartComponents();
};


