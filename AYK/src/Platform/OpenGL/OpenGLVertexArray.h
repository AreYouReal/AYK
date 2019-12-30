#pragma once

#include "AYK/Renderer/VertexArray.h"


namespace AYK {

	class OpenGlVertexArray : public VertexArray {

	public:
		OpenGlVertexArray();
		virtual ~OpenGlVertexArray();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void AddVertexBuffer(const Ref<VertexBuffer>& VBufferToAdd) override;
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& IBufferToSet) override;

		virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const { return(VBuffers); }
		virtual const Ref<IndexBuffer>& GetIndexBuffer() const { return(IBuffer); }

	private:
		uint32_t RendererID;
		std::vector<Ref<VertexBuffer>> VBuffers;
		Ref<IndexBuffer> IBuffer;

	};

}