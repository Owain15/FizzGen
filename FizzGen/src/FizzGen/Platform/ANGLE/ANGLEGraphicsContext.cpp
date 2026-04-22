
#include "fgpch.h"

#include "ANGLEGraphicsContext.h"

#include <GLFW/glfw3.h>

namespace FizzGen
{
	ANGLEGraphicsContext::ANGLEGraphicsContext(GLFWwindow* windowHandle)
		: m_windowHandle(windowHandle)
	{
		FG_CORE_ASSERT(windowHandle, "Window handle is null!");
	}

	void ANGLEGraphicsContext::Init()
	{
		FG_CORE_INFO("Creating ANGLE OpenGL graphics context");
		glfwMakeContextCurrent(m_windowHandle);

		FG_CORE_ASSERT(eglGetCurrentContext() != EGL_NO_CONTEXT, "Failed to initialize ANGLE context!");

		FG_CORE_INFO("OpenGL Info:");
		FG_CORE_INFO("  Vendor: {0}", (const char*)glGetString(GL_VENDOR));
		FG_CORE_INFO("  Renderer: {0}", (const char*)glGetString(GL_RENDERER));
		FG_CORE_INFO("  Version: {0}", (const char*)glGetString(GL_VERSION));

	}

	void ANGLEGraphicsContext::SwapBuffers()
	{
		glfwSwapBuffers(m_windowHandle);
	}

}