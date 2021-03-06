#pragma once

#include <string>
#include <GL/glew.h>
#include "Transform.h"
#include "Camera.h"

namespace CareEngine {

	class Shader
	{
	public:
		Shader(const std::string& fileName);

		void Bind();
		void Update(const Transform& transform, const Camera& camera);
		GLuint getUniformLocation(const std::string& uniformName);


		virtual ~Shader();
	private:
		static const unsigned int NUM_SHADERS = 2;

		Shader(const Shader& other);
		void operator=(const Shader& other);

		enum
		{
			TRANSFORM_U, // U - uniforms

			NUM_UNIFORMS
		};

		GLuint m_program;
		GLuint m_shaders[NUM_SHADERS];
		GLuint m_uniforms[NUM_UNIFORMS];
	};

}