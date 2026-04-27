#pragma once

#include <glm/glm.hpp>

namespace FizzGen
{
	
	class OrthographicCamera
	{

		public:

			OrthographicCamera(float left, float right, float bottom, float top);

			const glm::vec3& GetPosition() const { return m_Position; }
			void SetPosition(glm::vec3 position) {m_Position = position; RecalculateViewMatrix();};
			
			const float& GetRotation() const { return m_Rotation; }
			void SetRotation(float rotation) { m_Rotation = rotation; RecalculateViewMatrix(); }

			const glm::mat4& GetProjectionMatrix()	   const { return m_ProjectionMatrix; }
			const glm::mat4& GetViewMatrix()		   const { return m_ViewMatrix; }
			const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }

		private:

			void RecalculateViewMatrix();

		private:

			float m_Near, m_Far;
			float m_Rotation = 0.0f;

			//float m_Left, m_Right, m_Bottom, m_Top, m_Near, m_Far;

			glm::mat4 m_ProjectionMatrix;
			glm::mat4 m_ViewMatrix;

			glm::mat4 m_ViewProjectionMatrix;

			glm::vec3 m_Position = glm::vec3(0.0f);

	};


}
