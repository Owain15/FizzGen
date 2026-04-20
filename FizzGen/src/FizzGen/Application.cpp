
#include "fgpch.h"

#include "Application.h"

#include "FizzGen/Log.h"
#include "FizzGen/Platform/OpenGL/OpenGLBuild.h"

namespace FizzGen
{
	
	#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		FG_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		//temp render code
			glGenVertexArrays(1, &m_VertexArray);
			glBindVertexArray(m_VertexArray);

			//glGenBuffers(1, &m_VertexBuffer);
			//glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);

			float vertices[3 * 3] = 
			{
				-0.5f, -0.5f, 0.0f,
				 0.5f, -0.5f, 0.0f,
				 0.0f,  0.5f, 0.0f
			};
			
			m_VertexBuffer.reset(FizzGen::VertexBuffer::Create(vertices, sizeof(vertices)));

			//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),vertices,GL_STATIC_DRAW);

			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,(3 * sizeof(float)),nullptr);


			//glGenBuffers(1, &m_IndexBuffer);
			//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);

			uint32_t indices[3] = { 0, 1, 2 };
			m_IndexBuffer.reset(FizzGen::IndexBuffer::Create(indices, (sizeof(indices) / sizeof(uint32_t))));

			//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
		
			#ifdef FG_USE_ANGLE
			std::string vertexShaderSource = 
				"#version 300 es\n"
				"layout(location = 0) in vec3 a_Position;\n"
				"void main()\n"
				"{\n"
					"gl_Position = vec4(a_Position, 1.0);\n"
				"}";
 

				std::string fragmentShaderSource = 
         
					"#version 300 es\n"
         
					"precision mediump float;\n"
					"out vec4 f_Color;\n"
         
					"void main()\n"
					"{\n"
						"f_Color = vec4(1.0, 0.0, 0.0, 1.0);\n"
					"}";
				
				
			#else
				std::string vertexShaderSource = 
         
					"#version 330 core\n"
         
					"layout(location = 0) in vec3 a_Position;\n"
         
					"void main()\n"
					"{\n"
						"gl_Position = vec4(a_Position, 1.0);\n"
					"}";
				
				
				std::string fragmentShaderSource =

					"#version 330 core\n"

					"out vec4 f_Color;\n"

					"void main()\n"
					"{\n"
						"f_Color = vec4(1.0, 0.0, 0.0, 1.0);\n"
					"}";
     
				
			
			#endif

			m_Shader.reset(new Shader(vertexShaderSource, fragmentShaderSource));
			
		//


	}

	Application::~Application()
	{
		//m_ImGuiLayer->OnDetach();
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	void Application::Run()
	{
		//std::cout << "FizzGen!" << std::endl;

	
		while (m_Running)
		{
			//background
			glClearColor(0.1f, 0.1f, 0.1f, 1);
			//glClearColor(1, 1, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			//temp render code
				
				m_Shader->Bind();
				glBindVertexArray(m_VertexArray);

				m_IndexBuffer->Bind();

				glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);
			//

			for (Layer* layer : m_LayerStack)
			{
				layer->OnUpdate();
			}

			m_ImGuiLayer->Begin();
				for (Layer* layer : m_LayerStack)
				{
					layer->OnImGuiRender();
				}
			m_ImGuiLayer->End();

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
