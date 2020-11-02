#pragma once

#include <string>
#include <fstream>
#include <vector>

#include <GL/glew.h>


struct Vertex
{
    // Position
    Vector3 Position;
    // Normal
    Vector3 Normal;
    // TexCoords
    Vector2 TexCoords;
};

struct TextureData
{
    GLuint id;
    String type;
    String path;
};

class MeshData
{
public:
    /*  Mesh Data  */
    List<Vertex> vertices;
    List<GLuint> indices;
    List<TextureData> textures;
    
    /*  Functions  */
    // Constructor
    MeshData( List<Vertex> vertices, List<GLuint> indices, List<TextureData> textures )
    {
        this->vertices = vertices;
        this->indices = indices;
        this->textures = textures;
        
    }
};


