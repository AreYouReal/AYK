#pragma once

#include "AYK/Renderer/Buffer.h"

namespace AYK {

	class OpenGLVertexBuffer : public VertexBuffer {

	public:

		OpenGLVertexBuffer(uint32_t Size);
		OpenGLVertexBuffer(float* Vertices, uint32_t Size);
		~OpenGLVertexBuffer();

		virtual void Bind() const override;

		virtual void Unbind() const override;

		virtual void SetData(const void* Data, uint32_t Size) override;

		virtual void SetLayout(const BufferLayout& Layout) override { BLayout = Layout; }

		virtual const BufferLayout& GetLayout() const override { return(BLayout); }

	private:

		uint32_t RendererID;
		BufferLayout BLayout;

	};

	class OpenGLIndexBuffer : public IndexBuffer {

	public:
		OpenGLIndexBuffer(uint32_t* Indices, uint32_t Count);
		~OpenGLIndexBuffer();

		virtual void Bind() const override;

		virtual void Unbind() const override;

		virtual uint32_t GetCount() const override;

	private:
		uint32_t ICount;
		uint32_t RendererID;

	};


}

