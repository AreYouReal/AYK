#include "aykpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace AYK {

	OpenGLContext::OpenGLContext(GLFWwindow* WindowHandleToSet) : WindowHandle(WindowHandleToSet) {
		AYK_CORE_ASSERT(WindowHandle, "WindowHandle is null!");
	}

	void OpenGLContext::Init() {
		AYK_PROFILE_FUNCTION();

		glfwMakeContextCurrent(WindowHandle);
		int Status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		AYK_CORE_ASSERT(Status, "Failed to initialize Glad!");

		AYK_CORE_INFO("OpenGL Info:");
		AYK_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		AYK_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		AYK_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers() {
		AYK_PROFILE_FUNCTION();

		glfwSwapBuffers(WindowHandle);
	}

}