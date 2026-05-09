
#include "Sandbox2D.h"

#include <imgui/imgui.h>

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

//temp
//#include "FizzGen/Platform/OpenGL/Shader/OpenGLShader.h"
#include <chrono>

template <typename fn>
class Timer
{
	public:
		
		Timer(const char* name, fn&& function)
			:m_Name(name), m_Function(function), m_Stoped(false)
		{
			m_StartTime = std::chrono::high_resolution_clock::now();
		}

		~Timer()
		{
			if (!m_Stoped)
				Stop();
		}

		void Stop()
		{
			auto endTime = std::chrono::high_resolution_clock::now();

			long long start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTime).time_since_epoch().count();
			long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTime).time_since_epoch().count();

			float duration = (end - start) * 0.001f;

			m_Stoped = true;

			m_Function({ m_Name, duration });
		}

	private:

		const char* m_Name;
		std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTime;
		bool m_Stoped = false;
		fn m_Function;

};

#define PROFILE_SCOPE(name) Timer timer##__LINE__(name, [&](ProfileResult pr){m_ProfileResults.push_back(pr); });

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1.6f, true)
{}

void Sandbox2D::OnUpdate(FizzGen::Timestep timestep)
{
	PROFILE_SCOPE("Sandbox2D OnUpdate");

	//update
	{
		PROFILE_SCOPE("CameraController OnUpdate");
		m_CameraController.OnUpdate(timestep);
	}

	//render
	{
		PROFILE_SCOPE("Renderer2D Full");
	
		//prep
		{
			PROFILE_SCOPE("Renderer2D Prep");
			FizzGen::RenderCommand::SetClearColor(m_BackgroundColor);
			FizzGen::RenderCommand::Clear();
		}
		
		//draw
		{
			PROFILE_SCOPE("Renderer2D Draw");
			FizzGen::Renderer2D::BeginScene(m_CameraController.GetCamera());
			{
				FizzGen::Renderer2D::DrawQuad({ -0.5f, 0.0f }, { 0.8f, 0.8f }, 0, { 0.8f, 0.2f, 0.3f, 1.0f });
				FizzGen::Renderer2D::DrawQuad({ 0.5f, 0.5f, -0.1f }, { 2.5f, 2.5f }, m_Texture);


				//m_Shader->Bind();
				//m_Shader->SetFloat4("u_Color", m_SquareColor);

				//FizzGen::Renderer::Submit(m_Shader, m_VertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
			}
			FizzGen::Renderer2D::EndScene();
		}
	}
}

void Sandbox2D::OnEvent(FizzGen::Event& event)
{
	//update
	m_CameraController.OnEvent(event);


}

void Sandbox2D::OnAttach()
{
	m_Texture = FizzGen::Texture2D::Create("res/Textures/20x20sqaures.png");

	m_VertexArray = FizzGen::VertexArray::Create();

	float squareVertices[5 * 4] =
	{
		-0.5f, -0.5f, 0.0f,		0.0f, 0.0f,
		 0.5f, -0.5f, 0.0f,		1.0f, 0.0f,
		 0.5f,  0.5f, 0.0f,		1.0f, 1.0f,
		-0.5f,  0.5f, 0.0f,		0.0f, 1.0f
	};

	FizzGen::Ref<FizzGen::VertexBuffer> squareVB;
	squareVB.reset(FizzGen::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
	squareVB->SetLayout({
		{
			FizzGen::ShaderDataType::Float3, "a_Position" }
		,{ FizzGen::ShaderDataType::Float2, "a_TexCoords" }
		});

	m_VertexArray->AddVertexBuffer(squareVB);

	uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
	FizzGen::Ref<FizzGen::IndexBuffer> squareIB;

	squareIB.reset(FizzGen::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
	m_VertexArray->SetIndexBuffer(squareIB);

	m_Shader = FizzGen::Shader::Create("res/Shaders/flatcolor.angle.glsl");

}

void Sandbox2D::OnDetach()
{

}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit3("Square Color", &m_SquareColor.x);

	for (auto& result : m_ProfileResults)
	{
		ImGui::Text("%s : %.3fms", result.Name, result.Time);
		
		//char label[50];
		//strcpy(label, " : %.3fms   ");
		//strcat(label, result.Name);

		//ImGui::Text(label, result.Time);
		
	}
	m_ProfileResults.clear();

	ImGui::End();
}

