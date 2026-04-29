#pragma once

#include "FizzGen/Renderer/GraphicsContext/GraphicsContext.h"

// place holder, glfw is alrdey included eleswhare
struct GLFWwindow;

namespace FizzGen
{

	class ANGLEGraphicsContext : public GraphicsContext
	{
		public:

			ANGLEGraphicsContext(GLFWwindow* windowHandle);

			virtual void Init() override;
			virtual void SwapBuffers() override;

		private:

			GLFWwindow* m_windowHandle;

	};
}
