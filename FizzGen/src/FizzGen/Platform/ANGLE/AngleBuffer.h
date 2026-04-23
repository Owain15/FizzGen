
#pragma once

#include <cstdint>
#include "FizzGen/Renderer/Buffer.h"

namespace FizzGen
{

	class ANGLEVertexBuffer : public VertexBuffer
	{
		public:

			ANGLEVertexBuffer(float* vertices, uint32_t size);

			virtual ~ANGLEVertexBuffer();

			virtual void Bind() const override;
			virtual void Unbind() const override;

			virtual const BufferLayout& GetLayout() const override { return m_Layout; }
			virtual void SetLayout(const BufferLayout& layout) override { m_Layout = layout; }

		private:

			uint32_t m_RendererID;
			BufferLayout m_Layout;
	};

	class ANGLEIndexBuffer : public IndexBuffer
	{

		public:

			ANGLEIndexBuffer(uint32_t* indices, uint32_t count);

			virtual ~ANGLEIndexBuffer();

			virtual void Bind() const override;
			virtual void Unbind() const override;

			virtual uint32_t GetCount() const override { return m_Count; };

		private:

			uint32_t m_RendererID;
			uint32_t m_Count;

	};

}