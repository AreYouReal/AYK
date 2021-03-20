#include "aykpch.h"
#include "OpenGLFramebuffer.h"

#include <glad/glad.h>

namespace AYK {

	OpenGLFramebuffer::OpenGLFramebuffer(const FramebufferSpecification& InSpec) : Spec(InSpec) {
		Invalidate();
	}

	OpenGLFramebuffer::~OpenGLFramebuffer() {
		glDeleteFramebuffers(1, &RendererID);
	}



	void OpenGLFramebuffer::Invalidate() {
		glCreateFramebuffers(1, &RendererID);

		glBindFramebuffer(GL_TEXTURE_2D, RendererID);

		glCreateTextures(GL_TEXTURE_2D, 1, &ColorAttachment);
		glBindTexture(GL_TEXTURE_2D, ColorAttachment);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, Spec.Width, Spec.Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr );
		glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, ColorAttachment, 0);

		glCreateTextures(GL_TEXTURE_2D, 1, &DepthAttachment);
		glBindTexture(GL_TEXTURE_2D, DepthAttachment);
		glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, Spec.Width, Spec.Height); 
		//glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, Spec.Width, Spec.Height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, DepthAttachment, 0);

		AYK_CORE_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer is incomplete!");

		glBindFramebuffer(GL_TEXTURE_2D, 0);
	}

	void OpenGLFramebuffer::Bind() {
		glBindFramebuffer(GL_TEXTURE_2D, RendererID);
	}

	void OpenGLFramebuffer::Unbind() {
		glBindFramebuffer(GL_TEXTURE_2D, 0);
	}

}