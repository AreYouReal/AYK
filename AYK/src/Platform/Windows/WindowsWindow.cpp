#include "aykpch.h"
#include "WindowsWindow.h"

#include <AYK\Events\ApplicationEvent.h>
#include <AYK\Events\MouseEvent.h>
#include <AYK\Events\KeyEvent.h>

#include <glad/glad.h>

namespace AYK {

	static bool bGLFWInitialized = false;

	static void GLFWErrorCallback(int Error, const char* Description) {
		AYK_CORE_ERROR("GLFW Error ({0}): {1}", Error, Description);
	}

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
			glfwSetErrorCallback(GLFWErrorCallback);
			bGLFWInitialized = true;
		}

		WindowHandle = glfwCreateWindow((int)WData.Widht, (int)WData.Height, WData.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(WindowHandle);
		int Status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		AYK_CORE_ASSERT(Status, "Failed to initialize Glad!");
		glfwSetWindowUserPointer(WindowHandle, &WData);
		SetVSync(true);


		// Set GLFW Callbacks
		glfwSetWindowSizeCallback(WindowHandle, [](GLFWwindow* Wnd, int Width, int Height) {
			WindowData& Data = *(WindowData*)glfwGetWindowUserPointer(Wnd);
			WindowResizeEvent Event(Width, Height);
			Data.Widht = Width;
			Data.Height = Height;
			Data.EventCallback(Event);
		});

		glfwSetWindowCloseCallback(WindowHandle, [](GLFWwindow* Wnd) {
			WindowData& Data = *(WindowData*)glfwGetWindowUserPointer(Wnd);
			WindowCloseEvent Event;
			Data.EventCallback(Event);
			});

		glfwSetKeyCallback(WindowHandle, [](GLFWwindow* Wnd, int Key, int ScanCode, int Action, int Mods) {
			WindowData& Data = *(WindowData*)glfwGetWindowUserPointer(Wnd);
			switch (Action) {
				case GLFW_PRESS: {
					KeyPressedEvent Event(Key, 0);
					Data.EventCallback(Event);
				} break;
				case GLFW_RELEASE: {
					KeyReleaseEvent Event(Key);
					Data.EventCallback(Event);
				} break;
				case GLFW_REPEAT: {
					KeyPressedEvent Event(Key, 1);
					Data.EventCallback(Event);
				} break;
			};
			});

			glfwSetMouseButtonCallback(WindowHandle, [](GLFWwindow* Wnd, int Button, int Action, int Mods) {
				WindowData& Data = *(WindowData*)glfwGetWindowUserPointer(Wnd);

				switch (Action){
					case GLFW_PRESS: {
						MouseButtonPressedEvent Event(Button);
						Data.EventCallback(Event);
					} break;
					case GLFW_RELEASE: {
						MouseButtonReleasedEvent Event(Button);
						Data.EventCallback(Event);
					} break;
				}
			});

			glfwSetScrollCallback(WindowHandle, [](GLFWwindow* Wnd, double XOffset, double YOffset) {
				WindowData& Data = *(WindowData*)glfwGetWindowUserPointer(Wnd);
				MouseScrolledEvent Event((float)XOffset, (float)YOffset);
				Data.EventCallback(Event);
			});

			glfwSetCursorPosCallback(WindowHandle, [](GLFWwindow* Wnd, double X, double Y) {
				WindowData& Data = *(WindowData*)glfwGetWindowUserPointer(Wnd);
				MouseMovedEvent Event((float)X, (float)Y);
				Data.EventCallback(Event);
			});

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
