
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
			m_TriangleVA.reset(FizzGen::VertexArray::Create());

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
			m_TriangleVA->AddVertexBuffer(vertexBuffer);

			uint32_t indices[3] = { 0, 1, 2 };

			FizzGen::Ref<FizzGen::IndexBuffer> indexBuffer;
			indexBuffer.reset(FizzGen::IndexBuffer::Create(indices, (sizeof(indices) / sizeof(uint32_t))));
			m_TriangleVA->SetIndexBuffer(indexBuffer);



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

			
			m_Texture = FizzGen::Texture2D::Create("res/Textures/20x20sqaures.png");
		
			
			m_ShaderLibrary.Load("res/Shaders/texture.angle.glsl");
			m_ShaderLibrary.Load("res/Shaders/flatcolor.angle.glsl");
			m_ShaderLibrary.Load("res/Shaders/vertexposition.angle.glsl");
	
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

				auto flatColorShader = m_ShaderLibrary.Get("flatcolor.angle");
				std::dynamic_pointer_cast<FizzGen::OpenGLShader>(flatColorShader)->Bind();
				std::dynamic_pointer_cast<FizzGen::OpenGLShader>(flatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);

				for (int y = 0; y < 20; y++)
					for (int x = 0; x < 20; x++)
					{
						glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
						glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
						
						FizzGen::Renderer::Submit(flatColorShader, m_SquareVA, transform);
					}

				auto textureShader = m_ShaderLibrary.Get("texture.angle");				
				m_Texture->Bind();
				FizzGen::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.15)));

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

		FizzGen::ShaderLibrary m_ShaderLibrary;

		FizzGen::Ref<FizzGen::VertexArray> m_TriangleVA;

		FizzGen::Ref<FizzGen::Texture2D> m_Texture;

		FizzGen::Ref<FizzGen::VertexArray> m_SquareVA;

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
