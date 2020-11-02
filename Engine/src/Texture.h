#pragma once

#include "Object.h"

enum class TextureType
{
	Default,
	Normal
};

enum class TextureFormat
{
	RED = GL_RED,
	RGB = GL_RGB,
	RGBA = GL_RGBA,
};

enum class TextureWrapMode
{
	REPEAT = GL_REPEAT,

};


class Texture :public Object
{
public:
	friend Material;

	Texture(int width, int height, int mipmapLevel, TextureFormat format);
	~Texture();

	static void Bind(Texture* bindTexture);
	static void Unbind();

	void SetPixels(unsigned char* imageData);
	void GenerateMipmap();


private:
	uint textureID;

	int width;
	int height;

	int mipmapLevel;
	TextureFormat format;

	static Texture* activeTexture;

};

