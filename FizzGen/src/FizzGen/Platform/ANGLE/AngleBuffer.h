
#pragma once

#include <cstdint>
#include "FizzGen/Renderer/Buffer.h"

namespace FizzGen
{

	class AngleVertexBuffer : public VertexBuffer
	{
		public:

			AngleVertexBuffer(float* vertices, uint32_t size);

			virtual ~AngleVertexBuffer();

			virtual void Bind() const override;
			virtual void Unbind() const override;

			virtual const BufferLayout& GetLayout() const override { return m_Layout; }
			virtual void SetLayout(const BufferLayout& layout) override { m_Layout = layout; }

		private:

			uint32_t m_RendererID;
			BufferLayout m_Layout;
	};

	class AngleIndexBuffer : public IndexBuffer
	{

		public:

			AngleIndexBuffer(uint32_t* indices, uint32_t count);

			virtual ~AngleIndexBuffer();

			virtual void Bind() const override;
			virtual void Unbind() const override;

			virtual uint32_t GetCount() const override { return m_Count; };

		private:

			uint32_t m_RendererID;
			uint32_t m_Count;

	};

}