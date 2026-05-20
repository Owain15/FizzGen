
#include "fgpch.h"

#include "ANGLEBuffer.h"

#include <GLES3/gl3.h>


// VertexBuffer
namespace FizzGen
{
	ANGLEVertexBuffer::ANGLEVertexBuffer(float* vertices, uint32_t size)
	{
		FG_PROFILE_FUNCTION();

		glGenBuffers(1, &m_RendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}

	ANGLEVertexBuffer::~ANGLEVertexBuffer()
	{
		FG_PROFILE_FUNCTION();

		glDeleteBuffers(1, &m_RendererID);
	}

	void ANGLEVertexBuffer::Bind() const
	{
		FG_PROFILE_FUNCTION();
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	}

	void ANGLEVertexBuffer::Unbind() const
	{
		FG_PROFILE_FUNCTION();
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

}

// IndexBuffer
namespace FizzGen
{

	ANGLEIndexBuffer::ANGLEIndexBuffer(uint32_t* indices, uint32_t count)
		: m_Count(count)
	{
		FG_PROFILE_FUNCTION();
		glGenBuffers(1, &m_RendererID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
	}

	ANGLEIndexBuffer::~ANGLEIndexBuffer()
	{
		FG_PROFILE_FUNCTION();
		glDeleteBuffers(1, &m_RendererID);
	}

	void ANGLEIndexBuffer::Bind() const
	{
		FG_PROFILE_FUNCTION();
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	}

	void ANGLEIndexBuffer::Unbind() const
	{
		FG_PROFILE_FUNCTION();
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

}

