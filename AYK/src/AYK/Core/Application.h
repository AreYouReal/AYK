#pragma once

#include "Base.h"
#include "Window.h"
#include "AYK/Core/LayerStack.h"
#include "AYK/Events/Event.h"
#include "AYK/Events/ApplicationEvent.h"

#include "AYK/Core/Timestep.h"

#include "AYK/ImGui/ImGuiLayer.h"

namespace AYK {
	class Application {
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& E);

		void PushLayer(Layer* LayerToPush);
		void PushOverlay(Layer* OverlayToPush);


		void Close();

		inline static Application& Get() { return(*Instance); }

		inline Window& GetWindow() { return(*WindowPtr); }

	private:
		bool OnWindowClose(WindowCloseEvent& E);
		bool OnWindowResize(WindowResizeEvent& E);

		Scope<Window> WindowPtr;
		ImGuiLayer* ImGuiLayerPtr;
		bool bRunning = true;
		bool bMinimized = false;
		LayerStack LStack;
		float LastFrameTime = 0.0f;


		static Application* Instance;
	};

}



