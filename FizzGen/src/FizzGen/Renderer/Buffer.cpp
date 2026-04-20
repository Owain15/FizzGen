
#include "fgpch.h"

#include "Buffer.h"

#include "Renderer.h"
#include "FizzGen/Platform/OpenGL/OpenGLBuffer.h"

//ifdef ARM?
#include "FizzGen/Platform/ANGLE/ANGLEBuffer.h"



//VertexBuffer
namespace FizzGen
{

	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::None: FG_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::OpenGL: return new OpenGLVertexBuffer(vertices, size);
			case RendererAPI::ANGLE: return new AngleVertexBuffer(vertices, size);
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
			case RendererAPI::None: FG_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::OpenGL: return new OpenGLIndexBuffer(indices, size);
			case RendererAPI::ANGLE: return new AngleIndexBuffer(indices, size);
		}

		
		FG_ASSERT(false, "Unknown RendererAPI!");
		
		return nullptr;
	}
}