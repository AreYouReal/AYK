#include "aykpch.h"
#include "Texture.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLTexture.h"

namespace AYK {
	


	AYK::Ref<AYK::Texture2D> Texture2D::Create(const std::string& Path) {
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::OpenGL: return( std::make_shared<OpenGLTexture2D>(Path) );
		default:
			AYK_CORE_ASSERT(false, "RendererAPI is not supported!");
			return nullptr;
		}
	}

}