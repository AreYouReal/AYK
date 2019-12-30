#pragma once

#include "RendererAPI.h"

namespace AYK {

	class RenderCommand {
	public:
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