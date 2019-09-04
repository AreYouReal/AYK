#include "AYK.h"

class Sandbox : public AYK::Application {

public:

	Sandbox() {
	
	}

	~Sandbox() {
	
	}


};

AYK::Application* CreateApplication() {
	return(new Sandbox());
}