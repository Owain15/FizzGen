#pragma once

#include "Core.h"
#include "FizzGen/LayerStack.h"
#include "Events/Event.h"
#include "FizzGen/Events/ApplicationEvent.h"
#include "WindowInterface.h"
#include "ImGui/ImGuiLayer.h"

//temp
#include "FizzGen/Renderer/Shader.h"
#include "FizzGen/Renderer/Buffer.h"

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

			inline static Application& Get() { return *s_Instance; }

			inline Window& GetWindow() { return *m_Window; }

		private:

			bool OnWindowClose(WindowCloseEvent& e);

			std::unique_ptr<Window> m_Window;
			ImGuiLayer* m_ImGuiLayer;
			bool m_Running = true;
			LayerStack m_LayerStack;

			unsigned int m_VertexArray;
			std::unique_ptr<FizzGen::VertexBuffer> m_VertexBuffer;
			std::unique_ptr<FizzGen::IndexBuffer> m_IndexBuffer;
			std::unique_ptr<Shader> m_Shader;
			

		private:

			static Application* s_Instance;

	};

	// To be defined in client
	Application* CreateApplication();
}

