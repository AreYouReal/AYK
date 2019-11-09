#include "aykpch.h"
#include "OpenGLBuffer.h"

#include "glad/glad.h"

namespace AYK {


	///////////////////////////////////////////
	//////////VertexBuffer////////////////////
	//////////////////////////////////////////

	OpenGLVertexBuffer::OpenGLVertexBuffer(float* Vertices, uint32_t Size){
		glCreateBuffers(1, &RendererID);
		glBindBuffer(GL_ARRAY_BUFFER, RendererID);
		glBufferData(GL_ARRAY_BUFFER, Size, Vertices, GL_STATIC_DRAW);
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer() {
		glDeleteBuffers(1, &RendererID);
	}

	void OpenGLVertexBuffer::Bind() const {
		glBindBuffer(GL_ARRAY_BUFFER, RendererID);
	}

	void OpenGLVertexBuffer::Unbind() const {
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	
	///////////////////////////////////////////
	//////////IndexBuffer/////////////////////
	//////////////////////////////////////////
	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* Indices, uint32_t Count) : ICount(Count){
		glCreateBuffers(1, &RendererID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, RendererID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, Count * sizeof(uint32_t), Indices, GL_STATIC_DRAW);
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer() {
		glDeleteBuffers(1, &RendererID);
	}

	void OpenGLIndexBuffer::Bind() const {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, RendererID);
	}

	void OpenGLIndexBuffer::Unbind() const {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	uint32_t OpenGLIndexBuffer::GetCount() const{
		return(ICount);
	}

}


