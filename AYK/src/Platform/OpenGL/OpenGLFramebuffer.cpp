#include "aykpch.h"
#include "OpenGLFramebuffer.h"

namespace AYK {

	OpenGLFramebuffer::OpenGLFramebuffer(const FramebufferSpecification& InSpec) : Spec(InSpec) {
		Invalidate();
	}

	void OpenGLFramebuffer::Invalidate() {

	}

}