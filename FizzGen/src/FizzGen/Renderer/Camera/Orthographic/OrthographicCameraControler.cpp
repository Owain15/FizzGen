
#include "fgpch.h"
#include "OrthographicCameraControler.h"

#include "FizzGen/Core/InputInterface.h"
#include "FizzGen/InputCodes/Keycodes.h"

//public
namespace FizzGen
{
	OrthographicCameraControler::OrthographicCameraControler(float aspectRatio, bool rotationEnabled) 
		: m_AspectRatio(aspectRatio), 
		  m_RotationEnabled(rotationEnabled), 
		  m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel)
	{

	}

	void OrthographicCameraControler::OnUpdate(Timestep timestep)
	{
		FG_PROFILE_FUNCTION();

		//camera movement		
		if (FizzGen::Input::IsKeyPressed(FG_KEY_LEFT_CONTROL) && !FizzGen::Input::IsKeyPressed(FG_KEY_LEFT_SHIFT))
		{
			if (Input::IsKeyPressed(FG_KEY_LEFT) ^ Input::IsKeyPressed(FG_KEY_RIGHT))
			{ 
				if (Input::IsKeyPressed(FG_KEY_LEFT))
				{
					m_Position.x -= m_MovmentSpeed * timestep;
				}
				else
				{
					m_Position.x += m_MovmentSpeed * timestep;
				}
			
			}

			if (Input::IsKeyPressed(FG_KEY_UP) ^ Input::IsKeyPressed(FG_KEY_DOWN))
			{
				if (Input::IsKeyPressed(FG_KEY_UP))
				{
					m_Position.y += m_MovmentSpeed * timestep;
				}
				else
				{
					m_Position.y -= m_MovmentSpeed * timestep;
				}
			}

			m_Camera.SetPosition(m_Position);
		}

		//camera rotation
		if (FizzGen::Input::IsKeyPressed(FG_KEY_LEFT_CONTROL) && FizzGen::Input::IsKeyPressed(FG_KEY_LEFT_SHIFT))
		{
			if (FizzGen::Input::IsKeyPressed(FG_KEY_LEFT) ^ FizzGen::Input::IsKeyPressed(FG_KEY_RIGHT))
			{
				if(FizzGen::Input::IsKeyPressed(FG_KEY_LEFT))
				{
					m_Rotation += m_RotationSpeed * timestep;
				}
				else
				{
					m_Rotation -= m_RotationSpeed * timestep;
				}
			}

			m_Camera.SetRotation(m_Rotation);
		}


	}

	void OrthographicCameraControler::OnEvent(Event& event)
	{
		FG_PROFILE_FUNCTION();

		EventDispatcher dispatcher(event);

		dispatcher.Dispatch<MouseScrolledEvent>(FG_BIND_EVENT_FN(OrthographicCameraControler::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(FG_BIND_EVENT_FN(OrthographicCameraControler::OnWindowResized));
	}
}

//private
namespace FizzGen
{
	bool OrthographicCameraControler::OnMouseScrolled(MouseScrolledEvent& event)
	{
		FG_PROFILE_FUNCTION();

		m_ZoomLevel -= event.GetYOffset() * 0.25f;
		
		//bounds check
		m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
		m_ZoomLevel = std::min(m_ZoomLevel, 10.0f);

		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);

		//might need to be moved to OnUpdate() if it causes issues with camera movement speed
		m_MovmentSpeed = m_ZoomLevel;

		return false;
	}

	bool OrthographicCameraControler::OnWindowResized(WindowResizeEvent& event)
	{
		FG_PROFILE_FUNCTION();

		m_AspectRatio = (float)event.GetWidth() / (float)event.GetHeight();
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);

		return false;
	}
}
