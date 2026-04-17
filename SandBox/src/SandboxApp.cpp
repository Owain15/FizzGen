
#include "FizzGen.h"

#include "imgui/imgui.h"

class ExampleLayer : public FizzGen::Layer
{
	public:
	
		ExampleLayer() : Layer("Example") {}
	
		void OnUpdate() override
		{
			if (FizzGen::Input::IsKeyPressed(FG_KEY_ENTER))
			{
				FG_TRACE("Enter key is pressed!");
			}
		}
	
		virtual void OnImGuiRender() override
		{
			ImGui::Begin("Test");
			ImGui::Text("Hello World!");
			ImGui::End();
		}

		void OnEvent(FizzGen::Event& event) override
		{
				if(event.GetEventType() == FizzGen::EventType::KeyPressed)
				{
					FizzGen::KeyPressedEvent& e = (FizzGen::KeyPressedEvent&)event;

					if (e.GetKeyCode() == FG_KEY_TAB)
					{
						FG_TRACE("Tab key is pressed (event)!", e.GetRepeatCount());
					}

					FG_TRACE("{0}", (char)e.GetKeyCode());
				}
		}
};

class Sandbox : public FizzGen::Application
{
	public:
	
		Sandbox()
		{
			auto testLayer = new ExampleLayer();
			PushOverlay(testLayer);
		}
	
		~Sandbox()
		{
		
		}
	
};

FizzGen::Application* FizzGen::CreateApplication()
{
	return new Sandbox();
}
