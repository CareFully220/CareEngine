#pragma once
#include <map>
#include <string>
#include "Texture.h"

namespace CareEngine {

	class TextureCache
	{
	public:
		TextureCache();

		Texture* getTexture(const std::string fileName);

		~TextureCache();
	private:
		std::map<std::string, Texture*> m_textureMap;
	};

}