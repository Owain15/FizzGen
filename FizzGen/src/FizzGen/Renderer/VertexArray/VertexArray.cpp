
#include "fgpch.h"

#include "VertexArray.h"

#include "FizzGen/Renderer/Renderer.h"

#ifdef FG_USE_ANGLE
#include "FizzGen/Platform/ANGLE/VertexArray/ANGLEVertexArray.h"
#else
#include "FizzGen/Platform/OpenGL/VertexArray/OpenGLVertexArray.h"
#endif

namespace FizzGen
{
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None: FG_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
#ifdef FG_USE_ANGLE
			case RendererAPI::API::ANGLE: return new ANGLEVertexArray();
#else
			case RendererAPI::API::OpenGL: return new OpenGLVertexArray();
#endif
		}

		FG_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}