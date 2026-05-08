
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
		FizzGen::Ref<Shader> ColorTextureShader;
		FizzGen::Ref<Texture2D> WhiteTexture;
		
		//FizzGen::Ref<Shader> FlatColorShader;
		//FizzGen::Ref<Shader> TextureShader;
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
			{ FizzGen::ShaderDataType::Float2, "a_TexCoords" }
		};

		quadVB->SetLayout(layout);
		s_Data->QuadVertexArray->AddVertexBuffer(quadVB);

		uint32_t quadIndices[6] = { 0, 1, 2, 2, 3, 0 };
		FizzGen::Ref<FizzGen::IndexBuffer> quadIB;
		quadIB.reset(FizzGen::IndexBuffer::Create(quadIndices, sizeof(quadIndices)));

		s_Data->QuadVertexArray->SetIndexBuffer(quadIB);

		//should not be hardcoded, but is fine for now.
#ifdef FG_USE_ANGLE
		s_Data->ColorTextureShader = FizzGen::Shader::Create("res/shaders/colortextureshader.angle.glsl");
#else
		s_Data->ColorTextureShader = FizzGen::Shader::Create("res/shaders/colortextureshader.opengl.glsl");
#endif
		s_Data->ColorTextureShader->Bind();
		s_Data->ColorTextureShader->SetInt("u_Texture", 0);
		s_Data->ColorTextureShader->SetInt("u_TextureTileCount", 1);

		s_Data->WhiteTexture = FizzGen::Texture2D::Create(1, 1);
		uint32_t whiteTextureData = 0xffffffff;
		s_Data->WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));
	}

	void Renderer2D::Shutdown()
	{
		delete s_Data;
	}

	void Renderer2D::BeginScene(const FizzGen::OrthographicCamera& camera)
	{
		s_Data->ColorTextureShader->Bind();
		s_Data->ColorTextureShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
	}

	void Renderer2D::EndScene()
	{

	}

//draw quad by color
	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{ DrawQuad({ position.x, position.y, 0.0f }, size, 0, color); }

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{ DrawQuad(position, size, 0, color); }

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, float rotationInDegrees, const glm::vec4& color)
	{ DrawQuad({ position.x, position.y, 0.0f }, size, rotationInDegrees, color); }	

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, float rotationInDegrees, const glm::vec4& color)
	{
		//s_Data->ColorTextureShader->Bind();
		s_Data->ColorTextureShader->SetFloat4("u_FragColor", color);
		//bind texture 0 to white texture, so that the shader can use it
		s_Data->WhiteTexture->Bind();

		//position,rotation,scale
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * 
			glm::rotate(glm::mat4(1.0f), glm::radians(rotationInDegrees), { 0.0f, 0.0f, 1.0f }) *
			glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		
		s_Data->ColorTextureShader->SetMat4("u_Transform", transform);

		s_Data->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
	}

//draw quad by texture
	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const FizzGen::Ref<FizzGen::Texture2D>& texture)
	{ DrawQuad({position.x, position.y, 0.0f}, size, 0.0f, texture); }
	
	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const FizzGen::Ref<FizzGen::Texture2D>& texture)
	{ DrawQuad(position, size, 0.0f, texture); }
	
	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, float rotationInDegrees, const FizzGen::Ref<FizzGen::Texture2D>& texture)
	{ DrawQuad({position.x, position.y, 0.0f}, size, rotationInDegrees, texture); }
	
	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, float rotationInDegrees, const FizzGen::Ref<FizzGen::Texture2D>& texture)
	{ 
		//s_Data->ColorTextureShader->Bind();
		
		//reset color to white, so that the texture is not tinted
		s_Data->ColorTextureShader->SetFloat4("u_FragColor", glm::vec4(1.0f));
		texture->Bind();
		
		//position,rotation,scale
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) *
							  glm::rotate(glm::mat4(1.0f), glm::radians(rotationInDegrees), { 0.0f, 0.0f, 1.0f }) *
							  glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		s_Data->ColorTextureShader->SetMat4("u_Transform", transform);

		s_Data->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
	}

//draw quad by texture and color
	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const FizzGen::Ref<FizzGen::Texture2D>& texture, const glm::vec4& color)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, 0.0f, texture, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const FizzGen::Ref<FizzGen::Texture2D>& texture, const glm::vec4& color)
	{
		DrawQuad(position, size, 0.0f, texture, color);
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, float rotationInDegrees, const FizzGen::Ref<FizzGen::Texture2D>& texture, const glm::vec4& color)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, rotationInDegrees, texture, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, float rotationInDegrees, const FizzGen::Ref<FizzGen::Texture2D>& texture, const glm::vec4& color)
	{
		//s_Data->ColorTextureShader->Bind();

		//reset color to white, so that the texture is not tinted
		s_Data->ColorTextureShader->SetFloat4("u_FragColor", color);
		texture->Bind();

		//position,rotation,scale
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) *
			glm::rotate(glm::mat4(1.0f), glm::radians(rotationInDegrees), { 0.0f, 0.0f, 1.0f }) *
			glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		s_Data->ColorTextureShader->SetMat4("u_Transform", transform);

		s_Data->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
	}


}
