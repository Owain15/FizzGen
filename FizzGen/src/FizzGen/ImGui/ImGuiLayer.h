#pragma once

#include "FizzGen/Layer.h"

#include "FizzGen/Events/ApplicationEvent.h"
#include "FizzGen/Events/KeyEvent.h"
#include "FizzGen/Events/MouseEvent.h"

namespace FizzGen 
{
	class FIZZGEN_API ImGuiLayer : public Layer
	{
		public:
		
			ImGuiLayer();
			virtual ~ImGuiLayer() = default;
			
			virtual void OnAttach() override;
			virtual void OnDetach() override;
			virtual void OnImGuiRender() override;

			void Begin();
			void End();

		private:

			float m_Time = 0.0f;
	};
}


