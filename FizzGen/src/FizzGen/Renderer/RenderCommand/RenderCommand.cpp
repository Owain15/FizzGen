
#include "fgpch.h"

#include "RenderCommand.h"

#include "FizzGen/Platform/OpenGL/RendererAPI/OpenGLRendererAPI.h"
#include "FizzGen/Platform/ANGLE/RendererAPI/ANGLERendererAPI.h"

namespace FizzGen
{
	//RendererAPI* RenderCommand::s_RendererAPI = RendererAPI::Create();
	
#ifdef FG_USE_ANGLE
	RendererAPI* RenderCommand::s_RendererAPI = new ANGLERendererAPI;
#else
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
#endif


}
