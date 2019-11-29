#include "aykpch.h"
#include "VertexArray.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace AYK {

	VertexArray* VertexArray::Create() {
		switch (Renderer::GetAPI()) {
			case RendererAPI::API::OpenGL: return(new OpenGlVertexArray());
			default:
			AYK_CORE_ASSERT(false, "RendererAPI is not supported!");
			return nullptr;
		}
	}


}