#include "World.h"

#include "Graphics.h"
#include "Input.h"

#include "GameScene.h"

/**
 * \brief Initializes the main system. System resources will be loaded.
 */

World* World::instance = nullptr;

World::World()
{   
    LOG("Constructor of World");
}

void World::LoadScene(Scene* scene)
{
	activeScene = scene;

	activeScene->LoadSceneObjects();
	
	List<Actor*>& sceneActors = scene->GetPrefabs();
	
	for(Actor* sceneActor:sceneActors)
	{
		onStartActors.push_back(sceneActor);
		//SpawnActor(sceneActor);
	}
	
}

template<class T>
T* World::SpawnActor(T* original)
{
	LOG("Spawn Actor");
	
	if(!Type::IsChildOf<Actor, T>())
	{
		LOG_ERROR("Given type does not derive Actor class.");
		return nullptr;
	}
	
	T* clone = static_cast<T*>(original->Clone());
	onStartActors.push_back(clone);
	return clone;
	
}

template <class T>
void World::LoadActor(T* actor)
{
	
}


/**
 * \brief Terminates the main system. System resources will be released.
 */
World::~World()
{
	LOG("Destroy world");

	for(int i=0;i < activeActors.size();i++)
	{
		delete activeActors[i];
	}

	activeActors.clear();

}

World* World::GetInstance()
{
	if(instance == nullptr)
	{
		instance = new World();
	}
	return instance;
}

void World::Init()
{
	camera = static_cast<Camera*>(SpawnActor(new Camera()));
	
	Scene* scene = new GameScene();
	LoadScene(scene);
	
}

/*
 * \brief Run the main loop of this system (including rendering, input Update, etc).
 */
void World::Update()
{
	Input::update();
	
	ProcessStartActors();
	ProcessStartComponents();
	
    UpdateActors();
	
	UpdateComponents();
	
    Render();
	
}

void World::RegisterActor(Actor* actor)
{
	onStartActors.push_back(actor);
}

void World::ProcessStartActors()
{
	if (onStartActors.empty()) return;
	
	LOG("Start Actors");
	
    for (Actor* actor : onStartActors)
    {
		LOG("Start Actor:"<<actor->name);
        actor->Start();
    	activeActors.push_back(actor);
    }

	onStartActors.clear();
}

void World::ProcessStartComponents()
{
	if (onStartComponents.empty()) return;

	for (Component* component: onStartComponents)
	{
		component->Start();
		activeComponents.push_back(component);
	}

	onStartComponents.clear();
}

void World::UpdateActors()
{	
    for (auto renderObject : activeActors)
    {
    	if(renderObject->IsActive())
			renderObject->Update();
    }

}

void World::UpdateComponents()
{
	for(auto *component : activeComponents)
	{
		if (component->isEnabled)
			component->Update();
	}
}

void World::Render()
{
	Graphics::UpdateGlobalProperties();

	for(auto *renderer : activeRenderers)
	{
		renderer->Render();
	}

	Graphics::PostRender();
}

void World::RegisterRenderer(Renderer* renderer)
{
	LOG("Registering Renderers")
	activeRenderers.push_back(renderer);
}

void World::RegisterComponent(Component* component)
{
	onStartComponents.push_back(component);
}

void World::RegisterLight(Light* light)
{
	lights.push_back(light);
}
