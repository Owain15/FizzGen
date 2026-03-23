
#include "fgpch.h"

#include "Application.h"

#include "FizzGen/Events/ApplicationEvent.h"
#include "FizzGen/Log.h"

namespace FizzGen
{
	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		std::cout << "FizzGen!" << std::endl;

	
		while (m_Running)
		{
			m_Window->OnUpdate();
		}
	}
}
