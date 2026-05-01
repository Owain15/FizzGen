
#include "fgpch.h"

#include "FizzGen/Renderer/Texture/Texture.h"

#include "FizzGen/Renderer/Renderer.h"

#ifdef FG_USE_ANGLE
#include "FizzGen/Platform/ANGLE/Texture/ANGLETexture.h"
#else
#include "FizzGen/Platform/OpenGL/Texture/OpenGLTexture.h"
#endif

namespace FizzGen
{
	FizzGen::Ref<FizzGen::Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (RendererAPI::GetAPI())
		{
			case RendererAPI::API::None: FG_CORE_ASSERT(false, "RendererAPI::None is not supported!"); return nullptr;
#ifdef FG_USE_ANGLE
			case RendererAPI::API::ANGLE: return std::make_shared<ANGLETexture2D>(path);
#else
			case RendererAPI::API::OpenGL: return std::make_shared<OpenGLTexture2D>(path);
#endif
		}
		return nullptr;
	}
}