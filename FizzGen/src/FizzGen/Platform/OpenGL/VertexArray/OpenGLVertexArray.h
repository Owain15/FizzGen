#pragma once

#include "FizzGen/Renderer/VertexArray/VertexArray.h"

namespace FizzGen
{
	class OpenGLVertexArray : public VertexArray
	{
	
		public:
	
			OpenGLVertexArray();
			virtual ~OpenGLVertexArray();
	
			virtual void Bind() const override;
			virtual void Unbind() const override;
		
			virtual void AddVertexBuffer(const FizzGen::Ref<VertexBuffer>& vertexBuffer) override;
			virtual void SetIndexBuffer(const FizzGen::Ref<IndexBuffer>& indexBuffer) override;
		
			inline const std::vector<FizzGen::Ref<VertexBuffer>>& GetVertexBuffers() const { return m_VertexBuffers; }
			inline const FizzGen::Ref<IndexBuffer>& GetIndexBuffer() const { return m_IndexBuffer; }
	
		private:
		
			uint32_t m_RendererID;
			uint32_t m_VertexBufferIndex = 0;
		
			std::vector<FizzGen::Ref<VertexBuffer>> m_VertexBuffers;
			FizzGen::Ref<IndexBuffer> m_IndexBuffer;
	
	};
}
