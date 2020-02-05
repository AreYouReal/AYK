#include "aykpch.h"
#include "Sandbox2D.h"

#include "imgui/imgui.h"


#include <glm/gtc/type_ptr.hpp>

template<typename Fn>
class Timer {
public:

	Timer(const char* NameToSet, Fn&& FuncToSet) :Name(NameToSet), Func(FuncToSet), bStoped(false){
		StartTimepoint = std::chrono::high_resolution_clock::now();
	}

	~Timer() {
		if (!bStoped) {
			Stop();
		}
	}
	
	void Stop() {
		auto EndTimepoint = std::chrono::high_resolution_clock::now();
		long long Start = std::chrono::time_point_cast<std::chrono::microseconds>(StartTimepoint).time_since_epoch().count();
		long long End = std::chrono::time_point_cast<std::chrono::microseconds>(EndTimepoint).time_since_epoch().count();

		bStoped = true;

		float Duration = (End - Start) * 0.001f;
		Func({ Name, Duration });

		//std::cout << Name << ": " << Duration  << "ms" << std::endl;
	}

private:
	const char* Name;
	std::chrono::time_point<std::chrono::steady_clock> StartTimepoint;
	bool bStoped;
	Fn Func;
};

#define PROFILE_SCOPE(Name) Timer T##__LINE__(Name, [&](ProfileResult PResult){ProfileResults.push_back(PResult);})


Sandbox2D::Sandbox2D() : Layer("Sandbox2D"), CameraController(1280.0f / 720.0f){ }

void Sandbox2D::OnAttach() {
	CheckerboardTexture = AYK::Texture2D::Create("assets/textures/checkerboard.png");
}

void Sandbox2D::OnDetach() { }

void Sandbox2D::OnUpdate(AYK::Timestep Timestep) {

	PROFILE_SCOPE("Sandbox2D::OnUpdate");

	{
		PROFILE_SCOPE("CameraController::OnUpdate");
		CameraController.OnUpdate(Timestep);
	}

	{
		PROFILE_SCOPE("Render Prep");
		AYK::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		AYK::RenderCommand::Clear();
	}

	{
		PROFILE_SCOPE("Render Draw");
		AYK::Renderer2D::BeginScene(CameraController.GetCamera());

		AYK::Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 1.0f, 1.0f }, { 0.8f, 0.2f, 0.3f, 1.0f });

		AYK::Renderer2D::DrawQuad({ 1.0f, 0.5f }, { .2f, .2f }, { 0.3f, 0.2f, 0.8f, 1.0f });

		AYK::Renderer2D::DrawQuad({ .0f, .0f, -0.1f }, { 5.5f, 5.5f }, CheckerboardTexture);

		AYK::Renderer2D::EndScene();
	}

}

void Sandbox2D::OnImGuiRender() {
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(SquareColor));


	for (auto& Result : ProfileResults) {
		char Label[50];
		strcpy(Label, "  %.3fms");
		strcat(Label, Result.Name);
		ImGui::Text(Label, Result.Time);
	}
	ProfileResults.clear();

	ImGui::End();
}

void Sandbox2D::OnEvent(AYK::Event& E) {
	CameraController.OnEvent(E);
}

