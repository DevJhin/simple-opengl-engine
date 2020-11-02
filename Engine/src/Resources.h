#pragma once
#include "Mesh.h"
#include "Model.h"
#include "Texture.h"
#include "GL.h"
#include "geometry/Cube.h"

struct ModelData
{
	Mesh* mesh;
	//List<TextureData> textures;

	ModelData(Mesh* mesh)
	{
		this->mesh = mesh;
	}

	~ModelData()
	{
		delete mesh;
	}
};

class Resources {

public:

	static Mesh* primitiveCubeMesh;
	static Mesh* primitiveSphereMesh;
	
	static ModelData* LoadModel(const String& path)
	{
		String modelPath = "resources/models/" + path;

		Model model(modelPath.c_str());

		List<MeshData>& meshDataList = model.meshes;

		int meshSize = meshDataList.size();

		if (meshSize == 0) return nullptr;


		List<Mesh*> meshes;

		for (int i = 1; i < meshSize; i++)
		{
			meshes.push_back(MeshDataToMesh(meshDataList[i]));
		}

		Mesh* mainMesh = MeshDataToMesh(meshDataList[0]);
		mainMesh->setSubmeshes(meshes);

		auto modelData = new ModelData(mainMesh);

		return modelData;
	}

	static Mesh* MeshDataToMesh(const MeshData& meshData)
	{
		Mesh* newMesh = new Mesh();

		const List<Vertex>& vertices = meshData.vertices;

		List<Vector3> positions;
		List<Vector3> normals;
		List<Vector2> texCoords;

		for (const auto& vertex : vertices)
		{
			positions.push_back(vertex.Position);
			normals.push_back(vertex.Normal);
			texCoords.push_back(vertex.TexCoords);
		}

		newMesh->setVertices(positions);
		newMesh->setNormals(normals);
		newMesh->setTexCoords(texCoords);

		newMesh->setIndices(meshData.indices, MeshTopology::TRIANGLES);
		newMesh->uploadMeshData();
		return newMesh;
	}

	static Texture* LoadTexture(String fileName)
	{
		//Generate texture ID and load texture dat
		String filePath = "resources/textures/" + fileName;

		int width, height, nrChannels;
		unsigned char* image = stbi_load(filePath.c_str(), &width, &height, &nrChannels, 0);

		if (!image) {
			LOG_ERROR("texture %s loading error ... " << filePath);
			return nullptr;
		}
		else LOG("texture %s loaded" << filePath);

		TextureFormat format;
		if (nrChannels == 1) format = TextureFormat::RED;
		else if (nrChannels == 3) format = TextureFormat::RGB;
		else if (nrChannels == 4) format = TextureFormat::RGBA;
		else format = TextureFormat::RGB;

		Texture* texture = new Texture(width, height, 0, format);
		texture->name = fileName;
		//texture->name = "texture_diffuse";

		// Assign texture to ID
		Texture::Bind(texture);
		texture->SetPixels(image);
		texture->GenerateMipmap();

		GL::SetTextureWrapModeU(TextureWrapMode::REPEAT);
		GL::SetTextureWrapModeV(TextureWrapMode::REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		Texture::Unbind();

		stbi_image_free(image);

		return texture;
	}

	static Mesh* GetPrimitiveCubeMesh()
	{
		if(primitiveCubeMesh ==nullptr){
		
			Mesh* mesh = new Mesh();
			
			Cube cube;
			mesh->setVertices(Vec3Math::ToList(cube.cubeVertices, 72));
			mesh->setTriangles(Vec3Math::ToList(cube.cubeIndices, 36));
			mesh->setNormals(Vec3Math::ToList(cube.cubeNormals, 72));
			
			mesh->setTexCoords(Vec2Math::ToList(cube.cubeTexCoords, 48));
			mesh->uploadMeshData();
		
		primitiveCubeMesh = mesh;
		}
		
		return primitiveCubeMesh;
	}


	static Mesh* GetPrimitiveSphereMesh()
	{
		if (primitiveSphereMesh == nullptr) {

			Mesh* mesh = Resources::LoadModel("planet/planet.obj")->mesh;
			primitiveSphereMesh = mesh;
		}

		return primitiveSphereMesh;	
	}
};

/*
unsigned int loadCubemap(List<String> faces)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	int width, height, nrChannels;
	for (unsigned int i = 0; i < faces.size(); i++)
	{
		unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
			);
			stbi_image_free(data);
		}
		else
		{
			std::cout << "Cubemap tex failed to load at path: " << faces[i] << std::endl;
			stbi_image_free(data);
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	return textureID;
}
*/

Mesh* Resources::primitiveCubeMesh;
Mesh* Resources::primitiveSphereMesh;