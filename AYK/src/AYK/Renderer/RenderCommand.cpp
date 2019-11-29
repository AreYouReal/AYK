#include "aykpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace AYK {

	RendererAPI* RenderCommand::CurrentRendererAPI = new OpenGLRendererAPI();
													   
}