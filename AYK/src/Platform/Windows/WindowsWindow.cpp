#include "aykpch.h"
#include "WindowsWindow.h"

namespace AYK {

	static bool bGLFWInitialized = false;

	Window* Window::Create(const WindowProps& Props /* = WindowProps() */) {
		return(new WindowsWindow(Props));
	}

	WindowsWindow::WindowsWindow(const WindowProps& Props) {
		Init(Props);
	}

	WindowsWindow::~WindowsWindow() {
		Shutdown();
	}

	void WindowsWindow::Init(const WindowProps& PropsToSet) {
		WData.Title = PropsToSet.Title;
		WData.Widht = PropsToSet.Width;
		WData.Height = PropsToSet.Height;
		
		AYK_CORE_INFO("Creating window {0} ({1} {2})", WData.Title, WData.Widht, WData.Height);

		if (!bGLFWInitialized) {
			int Success = glfwInit();
			AYK_CORE_ASSERT(Success, "Could not initialize GLFW!");
			bGLFWInitialized = true;
		}

		WindowHandle = glfwCreateWindow((int)WData.Widht, (int)WData.Height, WData.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(WindowHandle);
		glfwSetWindowUserPointer(WindowHandle, &WData);
		SetVSync(true);
	}

	void WindowsWindow::Shutdown() {
		glfwDestroyWindow(WindowHandle);
	}

	void WindowsWindow::OnUpdate() {
		glfwPollEvents();
		glfwSwapBuffers(WindowHandle);
	}

	void WindowsWindow::SetVSync(bool Enabled) {
		if (Enabled) {
			glfwSwapInterval(1);
		} else { 	
			glfwSwapInterval(0); 
		}
		WData.bVSync = Enabled;
	}

	bool WindowsWindow::IsVSync() const {
		return(WData.bVSync);
	}

}
