#pragma once

#include "RendererAPI.h"

namespace AYK {

	class RenderCommand {
	public:

		inline static void Init() {
			CurrentRendererAPI->Init();
		}

		inline static void SetViewport(uint32_t X, uint32_t Y, uint32_t Width, uint32_t Height) {
			CurrentRendererAPI->SetViewport(X, Y, Width, Height);
		}

		inline static void SetClearColor(const glm::vec4& Color) {
			CurrentRendererAPI->SetClearColor(Color);
		}
		inline static void Clear() {
			CurrentRendererAPI->Clear();
		}


		inline static void DrawIndexed(const Ref<VertexArray>& VA){
			CurrentRendererAPI->DrawIndexed(VA);
		}

	private:
		static RendererAPI* CurrentRendererAPI;

	};

}