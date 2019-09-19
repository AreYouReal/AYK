#include "aykpch.h"
#include "Application.h"

#include "AYK/Events/ApplicationEvent.h"
#include "AYK/Log.h"

namespace AYK {

	Application::Application(){
	}
	
	Application::~Application(){
	}
	
	void Application::Run() {
		 
		WindowResizeEvent ResizeEvent(1280, 720);
		if (ResizeEvent.IsInCategory(EventCategoryApplication)) {
			AYK_TRACE(ResizeEvent);
		}

		if (ResizeEvent.IsInCategory(EventCategoryInput)) {
			AYK_TRACE(ResizeEvent);
		}

		while (true);
	}

}