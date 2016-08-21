#include "Camera.h"

namespace CareEngine
{

	Camera::Camera(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar)
	{
		m_perspective = glm::perspective(fov, aspect, zNear, zFar);
		m_position = pos;
		m_forward = glm::vec3(1, 0, 0);
		m_up = glm::vec3(0, 0, 1);
	}

}