#pragma once

//#include "fgpch.h"

#include <FizzGen.h>

class Sandbox2D : public FizzGen::Layer
{
	public:

		Sandbox2D();
		virtual ~Sandbox2D() = default;

		void OnUpdate(FizzGen::Timestep timestep) override;
		
		void OnEvent(FizzGen::Event& event) override;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		virtual void OnImGuiRender() override;


	private:

		FizzGen::OrthographicCameraControler m_CameraController;

		glm::vec4 m_BackgroundColor = { 0.1f, 0.1f, 0.1f, 1 };
		
		//temp
		FizzGen::Ref<FizzGen::Shader> m_Shader;
		FizzGen::Ref<FizzGen::Texture2D> m_Texture;
		FizzGen::Ref<FizzGen::VertexArray> m_VertexArray;
		glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };

};