#pragma once

#include <glm/glm.hpp>
#include <GL/glew.h>
#include "obj_loader.h"
namespace CareEngine {

	class Vertex
	{
	public:
		Vertex(const glm::vec3& pos, const glm::vec2& texCoord, const glm::vec3& normal = glm::vec3(0, 0, 0))
		{
			this->pos = pos;
			this->texCoord = texCoord;
			this->normal = normal;
		}
		inline glm::vec3* getPos() { return &pos; }
		inline glm::vec2* getTexCoord() { return &texCoord; }
		inline glm::vec3* getNormal() { return &normal; }

	private:
		glm::vec3 pos;
		glm::vec2 texCoord;
		glm::vec3 normal;
	};

	class Mesh
	{
	public:
		Mesh(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices);
		Mesh(const std::string& fileName);
		void Draw();

		virtual ~Mesh();

	protected:
		void InitMesh(const IndexedModel& model);

		enum
		{
			POSITION_VB, // VB - Vertex Buffer
			TEXCOORD_VB,
			NORMAL_VB,
			INDEX_VB,

			NUM_BUFFERS
		};

		GLuint m_vertexArrayObject;
		GLuint m_vertexArrayBuffers[NUM_BUFFERS];
		unsigned int m_drawCount;

	private:
		Mesh(const Mesh& other);
		void operator=(const Mesh& other);
	};

}