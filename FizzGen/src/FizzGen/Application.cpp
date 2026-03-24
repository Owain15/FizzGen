
#include "fgpch.h"

#include "Application.h"

#include "FizzGen/Log.h"

namespace FizzGen
{
	
	#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
	}

	Application::~Application()
	{

	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
	}

	void Application::Run()
	{
		//std::cout << "FizzGen!" << std::endl;

	
		while (m_Running)
		{

			for (Layer* layer : m_LayerStack)
			{
				layer->OnUpdate();
			}
		

			m_Window->OnUpdate();
		
		}
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);

		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

		FG_CORE_TRACE("{0}", e);
		/*if (e.GetEventType() == EventType::WindowClose)
			m_Running = false;*/

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			(*--it)->OnEvent(e);
			if (e.IsHandled())
			{ break; }
		}
		
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

}
