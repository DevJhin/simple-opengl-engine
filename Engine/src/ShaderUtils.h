#pragma once

enum class ShaderType
{
	Vertex = GL_VERTEX_SHADER,
	Fragment = GL_FRAGMENT_SHADER,
	Geometry = GL_GEOMETRY_SHADER
};

#include <fstream>
#include <sstream>

#include "CoreTypes.h"

#include "GL.h"

static const String BUILT_IN_SHADER_FOLDER_PATH("resources/shaders/built-in/");

class ShaderUtils{

public:

	static String getShaderFilePath(const String& shaderName, ShaderType shaderType)
	{
		String extension;
		
		switch (shaderType) {
			case ShaderType::Vertex: extension = ".vert"; break;
			case ShaderType::Fragment: extension = ".frag"; break;
			case ShaderType::Geometry: extension = ".geom"; break;
		default: ;
		}
		return BUILT_IN_SHADER_FOLDER_PATH + shaderName + extension;
	}
	/*
	 * Load shader source code from shader files.
	 */
	static String loadShaderSource(const String& shaderName, ShaderType shaderType)
	{
		String shaderPath = getShaderFilePath(shaderName, shaderType);
		
	    // 1. retrieve the  source code from filePath
	    std::string shaderSource;
	    std::ifstream shaderFile;
		
	    // ensure ifstream objects can throw exceptions:
	    shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	    try
	    {
	        // open files
	        shaderFile.open(shaderPath);
	        std::stringstream vShaderStream, fShaderStream;
	        // read file's buffer contents into streams
	        vShaderStream << shaderFile.rdbuf();
	        // close file handlers
	        shaderFile.close();
	        // convert stream into string
	        shaderSource = vShaderStream.str();
	    }
	    catch (std::ifstream::failure e)
	    {
	        LOG("ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ");
	    }
		return shaderSource;
	}

	/*
	 * Compile shader from the source.
	 */
	static uint compileShaderSource(const String& source, ShaderType shaderType)
	{
		const char* shaderSource = source.c_str();

		const uint shaderID = GL::CreateShader(shaderType);

		GL::ShaderSource(shaderID, source);
	
		GL::CompileShader(shaderID);
		
		String log;
		if (!GL::CheckShaderCompileError(shaderID, log))
		{
			LOG_ERROR("Failed to compile shader: " + log);
		}
		
		return shaderID;
	}

	/*
	 * Create a Shader program from vert and frag shader IDs.
	 */
	static uint createShaderProgramID(int vertShaderID, int fragShaderID)
	{
		uint shaderProgramID = GL::CreateShaderProgram();
		
		GL::AttachShaderToProgram(shaderProgramID, vertShaderID);
		GL::AttachShaderToProgram(shaderProgramID, fragShaderID);

		GL::LinkProgram(shaderProgramID);

		String log;
		if(!GL::CheckShaderProgramLinkError(shaderProgramID, log))
		{
			LOG_ERROR("Failed to link shader program: "<<log);
		}
		return shaderProgramID;
	}

};