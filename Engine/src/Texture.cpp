
#include "GL.h"

Texture* Texture::activeTexture = nullptr;

Texture::Texture(int width, int height, int mipmapLevel, TextureFormat format)
{
	this->width = width;
	this->height = height;
	this->mipmapLevel = mipmapLevel;
	this->format = format;

	textureID = GL::GenerateTexture();
}

Texture::~Texture()
{
	LOG("Destroy texture");
	GL::DeleteTexture(textureID);
}

void Texture::Bind(Texture* bindTexture)
{
	GL::BindTexture(bindTexture->textureID);
}


void Texture::Unbind()
{
	GL::UnbindTexture();
}

void Texture::SetPixels(unsigned char* imageData)
{
	GL::SetTexture2DImage(mipmapLevel, format, width, height, imageData);
}


void Texture::GenerateMipmap()
{
	GL::GenerateMipmap();
}

