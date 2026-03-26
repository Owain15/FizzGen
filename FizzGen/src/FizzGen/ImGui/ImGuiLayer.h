#pragma once

#include "FizzGen/Layer.h"

#include "FizzGen/Events/ApplicationEvents.h"
#include "FizzGen/Events/KeyEvent.h"
#include "FizzGen/Events/MouseEvent.h"

namespace FizzGen 
{
	class FIZZGEN_API ImGuiLayer : public Layer
	{
		public:
		
			ImGuiLayer();
			virtual ~ImGuiLayer() = default;
			
			void OnAttach() override;
			void OnDetach() override;
			void OnUpdate() override;
			void OnEvent(Event& event) override;
	

		private:

			bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& event);
			bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& event);
			bool OnMouseMovedEvent(MouseMovedEvent& event);
			bool OnMouseScrolledEvent(MouseScrolledEvent& event);

			bool OnKeyPressedEvent(KeyPressedEvent& event);
			bool OnKeyReleasedEvent(KeyReleasedEvent& event);
			bool OnKeyTypedEvent(KeyTypedEvent& event);

			bool OnWindowResizeEvent(WindowResizeEvent& event);
			


		private:

			float m_Time = 0.0f;
	};
}


