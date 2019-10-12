#include "AYK.h"

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale


glm::mat4 camera(float Translate, glm::vec2 const& Rotate)
{
	glm::mat4 Projection = glm::perspective(glm::pi<float>() * 0.25f, 4.0f / 3.0f, 0.1f, 100.f);
	glm::mat4 View = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -Translate));
	View = glm::rotate(View, Rotate.y, glm::vec3(-1.0f, 0.0f, 0.0f));
	View = glm::rotate(View, Rotate.x, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 Model = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));
	return Projection * View * Model;
}

class ExampleLayer : public AYK::Layer {

public:
	ExampleLayer() : Layer("Example") {
		auto ReturnValue  = camera(10, {0.5f, 0.5f});
	
	}

	void OnUpdate() override{
		//AYK_INFO("ExampleLayer::OnUpdate");

		if (AYK::Input::ISkeyPressed(AYK_KEY_TAB)) {
			AYK_TRACE("TAB KEY IS PRESSED! (poll)");
		}

	}

	void OnEvent(AYK::Event& E) override {
		if (E.GetEventType() == AYK::EventType::KeyPressed) {
			AYK::KeyPressedEvent& KPE = (AYK::KeyPressedEvent&) E;

			if (KPE.GetKeyCode() == AYK_KEY_TAB) {
				AYK_TRACE("TAB KEY IS PRESSED! (event)");
			}

			AYK_TRACE("{0}", (char)KPE.GetKeyCode());
		}
	}

};

class Sandbox : public AYK::Application {

public:

	Sandbox() {
		PushLayer(new ExampleLayer());
		PushOverlay(new AYK::ImGuiLayer());
	}

	~Sandbox() {
	
	}


};

AYK::Application* CreateApplication() {
	return(new Sandbox());
}