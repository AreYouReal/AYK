#pragma once

#include <memory.h>
#include "AYK/Renderer/Buffer.h"

namespace AYK {

	class VertexArray {

	public:
		virtual ~VertexArray() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void AddVertexBuffer(const Ref<VertexBuffer>& VBuffer ) = 0;
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& IBuffer) = 0;
		
		virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const = 0;
		virtual const Ref<IndexBuffer>& GetIndexBuffer() const = 0;

		static VertexArray* Create();

	};

}