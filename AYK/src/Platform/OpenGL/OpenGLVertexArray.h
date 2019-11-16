#pragma once

#include "AYK/Renderer/VertexArray.h"


namespace AYK {

	class OpenGlVertexArray : public VertexArray {

	public:
		OpenGlVertexArray();
		virtual ~OpenGlVertexArray();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& VBufferToAdd) override;
		virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& IBufferToSet) override;

		virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const { return(VBuffers); }
		virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const { return(IBuffer); }

	private:
		uint32_t RendererID;
		std::vector<std::shared_ptr<VertexBuffer>> VBuffers;
		std::shared_ptr<IndexBuffer> IBuffer;

	};

}