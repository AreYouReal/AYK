#include "aykpch.h"
#include "Application.h"

#include "AYK/Events/ApplicationEvent.h"
#include "AYK/Log.h"

#include <GLFW/glfw3.h>

namespace AYK {

	Application::Application(){
		WindowPtr = std::unique_ptr<Window>( Window::Create() );
	}
	
	Application::~Application(){
	}
	
	void Application::Run() {

		while (bRunning) {
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			WindowPtr->OnUpdate();
		}
	}

}