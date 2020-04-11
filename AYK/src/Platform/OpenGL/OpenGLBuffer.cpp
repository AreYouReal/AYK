#include "aykpch.h"
#include "OpenGLBuffer.h"

#include "glad/glad.h"

namespace AYK {


	///////////////////////////////////////////
	//////////VertexBuffer////////////////////
	//////////////////////////////////////////

	OpenGLVertexBuffer::OpenGLVertexBuffer(uint32_t Size){
		AYK_PROFILE_FUNCTION();

		glCreateBuffers(1, &RendererID);
		glBindBuffer(GL_ARRAY_BUFFER, RendererID);
		glBufferData(GL_ARRAY_BUFFER, Size, nullptr, GL_DYNAMIC_DRAW);
	}

	OpenGLVertexBuffer::OpenGLVertexBuffer(float* Vertices, uint32_t Size){
		AYK_PROFILE_FUNCTION();

		glCreateBuffers(1, &RendererID);
		glBindBuffer(GL_ARRAY_BUFFER, RendererID);
		glBufferData(GL_ARRAY_BUFFER, Size, Vertices, GL_STATIC_DRAW);
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer() {
		AYK_PROFILE_FUNCTION();

		glDeleteBuffers(1, &RendererID);
	}

	void OpenGLVertexBuffer::Bind() const {
		AYK_PROFILE_FUNCTION();

		glBindBuffer(GL_ARRAY_BUFFER, RendererID);
	}

	void OpenGLVertexBuffer::Unbind() const {
		AYK_PROFILE_FUNCTION();

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void OpenGLVertexBuffer::SetData(const void* Data, uint32_t Size){
		glBindBuffer(GL_ARRAY_BUFFER, RendererID);
		glBufferSubData(GL_ARRAY_BUFFER, 0, Size, Data);
	}
	
	///////////////////////////////////////////
	//////////IndexBuffer/////////////////////
	//////////////////////////////////////////
	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* Indices, uint32_t Count) : ICount(Count){
		AYK_PROFILE_FUNCTION();

		glCreateBuffers(1, &RendererID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, RendererID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, Count * sizeof(uint32_t), Indices, GL_STATIC_DRAW);
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer() {
		AYK_PROFILE_FUNCTION();

		glDeleteBuffers(1, &RendererID);
	}

	void OpenGLIndexBuffer::Bind() const {
		AYK_PROFILE_FUNCTION();

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, RendererID);
	}

	void OpenGLIndexBuffer::Unbind() const {
		AYK_PROFILE_FUNCTION();

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	uint32_t OpenGLIndexBuffer::GetCount() const{
		return(ICount);
	}

}


