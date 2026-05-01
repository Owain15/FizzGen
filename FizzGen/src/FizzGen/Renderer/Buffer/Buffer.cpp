
#include "fgpch.h"

#include "Buffer.h"

#include "FizzGen/Renderer/Renderer.h"

#ifdef FG_USE_ANGLE
#include "FizzGen/Platform/ANGLE/Buffer/ANGLEBuffer.h"
#else
#include "FizzGen/Platform/OpenGL/Buffer/OpenGLBuffer.h"
#endif

//VertexBuffer
namespace FizzGen
{

	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None: FG_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
#ifdef FG_USE_ANGLE
			case RendererAPI::API::ANGLE: return new ANGLEVertexBuffer(vertices, size);
#else
			case RendererAPI::API::OpenGL: return new OpenGLVertexBuffer(vertices, size);
#endif
		}

		FG_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}

//IndexBuffer
namespace FizzGen
{
	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None: FG_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
#ifdef FG_USE_ANGLE
			case RendererAPI::API::ANGLE: return new ANGLEIndexBuffer(indices, size);
#else
			case RendererAPI::API::OpenGL: return new OpenGLIndexBuffer(indices, size);
#endif
		}

		FG_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}