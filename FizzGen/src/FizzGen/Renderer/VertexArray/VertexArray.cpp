
#include "fgpch.h"

#include "VertexArray.h"

#include "FizzGen/Renderer/Renderer.h"
#include "FizzGen/Platform/OpenGL/VertexArray/OpenGLVertexArray.h"
#include "FizzGen/Platform/ANGLE/VertexArray/ANGLEVertexArray.h"

namespace FizzGen
{
	VertexArray* VertexArray::Create()
	{

		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None: FG_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL: return new OpenGLVertexArray();
			case RendererAPI::API::ANGLE: return new ANGLEVertexArray();
		}

		FG_ASSERT(false, "Unknown RendererAPI!");

		return nullptr;
	}
}