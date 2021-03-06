#include <cassert>
#include <iostream>
#include "Texture.h"
#include "ResourceManager.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace CareEngine {
	Texture::Texture(const std::string& fileName)
	{
		int width, height, numComponents;
		unsigned char* imageData = stbi_load(fileName.c_str(), &width, &height, &numComponents, 4);
		// unsigned char is 32 bits, 8 bits for each color channel, r, g, b, a.
		if (imageData == NULL)
			std::cerr << "Error: Failed to load texture: " << fileName << std::endl;

		glGenTextures(1, &m_texture);
		glBindTexture(GL_TEXTURE_2D, m_texture);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);

		stbi_image_free(imageData);
	}


	Texture::~Texture()
	{
		glDeleteTextures(1, &m_texture);
	}

	void Texture::Bind(unsigned int unit)
	{
		assert(unit >= 0 && unit <= 31);
		if (ResourceManager::m_boundTexture != m_texture)
		{
			glActiveTexture(GL_TEXTURE0 + unit);
			glBindTexture(GL_TEXTURE_2D, m_texture);
		}
	}
}