
#include "fgpch.h"

#include "Renderer2D.h"

#include "FizzGen/Renderer/RenderCommand/RenderCommand.h"

#include "FizzGen/Renderer/VertexArray/VertexArray.h"
#include "FizzGen/Renderer/Shader/Shader.h"

#include <glm/gtc/matrix_transform.hpp>

//#include "FizzGen/Platform/OpenGL/Shader/OpenGLShader.h"
//#include "FizzGen/Platform/ANGLE/Shader/ANGLEShader.h"

//public
namespace FizzGen
{
	struct Renderer2DData
	{
		FizzGen::Ref<VertexArray> QuadVertexArray;
		FizzGen::Ref<Shader> FlatColorShader;
	};

	static Renderer2DData* s_Data;

	void Renderer2D::Init()
	{
		s_Data = new Renderer2DData();

		s_Data->QuadVertexArray = FizzGen::VertexArray::Create();

		float quadVertices[5 * 4] =
		{
			-0.5f, -0.5f, 0.0f,		0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f,		1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f,		1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f,		0.0f, 1.0f
		};

		FizzGen::Ref<FizzGen::VertexBuffer> quadVB;
		quadVB.reset(FizzGen::VertexBuffer::Create(quadVertices, sizeof(quadVertices)));

		FizzGen::BufferLayout layout = {
			{ FizzGen::ShaderDataType::Float3, "a_Position" },
			{ FizzGen::ShaderDataType::Float2, "a_TexCoord" }
		};

		quadVB->SetLayout(layout);
		s_Data->QuadVertexArray->AddVertexBuffer(quadVB);

		uint32_t quadIndices[6] = { 0, 1, 2, 2, 3, 0 };
		FizzGen::Ref<FizzGen::IndexBuffer> quadIB;
		quadIB.reset(FizzGen::IndexBuffer::Create(quadIndices, sizeof(quadIndices)));

		s_Data->QuadVertexArray->SetIndexBuffer(quadIB);

		//should not be hardcoded, but is fine for now.
		s_Data->FlatColorShader = FizzGen::Shader::Create("res/shaders/flatcolor.angle.glsl");

	}

	void Renderer2D::Shutdown()
	{
		delete s_Data;
	}

	void Renderer2D::BeginScene(const FizzGen::OrthographicCamera& camera)
	{
		s_Data->FlatColorShader->Bind();
		s_Data->FlatColorShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
	}

	void Renderer2D::EndScene()
	{

	}


	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, 0, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		DrawQuad(position, size, 0, color);
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, float rotationInDegrees, const glm::vec4& color)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, rotationInDegrees, color);
	}	

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, float rotationInDegrees, const glm::vec4& color)
	{
		s_Data->FlatColorShader->Bind();
		s_Data->FlatColorShader->SetFloat4("u_Color", color);
		
		//position,rotation,scale
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * 
			glm::rotate(glm::mat4(1.0f), glm::radians(rotationInDegrees), { 0.0f, 0.0f, 1.0f }) *
			glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		
		s_Data->FlatColorShader->SetMat4("u_Transform", transform);

		s_Data->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
	}

}
