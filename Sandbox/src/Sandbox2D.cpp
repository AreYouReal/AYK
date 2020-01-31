#include "aykpch.h"
#include "Sandbox2D.h"

#include "imgui/imgui.h"


#include <glm/gtc/type_ptr.hpp>

Sandbox2D::Sandbox2D() : Layer("Sandbox2D"), CameraController(1280.0f / 720.0f){ }

void Sandbox2D::OnAttach() {}

void Sandbox2D::OnDetach() { }

void Sandbox2D::OnUpdate(AYK::Timestep Timestep) {
	CameraController.OnUpdate(Timestep);

	AYK::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	AYK::RenderCommand::Clear();

	AYK::Renderer2D::BeginScene(CameraController.GetCamera());
	
	AYK::Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 1.0f, 1.0f }, { 0.8f, 0.2f, 0.3f, 1.0f });

	AYK::Renderer2D::DrawQuad({ 1.0f, 0.5f }, { .2f, .2f }, { 0.3f, 0.2f, 0.8f, 1.0f });

	AYK::Renderer2D::EndScene();
}

void Sandbox2D::OnImGuiRender() {
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(AYK::Event& E) {
	CameraController.OnEvent(E);
}

