#pragma once

#include <string>
#include <GL/glew.h>

namespace CareEngine {

	class Texture
	{
	public:
		Texture(const std::string& fileName);

		void Bind(unsigned int unit);

		virtual ~Texture();
	private:
		Texture(const Texture& other);
		void operator=(const Texture& other);

		GLuint m_texture;
	};

}
