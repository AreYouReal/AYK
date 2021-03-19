#pragma once

#include "AYK/Renderer/Framebuffer.h"

namespace AYK {

	class OpenGLFramebuffer : public Framebuffer {

	public:
		OpenGLFramebuffer(const FramebufferSpecification& InSpec);
		virtual ~OpenGLFramebuffer();

		void Invalidate();
	private:
		uint32_t RendererID;
		FramebufferSpecification Spec;

	};

}