
#include "fgpch.h"

#include "AngleBuffer.h"

#include <GLES3/gl3.h>


// VertexBuffer
namespace FizzGen
{
	AngleVertexBuffer::AngleVertexBuffer(float* vertices, uint32_t size)
	{
		glGenBuffers(1, &m_RendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}

	AngleVertexBuffer::~AngleVertexBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
	}

	void AngleVertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	}

	void AngleVertexBuffer::Unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

}

// IndexBuffer
namespace FizzGen
{

	AngleIndexBuffer::AngleIndexBuffer(uint32_t* indices, uint32_t count)
		: m_Count(count)
	{
		glGenBuffers(1, &m_RendererID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
	}

	AngleIndexBuffer::~AngleIndexBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
	}

	void AngleIndexBuffer::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	}

	void AngleIndexBuffer::Unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

}

