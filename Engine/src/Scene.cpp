#include "Scene.h"


void Scene::AddSceneObject(Actor* prefab)
{
	sceneObjects.push_back(prefab);
}
