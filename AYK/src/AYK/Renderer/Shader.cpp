#include "aykpch.h"
#include "Shader.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace AYK {

	Shader* Shader::Create(const std::string& VertexSource, const std::string& FragmentSource) {
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::OpenGL: return(new OpenGLShader(VertexSource, FragmentSource));
		default:
			AYK_CORE_ASSERT(false, "RendererAPI is not supported!");
			return nullptr;
		}
	}

}

