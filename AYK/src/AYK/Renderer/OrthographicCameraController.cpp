#include "aykpch.h"
#include "OrthographicCameraController.h"

#include "AYK/Core/Input.h"
#include "AYK/Core/KeyCodes.h"

namespace AYK {

	OrthographicCameraController::OrthographicCameraController(float AspectRationToSet, bool Rotation) : 
		AspectRatio(AspectRationToSet), 
		CamBounds({ -AspectRatio * ZoomLevel, AspectRatio * ZoomLevel, -ZoomLevel, ZoomLevel }),
		Cam(-AspectRatio * ZoomLevel, AspectRatio * ZoomLevel, -ZoomLevel, ZoomLevel), bRotation(Rotation) {}

	void OrthographicCameraController::OnUpdate(Timestep TS) {
		AYK_PROFILE_FUNCTION();

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
		AYK_PROFILE_FUNCTION();

		EventDispatcher D(E);
		D.Dispatch<MouseScrolledEvent>(AYK_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolledEvent));
		D.Dispatch<WindowResizeEvent>(AYK_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
	}

	void OrthographicCameraController::OnResize(float Width, float Height) {
		AspectRatio = Width/Height;
		CalculateView();
	}

	void OrthographicCameraController::CalculateView() {
		CamBounds = { -AspectRatio * ZoomLevel, AspectRatio * ZoomLevel, -ZoomLevel, ZoomLevel };
		Cam.SetProjection(CamBounds.Left, CamBounds.Right, CamBounds.Bottom, CamBounds.Top);
	}

	bool OrthographicCameraController::OnMouseScrolledEvent(MouseScrolledEvent& E) {
		AYK_PROFILE_FUNCTION();
		ZoomLevel -= E.GetYOffset() * 0.25f;
		ZoomLevel = std::max(ZoomLevel, 0.25f);
		CalculateView();
		return(false);
	}

	bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& E) {
		AYK_PROFILE_FUNCTION();
		OnResize(E.GetWidth() , E.GetHeight());
		return(false);
	}

}