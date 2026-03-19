
#include "fgpch.h"

#include "Application.h"

#include "FizzGen/Events/ApplicationEvent.h"
#include "FizzGen/Log.h"

namespace FizzGen
{
	Application::Application()
	{
		 
	}

	Application::~Application()
	{
	}

	void Application::run()
	{
		std::cout << "FizzGen!" << std::endl;

		//// Test code
		WindowResizeEvent e(1280, 720);
		//FG_TRACE(e);
		FG_TRACE(e.ToString());

		while (true)
		{

		}
	}
}
