#pragma once

#include "Core.h"
#include "Events/Event.h"

namespace FizzGen
{
	class FIZZGEN_API Application
	{
		public:
		
			Application();
			virtual ~Application();
		
			void run();
	
	};

	// To be defined in client
	Application* CreateApplication();
}

