#include "Mesh.h"
#include <GL/glew.h>


Mesh::Mesh()
{
	hasGenerated = false;
	meshTopology = MeshTopology::TRIANGLES;
}

Mesh::~Mesh()
{
	LOG("Destroy Mesh");

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

	for (Mesh* mesh: subMeshes)
	{
		delete mesh;
	}
	
	vertices.clear();
	colors.clear();
	normals.clear();
	texCoords.clear();
}

int Mesh::vertexCount() const
{
	return vertices.size();
}

int Mesh::indicesCount() const
{
	return indices.size();
}

MeshTopology Mesh::getMeshTopology() const
{
	return meshTopology;
}

void Mesh::setVertices(const List<Vector3>& vertices)
{
	this->vertices = vertices;
}

void Mesh::setTriangles(const List<Vector3Int>& triangles)
{
	List<uint> tempIndices;
	for (auto triangle : triangles)
	{
		tempIndices.push_back(triangle.x);
		tempIndices.push_back(triangle.y);
		tempIndices.push_back(triangle.z);
	}
	setIndices(tempIndices, MeshTopology::TRIANGLES);
}

void Mesh::setColors(const List<Vector4>& colors)
{
	this->colors = colors;
}

void Mesh::setNormals(const List<Vector3>& normals)
{
	this->normals = normals;
}

void Mesh::setTexCoords(const List<Vector2>& texCoords)
{
	this->texCoords = texCoords;
}

void Mesh::setSubmeshes(const List<Mesh*>& subMeshes)
{
	this->subMeshes = subMeshes;
}

void Mesh::setIndices(const List<uint>& indices, MeshTopology meshTopology)
{
	this->indices=indices;
	this->meshTopology = meshTopology;
}

List<Mesh*>& Mesh::getSubMeshes()
{
	return subMeshes;
}

struct Attribute
{
	int typeSize;
	int typeFloatCount;
	
	int dataCount;
	int dataSize;
	
	void* dataPtr;
	
	template<typename T>
	Attribute(List<T>& data)
	{
		
		this->dataPtr = &data[0];
		dataCount = data.size();
		typeSize = sizeof(T);

		typeFloatCount= typeSize/sizeof(float);
		dataSize = typeSize * dataCount;
		
	}
};


/**
 * \brief Bind flatShadingMesh of pentagons to GL.
 */
void Mesh::uploadMeshData()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	
    glBindVertexArray(VAO);


	List<Attribute> attributes;

	attributes.push_back(Attribute(vertices));
	
	if(!normals.empty())
		attributes.push_back(Attribute(normals));
	if(!colors.empty())
		attributes.push_back(Attribute(colors));
	if(!texCoords.empty())
		attributes.push_back(Attribute(texCoords));

	
	const int attributeCount = attributes.size();
	int totalSizeSum = 0;

	for(int i=0;i<attributeCount;i++)
	{
		totalSizeSum+=attributes[i].dataSize;
	}
	
	// copy vertex attrib data to VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, totalSizeSum, nullptr, GL_STATIC_DRAW); // reserve space

	int subDataSum = 0;
	//copy data to buffer
	for(int i=0;i<attributeCount;i++)
	{
		int dataSize = attributes[i].dataSize;
		glBufferSubData(GL_ARRAY_BUFFER, subDataSum, dataSize, attributes[i].dataPtr);
		subDataSum += dataSize;
	}

	uint iSize = indices.size() * sizeof(int);
	// copy index data to EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, iSize, &indices[0], GL_STATIC_DRAW);

	int attribPointerOffset = 0;
	for(int i=0;i<attributeCount;i++)
	{
		glVertexAttribPointer(i, attributes[i].typeFloatCount, GL_FLOAT, GL_FALSE, attributes[i].typeSize, (void*)attribPointerOffset);
		attribPointerOffset += attributes[i].dataSize;		
	}

	for (int i = 0; i < attributeCount; i++)
	{
		glEnableVertexAttribArray(i);
	}

    //Clear buffer.
	glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

}

void Mesh::bindVertexArray()
{
    glBindVertexArray(VAO);
}

void Mesh::updateVertexPosAt(int index, Vector2 position, float depth)
{
    Vector3 vertPos(position, depth);
	
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferSubData(GL_ARRAY_BUFFER, index * sizeof(Vector3), sizeof(Vector3), &vertPos);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vector3), (void*)0);

	glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
