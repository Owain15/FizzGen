#pragma once

#include "OrthographicCamera.h"
#include "FizzGen/Core/Timestep.h"

#include "FizzGen/Events/ApplicationEvent.h"
#include "FizzGen/Events/MouseEvent.h"

namespace FizzGen
{
	
	class OrthographicCameraControler
	{
		public:

			OrthographicCameraControler(float aspectRatio, bool rotationEnabled = false);

			void OnUpdate(Timestep timestep);
			void OnEvent(Event& event);

			OrthographicCamera& GetCamera() { return m_Camera; }
			const OrthographicCamera& GetCamera() const { return m_Camera; }

			float GetZoomLevel() const { return m_ZoomLevel; }
			void SetZoomLevel(float level) { m_ZoomLevel = level; /*UpdateCameraProjection();*/ }

		private:

			bool OnMouseScrolled(MouseScrolledEvent& event);
			bool OnWindowResized(WindowResizeEvent& event);
			
			//void CalculateView();
			//void UpdateCameraProjection();
		
		private:

			float m_AspectRatio;
			float m_ZoomLevel = 1.0f;

			bool m_RotationEnabled;

			float m_Rotation = 0.0f;
			glm::vec3 m_Position = glm::vec3(0.0f);

			float m_MovmentSpeed = 5.0f;
			float m_RotationSpeed = 30.0f;

			OrthographicCamera m_Camera;

	};

}