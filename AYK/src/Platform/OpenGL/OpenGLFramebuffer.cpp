#include "aykpch.h"
#include "OpenGLFramebuffer.h"

#include <glad/glad.h>

namespace AYK {

	static const uint32_t sMaxFBSize = 8192;

	OpenGLFramebuffer::OpenGLFramebuffer(const FramebufferSpecification& spec)
		: Spec(spec)
	{
		Invalidate();
	}

	OpenGLFramebuffer::~OpenGLFramebuffer()
	{
		glDeleteFramebuffers(1, &RendererID);
		glDeleteTextures(1, &ColorAttachment);
		glDeleteTextures(1, &DepthAttachment);
	}

	void OpenGLFramebuffer::Invalidate()
	{

		if (RendererID) {
			glDeleteFramebuffers(1, &RendererID);
			glDeleteTextures(1, &ColorAttachment);
			glDeleteTextures(1, &DepthAttachment);
		}

		glCreateFramebuffers(1, &RendererID);
		glBindFramebuffer(GL_FRAMEBUFFER, RendererID);

		glCreateTextures(GL_TEXTURE_2D, 1, &ColorAttachment);
		glBindTexture(GL_TEXTURE_2D, ColorAttachment);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, Spec.Width, Spec.Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, ColorAttachment, 0);

		glCreateTextures(GL_TEXTURE_2D, 1, &DepthAttachment);
		glBindTexture(GL_TEXTURE_2D, DepthAttachment);
		glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, Spec.Width, Spec.Height);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, DepthAttachment, 0);

		AYK_CORE_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer is incomplete!");

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void OpenGLFramebuffer::Bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, RendererID);
		glViewport(0, 0, Spec.Width, Spec.Height);
	}

	void OpenGLFramebuffer::Unbind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void OpenGLFramebuffer::Resize(uint32_t Width, uint32_t Height) {

		if (Width == 0 || Height == 0 || Width > sMaxFBSize || Height > sMaxFBSize) {
			AYK_CORE_WARN("Attempt to resize framebuffer to {0}, {1}", Width, Height);
			return;
		}

		Spec.Width = Width;
		Spec.Height = Height;
		Invalidate();
	}

}