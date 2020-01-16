#include "aykpch.h"
#include "OrthographicCameraController.h"


namespace AYK {



	OrthographicCameraController::OrthographicCameraController(float AspectRationToSet) {

	}

	void OrthographicCameraController::OnUpdate(Timestep TS) {

		float CameraOffset = CameraSpeed * Timestep;

		if (Input::IsKeyPressed(AYK_KEY_LEFT)) {
			CameraPosition.x -= CameraOffset;
		}
		else if (Input::IsKeyPressed(AYK_KEY_RIGHT)) {
			CameraPosition.x += CameraOffset;
		}

		if (Input::IsKeyPressed(AYK_KEY_UP)) {
			CameraPosition.y += CameraOffset;
		}
		else if (Input::IsKeyPressed(AYK_KEY_DOWN)) {
			CameraPosition.y -= CameraOffset;
		}

		if (Input::IsKeyPressed(AYK_KEY_E)) {
			CameraRotation -= CameraOffset * 100;
		}
		else if (Input::IsKeyPressed(AYK_KEY_Q)) {
			CameraRotation += CameraOffset * 100;
		}

	}

	void OrthographicCameraController::OnEvent(Event& E)
	{

	}

	bool OrthographicCameraController::OnMouseScrolledEvent(MouseScrolledEvent& E)
	{

	}

	bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& E)
	{

	}

}