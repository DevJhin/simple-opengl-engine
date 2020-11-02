#include <GL/glew.h>
#include "GL.h"

#include "Mathematics.h"
#include "Texture.h"

void GL::EnableDepthTest()
{
	glEnable(GL_DEPTH_TEST);
}

void GL::DisableDepthTest()
{
	glDisable(GL_DEPTH_TEST);
}

void GL::SetDepthTestMode(DepthTestMode depthTestMode)
{
	glDepthFunc(GLenum(depthTestMode));
}

void GL::EnableStencilTest()
{
	glEnable(GL_STENCIL_TEST);
}

void GL::DisableStencilTest()
{
	glDisable(GL_STENCIL_TEST);
}

void GL::SetStencilTestMode(StencilTestMode stencilTestMode, uint stencilMask)
{
	glStencilFunc(GLenum(stencilTestMode),1,stencilMask);
}

void GL::SetStencilMask(uint stencilMask)
{
	glStencilMask(stencilMask);
}

uint GL::CreateShader(ShaderType shaderType)
{
	return glCreateShader(GLenum(shaderType));
}

void GL::ShaderSource(uint shaderID, const String& shaderSource)
{
	const char* src = shaderSource.c_str();
	glShaderSource(shaderID, 1, &src, nullptr);
}

void GL::CompileShader(uint shaderID)
{
	glCompileShader(shaderID);
}

uint GL::CreateShaderProgram()
{
	return glCreateProgram();
}

void GL::AttachShaderToProgram(uint shaderProgramID, uint shaderID)
{
	glAttachShader(shaderProgramID, shaderID);
}

void GL::LinkProgram(uint shaderProgramID)
{
	glLinkProgram(shaderProgramID);
}

bool GL::CheckShaderCompileError(uint shaderID, String& log)
{
	int success;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		char infoLog[1024];
		glGetShaderInfoLog(shaderID, 1024, nullptr, infoLog);
		log = infoLog;
		return false;
	}
	return true;
}

bool GL::CheckShaderProgramLinkError(uint shaderProgramID, String& log)
{
	int success;
	glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &success);
	if (!success)
	{
		char infoLog[1024];
		glGetProgramInfoLog(shaderProgramID, 1024, nullptr, infoLog);
		log = String(infoLog);
		return false;
	}
	return true;
}

void GL::DeleteShader(uint shaderID)
{
	glDeleteShader(shaderID);
}

void GL::DeleteShaderProgram(uint shaderProgramID)
{
	glDeleteProgram(shaderProgramID);
}

void GL::UseShaderProgram(uint shaderID)
{
	glUseProgram(shaderID);
}

void GL::SetUniformBool(uint shaderID, const String& name, bool value)
{
	glUniform1i(glGetUniformLocation(shaderID, name.c_str()), int(value));
}

// ------------------------------------------------------------------------
void GL::SetUniformInt(uint shaderID, const String& name, int value)
{
	glUniform1i(glGetUniformLocation(shaderID, name.c_str()), value);
}

void GL::SetUniformFloat(uint shaderID, const String& name, float value)
{
	glUniform1f(glGetUniformLocation(shaderID, name.c_str()), value);
}

void GL::SetUniformVec2(uint shaderID, const String& name, const Vector2& value)
{
	glUniform2fv(glGetUniformLocation(shaderID, name.c_str()), 1, &value[0]);
}
void GL::SetUniformVec2(uint shaderID, const String& name, float x, float y)
{
	glUniform2f(glGetUniformLocation(shaderID, name.c_str()), x, y);
}

void GL::SetUniformVec3(uint shaderID, const String& name, const Vector3& value)
{
	glUniform3fv(glGetUniformLocation(shaderID, name.c_str()), 1, &value[0]);
}
void GL::SetUniformVec3(uint shaderID, const String& name, float x, float y, float z)
{
	glUniform3f(glGetUniformLocation(shaderID, name.c_str()), x, y, z);
}

void GL::SetUniformVec4(uint shaderID, const String& name, const Vector4& value)
{
	glUniform4fv(glGetUniformLocation(shaderID, name.c_str()), 1, &value[0]);
}
void GL::SetUniformVec4(uint shaderID, const String& name, float x, float y, float z, float w)
{
	glUniform4f(glGetUniformLocation(shaderID, name.c_str()), x, y, z, w);
}
// ------------------------------------------------------------------------
void GL::SetUniformMatrix2x2(uint shaderID, const String& name, const glm::mat2& mat)
{
	glUniformMatrix2fv(glGetUniformLocation(shaderID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
// ------------------------------------------------------------------------
void GL::SetUniformMatrix3x3(uint shaderID, const String& name, const glm::mat3& mat)
{
	glUniformMatrix3fv(glGetUniformLocation(shaderID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
// ------------------------------------------------------------------------
void GL::SetUniformMatrix4x4(uint shaderID, const String& name, const Matrix4x4& mat)
{
	glUniformMatrix4fv(glGetUniformLocation(shaderID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

/*
 * Draw calls
 */
void GL::DrawElements(MeshTopology meshTopology, int indicesCount)
{
	glDrawElements(GLenum(meshTopology), indicesCount, GL_UNSIGNED_INT, 0);
}

uint GL::GenerateTexture()
{
	uint textureId;
	glGenTextures(1, &textureId);
	return textureId;
}

void GL::SetTexture2DImage(int mipmapLevel, TextureFormat format, int width, int height, unsigned char* imageData)
{
	glTexImage2D(GL_TEXTURE_2D, mipmapLevel, GLenum(format), width, height, 0, GLenum(format), GL_UNSIGNED_BYTE, imageData);
}

void GL::SetTextureWrapModeU(TextureWrapMode wrapMode)
{
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GLenum(wrapMode));
}

void GL::SetTextureWrapModeV(TextureWrapMode wrapMode)
{
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GLenum(wrapMode));
}

void GL::DeleteTexture(uint textureID)
{
	glDeleteTextures(0, &textureID);
}

void GL::GenerateMipmap()
{
	glGenerateMipmap(GL_TEXTURE_2D);
}


void GL::BindTexture(uint textureID)
{
	glBindTexture(GL_TEXTURE_2D, textureID);
}

void GL::UnbindTexture()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void GL::ActiveTexture(uint index)
{
	glActiveTexture(GL_TEXTURE0+index);
}
