
#include "FizzGen.h"

//temp
#include "imgui/imgui.h"

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "FizzGen/Platform/OpenGL/Shader/OpenGLShader.h"

class ExampleLayer : public FizzGen::Layer
{
	public:
	
		ExampleLayer() : Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f),
			m_CameraPosition(0.0f), m_CameraRotation(0.0f), m_SquarePosition(0.0f), m_SquareColor(0.0f, 0.0f, 0.0f)
		{
			m_VertexArray.reset(FizzGen::VertexArray::Create());

			//temp render code

			float vertices[3 * 7] =
			{
				-0.5f, -0.5f, 0.0f,		0.1f, 0.5f, 1.0f, 1.0f,
				 0.5f, -0.5f, 0.0f,		0.0f, 0.5f, 0.5f, 1.0f,
				 0.0f,  0.5f, 0.0f,		1.0f, 0.5f, 0.0f, 1.0f
			};

			FizzGen::Ref<FizzGen::VertexBuffer> vertexBuffer;
			vertexBuffer.reset(FizzGen::VertexBuffer::Create(vertices, sizeof(vertices)));

			FizzGen::BufferLayout layout =
			{
				{ FizzGen::ShaderDataType::Float3, "a_Position" },
				{ FizzGen::ShaderDataType::Float4, "a_Color" }
			};

			vertexBuffer->SetLayout(layout);
			m_VertexArray->AddVertexBuffer(vertexBuffer);

			uint32_t indices[3] = { 0, 1, 2 };

			FizzGen::Ref<FizzGen::IndexBuffer> indexBuffer;
			indexBuffer.reset(FizzGen::IndexBuffer::Create(indices, (sizeof(indices) / sizeof(uint32_t))));
			m_VertexArray->SetIndexBuffer(indexBuffer);



			m_SquareVA.reset(FizzGen::VertexArray::Create());

			float squareVertices[5 * 4] =
			{
				-0.5f, -0.5f, 0.0f,		0.0f, 0.0f,
				 0.5f, -0.5f, 0.0f,		1.0f, 0.0f,	
				 0.5f,  0.5f, 0.0f,		1.0f, 1.0f,
				-0.5f,  0.5f, 0.0f,		0.0f, 1.0f
			};

			FizzGen::Ref<FizzGen::VertexBuffer> squareVB;
			squareVB.reset(FizzGen::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

			FizzGen::BufferLayout squareLayout =
			{
				{ FizzGen::ShaderDataType::Float3, "a_Position" },
				{ FizzGen::ShaderDataType::Float2, "a_TexCoords" }
			};

			squareVB->SetLayout(squareLayout);
			m_SquareVA->AddVertexBuffer(squareVB);

			uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
			FizzGen::Ref<FizzGen::IndexBuffer> squareIB;
			squareIB.reset(FizzGen::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
			m_SquareVA->SetIndexBuffer(squareIB);

#ifdef FG_USE_ANGLE
			std::string vertexShaderSource =
				"#version 300 es\n"
				
				"layout(location = 0) in vec3 a_Position;\n"
				"layout(location = 1) in vec4 a_Color;\n"
				
				"uniform mat4 u_ViewProjection;\n"
				"uniform mat4 u_Transform;\n"
				
				"out vec4 v_Color;\n"
				
				"void main()\n"
				"{\n"
					"gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);\n"
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
				"uniform mat4 u_Transform;\n"

				"out vec4 v_Color;\n"

				"void main()\n"
				"{\n"
					"gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);\n"
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

			m_Shader.reset(FizzGen::Shader::Create(vertexShaderSource, fragmentShaderSource));

//Flat color shader

#ifdef FG_USE_ANGLE

			std::string flatColorVertexShaderSource =

				"#version 300 es\n"

				"layout(location = 0) in vec3 a_Position;\n"
				
				"out vec3 v_Position;\n"

				"uniform mat4 u_ViewProjection;\n"
				"uniform mat4 u_Transform;\n"

				"void main()\n"
				"{\n"
					"v_Position = a_Position;\n"
					"gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);\n"
				"}";


			std::string flatColorFragmentShaderSource =

				"#version 300 es\n"
				"precision mediump float;\n"
				
				"in vec3 v_Position;\n"
				
				"out vec4 FragColor;\n"
				
				"uniform vec3 u_Color;\n"

				"void main()\n"
				"{\n"
					"FragColor = vec4(u_Color, 1.0);\n"
				"}";


#else

			std::string flatColorVertexShaderSource =

				"#version 330 core\n"

				"layout(location = 0) in vec3 a_Position;\n"

				"uniform mat4 u_ViewProjection;\n"
				"uniform mat4 u_Transform;\n"

				"out vec3 v_Position;\n"

				"void main()\n"
				"{\n"
					"v_Position = a_Position;\n"
					"gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);\n"
				"}";


			std::string flatColorFragmentShaderSource =

				"#version 330 core\n"

				"in vec3 v_Position;\n"
				"out vec4 FragColor;\n"

				"uniform vec3 u_Color;\n"

				"void main()\n"
				"{\n"
					"FragColor = vec4(u_Color, 1.0);\n"
				"}";
#endif

			m_FlatColorShader.reset(FizzGen::Shader::Create(flatColorVertexShaderSource, flatColorFragmentShaderSource));


//Textured shader

#ifdef FG_USE_ANGLE

			std::string texturedVertexShaderSource =

				"#version 300 es\n"

				"layout(location = 0) in vec3 a_Position;\n"
				"layout(location = 1) in vec2 a_TexCoords;\n"

				"uniform mat4 u_ViewProjection;\n"
				"uniform mat4 u_Transform;\n"

				"out vec2 v_TexCoords;\n"

				"void main()\n"
				"{\n"
					"v_TexCoords = a_TexCoords;\n"
					"gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);\n"
				"}";


			std::string texturedFragmentShaderSource =

				"#version 300 es\n"
				"precision mediump float;\n"

				"in vec2 v_TexCoords;\n"

				"out vec4 FragColor;\n"

				"uniform sampler2D u_Texture;\n"

				"void main()\n"
				"{\n"
					"FragColor = texture(u_Texture, v_TexCoords);\n"
				"}";


#else

			std::string texturedVertexShaderSource =

				"#version 330 core\n"

				"layout(location = 0) in vec3 a_Position;\n"
				"layout(location = 1) in vec2 a_TexCoords;\n"

				"uniform mat4 u_ViewProjection;\n"
				"uniform mat4 u_Transform;\n"

				"out vec2 v_TexCoords;\n"

				"void main()\n"
				"{\n"
					"v_TexCoords = a_TexCoords;\n"
					"gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);\n"
				"}";


			std::string texturedFragmentShaderSource =

				"#version 330 core\n"

				"layout(location = 0) out vec4 FragColor;\n"

				"in vec2 v_TexCoords;\n"
				"out vec4 FragColor;\n"

				"uniform sampler2D u_Texture;\n"

				"void main()\n"
				"{\n"
					"FragColor = texture(u_Texture, v_TexCoords);\n"
				"}";
#endif

			//m_TexturedShader.reset(FizzGen::Shader::Create(texturedVertexShaderSource, texturedFragmentShaderSource));
			m_TexturedShader.reset(FizzGen::Shader::Create("res/Shaders/texture.angle.glsl"));

			m_Texture = FizzGen::Texture2D::Create("res/Textures/20x20sqaures.png");
			//"C:\Dev\FizzGen\SandBox\res\Textures\20x20sqaures.png"
			//"C:\Dev\FizzGen\SandBox\res\Shaders\texture.glsl"

			std::dynamic_pointer_cast<FizzGen::OpenGLShader>(m_TexturedShader)->Bind();
			std::dynamic_pointer_cast<FizzGen::OpenGLShader>(m_TexturedShader)->UploadUniformInt("u_Texture", 0);

			//
		}
	
		void OnUpdate(FizzGen::Timestep timestep) override
		{
	
			//camera movement
			{
				if (FizzGen::Input::IsKeyPressed(FG_KEY_LEFT))
				{
					if (FizzGen::Input::IsKeyPressed(FG_KEY_LEFT_CONTROL))
					{
						m_CameraRotation += m_RotationSpeed * timestep;
					}
					else if (FizzGen::Input::IsKeyPressed(FG_KEY_LEFT_SHIFT))
					{
						m_SquarePosition.x -= m_MovmentSpeed * timestep;
					}
					else
					{
						m_CameraPosition.x -= m_MovmentSpeed * timestep;
					}
				}

				if (FizzGen::Input::IsKeyPressed(FG_KEY_RIGHT))
				{
					if (FizzGen::Input::IsKeyPressed(FG_KEY_LEFT_CONTROL))
					{
						m_CameraRotation -= m_RotationSpeed * timestep;
					}
					else if (FizzGen::Input::IsKeyPressed(FG_KEY_LEFT_SHIFT))
					{
						m_SquarePosition.x += m_MovmentSpeed * timestep;
					}
					else
					{
						m_CameraPosition.x += m_MovmentSpeed * timestep;
					}
				}

				if (FizzGen::Input::IsKeyPressed(FG_KEY_UP))
				{
					if (FizzGen::Input::IsKeyPressed(FG_KEY_LEFT_SHIFT))
					{
						m_SquarePosition.y += m_MovmentSpeed * timestep;
					}
					else
					{
						m_CameraPosition.y += m_MovmentSpeed * timestep;
					}
					
				}

				if (FizzGen::Input::IsKeyPressed(FG_KEY_DOWN))
				{
					if (FizzGen::Input::IsKeyPressed(FG_KEY_LEFT_SHIFT))
					{
						m_SquarePosition.y -= m_MovmentSpeed * timestep;
					}
					else
					{
						m_CameraPosition.y -= m_MovmentSpeed * timestep;
					}
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
				glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

				//glm::vec3 redColor(0.8f, 0.2f, 0.3f);
				//glm::vec3 blueColor(0.2f, 0.3f, 0.8f);

				std::dynamic_pointer_cast<FizzGen::OpenGLShader>(m_FlatColorShader)->Bind();
				std::dynamic_pointer_cast<FizzGen::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);

				for (int y = 0; y < 20; y++)
					for (int x = 0; x < 20; x++)
					{
						glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
						glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
						
						FizzGen::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
					}

				m_Texture->Bind();
				FizzGen::Renderer::Submit(m_TexturedShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.15)));

			}
			FizzGen::Renderer::EndScene();

			//FizzGen::Renderer::Flush();
		}
	
		virtual void OnImGuiRender() override
		{
			ImGui::Begin("Settings");
			{
				ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
			}
			ImGui::End();
		}

		void OnEvent(FizzGen::Event& event) override
		{
		
		}


	private:

		FizzGen::Ref<FizzGen::VertexArray> m_VertexArray;
		FizzGen::Ref<FizzGen::Shader> m_Shader;

		FizzGen::Ref<FizzGen::Texture2D> m_Texture;

		FizzGen::Ref<FizzGen::VertexArray> m_SquareVA;
		FizzGen::Ref<FizzGen::Shader> m_FlatColorShader, m_TexturedShader;

		FizzGen::OrthographicCamera m_Camera;
		glm::vec3 m_CameraPosition;
		float m_CameraRotation;

		float m_MovmentSpeed = 1.0f;
		float m_RotationSpeed = 30.0f;

		glm::vec3 m_SquarePosition;
		glm::vec3 m_SquareColor;
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
