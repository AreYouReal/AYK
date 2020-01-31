#include "aykpch.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLShader.h"
#include "Renderer2D.h"

namespace AYK {

	Renderer::SceneData* Renderer::CurrentSceneData = new Renderer::SceneData;

	void Renderer::Init() {
		RenderCommand::Init();
		Renderer2D::Init();
	}

	void Renderer::OnWindowResize(uint32_t Width, uint32_t Height) {
		RenderCommand::SetViewport(0, 0, Width, Height);
	}

	void Renderer::BeginScene(OrthographicCamera& Camera) {
		CurrentSceneData->ViewProjectionMatrix = Camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene() {

	}

	void Renderer::Submit(const Ref<Shader>& Sh, const Ref<VertexArray>& VA, const glm::mat4& Transform) {
		Sh->Bind();
		std::dynamic_pointer_cast<OpenGLShader>( Sh )->UploadUniformMat4("uViewProjection", CurrentSceneData->ViewProjectionMatrix);
		std::dynamic_pointer_cast<OpenGLShader>( Sh )->UploadUniformMat4("uTransform", Transform);
		VA->Bind();
		RenderCommand::DrawIndexed(VA);
	}

}
