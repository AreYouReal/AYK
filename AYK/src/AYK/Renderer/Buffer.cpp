#include "aykpch.h"
#include "Buffer.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace AYK {

	Ref<VertexBuffer> VertexBuffer::Create(uint32_t Size){
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::OpenGL: return(CreateRef<OpenGLVertexBuffer>(Size));
		default:
			AYK_CORE_ASSERT(false, "RendererAPI is not supported!");
			return nullptr;
		}
	}
	
	
	Ref<VertexBuffer> VertexBuffer::Create(float* Vertices, uint32_t Size) {
		switch (Renderer::GetAPI()){
			case RendererAPI::API::OpenGL: return(CreateRef<OpenGLVertexBuffer>(Vertices, Size));
			default: 
				AYK_CORE_ASSERT(false, "RendererAPI is not supported!");
			return nullptr;
		}
	}

	Ref<IndexBuffer> IndexBuffer::Create(uint32_t* Indices, uint32_t Count) {
		switch (Renderer::GetAPI()) {
			case RendererAPI::API::OpenGL: return( CreateRef<OpenGLIndexBuffer>(Indices, Count));
			default:
			AYK_CORE_ASSERT(false, "RendererAPI is not supported!");
			return nullptr;
		}
	}

}