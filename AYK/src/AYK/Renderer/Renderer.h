#pragma once

#include "RenderCommand.h"

#include "OrthographicCamera.h"
#include "Shader.h"

namespace AYK {
	
	class Renderer {

	public:
		
		static void BeginScene(OrthographicCamera& Camera);
		static void EndScene();

		static void Submit(const std::shared_ptr<Shader>& Sh, const std::shared_ptr<VertexArray>& VA);
		
		inline static RendererAPI::API GetAPI() { return(RendererAPI::GetAPI()); }

	private:
		
		struct SceneData {
			glm::mat4 ViewProjectionMatrix;
		};

		static SceneData* CurrentSceneData;

	};




}