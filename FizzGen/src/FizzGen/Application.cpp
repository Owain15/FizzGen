
#include "fgpch.h"

#include "Application.h"

#include "FizzGen/Log.h"

#include "FizzGen/Renderer/Renderer.h"
//#include "FizzGen/Renderer/Camera/Orthographic/OrthographicCamera.h"


namespace FizzGen
{

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;


	Application::Application()
		: m_Camera(-1.6f, 1.6f, -0.9f, 0.9f)
	{
		FG_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		m_VertexArray.reset(FizzGen::VertexArray::Create());

		//temp render code

			float vertices[3 * 7] = 
			{
				-0.5f, -0.5f, 0.0f,		0.1f, 0.5f, 1.0f, 1.0f,
				 0.5f, -0.5f, 0.0f,		0.0f, 0.5f, 0.5f, 1.0f,
				 0.0f,  0.5f, 0.0f,		1.0f, 0.5f, 0.0f, 1.0f
			};
			
			std::shared_ptr<VertexBuffer> vertexBuffer;
			vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
			
			BufferLayout layout =
			{
				{ ShaderDataType::Float3, "a_Position" },
				{ ShaderDataType::Float4, "a_Color" }
			};

			vertexBuffer->SetLayout(layout);
			m_VertexArray->AddVertexBuffer(vertexBuffer);
			
			uint32_t indices[3] = { 0, 1, 2 };

			std::shared_ptr<IndexBuffer> indexBuffer;
			indexBuffer.reset(IndexBuffer::Create(indices, (sizeof(indices) / sizeof(uint32_t))));
			m_VertexArray->SetIndexBuffer(indexBuffer);
	


			m_SquareVA.reset(FizzGen::VertexArray::Create());
			
			float squareVertices[3 * 4] =
			{
				-0.75f, -0.75f, 0.0f,
				 0.75f, -0.75f, 0.0f,
				 0.75f,  0.75f, 0.0f,
				-0.75f,  0.75f, 0.0f
			};
			
			std::shared_ptr<FizzGen::VertexBuffer> squareVB;
			squareVB.reset(FizzGen::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

			BufferLayout squareLayout =
			{
				{ ShaderDataType::Float3, "a_Position" }
			};

			squareVB->SetLayout(squareLayout);
			m_SquareVA->AddVertexBuffer(squareVB);

			uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
			std::shared_ptr<FizzGen::IndexBuffer> squareIB;
			squareIB.reset(FizzGen::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
			m_SquareVA->SetIndexBuffer(squareIB);

		#ifdef FG_USE_ANGLE
			std::string vertexShaderSource =
				"#version 300 es\n"
				"layout(location = 0) in vec3 a_Position;\n"
				"layout(location = 1) in vec4 a_Color;\n"
				"uniform mat4 u_ViewProjection;\n"
				"out vec4 v_Color;\n"
				"void main()\n"
				"{\n"
					"gl_Position = u_ViewProjection * vec4(a_Position, 1.0);\n"
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
					
					"uniform mat4 u_ViewProjection;\n"
					
					"out vec4 v_Color;\n"

					"void main()\n"
					"{\n"
						"gl_Position = u_ViewProjection * vec4(a_Position, 1.0);\n"
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
		
		#ifdef FG_USE_ANGLE
		
			std::string vertexShaderSource2 =
				"#version 300 es\n"
				
				"layout(location = 0) in vec3 a_Position;\n"
				"out vec3 v_Position;\n"

				"uniform mat4 u_ViewProjection;\n"
				
				"void main()\n"
				"{\n"
					"v_Position = a_Position;\n"
					"gl_Position = u_ViewProjection * vec4(a_Position, 1.0);\n"
				"}";


			std::string fragmentShaderSource2 =

				"#version 300 es\n"
				"precision mediump float;\n"
				"in vec3 v_Position;\n"
				"out vec4 FragColor;\n"
				"void main()\n"
				"{\n"
					"FragColor = vec4(0.2, 0.3, 0.8, 1.0);\n"
				"}";


		#else
		
			std::string vertexShaderSource2 =

				"#version 330 core\n"

				"layout(location = 0) in vec3 a_Position;\n"

				"uniform mat4 u_ViewProjection;\n"

				"out vec3 v_Position;\n"

				"void main()\n"
				"{\n"
					"v_Position = a_Position;\n"
					"gl_Position = u_ViewProjection * vec4(a_Position, 1.0);\n"
				"}";


			std::string fragmentShaderSource2 =

				"#version 330 core\n"

				"in vec3 v_Position;\n"
				"out vec4 FragColor;\n"

				"void main()\n"
				"{\n"
					"FragColor = vec4(0.2, 0.3, 0.8, 1.0);\n"
				"}";
		#endif
		
			m_Shader2.reset(new Shader(vertexShaderSource2, fragmentShaderSource2));

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

		while (m_Running)
		{
			//background
			glm::vec4 backgroundColor = { 0.1f, 0.1f, 0.1f, 1 };
			RenderCommand::SetClearColor(backgroundColor);
			RenderCommand::Clear();

			//camera propreties test
			//m_Camera.SetPosition({ 0.0f, 0.0f, 0.0f });
			//m_Camera.setRotation(0.0f);
				

			Renderer::BeginScene(m_Camera);
			{
				
				Renderer::Submit(m_Shader2, m_SquareVA);

				Renderer::Submit(m_Shader, m_VertexArray);

			}
			Renderer::EndScene();

			//Renderer::Flush();


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
