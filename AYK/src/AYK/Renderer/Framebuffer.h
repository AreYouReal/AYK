#pragma once

#include "AYK/Core/Core.h"

namespace AYK {

	struct FramebufferSpecification {
		uint32_t Width, Height;
		//FramebufferFormat Format
		uint32_t Samples = 1;

		bool bSwapChainTarget = false;
 	};

	class Framebuffer {

	public:

		virtual const FramebufferSpecification& GetSpecification() const = 0;

		static Ref<Framebuffer> Create(const FramebufferSpecification Spec);
	};

}