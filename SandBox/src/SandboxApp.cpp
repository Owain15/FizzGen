
#include "FizzGen.h"

class ExampleLayer : public FizzGen::Layer
{
	public:
	
		ExampleLayer() : Layer("Example") {}
	
		void OnUpdate() override
		{
			FG_INFO("ExampleLayer::Update");
		}
	
		void OnEvent(FizzGen::Event& event) override
		{
				FG_INFO("{0}", event);	
		}
};

class Sandbox : public FizzGen::Application
{
	public:
	
		Sandbox()
		{
			//PushLayer(new ExampleLayer());
			//PushOverlay(new FizzGen::ImGuiLayer());
		}
	
		~Sandbox()
		{
		
		}
	
};

FizzGen::Application* FizzGen::CreateApplication()
{
	return new Sandbox();
}
