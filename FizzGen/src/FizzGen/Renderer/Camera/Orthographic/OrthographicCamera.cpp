
#include "fgpch.h"

#include "OrthographicCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace FizzGen
{

	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
		:m_Near( - 1.0f), m_Far(1.0f), m_ProjectionMatrix(glm::ortho(left, right, bottom, top, m_Near, m_Far)), m_ViewMatrix(1.0f)
	{
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void OrthographicCamera::RecalculateViewMatrix()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) *
			glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0, 0, 1));
		
		m_ViewMatrix = glm::inverse(transform);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

}
