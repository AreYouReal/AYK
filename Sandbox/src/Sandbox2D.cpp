#include "aykpch.h"
#include "Sandbox2D.h"

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// TEMP!
#include "Platform/OpenGL/OpenGLShader.h" 

Sandbox2D::Sandbox2D() : Layer("Sandbox2D"), CameraController(1280.0f / 720.0f){ }

void Sandbox2D::OnAttach() {

	// Generate VA - Square
	VA = AYK::VertexArray::Create();

	float SquareVertices[5 * 4] = {
		-.5f, -.5f, .0f,
		 .5f, -.5f, .0f,
		 .5f,  .5f, .0f,
		-.5f,  .5f, .0f
	};

	AYK::Ref<AYK::VertexBuffer> VB;
	VB.reset(AYK::VertexBuffer::Create(SquareVertices, sizeof(SquareVertices)));
	VB->SetLayout({ { AYK::ShaderDataType::Float3, "aPosition"} });
	VA->AddVertexBuffer(VB);

	uint32_t SquareIndices[6] = { 0, 1, 2, 2, 3, 0 };
	AYK::Ref<AYK::IndexBuffer> IB;
	IB.reset(AYK::IndexBuffer::Create(SquareIndices, (sizeof(SquareIndices) / sizeof(uint32_t))));
	VA->SetIndexBuffer(IB);

	FlatColorShader = (AYK::Shader::Create("assets/shaders/FlatColor.glsl"));
}

void Sandbox2D::OnDetach() { }

void Sandbox2D::OnUpdate(AYK::Timestep Timestep) {
	CameraController.OnUpdate(Timestep);

	AYK::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	AYK::RenderCommand::Clear();

	AYK::Renderer::BeginScene(CameraController.GetCamera());
	
	std::dynamic_pointer_cast<AYK::OpenGLShader>(FlatColorShader)->Bind();
	std::dynamic_pointer_cast<AYK::OpenGLShader>(FlatColorShader)->UploadUniformFloat4("uColor", SquareColor);

	AYK::Renderer::Submit(FlatColorShader, VA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

	AYK::Renderer::EndScene();
}

void Sandbox2D::OnImGuiRender() {
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(AYK::Event& E) {
	CameraController.OnEvent(E);
}

