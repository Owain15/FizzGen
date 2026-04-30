#pragma once

#include <glm/glm.hpp>
#include "FizzGen/Renderer/VertexArray/VertexArray.h"

namespace FizzGen
{
	class RendererAPI
	{

		public:

			enum class API
			{
				None = 0,
				OpenGL = 1,
				ANGLE = 2

			};

		public:



			virtual void SetClearColor(const glm::vec4& color) = 0;
			virtual void Clear() = 0;

			virtual void DrawIndexed(const FizzGen::Ref<VertexArray>& vertexArray) = 0;

			inline static API GetAPI() { return s_API; }

		private:

			static API s_API;

	};

}

