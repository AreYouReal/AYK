#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Window.h"

namespace AYK {
	class AYK_API Application {
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& E);

	private:
		//bool OnWindowClose(WindowCloseEvent& E);


		std::unique_ptr<Window> WindowPtr;
		bool bRunning = true;
	};

}



