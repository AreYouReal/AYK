#include "aykpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace AYK {

	OpenGLContext::OpenGLContext(GLFWwindow* WindowHandleToSet) : WindowHandle(WindowHandleToSet) {
		AYK_CORE_ASSERT(WindowHandle, "WindowHandle is null!");
	}

	void OpenGLContext::Init() {
		glfwMakeContextCurrent(WindowHandle);
		int Status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		AYK_CORE_ASSERT(Status, "Failed to initialize Glad!");
	}

	void OpenGLContext::SwapBuffers() {
		glfwSwapBuffers(WindowHandle);
	}

}