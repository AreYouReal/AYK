#include "aykpch.h"
#include "Sandbox2D.h"

#include "imgui/imgui.h"


#include <glm/gtc/type_ptr.hpp>

Sandbox2D::Sandbox2D() : Layer("Sandbox2D"), CameraController(1280.0f / 720.0f){ }

void Sandbox2D::OnAttach() {
	AYK_PROFILE_FUNCTION();

	CheckerboardTexture = AYK::Texture2D::Create("assets/textures/checkerboard.png");
}

void Sandbox2D::OnDetach() {
	AYK_PROFILE_FUNCTION();
}

void Sandbox2D::OnUpdate(AYK::Timestep Timestep) {

	AYK_PROFILE_FUNCTION();

	CameraController.OnUpdate(Timestep);

	{
		AYK_PROFILE_SCOPE("Render Prep");
		AYK::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		AYK::RenderCommand::Clear();
	}

	{
		AYK_PROFILE_SCOPE("Render Draw");
		AYK::Renderer2D::BeginScene(CameraController.GetCamera());

		AYK::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { .8f, .8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		AYK::Renderer2D::DrawQuad({ .5f, -0.5f }, { .5f, .75f }, { 0.2f, 0.3f, 0.8f, 1.0f });

		AYK::Renderer2D::EndScene();
	}

}

void Sandbox2D::OnImGuiRender() {
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(AYK::Event& E) {
	CameraController.OnEvent(E);
}

