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
#include "FizzGen/Renderer/VertexArray.h"
#include "FizzGen/Renderer/Camera/Orthographic/OrthographicCamera.h"


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

			std::shared_ptr<FizzGen::VertexArray> m_VertexArray;
			std::shared_ptr<Shader> m_Shader;

			std::shared_ptr<FizzGen::VertexArray> m_SquareVA;
			std::shared_ptr<Shader> m_Shader2;

			OrthographicCamera m_Camera;

		private:

			static Application* s_Instance;

	};

	// To be defined in client
	Application* CreateApplication();
}

