#pragma once

#include "AYK/Renderer/OrthographicCamera.h"
#include "AYK/Core/Timestep.h"


#include "AYK/Events/ApplicationEvent.h"
#include "AYK/Events/MouseEvent.h"

namespace AYK {

	struct OrthographicCameraBounds {
		float Left, Right;
		float Bottom, Top;

		float GetWight() { return(Right - Left); }
		float GetHeight() { return(Top - Bottom); }
	};

	class OrthographicCameraController {
	public:
		OrthographicCameraController(float AspectRationToSet, bool Rotation = false);

		void OnUpdate(Timestep TS);
		void OnEvent(Event& E);

		OrthographicCamera& GetCamera() { return(Cam); }
		const OrthographicCamera& GetCamera() const { return(Cam); }

		float GetZoomLevel() const { return(ZoomLevel); }
		void SetZoomLevel(float Level) { ZoomLevel = Level; }

		const OrthographicCameraBounds& GetBounds() const { return(CamBounds); }

	private:
		bool OnMouseScrolledEvent(MouseScrolledEvent& E);
		bool OnWindowResized(WindowResizeEvent& E);

	private:

		float AspectRatio;
		float ZoomLevel = 1.0f;

		OrthographicCameraBounds CamBounds;
		OrthographicCamera Cam;


		bool bRotation;

		glm::vec3 CameraPosition = {0.0f, 0.0f, 0.0f};
		float CameraRotation = 0.0f;

		float CameraTranslationSpeed = 5.0f;
		float CameraRotationSpeed = 180.0f;

	};

}