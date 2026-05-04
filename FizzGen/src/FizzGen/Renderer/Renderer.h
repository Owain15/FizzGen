#pragma once

#include "FizzGen/Renderer/RenderCommand/RenderCommand.h"

#include "FizzGen/Renderer/Camera/Orthographic/OrthographicCamera.h"
#include "FizzGen/Renderer/Shader/Shader.h"

namespace FizzGen
{

	class Renderer
	{
		public:

			static void Init();

			static void BeginScene(const OrthographicCamera& camera);
			static void EndScene();

			static void Submit(const FizzGen::Ref<Shader>& shader, const FizzGen::Ref<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));

			inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

			static void OnWindowResize(uint32_t width, uint32_t height);

		private:

			struct SceneData
			{
				glm::mat4 ViewProjectionMatrix;
			};

			static SceneData* m_SceneData;

	};

}


