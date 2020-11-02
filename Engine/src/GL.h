#pragma once
#include "CoreTypes.h"
#include "Mesh.h"
#include "Texture.h"

/*
 * Low-level graphics library class.
 */
class GL
{
public:
	inline static void EnableDepthTest();
	inline static void DisableDepthTest();
	inline static void SetDepthTestMode(DepthTestMode depthTestMode);
	
	inline static void EnableStencilTest();
	inline static void DisableStencilTest();
	inline static void SetStencilTestMode(StencilTestMode stencilTestMode, uint stencilMask);

	inline static void SetStencilMask(uint stencilMask);
	inline static uint CreateShader(ShaderType shaderType);

	inline static void ShaderSource(uint shaderID, const String& shaderSource);

	inline static void CompileShader(uint shaderID);

	inline static uint CreateShaderProgram();

	inline static void AttachShaderToProgram(uint shaderProgramID, uint shaderID);

	inline static void LinkProgram(uint shaderProgramID);


	inline static bool CheckShaderCompileError(uint shaderID, String& log);

	inline static bool CheckShaderProgramLinkError(uint shaderProgramID, String& log);

	inline static void DeleteShader(uint shaderID);

	inline static void DeleteShaderProgram(uint shaderProgramID);

	/*
	 * Shader utilities
	 */
	inline static void UseShaderProgram(uint shaderID);

	inline static void SetUniformBool(uint shaderID, const String& name, bool value);

	inline static void SetUniformInt(uint shaderID, const String& name, int value);

	inline static void SetUniformFloat(uint shaderID, const String& name, float value);

	inline static void SetUniformVec2(uint shaderID, const String& name, const Vector2& value);

	inline static void SetUniformVec2(uint shaderID, const String& name, float x, float y);

	inline static void SetUniformVec3(uint shaderID, const String& name, const Vector3& value);

	inline static void SetUniformVec3(uint shaderID, const String& name, float x, float y, float z);

	inline static void SetUniformVec4(uint shaderID, const String& name, const Vector4& value);

	inline static void SetUniformVec4(uint shaderID, const String& name, float x, float y, float z, float w);

	inline static void SetUniformMatrix2x2(uint shaderID, const String& name, const glm::mat2& mat);

	inline static void SetUniformMatrix3x3(uint shaderID, const String& name, const glm::mat3& mat);

	inline static void SetUniformMatrix4x4(uint shaderID, const String& name, const Matrix4x4& mat);

	/*
	 * Draw utilities
	 */

	inline static void DrawElements(MeshTopology meshTopology, int indicesCount);

	/*
	 * Texture utilities
	 */
	inline static uint GenerateTexture();

	inline static void BindTexture(uint textureID);
	inline static void UnbindTexture();

	inline static void ActiveTexture(uint index);

	inline static void SetTexture2DImage(int mipmapLevel, TextureFormat format, int width, int height, unsigned char* imageData);

	inline static void SetTextureWrapModeU(TextureWrapMode wrapMode);
	inline static void SetTextureWrapModeV(TextureWrapMode wrapMode);

	inline static void DeleteTexture(uint textureID);

	inline static void GenerateMipmap();
};
