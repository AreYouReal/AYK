#include <AYK.h>
#include <AYK/Core/EntryPoint.h>

#include "Platform/OpenGL/OpenGLShader.h" 

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "EditorLayer.h"

namespace AYK {

	class AYKEditor : public Application {

	public:

		AYKEditor() {
			PushLayer(new EditorLayer());
		}

		~AYKEditor() { }

	};



}

AYK::Application* CreateApplication() {
	return(new AYK::AYKEditor());
}