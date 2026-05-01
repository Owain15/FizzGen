#pragma once

#include "FizzGen/Renderer/RendererAPI.h"	

namespace FizzGen
{
	class ANGLERendererAPI : public RendererAPI
	{
		public:

			virtual void Init() override;

			virtual void SetClearColor(const glm::vec4& color) override;
			virtual void Clear() override;

			virtual void DrawIndexed(const FizzGen::Ref<VertexArray>& vertexArray) override;

	};
}
