
#include "fgpch.h"

#include "Application.h"

#include "FizzGen/Log.h"
#include "FizzGen/Platform/OpenGL/OpenGLBuild.h"

namespace FizzGen
{
	
	#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
			case ShaderDataType::Float:		return GL_FLOAT;
			case ShaderDataType::Float2:	return GL_FLOAT;
			case ShaderDataType::Float3:	return GL_FLOAT;
			case ShaderDataType::Float4:	return GL_FLOAT;
			case ShaderDataType::Mat3:		return GL_FLOAT;
			case ShaderDataType::Mat4:		return GL_FLOAT;
			case ShaderDataType::Int:		return GL_INT;
			case ShaderDataType::Int2:		return GL_INT;
			case ShaderDataType::Int3:		return GL_INT;
			case ShaderDataType::Int4:		return GL_INT;
			case ShaderDataType::Bool:		return GL_BOOL;
		}
	
		FG_CORE_ASSERT(false, "Unknown ShaderDataType!");

	
		return 0; 
	}

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

			float vertices[3 * 7] = 
			{
				-0.5f, -0.5f, 0.0f,		0.1f, 0.5f, 1.0f, 1.0f,
				 0.5f, -0.5f, 0.0f,		0.0f, 0.5f, 0.5f, 1.0f,
				 0.0f,  0.5f, 0.0f,		1.0f, 0.5f, 0.0f, 1.0f
			};
			
			m_VertexBuffer.reset(FizzGen::VertexBuffer::Create(vertices, sizeof(vertices)));
			{

				BufferLayout layout =
				{
					{ ShaderDataType::Float3, "a_Position" },
					{ ShaderDataType::Float4, "a_Color" }
				};

				m_VertexBuffer->SetLayout(layout);
			}

			uint32_t index = 0;
			const auto& layout = m_VertexBuffer->GetLayout();
			for (const auto& element : layout)
			{
				glEnableVertexAttribArray(index);
				glVertexAttribPointer
				(
					index, 
					element.GetComponentCount(), 
					ShaderDataTypeToOpenGLBaseType(element.Type), 
					element.Normalized ? GL_TRUE : GL_FALSE, 
					layout.GetStride(), 
					(const void*)element.Offset
				);
				index++;
			}
			
			
			uint32_t indices[3] = { 0, 1, 2 };
			m_IndexBuffer.reset(FizzGen::IndexBuffer::Create(indices, (sizeof(indices) / sizeof(uint32_t))));

	
			#ifdef FG_USE_ANGLE
			std::string vertexShaderSource =
				"#version 300 es\n"
				"layout(location = 0) in vec3 a_Position;\n"
				"layout(location = 1) in vec4 a_Color;\n"
				"out vec4 v_Color;\n"
				"void main()\n"
				"{\n"
					"gl_Position = vec4(a_Position, 1.0);\n"
					"v_Color = a_Color;\n"
				"}";


				std::string fragmentShaderSource =

					"#version 300 es\n"

					"precision mediump float;\n"
					"in vec4 v_Color;\n"
					"out vec4 FragColor;\n"

					"void main()\n"
					"{\n"
						"FragColor = v_Color;\n"
					"}";


			#else
				std::string vertexShaderSource =

					"#version 330 core\n"

					"layout(location = 0) in vec3 a_Position;\n"
					"layout(location = 1) in vec4 a_Color;\n"
					"out vec4 v_Color;\n"

					"void main()\n"
					"{\n"
						"gl_Position = vec4(a_Position, 1.0);\n"
						"v_Color = a_Color;\n"
					"}";


				std::string fragmentShaderSource =

					"#version 330 core\n"

					"in vec4 v_Color;\n"
					"out vec4 FragColor;\n"

					"void main()\n"
					"{\n"
						"FragColor = v_Color;\n"
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
