#include "aykpch.h"
#include "OrthographicCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace AYK {

	OrthographicCamera::OrthographicCamera(float Left, float Right, float Bottom, float Top) : ProjectionMatrix(glm::ortho(Left, Right, Bottom, Top, -1.0f, 1.0f)), ViewMatrix(1.0f){
		ViewProjectionMatrix = ProjectionMatrix * ViewMatrix;
	}

	void OrthographicCamera::RecalculateViewMatrix(){
		glm::mat4 Transform = glm::translate(glm::mat4(1.0f), Position) * glm::rotate(glm::mat4(1.0f), glm::radians(Rotation), glm::vec3(0, 0, 1));

		ViewMatrix = glm::inverse(Transform);
		ViewProjectionMatrix = ProjectionMatrix * ViewMatrix;
	}

}



