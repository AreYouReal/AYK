#pragma once

#include "AYK/Renderer/RendererAPI.h"

namespace AYK {

	class OpenGLRendererAPI : public RendererAPI {
	public:
		virtual void SetClearColor(const glm::vec4& Color) override;
		virtual void Clear() override;

		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& VA) override;

	};

}