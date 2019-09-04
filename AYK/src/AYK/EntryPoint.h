#pragma once



#ifdef AYK_PLATFORM_WINDOWS
extern AYK::Application* CreateApplication();

int main(int argc, char** argv) {
	auto App = CreateApplication();
	App->Run();
	delete App;
}
#endif