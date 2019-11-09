#pragma once


namespace AYK {

	enum class RendererAPI {
		None = 0,
		OpenGL = 1
	};
	
	class Renderer {

	public:
		inline static RendererAPI GetAPI() { return(RAPI); }

	private:
		static RendererAPI RAPI;

	};




}