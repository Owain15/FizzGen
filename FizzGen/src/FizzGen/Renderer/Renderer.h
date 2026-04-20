#pragma once

namespace FizzGen
{

	enum class RendererAPI
	{
		None = 0, 
		OpenGL = 1,
		ANGLE = 2

	};

	class Renderer
	{
		public:

			inline static RendererAPI GetAPI() { return s_RendererAPI; }
			
			//set?
		
		private:

			static RendererAPI s_RendererAPI;

	};

}


