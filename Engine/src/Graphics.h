#pragma once
#include "Mesh.h"
#include "Material.h"
/*
 * High-level Graphics operations. 
 */

struct RenderCommand
{
	Mesh* mesh;
	Material* material;
	
	Matrix4x4 modelMatrix;
};

class Graphics final
{
public:
	static void UpdateGlobalProperties();
	static void PostRender();

	static void DrawMesh(Mesh* mesh, const Matrix4x4& modelMatrix, Material* material);
	static void BindTexture(Texture* texture, uint index, Material* mat);
private:
	static Vector3 lightDir;

	static Matrix4x4 cameraViewMatrix;
	static Matrix4x4 cameraProjectionMatrix;
	
	static Queue<RenderCommand> renderCommandBuffer;
};

