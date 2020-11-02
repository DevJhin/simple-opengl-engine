#include "Material.h"
#include "ShaderUtils.h"


Material::Material(Shader* shader)
{
	this->shader = shader;

	this->shaderProgramID = ShaderUtils::createShaderProgramID(shader->vertShaderID, shader->fragShaderID);
}

Material::~Material()
{
	GL::DeleteShaderProgram(shaderProgramID);
	LOG("Material Destroyed");
}

uint Material::getShaderProgramID() const
{
	return shaderProgramID;
}


Shader* Material::getShader() const
{
	return shader;
}

void Material::Use()
{
	GL::UseShaderProgram(shaderProgramID);
}

void Material::SetBool(const String& name, bool value) const
{
	GL::SetUniformBool(shaderProgramID, name, value);
}

void Material::SetInt(const String& name, int value) const
{
	GL::SetUniformInt(shaderProgramID, name, value);
}

void Material::SetFloat(const String& name, float value) const
{
	GL::SetUniformFloat(shaderProgramID, name, value);
}

void Material::SetVec2(const String& name, const Vector2& value) const
{
	GL::SetUniformVec2(shaderProgramID, name, value);
}

void Material::SetVec2(const String& name, float x, float y) const
{
	GL::SetUniformVec2(shaderProgramID, name, x, y);
}

void Material::SetVec3(const String& name, const Vector3& value) const
{
	GL::SetUniformVec3(shaderProgramID, name, value);
}

void Material::SetVec3(const String& name, float x, float y, float z) const
{
	GL::SetUniformVec3(shaderProgramID, name, x, y, z);
}

void Material::SetVec4(const String& name, const Vector4& value) const
{
	GL::SetUniformVec4(shaderProgramID, name, value);
}

void Material::SetVec4(const String& name, float x, float y, float z, float w) const
{
	GL::SetUniformVec4(shaderProgramID, name, x, y, z, w);
}

void Material::SetMat2(const String& name, const glm::mat2& mat) const
{
	GL::SetUniformMatrix2x2(shaderProgramID, name, mat);
}

void Material::SetMat3(const String& name, const glm::mat3& mat) const
{
	GL::SetUniformMatrix3x3(shaderProgramID, name, mat);
}

void Material::SetMat4(const String& name, const Matrix4x4& mat) const
{
	GL::SetUniformMatrix4x4(shaderProgramID, name, mat);
}

void Material::SetTexture(const String& name, const Texture& texture) const
{
	SetInt(name, texture.textureID);
}


Material* Material::copy()
{
	Material* newMaterial = new Material(shader);
	newMaterial->SetTextures(textures);
	return newMaterial;
}

List<Texture*>& Material::GetTextures()
{
	return textures;
}

void Material::SetTextures(const List<Texture*>& textures)
{
	this->textures = textures;
}
