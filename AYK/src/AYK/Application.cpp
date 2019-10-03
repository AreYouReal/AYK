#include "aykpch.h"
#include "Application.h"

#include "AYK/Log.h"

#include "Events/ApplicationEvent.h"

#include <glad/glad.h>

namespace AYK {

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

	Application* Application::Instance = nullptr;

	Application::Application(){
		AYK_CORE_ASSERT(!Instance, "Application already exists!");
		Instance = this;

		WindowPtr = std::unique_ptr<Window>( Window::Create() );
		WindowPtr->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

		unsigned int ID;
		glGenVertexArrays(1, &ID);
	}
	
	Application::~Application(){
	}
	
	void Application::Run() {

		while (bRunning) {
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			for (Layer* L : LStack) {
				L->OnUpdate();
			}


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

		for (auto it = LStack.end(); it != LStack.begin();) {
			(*--it)->OnEvent(E);
			if (E.bHandled) {
				break;
			}
		}

	}

	void Application::PushLayer(Layer* LayerToPush){
		LStack.PushLayer(LayerToPush);
		LayerToPush->OnAttach();
	}

	void Application::PushOverlay(Layer* OverlayToPush){ 
		LStack.PushOverlay(OverlayToPush);
		OverlayToPush->OnAttach();
	}



}