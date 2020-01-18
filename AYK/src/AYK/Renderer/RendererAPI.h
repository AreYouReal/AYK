#pragma once

#include <glm/glm.hpp>
#include "VertexArray.h"

namespace AYK {

	class RendererAPI {
	public:
		enum class API {
			None = 0,
			OpenGL = 1
		};

	public:
		virtual void Init() = 0;
		virtual void SetViewport(uint32_t X, uint32_t Y, uint32_t Width, uint32_t Height) = 0;
		virtual void SetClearColor(const glm::vec4& Color) = 0;
		virtual void Clear() = 0;

		virtual void DrawIndexed(const Ref<VertexArray>& VA) = 0;
	
		inline static API GetAPI() { return(CurrentAPI); }
	private:

		static API CurrentAPI;
	};

}