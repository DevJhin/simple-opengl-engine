#include "ShaderUtils.h"
#include "Shader.h"

Dictionary<String, Shader*> Shader::shaderDictionary;

Shader::~Shader()
{
	LOG("Shader Destroyed");
}


Shader* Shader::Find(const String& shaderName)
{
	auto iterator = shaderDictionary.find(shaderName);
	if(iterator != shaderDictionary.end())
	{
		return iterator->second;
	}
	
	const String vertShaderSource = ShaderUtils::loadShaderSource(shaderName, ShaderType::Vertex);
	const String fragShaderSource = ShaderUtils::loadShaderSource(shaderName, ShaderType::Fragment);

	Shader* shader = new Shader();

	shader->vertShaderID = ShaderUtils::compileShaderSource(vertShaderSource, ShaderType::Vertex);
	shader->fragShaderID = ShaderUtils::compileShaderSource(fragShaderSource, ShaderType::Fragment);

	shaderDictionary.insert(std::pair<String, Shader*>(shaderName, shader));
	return shader;
}




Shader::Shader():depthTestMode(DepthTestMode::Less),stencilMode(StencilTestMode::Always)
{
	useDepthMode = true;
	useStencilMode = false;
}

Shader::Shader(const Shader& copy) :depthTestMode(DepthTestMode::Less), stencilMode(StencilTestMode::Always)
{
	useDepthMode = true;
	useStencilMode = false;
	fragShaderID = copy.fragShaderID;
	vertShaderID = copy.vertShaderID;
}
