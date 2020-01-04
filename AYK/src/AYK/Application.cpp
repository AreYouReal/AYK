#include "aykpch.h"
#include "Application.h"

#include "AYK/Log.h"

#include "Events/ApplicationEvent.h"

#include "AYK/Renderer/Renderer.h"

#include "Input.h"



#include <GLFW/glfw3.h>


namespace AYK {

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

	Application* Application::Instance = nullptr;

	Application::Application(){
		AYK_CORE_ASSERT(!Instance, "Application already exists!");
		Instance = this;

		WindowPtr = Scope<Window>( Window::Create() );
		WindowPtr->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
		//WindowPtr->SetVSync(false);
		
		Renderer::Init();

		ImGuiLayerPtr = new ImGuiLayer();
		PushOverlay(ImGuiLayerPtr);

	}
	
	Application::~Application(){
	}
	
	void Application::Run() {

		while (bRunning) {
			float Time = (float)glfwGetTime(); // Platform::GetTime
			Timestep T = Time - LastFrameTime;
			LastFrameTime = Time;

			for (Layer* L : LStack) {
				L->OnUpdate(T);
			}

			ImGuiLayerPtr->Begin();
			for (Layer* L : LStack) { L->OnImGuiRender(); }
			ImGuiLayerPtr->End();

			WindowPtr->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& E) {
		bRunning = false;
		return false;
	}

	void Application::OnEvent(Event& E){
		EventDispatcher Dispactcher(E);
		//Dispactcher.Dispatch<WindowCloseEvent>([=](WindowCloseEvent& E) -> bool {
		//	bRunning = false;
		//	return(true);
		//});

		Dispactcher.Dispatch<WindowCloseEvent>(AYK_BIND_EVENT_FN(Application::OnWindowClose));
	
		//AYK_CORE_TRACE("{0}", E);
		  
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