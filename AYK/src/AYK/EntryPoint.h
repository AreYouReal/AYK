#pragma once

#ifdef AYK_PLATFORM_WINDOWS
extern AYK::Application* CreateApplication();

int main(int argc, char** argv) {

	AYK::Log::Init();
	AYK_CORE_WARN("Initiliazed Log!");
	int a = 1023;
	AYK_INFO("Hello VAr={0}", a);


	auto App = CreateApplication();
	App->Run();
	delete App;
}
#endif