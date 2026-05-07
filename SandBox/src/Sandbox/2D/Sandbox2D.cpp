
#include "Sandbox2D.h"

#include <imgui/imgui.h>

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

//temp
//#include "FizzGen/Platform/OpenGL/Shader/OpenGLShader.h"


Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1.6f, true)
{}

void Sandbox2D::OnUpdate(FizzGen::Timestep timestep)
{
	m_CameraController.OnUpdate(timestep);

	//render
	FizzGen::RenderCommand::SetClearColor(m_BackgroundColor);
	FizzGen::RenderCommand::Clear();

	FizzGen::Renderer2D::BeginScene(m_CameraController.GetCamera());
	{
		FizzGen::Renderer2D::DrawQuad({ -0.5f, 0.0f }, { 0.8f, 0.8f }, 0, { 0.8f, 0.2f, 0.3f, 1.0f });
		FizzGen::Renderer2D::DrawQuad({ 0.5f, 0.5f }, { 0.5f, 0.75f },30, { 0.0f, 0.2f, 0.3f, 1.0f });


		//m_Shader->Bind();
		//m_Shader->SetFloat4("u_Color", m_SquareColor);

		//FizzGen::Renderer::Submit(m_Shader, m_VertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
	}
	FizzGen::Renderer2D::EndScene();
}

void Sandbox2D::OnEvent(FizzGen::Event& event)
{
	//update
	m_CameraController.OnEvent(event);


}

void Sandbox2D::OnAttach()
{
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
	ImGui::End();
}

