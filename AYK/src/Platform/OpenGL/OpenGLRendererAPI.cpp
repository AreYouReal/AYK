#include "aykpch.h"
#include "OpenGLRendererAPI.h"

#include "glad/glad.h"

namespace AYK { 

	void OpenGLRendererAPI::Init() {
		AYK_PROFILE_FUNCTION();

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_DEPTH_TEST);
	}

	void OpenGLRendererAPI::SetViewport(uint32_t X, uint32_t Y, uint32_t Width, uint32_t Height) {
		glViewport(X, Y, Width, Height);
	}

	void OpenGLRendererAPI::SetClearColor(const glm::vec4& Color) {
		glClearColor(Color.r, Color.g, Color.b, Color.a);
	}

	void OpenGLRendererAPI::Clear() {
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	}

	void OpenGLRendererAPI::DrawIndexed(const Ref<VertexArray>& VA, uint32_t IndexCount) {
		uint32_t Count = IndexCount ? VA->GetIndexBuffer()->GetCount() : IndexCount;
		glDrawElements(GL_TRIANGLES, Count, GL_UNSIGNED_INT, nullptr);
		glBindTexture(GL_TEXTURE_2D, 0);
	}



}