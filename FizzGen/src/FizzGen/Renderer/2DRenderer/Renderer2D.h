#pragma once

// entirely static class to hold render functionality for 2D rendering

#include "FizzGen/Renderer/Camera/Orthographic/OrthographicCamera.h"

namespace FizzGen
{

	class Renderer2D
	{

		public:

			static void Init();
			static void Shutdown();
			
			static void BeginScene(const FizzGen::OrthographicCamera& camera);
			static void EndScene();

			static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
			static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);

		private:


	};
}
