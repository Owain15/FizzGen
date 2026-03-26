#pragma once

#include "FizzGen/Layer.h"

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

			float m_Time = 0.0f;
	};
}


