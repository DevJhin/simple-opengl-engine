#include "Renderer.h"

void Renderer::Render() const
{
	if (!isEnabled) return;
	if (material == nullptr || mesh == nullptr) return;

	Matrix4x4 worldMatrix = transform->GetWorldMatrix();

	Graphics::DrawMesh(mesh, worldMatrix, material);

	List<Mesh*> subMeshes = mesh->getSubMeshes();


	int i = 0;
	for (Mesh* subMesh : subMeshes)
	{
		Graphics::DrawMesh(subMesh, worldMatrix, subMaterials[i++]);
	}
}


Renderer::Renderer(Actor* actor) :Component(actor)
{
	isEnabled = true;
	World::GetInstance()->RegisterRenderer(this);
}

Renderer::~Renderer()
{
	LOG("Destroy this renderer");
}
