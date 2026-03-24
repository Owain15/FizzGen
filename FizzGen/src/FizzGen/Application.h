#pragma once

#include "Core.h"
#include "FizzGen/LayerStack.h"
#include "Events/Event.h"
#include "FizzGen/Events/ApplicationEvent.h"
#include "Window.h"

namespace FizzGen
{
	class FIZZGEN_API Application
	{
		public:
		
			Application();
			virtual ~Application();
		
			void Run();

			void OnEvent(Event& e);


			void PushLayer(Layer* layer);
			void PushOverlay(Layer* layer);

		private:

			bool OnWindowClose(WindowCloseEvent& e);

			std::unique_ptr<Window> m_Window;
			bool m_Running = true;
			LayerStack m_LayerStack;

	};

	// To be defined in client
	Application* CreateApplication();
}

