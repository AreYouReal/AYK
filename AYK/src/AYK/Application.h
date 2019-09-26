#pragma once

#include "Core.h"
#include "Window.h"
#include "AYK/LayerStack.h"
#include "AYK/Events/Event.h"
#include "AYK/Events/ApplicationEvent.h"

namespace AYK {
	class AYK_API Application {
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& E);

		void PushLayer(Layer* LayerToPush);
		void PushOverlay(Layer* OverlayToPush);

	private:
		//bool OnWindowClose(WindowCloseEvent& E);


		std::unique_ptr<Window> WindowPtr;
		bool bRunning = true;
		LayerStack LStack;
	};

}



