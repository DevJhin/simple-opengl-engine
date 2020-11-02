#pragma once
#include "Component.h"
#include "Material.h"
#include "Mesh.h"

class Actor;

class Renderer :public Component {
public:

	Renderer(Actor* actor);
	~Renderer();

	Material* material;
	List<Material*> subMaterials;

	Mesh* mesh;
	Actor* actor;

	void Render() const;
private:
};
