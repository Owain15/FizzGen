#pragma once

#include "FizzGen/Renderer/RendererAPI.h"	

namespace FizzGen
{
	class OpenGLRendererAPI : public RendererAPI
	{
		public:

			virtual void SetClearColor(const glm::vec4& color) override;
			virtual void Clear() override;

			virtual void DrawIndexed(const FizzGen::Ref<VertexArray>& vertexArray) override;

	};
}
