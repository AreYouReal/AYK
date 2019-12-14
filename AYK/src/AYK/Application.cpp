#include "aykpch.h"
#include "Application.h"

#include "AYK/Log.h"

#include "Events/ApplicationEvent.h"

#include "AYK/Renderer/Renderer.h"

#include "Input.h"


namespace AYK {

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

	Application* Application::Instance = nullptr;

	Application::Application(){
		AYK_CORE_ASSERT(!Instance, "Application already exists!");
		Instance = this;

		WindowPtr = std::unique_ptr<Window>( Window::Create() );
		WindowPtr->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

		ImGuiLayerPtr = new ImGuiLayer();
		PushOverlay(ImGuiLayerPtr);


		

	}
	
	Application::~Application(){
	}
	
	void Application::Run() {

		while (bRunning) {



			for (Layer* L : LStack) {
				L->OnUpdate();
			}

			ImGuiLayerPtr->Begin();
			for (Layer* L : LStack) { L->OnImGuiRender(); }
			ImGuiLayerPtr->End();

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