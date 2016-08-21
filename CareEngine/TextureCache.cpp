#include "TextureCache.h"
#include <iostream>

namespace CareEngine {

	TextureCache::TextureCache()
	{

	}


	TextureCache::~TextureCache()
	{

	}


	Texture* TextureCache::getTexture(const std::string fileName)
	{
		// auto will be: std::map<std::string, Texture>::iterator
		auto mit = m_textureMap.find(fileName);

		// check if texture is not in map
		if (mit == m_textureMap.end()) {
			Texture* newTexture = new Texture(fileName);

			m_textureMap.insert(make_pair(fileName, newTexture)); // will make pair: std::pair<std::string, Texture>
			std::cout << "Loaded texture!" << std::endl;
			return newTexture;
		}
		std::cout << "Used cached texture!" << std::endl;
		return mit->second;
	}
}