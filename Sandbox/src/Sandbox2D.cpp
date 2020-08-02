#include "aykpch.h"
#include "Sandbox2D.h"

#include "imgui/imgui.h"

#include <glm/gtc/type_ptr.hpp>

Sandbox2D::Sandbox2D() : Layer("Sandbox2D"), CameraController(1280.0f / 720.0f){ }

void Sandbox2D::OnAttach() {
	AYK_PROFILE_FUNCTION();

	CheckerboardTexture = AYK::Texture2D::Create("assets/textures/checkerboard.png");

	Particle.ColorBegin = { 254/255.0f, 212 / 255.0f, 123 / 255.0f, 1.0f };
	Particle.ColorEnd = { 254 / 255.0f, 109 / 255.0f, 41 / 255.0f, 1.0f };
	Particle.SizeBegin = 0.5f;
	Particle.SizeVariation = 0.3f;
	Particle.SizeEnd = 0.0f;
	Particle.Velocity = { 0.0f, 0.0f };
	Particle.VelocityVariation = { 3.0f, 1.0f };
	Particle.Position = { 0.0f, 0.0f };

}

void Sandbox2D::OnDetach() {
	AYK_PROFILE_FUNCTION();
}

void Sandbox2D::OnUpdate(AYK::Timestep Timestep) {

	AYK_PROFILE_FUNCTION();

	CameraController.OnUpdate(Timestep);

	AYK::Renderer2D::ResetStats();

	{
		AYK_PROFILE_SCOPE("Render Prep");
		AYK::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		AYK::RenderCommand::Clear();
	}

	{

		float static Rotation = 0.0f;
		Rotation += Timestep * 3.0f;

		AYK_PROFILE_SCOPE("Render Draw");
		AYK::Renderer2D::BeginScene(CameraController.GetCamera());

		AYK::Renderer2D::DrawRotatedQuad({ 1.0f, 0.0f }, { 0.8f, 0.8f }, glm::radians(-45.0f), { 0.8f, 0.2f, 0.3f, 1.0f });

		AYK::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { .8f, .8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		AYK::Renderer2D::DrawQuad({ .5f, -0.5f }, { .5f, .75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
		AYK::Renderer2D::DrawRotatedQuad({-2.0f, 0.0f, -0.1f}, {10.0f, 10.0f}, Rotation, CheckerboardTexture, 10.0f);

		AYK::Renderer2D::EndScene();

		AYK::Renderer2D::BeginScene(CameraController.GetCamera());
		for (float y = -5.0f; y < 5.0f; y += 0.5f) {
			for (float x = -5.0f; x < 5.0f; x += 0.5f) {
				glm::vec4 color = { (x + 5.0f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f, .5f};
				AYK::Renderer2D::DrawQuad({ x, y }, { 0.45f, 0.45f }, color);
			}
		}
		AYK::Renderer2D::EndScene();


	}


	if (AYK::Input::IsMouseButtonPressed(AYK_MOUSE_BUTTON_LEFT)) {
		auto [x, y] = AYK::Input::GetMousePosition();
		auto Width = AYK::Application::Get().GetWindow().GetWidth();
		auto Height = AYK::Application::Get().GetWindow().GetHeight();

		auto Bounds = CameraController.GetBounds();
		auto Pos = CameraController.GetCamera().GetPosition();
		x = (x / Width) * Bounds.GetWight() - Bounds.GetWight() * 0.5f;
		y = Bounds.GetHeight() * 0.5f - (y / Height) * Bounds.GetHeight();
		Particle.Position = { x + Pos.x, y + Pos.y };
		for (int i = 0; i < 50; ++i) {
			PSystem.Emit(Particle);
		}

	}

	PSystem.OnUpdate(Timestep);
	PSystem.OnRender(CameraController.GetCamera());
}

void Sandbox2D::OnImGuiRender() {
	ImGui::Begin("Settings");

	auto Stats = AYK::Renderer2D::GetStats();
	ImGui::Text("Renderer2D Stats:");
	ImGui::Text("Draw Calls: %d", Stats.DrawCalls);
	ImGui::Text("Quads: %d", Stats.QuadCount);
	ImGui::Text("Vertices: %d", Stats.GetTotalVErtexCount());
	ImGui::Text("Indices %d:", Stats.GetTotalIndexCount());


	ImGui::ColorEdit4("Square Color", glm::value_ptr(SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(AYK::Event& E) {
	CameraController.OnEvent(E);
}

