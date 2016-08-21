#include "ResourceManager.h"

namespace CareEngine {

	TextureCache ResourceManager::m_textureCache;
	GLuint ResourceManager::m_boundTexture;

	Texture* ResourceManager::getTexture(std::string fileName)
	{
		return m_textureCache.getTexture(fileName);
	}

}