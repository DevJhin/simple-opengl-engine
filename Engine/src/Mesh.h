#pragma once
#include <GL/glew.h>

#include "CoreTypes.h"

enum class MeshTopology
{
	POINT = GL_POINT,
	LINE_STRIP = GL_LINE_STRIP,
	TRIANGLES = GL_TRIANGLES,
	TRIANGLES_FAN = GL_TRIANGLE_FAN,
	TRIANGLE_STRIP = GL_TRIANGLE_STRIP,
};

class Mesh
{
private:
	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;
	
	bool hasGenerated;

	List<Mesh*> subMeshes;
	
	List<Vector3> vertices;
	List<Vector4> colors;
	List<Vector3> normals;
	List<Vector2> texCoords;

	List<uint> indices;

	MeshTopology meshTopology;
	
public:
	Mesh();
	~Mesh();
	
	
	int vertexCount() const;
	int indicesCount() const;

	MeshTopology getMeshTopology() const;
	
	void setVertices(const List<Vector3>& vertices);
	void setNormals(const List<Vector3>& normals);
	void setColors(const List<Vector4>& colors);	
	void setTexCoords(const List<Vector2>& texCoords);
	
	void setSubmeshes(const List<Mesh*>& subMeshes);
	
	void setTriangles(const List<Vector3Int>& triangles);
	void setIndices(const List<uint>& indices, MeshTopology meshTopology);
	List<Mesh*>& getSubMeshes();
	List<Vector3>& getTriangles();

	void uploadMeshData();
	void bindVertexArray();
	void updateVertexPosAt(int index, Vector2 position, float depth);
};

