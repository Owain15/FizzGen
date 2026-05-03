
#include "fgpch.h"
#include "FizzGen/Renderer/Shader/Shader.h"

#include "FizzGen/Renderer/Renderer.h"

#include "FizzGen/Platform/OpenGL/Shader/OpenGLShader.h"

//Shader
namespace FizzGen
{
	FizzGen::Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None: FG_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL: return std::shared_ptr<Shader>(new OpenGLShader(name, vertexSrc, fragmentSrc));
			case RendererAPI::API::ANGLE: return std::shared_ptr<Shader>(new OpenGLShader(name, vertexSrc, fragmentSrc));
		}

		FG_CORE_ASSERT(false, "Unknown RendererAPI!");
	
		return nullptr;
	}

	FizzGen::Ref<Shader> Shader::Create(const std::string& filepath)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None: FG_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL: return std::shared_ptr<Shader>(new OpenGLShader(filepath));
			case RendererAPI::API::ANGLE: return std::shared_ptr<Shader>(new OpenGLShader(filepath));
		}

		FG_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}



}

//ShaderLibrary
namespace FizzGen
{
	
	void ShaderLibrary::Add(const FizzGen::Ref<Shader>& shader)
	{
		auto& name = shader->GetName();
		FG_CORE_ASSERT(!Exists(name), "Shader name, '{0}', already exists!", name);
		m_Shaders[name] = shader;
	}
	
	void ShaderLibrary::Add(const std::string& name, const FizzGen::Ref<Shader>& shader)
	{
		FG_CORE_ASSERT(!Exists(name), "Shader name, '{0}', already exists!", name);
		m_Shaders[name] = shader;
	}
	
	FizzGen::Ref<Shader> ShaderLibrary::Load(const std::string& filepath)
	{
		auto shader = FizzGen::Ref<Shader>(Shader::Create(filepath));
		Add(shader);
		return shader;
	}
	
	FizzGen::Ref<Shader> ShaderLibrary::Load(const std::string& name, const std::string& filepath)
	{
		auto shader = FizzGen::Ref<Shader>(Shader::Create(filepath));
		Add(name, shader);
		return shader;
	}
	
	FizzGen::Ref<Shader> ShaderLibrary::Get(const std::string& name)
	{
		FG_CORE_ASSERT(Exists(name), "Shader, '{0}', could not be found!", name);
		return m_Shaders[name];
	}

	bool ShaderLibrary::Exists(const std::string& name) const
	{
		return m_Shaders.find(name) != m_Shaders.end();
	}

}

