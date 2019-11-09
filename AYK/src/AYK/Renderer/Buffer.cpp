#include "aykpch.h"
#include "Buffer.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace AYK {

	VertexBuffer* VertexBuffer::Create(float* Vertices, uint32_t Size) {
		switch (Renderer::GetAPI()){
			case RendererAPI::OpenGL: return(new OpenGLVertexBuffer(Vertices, Size));
			default: 
				AYK_CORE_ASSERT(false, "RendererAPI is not supported!");
			return nullptr;
		}
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* Indices, uint32_t Count) {
		switch (Renderer::GetAPI()) {
			case RendererAPI::OpenGL: return(new OpenGLIndexBuffer(Indices, Count));
			default:
			AYK_CORE_ASSERT(false, "RendererAPI is not supported!");
			return nullptr;
		}
	}

}