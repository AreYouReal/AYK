#include "aykpch.h"
#include "Renderer.h"


namespace AYK {

	void Renderer::BeginScene() {

	}

	void Renderer::EndScene() {

	}

	void Renderer::Submit(const std::shared_ptr<VertexArray>& VA) {
		VA->Bind();
		RenderCommand::DrawIndexed(VA);
	}

}
