#pragma once

#include "AYK/Renderer/Framebuffer.h"

namespace AYK {

	class OpenGLFramebuffer : public Framebuffer {

	public:
		OpenGLFramebuffer(const FramebufferSpecification& InSpec);
		virtual ~OpenGLFramebuffer();

		void Invalidate();

		virtual void Bind() override;
		virtual void Unbind() override;

		virtual uint32_t GetColorAttachmentRendererID() const override { return(ColorAttachment); };

		virtual const FramebufferSpecification& GetSpecification() const override { return(Spec); };

	private:
		uint32_t RendererID;
		uint32_t ColorAttachment, DepthAttachment;
		FramebufferSpecification Spec;

	};

}