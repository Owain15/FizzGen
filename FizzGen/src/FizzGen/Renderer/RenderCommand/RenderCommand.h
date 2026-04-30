#pragma once

#include "FizzGen/Renderer/RendererAPI.h"

namespace FizzGen
{
	class RenderCommand
	{
		public:

			//static void Init();

			inline static void SetClearColor(const glm::vec4& color)
			{	s_RendererAPI->SetClearColor(color); }
			
			inline static void Clear()
			{	s_RendererAPI->Clear(); }

			inline static void DrawIndexed(const FizzGen::Ref<VertexArray>& vertexArray)
			{
				s_RendererAPI->DrawIndexed(vertexArray);
			}

		private:

			static RendererAPI* s_RendererAPI;

	};
}
