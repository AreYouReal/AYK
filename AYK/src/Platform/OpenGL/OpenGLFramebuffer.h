#pragma once

#include "AYK/Renderer/Framebuffer.h"

namespace AYK {

	class OpenGLFramebuffer : public Framebuffer
	{
	public:
		OpenGLFramebuffer(const FramebufferSpecification& spec);
		virtual ~OpenGLFramebuffer();

		void Invalidate();

		virtual void Bind() override;
		virtual void Unbind() override;

		virtual void Resize(uint32_t Width, uint32_t Height) override;

		virtual uint32_t GetColorAttachmentRendererID() const override { return ColorAttachment; }

		virtual const FramebufferSpecification& GetSpecification() const override { return Spec; }
	private:
		uint32_t RendererID{0};
		uint32_t ColorAttachment{ 0 }, DepthAttachment{0};
		FramebufferSpecification Spec;
	};

}