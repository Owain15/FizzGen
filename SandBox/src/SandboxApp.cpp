
#include "FizzGen.h"

#include "imgui/imgui.h"

class ExampleLayer : public FizzGen::Layer
{
	public:
	
		ExampleLayer() : Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f), m_CameraRotation(0.0f)
		{
			m_VertexArray.reset(FizzGen::VertexArray::Create());

			//temp render code

			float vertices[3 * 7] =
			{
				-0.5f, -0.5f, 0.0f,		0.1f, 0.5f, 1.0f, 1.0f,
				 0.5f, -0.5f, 0.0f,		0.0f, 0.5f, 0.5f, 1.0f,
				 0.0f,  0.5f, 0.0f,		1.0f, 0.5f, 0.0f, 1.0f
			};

			std::shared_ptr<FizzGen::VertexBuffer> vertexBuffer;
			vertexBuffer.reset(FizzGen::VertexBuffer::Create(vertices, sizeof(vertices)));

			FizzGen::BufferLayout layout =
			{
				{ FizzGen::ShaderDataType::Float3, "a_Position" },
				{ FizzGen::ShaderDataType::Float4, "a_Color" }
			};

			vertexBuffer->SetLayout(layout);
			m_VertexArray->AddVertexBuffer(vertexBuffer);

			uint32_t indices[3] = { 0, 1, 2 };

			std::shared_ptr<FizzGen::IndexBuffer> indexBuffer;
			indexBuffer.reset(FizzGen::IndexBuffer::Create(indices, (sizeof(indices) / sizeof(uint32_t))));
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

			FizzGen::BufferLayout squareLayout =
			{
				{ FizzGen::ShaderDataType::Float3, "a_Position" }
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

			m_Shader.reset(new FizzGen::Shader(vertexShaderSource, fragmentShaderSource));

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

			m_Shader2.reset(new FizzGen::Shader(vertexShaderSource2, fragmentShaderSource2));

			//
		}
	
		void OnUpdate() override
		{
			//camera movement
			{
				if (FizzGen::Input::IsKeyPressed(FG_KEY_LEFT))
				{
					if (FizzGen::Input::IsKeyPressed(FG_KEY_LEFT_CONTROL))
					{
						m_CameraRotation += m_CameraRotationSpeed;
					}
					else
					{
						m_CameraPosition.x -= m_CameraSpeed;
					}
				}

				if (FizzGen::Input::IsKeyPressed(FG_KEY_RIGHT))
				{
					if (FizzGen::Input::IsKeyPressed(FG_KEY_LEFT_CONTROL))
					{
						m_CameraRotation += m_CameraRotationSpeed;
					}
					else
					{
						m_CameraPosition.x += m_CameraSpeed;
					}
				}

				if (FizzGen::Input::IsKeyPressed(FG_KEY_UP))
				{
					m_CameraPosition.y += m_CameraSpeed;
				}

				if (FizzGen::Input::IsKeyPressed(FG_KEY_DOWN))
				{
					m_CameraPosition.y -= m_CameraSpeed;
				}

			
			}

			//background
			glm::vec4 backgroundColor = { 0.1f, 0.1f, 0.1f, 1 };
			FizzGen::RenderCommand::SetClearColor(backgroundColor);
			FizzGen::RenderCommand::Clear();

			//camera propreties test
			m_Camera.SetPosition(m_CameraPosition);
			m_Camera.SetRotation(m_CameraRotation);


			FizzGen::Renderer::BeginScene(m_Camera);
			{

				FizzGen::Renderer::Submit(m_Shader2, m_SquareVA);

				FizzGen::Renderer::Submit(m_Shader, m_VertexArray);

			}
			FizzGen::Renderer::EndScene();

			//FizzGen::Renderer::Flush();
		}
	
		virtual void OnImGuiRender() override
		{
	
		}

		void OnEvent(FizzGen::Event& event) override
		{
		
		}


	private:

		std::shared_ptr<FizzGen::VertexArray> m_VertexArray;
		std::shared_ptr<FizzGen::Shader> m_Shader;

		std::shared_ptr<FizzGen::VertexArray> m_SquareVA;
		std::shared_ptr<FizzGen::Shader> m_Shader2;

		FizzGen::OrthographicCamera m_Camera;
		glm::vec3 m_CameraPosition;
		float m_CameraRotation;
		float m_CameraSpeed = 0.05f;
		float m_CameraRotationSpeed = 1.0f;
};

class Sandbox : public FizzGen::Application
{
	public:
	
		Sandbox()
		{
			auto testLayer = new ExampleLayer();
			PushLayer(testLayer);
		}
	
		~Sandbox()
		{
		
		}
	
};

FizzGen::Application* FizzGen::CreateApplication()
{
	return new Sandbox();
}
