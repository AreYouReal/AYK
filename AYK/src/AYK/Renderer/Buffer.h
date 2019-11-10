#pragma once


namespace AYK {

	enum class ShaderDataType{
		None = 0,
		Float, 
		Float2,
		Float3,
		Float4, 
		Mat3,
		Mat4,
		Int,
		Int2,
		Int3,
		Int4,
		Bool
	};

	static uint32_t ShaderDataTypeSize(ShaderDataType Type) {
		switch (Type){
			case AYK::ShaderDataType::Float:	return(4);
			case AYK::ShaderDataType::Float2:	return(4 * 2);
			case AYK::ShaderDataType::Float3:	return(4 * 3);
			case AYK::ShaderDataType::Float4:	return(4 * 4);
			case AYK::ShaderDataType::Mat3:		return(4 * 3 * 3);
			case AYK::ShaderDataType::Mat4:		return(4 * 4 * 4);
			case AYK::ShaderDataType::Int:		return(4);
			case AYK::ShaderDataType::Int2:		return(4 * 2);
			case AYK::ShaderDataType::Int3:		return(4 * 3);
			case AYK::ShaderDataType::Int4:		return(4 * 4);
			case AYK::ShaderDataType::Bool:		return(1);
		}
		AYK_CORE_ASSERT(false, "Unknown ShderDataType");
		return(0);
	}

	struct BufferElement {
		std::string Name;
		ShaderDataType Type;
		uint32_t Offset;
		uint32_t Size;
		bool Normalized;
	
		BufferElement() {}

		BufferElement(ShaderDataType TypeToSet, const std::string& NameToSet, bool NormalizedToSet = false) : 
			Name(NameToSet), Type(TypeToSet), Size(ShaderDataTypeSize(Type)), Offset(0), Normalized(NormalizedToSet) { }
	
		uint32_t GetComponentCount() const {
			switch (Type)
			{
				case AYK::ShaderDataType::Float:	return(1);
				case AYK::ShaderDataType::Float2:	return(2);
				case AYK::ShaderDataType::Float3:	return(3);
				case AYK::ShaderDataType::Float4:	return(4);
				case AYK::ShaderDataType::Mat3:		return(3 * 3);
				case AYK::ShaderDataType::Mat4:		return(4 * 4);
				case AYK::ShaderDataType::Int:		return(1);
				case AYK::ShaderDataType::Int2:		return(2);
				case AYK::ShaderDataType::Int3:		return(3);
				case AYK::ShaderDataType::Int4:		return(4);
				case AYK::ShaderDataType::Bool:		return(1);
			}
			AYK_CORE_ASSERT(false, "Unknown ShderDataType");
			return(0);
		}

	};


	class BufferLayout {
	public:

		BufferLayout() {}
		BufferLayout(const std::initializer_list<BufferElement>& Elems) : Elements(Elems) { 
			CalculateOffsetsAndStride();
		}

		inline uint32_t GetStride() const { return(Stride); }
		inline const std::vector<BufferElement>& GetElements() const { return(Elements); }

		std::vector<BufferElement>::iterator begin() { return(Elements.begin()); }
		std::vector<BufferElement>::iterator end() { return(Elements.end()); }

		std::vector<BufferElement>::const_iterator begin() const { return(Elements.begin()); }
		std::vector<BufferElement>::const_iterator end() const { return(Elements.end()); }
	private:
		void CalculateOffsetsAndStride() {
			Stride = 0;
			for (auto& E : Elements) {
				E.Offset = Stride;
				Stride += E.Size;
			}
		}

	private:
		std::vector<BufferElement> Elements;
		uint32_t Stride;
	};

	class VertexBuffer{

	public:
		virtual ~VertexBuffer() {}
		
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetLayout(const BufferLayout& Layout) = 0;
		virtual const BufferLayout& GetLayout() const = 0;

		static VertexBuffer* Create(float* Vertices, uint32_t Size);

	};


	class IndexBuffer {
	public:
		virtual ~IndexBuffer() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual uint32_t GetCount() const = 0;

		static IndexBuffer* Create(uint32_t* Indices, uint32_t Count);

	};

}



