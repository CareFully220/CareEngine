#pragma once
#include "TextureCache.h"
#include <string>

namespace CareEngine {

	class ResourceManager
	{
	public:
		static Texture* getTexture(std::string fileName);
		static GLuint m_boundTexture;
	private:
		static TextureCache m_textureCache;
	};

}

