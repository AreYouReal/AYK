#include "aykpch.h"
#include "Renderer.h"


namespace AYK {

	Renderer::SceneData* Renderer::CurrentSceneData = new Renderer::SceneData;

	void Renderer::BeginScene(OrthographicCamera& Camera) {
		CurrentSceneData->ViewProjectionMatrix = Camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene() {

	}

	void Renderer::Submit(const std::shared_ptr<Shader>& Sh, const std::shared_ptr<VertexArray>& VA, const glm::mat4& Transform) {
		Sh->Bind();
		Sh->UploadUniformMat4("uViewProjection", CurrentSceneData->ViewProjectionMatrix);
		Sh->UploadUniformMat4("uTransform", Transform);
		VA->Bind();
		RenderCommand::DrawIndexed(VA);
	}

}
