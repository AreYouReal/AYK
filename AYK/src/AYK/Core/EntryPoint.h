#pragma once

#ifdef AYK_PLATFORM_WINDOWS
extern AYK::Application* CreateApplication();

int main(int argc, char** argv) {

	AYK::Log::Init();

	AYK_PROFILE_BEGIN_SESSION("Startup", "AYKProfile-Startup.json");
	auto App = CreateApplication();
	AYK_PROFILE_END_SESSION();
	AYK_PROFILE_BEGIN_SESSION("Runtime", "AYKProfile-Runtime.json");
	App->Run();
	AYK_PROFILE_END_SESSION();
	AYK_PROFILE_BEGIN_SESSION("Shutdown", "AYKProfile-Shutdown.json");
	delete App;
	AYK_PROFILE_END_SESSION();
}
#endif