#include "aykpch.h"
#include "Texture.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLTexture.h"

namespace AYK {
	


	Ref<Texture2D> Texture2D::Create(uint32_t Width, uint32_t Height) {
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::OpenGL: return( CreateRef<OpenGLTexture2D>(Width, Height) );
		default:
			AYK_CORE_ASSERT(false, "RendererAPI is not supported!");
			return nullptr;
		}
	}

	AYK::Ref<AYK::Texture2D> Texture2D::Create(const std::string& Path) {
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::OpenGL: return( CreateRef<OpenGLTexture2D>(Path) );
		default:
			AYK_CORE_ASSERT(false, "RendererAPI is not supported!");
			return nullptr;
		}
	}

}