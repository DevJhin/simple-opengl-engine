#pragma once

#include "Shader.h"
#include "MeshData.h"
#include "Texture.h"

enum class PropertyType
{
	Texture,
	Color,
	Vector,
	Float
};

class MaterialProperty
{
	String name;
	
};


class Material
{	
public:
	Material(Shader* shader);
	~Material();

	uint getShaderProgramID() const;

	Shader* getShader() const;

    // activate the shader
// ------------------------------------------------------------------------
	void Use();

	void SetBool(const String& name, bool value) const;

	void SetInt(const String& name, int value) const;

	void SetFloat(const String& name, float value) const;

	void SetVec2(const String& name, const Vector2& value) const;

	void SetVec2(const String& name, float x, float y) const;

	void SetVec3(const String& name, const Vector3& value) const;

	void SetVec3(const String& name, float x, float y, float z) const;

	void SetVec4(const String& name, const Vector4& value) const;

	void SetVec4(const String& name, float x, float y, float z, float w) const;

	void SetMat2(const String& name, const glm::mat2& mat) const;

	void SetMat3(const String& name, const glm::mat3& mat) const;

	void SetMat4(const String& name, const Matrix4x4& mat) const;
	
	void SetTexture(const String& name, const Texture& texture) const;
	
	Material* copy();

	List<Texture*>& GetTextures();
	void SetTextures(const List<Texture*>& textures);
	
private:
	Shader* shader;
	uint shaderProgramID;

	List<Texture*> textures;
};

