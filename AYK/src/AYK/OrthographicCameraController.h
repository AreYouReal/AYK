#pragma once

#include "AYK/Renderer/OrthographicCamera.h"
#include "AYK/Core/Timestep.h"


#include "AYK/Events/ApplicationEvent.h"
#include "AYK/Events/MouseEvent.h"

namespace AYK {

	class OrthographicCameraController {
	public:
		OrthographicCameraController(float AspectRationToSet, bool Rotation = false);


		void OnUpdate(Timestep TS);
		void OnEvent(Event& E);

		OrthographicCamera& GetCamera() { return(Cam); }
		const OrthographicCamera& GetCamera() const { return(Cam); }

	private:
		bool OnMouseScrolledEvent(MouseScrolledEvent& E);
		bool OnWindowResized(WindowResizeEvent& E);

	private:

		float AspectRation;
		float ZoomLevel = 1.0f;

		OrthographicCamera Cam;

		bool bRotation;

		glm::vec3 CameraPosition = {0.0f, 0.0f, 0.0f};
		float CameraRotation = 0.0f;

		float CameraTranslationSpeed = 5.0f;
		float CameraRotationSpeed = 180.0f;

	};

}