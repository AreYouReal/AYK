#pragma once

#include "AYK/Renderer/RendererAPI.h"

namespace AYK {

	class OpenGLRendererAPI : public RendererAPI {
	public:

		virtual void Init() override;
		virtual void SetViewport(uint32_t X, uint32_t Y, uint32_t Width, uint32_t Height) override;
		virtual void SetClearColor(const glm::vec4& Color) override;
		virtual void Clear() override;

		virtual void DrawIndexed(const Ref<VertexArray>& VA) override;



	};

}