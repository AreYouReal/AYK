#include "AYK.h"



class ExampleLayer : public AYK::Layer {

public:
	ExampleLayer() : Layer("Example") {}

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