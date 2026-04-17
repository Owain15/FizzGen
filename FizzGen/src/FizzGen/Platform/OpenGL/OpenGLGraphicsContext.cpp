
#include "fgpch.h"

#include "OpenGLGraphicsContext.h"

#include <GLFW/glfw3.h>
#include "OpenGLBuild.h"

namespace FizzGen
{
	OpenGLGraphicsContext::OpenGLGraphicsContext(GLFWwindow* windowHandle)
		: m_windowHandle(windowHandle)
	{
		FG_CORE_ASSERT(windowHandle, "Window handle is null!");
	}

	void OpenGLGraphicsContext::Init()
	{
		FG_CORE_INFO("Creating OpenGL graphics context");
		glfwMakeContextCurrent(m_windowHandle);

		#ifndef FG_USE_ANGLE
			int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
			FG_CORE_ASSERT(status, "Failed to initialize Glad!");
		#endif

	}

	void OpenGLGraphicsContext::SwapBuffers()
	{
		glfwSwapBuffers(m_windowHandle);
	}
}