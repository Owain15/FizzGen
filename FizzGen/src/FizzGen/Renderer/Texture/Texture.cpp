
#include "fgpch.h"

#include "FizzGen/Renderer/Texture/Texture.h"

#include "FizzGen/Renderer/Renderer.h"
#include "FizzGen/Platform/OpenGL/Texture/OpenGLTexture.h"
#include "FizzGen/Platform/ANGLE/Texture/ANGLETexture.h"


namespace FizzGen
{
	FizzGen::Ref<FizzGen::Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (RendererAPI::GetAPI())
		{
			case RendererAPI::API::None: FG_CORE_ASSERT(false, "RendererAPI::None is not supported!");
			
			case RendererAPI::API::OpenGL: return std::make_shared<OpenGLTexture2D>(path);
			case RendererAPI::API::ANGLE: return  std::make_shared<ANGLETexture2D>(path);
		}
		return nullptr;
	}
}