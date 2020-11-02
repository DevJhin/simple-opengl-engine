#pragma once
#include "CoreTypes.h"

enum class DepthTestMode
{
	Always = GL_ALWAYS,
	Less =GL_LESS,
	Greater = GL_GREATER,
	
	Equal = GL_EQUAL
};

enum class StencilTestMode
{
	Always = GL_ALWAYS,
	Less = GL_LESS,
	Greater = GL_GREATER,
	Equal = GL_EQUAL,
	NotEqual = GL_NOTEQUAL,
};
class Shader
{
public:
    ~Shader();

    static Shader* Find(const String& shaderName);

	friend class Material;

	bool useDepthMode;
	DepthTestMode depthTestMode;
	
	bool useStencilMode;
	StencilTestMode stencilMode;
	uint stencilMask;
	
	Shader(const Shader& copy);
private:
    Shader();
	static Dictionary<String,Shader*> shaderDictionary;
	
	uint vertShaderID;
	uint fragShaderID;
	
};