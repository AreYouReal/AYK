#pragma once

#include "AYK/Renderer/OrthographicCamera.h"
#include "AYK/Core/Timestep.h"


#include "AYK/Events/ApplicationEvent.h"
#include "AYK/Events/MouseEvent.h"

namespace AYK {

	class OrthographicCameraController {
	public:
		OrthographicCameraController(float AspectRationToSet);


		void OnUpdate(Timestep TS);
		void OnEvent(Event& E);

	private:
		bool OnMouseScrolledEvent(MouseScrolledEvent& E);
		bool OnWindowResized(WindowResizeEvent& E);

	private:

		float AspectRation;
		float ZoomLevel = 1.0f;

		OrthographicCamera Cam;

	};

}