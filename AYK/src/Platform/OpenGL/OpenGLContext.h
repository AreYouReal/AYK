#pragma once

#include "AYK/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace AYK {

	class OpenGLContext : public GraphicsContext {

	public:

		OpenGLContext(GLFWwindow* WindowHandleToSet);

		virtual void Init() override;
		virtual void SwapBuffers() override;

	private:

		GLFWwindow* WindowHandle;
	};


}


