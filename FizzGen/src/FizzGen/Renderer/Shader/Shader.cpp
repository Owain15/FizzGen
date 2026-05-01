
#include "fgpch.h"
#include "FizzGen/Renderer/Shader/Shader.h"

#include "FizzGen/Renderer/Renderer.h"

#include "FizzGen/Platform/OpenGL/Shader/OpenGLShader.h"

namespace FizzGen
{
	Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None: FG_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:
			case RendererAPI::API::ANGLE: return new OpenGLShader(vertexSrc, fragmentSrc);
		}

		FG_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}