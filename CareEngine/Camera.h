#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include "Transform.h"

namespace CareEngine {

	class Camera
	{
	public:
		Camera(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar);

		inline glm::mat4 getViewProjection()
		{
			return m_perspective * glm::lookAt(m_transform.getPos(), m_position + m_forward, m_up);
		}
	private:
		glm::mat4 m_perspective;
		glm::vec3 m_up;

		Transform m_transform;

	};
}

