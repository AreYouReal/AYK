#include "aykpch.h"
#include "Application.h"

#include "AYK/Log.h"
#include <GLFW/glfw3.h>

#include "Events/ApplicationEvent.h"



namespace AYK {

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

	Application::Application(){
		WindowPtr = std::unique_ptr<Window>( Window::Create() );
		WindowPtr->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
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

	//bool Application::OnWindowClose(WindowCloseEvent& E) {
	//	bRunning = false;
	//	return false;
	//}

	void Application::OnEvent(Event& E){
		EventDispatcher Dispactcher(E);
		Dispactcher.Dispatch<WindowCloseEvent>([=](WindowCloseEvent& E) -> bool {
			bRunning = false;
			return(true);
		});
	
		AYK_CORE_TRACE("{0}", E);
	}



}