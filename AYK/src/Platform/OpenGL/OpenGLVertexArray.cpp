#include "aykpch.h"
#include "OpenGLVertexArray.h"

#include "glad/glad.h"

namespace AYK {

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType Type) {
		switch (Type) {
			case AYK::ShaderDataType::Float:
			case AYK::ShaderDataType::Float2:
			case AYK::ShaderDataType::Float3:
			case AYK::ShaderDataType::Float4:
			case AYK::ShaderDataType::Mat3:
			case AYK::ShaderDataType::Mat4:
			return(GL_FLOAT);
			case AYK::ShaderDataType::Int:
			case AYK::ShaderDataType::Int2:
			case AYK::ShaderDataType::Int3:
			case AYK::ShaderDataType::Int4:
			return(GL_INT);
			case AYK::ShaderDataType::Bool:
			return(GL_BOOL);
		}
		AYK_CORE_ASSERT(false, "Unknown ShderDataType");
		return(0);
	}

	OpenGlVertexArray::OpenGlVertexArray() {
		AYK_PROFILE_FUNCTION();

		glCreateVertexArrays(1, &RendererID);
	}

	OpenGlVertexArray::~OpenGlVertexArray() {
		AYK_PROFILE_FUNCTION();

		glDeleteVertexArrays(1, &RendererID);
	}


	void OpenGlVertexArray::Bind() const{
		AYK_PROFILE_FUNCTION();

		glBindVertexArray(RendererID);
	}

	void OpenGlVertexArray::Unbind() const{
		AYK_PROFILE_FUNCTION();

		glBindVertexArray(0);
	}

	void OpenGlVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& VBufferToAdd){
		AYK_PROFILE_FUNCTION();

		AYK_CORE_ASSERT(VBufferToAdd->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");

		glBindVertexArray(RendererID);
		VBufferToAdd->Bind();

		uint32_t CurrentIndex = 0;
		const auto& VertexBufferLayout = VBufferToAdd->GetLayout();
		for (const auto& E : VertexBufferLayout) {
			glEnableVertexAttribArray(CurrentIndex);
			glVertexAttribPointer(CurrentIndex++,
				E.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(E.Type),
				E.Normalized ? GL_TRUE : GL_FALSE,
				VertexBufferLayout.GetStride(),
				(const void*)E.Offset);
		}

		VBuffers.push_back(VBufferToAdd);
	}

	void OpenGlVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& IBufferToSet){
		AYK_PROFILE_FUNCTION();

		glBindVertexArray(RendererID);
		IBuffer = IBufferToSet;
		IBuffer->Bind();
	}

}