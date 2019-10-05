#include "AYK.h"



class ExampleLayer : public AYK::Layer {

public:
	ExampleLayer() : Layer("Example") {}

	void OnUpdate() override{
		//AYK_INFO("ExampleLayer::OnUpdate");
	}

	void OnEvent(AYK::Event& E) override {
		//AYK_TRACE("{0}, ", E);
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