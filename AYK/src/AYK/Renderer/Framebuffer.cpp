#include "aykpch.h"
#include "Framebuffer.h"

#include "AYK/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLFramebuffer.h"

namespace AYK {




	Ref<Framebuffer> Framebuffer::Create(const FramebufferSpecification Spec){
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::OpenGL: return(CreateRef<OpenGLFramebuffer>(Spec));
		default:
			AYK_CORE_ASSERT(false, "RendererAPI is not supported!");
			return nullptr;
		}
	}

}