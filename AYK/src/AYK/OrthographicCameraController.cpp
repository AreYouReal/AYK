#include "aykpch.h"
#include "OrthographicCameraController.h"

#include "AYK/Input.h"
#include "AYK/KeyCodes.h"

namespace AYK {

	OrthographicCameraController::OrthographicCameraController(float AspectRationToSet, bool Rotation) : AspectRation(AspectRationToSet), Cam(-AspectRation * ZoomLevel, AspectRation * ZoomLevel, -ZoomLevel, ZoomLevel), bRotation(Rotation) {}

	void OrthographicCameraController::OnUpdate(Timestep TS) {

		float CameraOffset = CameraTranslationSpeed * TS;

		if (Input::IsKeyPressed(AYK_KEY_A)) { CameraPosition.x -= CameraOffset;
		} else if (Input::IsKeyPressed(AYK_KEY_D)) { CameraPosition.x += CameraOffset; }

		if (Input::IsKeyPressed(AYK_KEY_W)) { CameraPosition.y += CameraOffset;
		} else if (Input::IsKeyPressed(AYK_KEY_S)) { CameraPosition.y -= CameraOffset; }

		if (bRotation) {
			float CameraRotAngle = CameraRotationSpeed * TS;
			if (Input::IsKeyPressed(AYK_KEY_E)) {		CameraRotation -= CameraOffset;
			}else if (Input::IsKeyPressed(AYK_KEY_Q)) { CameraRotation += CameraOffset; }

			Cam.SetRotation(CameraRotation);
		}

		Cam.SetPosition(CameraPosition);

		CameraTranslationSpeed = ZoomLevel;
	}

	void OrthographicCameraController::OnEvent(Event& E) {
		EventDispatcher D(E);
		D.Dispatch<MouseScrolledEvent>(AYK_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolledEvent));
		D.Dispatch<WindowResizeEvent>(AYK_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
	}

	bool OrthographicCameraController::OnMouseScrolledEvent(MouseScrolledEvent& E) {
		ZoomLevel -= E.GetYOffset() * 0.25f;
		ZoomLevel = std::max(ZoomLevel, 0.25f);
		Cam.SetProjection(-AspectRation * ZoomLevel, AspectRation * ZoomLevel, -ZoomLevel, ZoomLevel);
		return(false);
	}

	bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& E) {
		AspectRation = (float)E.GetWidth() / (float)E.GetHeight();
		Cam.SetProjection(-AspectRation * ZoomLevel, AspectRation * ZoomLevel, -ZoomLevel, ZoomLevel);
		return(false);
	}

}