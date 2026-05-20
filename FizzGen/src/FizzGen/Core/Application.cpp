
#include "fgpch.h"

#include "Application.h"

#include "FizzGen/Core/Log.h"

#include "FizzGen/Renderer/Renderer.h"

//temp
#include <GLFW/glfw3.h>


namespace FizzGen
{

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;


	Application::Application()
	{
		FG_PROFILE_FUNCTION();

		FG_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

		Renderer::Init();


		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

	}

	Application::~Application()
	{
		FG_PROFILE_FUNCTION();
		//m_ImGuiLayer->OnDetach();
	}

	void Application::PushLayer(Layer* layer)
	{
		FG_PROFILE_FUNCTION();

		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		FG_PROFILE_FUNCTION();

		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	void Application::Run()
	{
		FG_PROFILE_FUNCTION();

		while (m_Running)
		{
			FG_PROFILE_SCOPE("RunLoop");

			float time = (float)glfwGetTime(); // Platform::GetTime()
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			if (!m_Minimized)
			{
				{
					FG_PROFILE_SCOPE("LayerStack OnUpdate");
					for (Layer* layer : m_LayerStack)
					{
						layer->OnUpdate(timestep);
					}
				}
				m_ImGuiLayer->Begin();
				{
					FG_PROFILE_SCOPE("LayerStack ImGui Render");

					for (Layer* layer : m_LayerStack)
					{
						layer->OnImGuiRender();
					}

				}
				m_ImGuiLayer->End();

			}
		
			m_Window->OnUpdate();
		
		}
	}

	void Application::OnEvent(Event& e)
	{
		FG_PROFILE_FUNCTION();

		EventDispatcher dispatcher(e);

		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(OnWindowResize));

		FG_CORE_TRACE("{0}", e);

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			(*--it)->OnEvent(e);
			if (e.IsHandled())
			{ break; }
		}
		
	}

	bool Application::OnWindowClose(WindowCloseEvent& event)
	{
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& event)
	{

		FG_PROFILE_FUNCTION();

		if (event.GetWidth() == 0 || event.GetHeight() == 0)
		{
			m_Minimized = true;
			return false;
		}

		m_Minimized = false;
		
		Renderer::OnWindowResize(event.GetWidth(), event.GetHeight());
		
		return false;
	}

}
