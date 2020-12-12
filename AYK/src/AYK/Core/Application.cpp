#include "aykpch.h"
#include "Application.h"

#include "AYK/Core/Log.h"

#include "AYK/Events/ApplicationEvent.h"

#include "AYK/Renderer/Renderer.h"

#include "Input.h"



#include <GLFW/glfw3.h>


namespace AYK {

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

	Application* Application::Instance = nullptr;

	Application::Application(){

		AYK_PROFILE_FUNCTION();

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
		AYK_PROFILE_FUNCTION();
	}
	
	void Application::Run() {

		AYK_PROFILE_FUNCTION();

		while (bRunning) {
			AYK_PROFILE_SCOPE("RunLoop");

			float Time = (float)glfwGetTime(); // Platform::GetTime
			Timestep T = Time - LastFrameTime;
			LastFrameTime = Time;

			if (!bMinimized) {

				{
					AYK_PROFILE_SCOPE("LayerStack OnUpdate");
					for (Layer* L : LStack) {
						L->OnUpdate(T);
					}

				}

				ImGuiLayerPtr->Begin();
				{
					AYK_PROFILE_SCOPE("LayerStack OnImGuiRenderer");
					for (Layer* L : LStack) { L->OnImGuiRender(); }
				}

				ImGuiLayerPtr->End();
			}



			WindowPtr->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& E) {
		bRunning = false;
		return(false);
	}

	bool Application::OnWindowResize(WindowResizeEvent& E){
		AYK_PROFILE_FUNCTION();

		uint32_t Width = E.GetWidth();
		uint32_t Height = E.GetHeight();
		bMinimized = (Width == 0 || Height == 0);

		Renderer::OnWindowResize(Width, Height);

		return(false);
	}

	void Application::OnEvent(Event& E){
		AYK_PROFILE_FUNCTION();

		EventDispatcher Dispactcher(E);
		//Dispactcher.Dispatch<WindowCloseEvent>([=](WindowCloseEvent& E) -> bool {
		//	bRunning = false;
		//	return(true);
		//});

		Dispactcher.Dispatch<WindowCloseEvent>(AYK_BIND_EVENT_FN(Application::OnWindowClose));
		Dispactcher.Dispatch<WindowResizeEvent>(AYK_BIND_EVENT_FN(Application::OnWindowResize));
	
		//AYK_CORE_TRACE("{0}", E);
		  
		for (auto it = LStack.end(); it != LStack.begin();) {
			(*--it)->OnEvent(E);
			if (E.bHandled) {
				break;
			}
		}

	}

	void Application::PushLayer(Layer* LayerToPush){
		AYK_PROFILE_FUNCTION();

		LStack.PushLayer(LayerToPush);
		LayerToPush->OnAttach();
	}

	void Application::PushOverlay(Layer* OverlayToPush){ 
		AYK_PROFILE_FUNCTION();

		LStack.PushOverlay(OverlayToPush);
		OverlayToPush->OnAttach();
	}

	void Application::Close(){
		bRunning = false;
	}



}