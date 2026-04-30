#pragma once

#include <memory>
#include "FizzGen/Renderer/Buffer/Buffer.h"

namespace FizzGen
{
	class VertexArray
	{
		public:

			virtual ~VertexArray() {};
			
			virtual void Bind() const = 0;
			virtual void Unbind() const = 0;
			
			virtual void AddVertexBuffer(const FizzGen::Ref<VertexBuffer>& vertexBuffer) = 0;
			virtual void SetIndexBuffer(const FizzGen::Ref<IndexBuffer>& indexBuffer) = 0;

			virtual const std::vector<FizzGen::Ref<VertexBuffer>>& GetVertexBuffers() const = 0;
			virtual const FizzGen::Ref<IndexBuffer>& GetIndexBuffer() const = 0;

			static VertexArray* Create();

	};
}
