#pragma once

#include "glm/glm.hpp"

namespace AYK {

	class OrthographicCamera {
	public:
		OrthographicCamera(float Left, float Right, float Bottom, float Top);

		const glm::vec3& GetPosition() const { return(Position); }
		void SetPosition(const glm::vec3& PositionToSet) {
			Position = PositionToSet; RecalculateViewMatrix();
		}

		float GetRotation() const { return(Rotation); }
		void SetRotation(float RotationToSet) {
			Rotation = RotationToSet;  RecalculateViewMatrix();
		}

		void SetProjection(float Left, float Right, float Bottom, float Top);

		const glm::mat4 GetProjectionMatrix() const { return(ProjectionMatrix); }
		const glm::mat4 GetViewMatrix() const { return(ViewMatrix); }
		const glm::mat4 GetViewProjectionMatrix() const { return(ViewProjectionMatrix); }

	private:
		glm::mat4 ProjectionMatrix;
		glm::mat4 ViewMatrix;
		glm::mat4 ViewProjectionMatrix;

		glm::vec3 Position = {0.0f, 0.0f, 0.0f};
		float Rotation = 0.0f;

	private:
		void RecalculateViewMatrix();

	};


}