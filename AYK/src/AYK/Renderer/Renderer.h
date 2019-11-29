#pragma once

#include "RenderCommand.h"

namespace AYK {
	
	class Renderer {

	public:
		
		static void BeginScene();
		static void EndScene();

		static void Submit(const std::shared_ptr<VertexArray>& VA);
		
		inline static RendererAPI::API GetAPI() { return(RendererAPI::GetAPI()); }

	private:

	};




}