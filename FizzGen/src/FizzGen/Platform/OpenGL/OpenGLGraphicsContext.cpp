
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

			FG_CORE_INFO("OpenGL Info:");
			FG_CORE_INFO("  Vendor: {0}", (const char*)glGetString(GL_VENDOR));
			FG_CORE_INFO("  Renderer: {0}", (const char*)glGetString(GL_RENDERER));
			FG_CORE_INFO("  Version: {0}", (const char*)glGetString(GL_VERSION));

	}

	void OpenGLGraphicsContext::SwapBuffers()
	{
		glfwSwapBuffers(m_windowHandle);
	}
}