#pragma once

#include <memory.h>
#include "AYK/Renderer/Buffer.h"

namespace AYK {

	class VertexArray {

	public:
		virtual ~VertexArray() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& VBuffer ) = 0;
		virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& IBuffer) = 0;
		
		virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const = 0;
		virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const = 0;

		static VertexArray* Create();

	};

}