#include "aykpch.h"
#include "Renderer2D.h"

#include "VertexArray.h"
#include "Shader.h"

#include "RenderCommand.h"

#include <glm/gtc/matrix_transform.hpp>

namespace AYK {

	struct QuadVertex {
		glm::vec3 Position;
		glm::vec4 Color;
		glm::vec2 TexCoord;
		float TexIndex;
	};

	struct Renderer2DData {
		const uint32_t MaxQuads = 10000;
		const uint32_t MaxVertices = MaxQuads * 4;
		const uint32_t MaxIndices = MaxQuads * 6;
		static const uint32_t MaxTextureSlots = 32; // TOD: RenderCaps

		Ref<VertexArray> VA;
		Ref<VertexBuffer> VB;
		Ref<Shader> TextureShader;
		Ref<Texture2D> WhiteTexture;

		uint32_t QuadIndexCount = 0;
		QuadVertex* QuadVertexBufferBase = nullptr;
		QuadVertex* QuadVertexBufferPtr = nullptr;

		std::array<Ref<Texture2D>, MaxTextureSlots> TextureSlots;
		uint32_t TextureSlotIndex = 1; // 0 - white texture
	};

	static Renderer2DData Data;



	void Renderer2D::Init() {

		AYK_PROFILE_FUNCTION(); 

		Data.VA = VertexArray::Create();

		Data.VB = VertexBuffer::Create(Data.MaxVertices * sizeof(QuadVertex));
		Data.VB->SetLayout({ 
			{ ShaderDataType::Float3, "aPosition"},
			{ ShaderDataType::Float4, "aColor"},
			{ ShaderDataType::Float2, "aTexCoord"},
			{ ShaderDataType::Float, "aTexIndex"}
			});
		Data.VA->AddVertexBuffer(Data.VB);

		Data.QuadVertexBufferBase = new QuadVertex[Data.MaxVertices];
		
		uint32_t* QuadIndices = new uint32_t[Data.MaxIndices];

		uint32_t Offset = 0;
		for (uint32_t i = 0; i < Data.MaxIndices; i+=6) {
			QuadIndices[i + 0] = Offset + 0;
			QuadIndices[i + 1] = Offset + 1;
			QuadIndices[i + 2] = Offset + 2;

			QuadIndices[i + 3] = Offset + 2;
			QuadIndices[i + 4] = Offset + 3;
			QuadIndices[i + 5] = Offset + 0;

			Offset += 4;
		}

		Ref<IndexBuffer> IB = IndexBuffer::Create(QuadIndices, Data.MaxIndices);
		Data.VA->SetIndexBuffer(IB);
		delete[] QuadIndices;

		Data.WhiteTexture = Texture2D::Create(1, 1);
		uint32_t WhiteTextureData = 0xffffffff;
		Data.WhiteTexture->SetData(&WhiteTextureData, sizeof(uint32_t));

		int32_t Samplers[Data.MaxTextureSlots];
		for (uint32_t i = 0; i < Data.MaxTextureSlots; ++i) {
			Samplers[i] = i;
		}
		Data.TextureShader = Shader::Create("assets/shaders/Texture.glsl");
		Data.TextureShader->Bind();
		Data.TextureShader->SetIntArray("UTextures", Samplers, Data.MaxTextureSlots);
		
		Data.TextureSlots[0] = Data.WhiteTexture;
	}

	void Renderer2D::Shutdown() {
		AYK_PROFILE_FUNCTION();
	}

	void Renderer2D::BeginScene(const OrthographicCamera& Cam) {
		AYK_PROFILE_FUNCTION();

		Data.TextureShader->Bind();
		Data.TextureShader->SetMat4("uViewProjection", Cam.GetViewProjectionMatrix());
	
		Data.QuadVertexBufferPtr = Data.QuadVertexBufferBase;
		Data.QuadIndexCount = 0;

		Data.TextureSlotIndex = 1;
	
	}

	void Renderer2D::EndScene() {
		AYK_PROFILE_FUNCTION();

		uint32_t DataSize =(uint8_t*)Data.QuadVertexBufferPtr - (uint8_t*)Data.QuadVertexBufferBase;
		Data.VB->SetData(Data.QuadVertexBufferBase, DataSize);

		Flush();
	}

	void Renderer2D::Flush(){
		for (uint32_t i = 0; i < Data.TextureSlotIndex; ++i) {
			Data.TextureSlots[i]->Bind(i);
		}
		RenderCommand::DrawIndexed(Data.VA, Data.QuadIndexCount);
	}

	void Renderer2D::DrawQuad(const glm::vec2& Position, const glm::vec2 Size, const glm::vec4 Color) {
		DrawQuad({ Position.x, Position.y, 0.0f }, Size, Color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& Position, const glm::vec2 Size, const glm::vec4 Color) {
		AYK_PROFILE_FUNCTION();

		// NOTE: Batching 
		
		const float TextureIndex = 0.0f; // White texture
		
		Data.QuadVertexBufferPtr->Position = Position;
		Data.QuadVertexBufferPtr->Color = Color;
		Data.QuadVertexBufferPtr->TexCoord = {0.0f, 0.0f};
		Data.QuadVertexBufferPtr->TexIndex = TextureIndex;
		Data.QuadVertexBufferPtr++;

		Data.QuadVertexBufferPtr->Position = {Position.x + Size.x, Position.y, 0.0f};
		Data.QuadVertexBufferPtr->Color = Color;
		Data.QuadVertexBufferPtr->TexCoord = { 1.0f, 0.0f };
		Data.QuadVertexBufferPtr->TexIndex = TextureIndex;
		Data.QuadVertexBufferPtr++;

		Data.QuadVertexBufferPtr->Position = { Position.x + Size.x, Position.y + Size.y, 0.0f };
		Data.QuadVertexBufferPtr->Color = Color;
		Data.QuadVertexBufferPtr->TexCoord = { 1.0f, 1.0f };
		Data.QuadVertexBufferPtr->TexIndex = TextureIndex;
		Data.QuadVertexBufferPtr++;

		Data.QuadVertexBufferPtr->Position = { Position.x, Position.y + Size.y, 0.0f };
		Data.QuadVertexBufferPtr->Color = Color;
		Data.QuadVertexBufferPtr->TexCoord = { 0.0f, 1.0f };
		Data.QuadVertexBufferPtr->TexIndex = TextureIndex;
		Data.QuadVertexBufferPtr++;

		Data.QuadIndexCount += 6;
		//________________________

		//Data.TextureShader->SetFloat("uTilingTexture", 1.0f);
		//Data.WhiteTexture->Bind();

		//glm::mat4 Transform = glm::translate(glm::mat4(1.0f), Position) * glm::scale(glm::mat4(1.0f), { Size.x, Size.y, 1.0f });
		//Data.TextureShader->SetMat4("uTransform", Transform);

		//Data.VA->Bind();
		//RenderCommand::DrawIndexed(Data.VA);
	}

	void Renderer2D::DrawQuad(const glm::vec2& Position, 
		const glm::vec2 Size, const Ref<Texture2D>& Texture, float TilingFactor,
		const glm::vec4& TintColor) {
		DrawQuad({ Position.x, Position.y, 0.0f }, Size, Texture, TilingFactor, TintColor);
	}

	void Renderer2D::DrawQuad(const glm::vec3& Position, 
		const glm::vec2 Size, const Ref<Texture2D>& Texture, float TilingFactor,
		const glm::vec4& TintColor) {
		AYK_PROFILE_FUNCTION();

		constexpr glm::vec4 DefaultColor = {1.0f, 1.0f, 1.0f, 1.0f};

		float TextureIndex = 0.0f;

		for (uint32_t i = 1; i < Data.TextureSlotIndex; ++i) {
			if (*Data.TextureSlots[i].get() == *Texture.get()) {
				TextureIndex = (float)i;
			}
		}

		if (TextureIndex) {
			TextureIndex = (float)Data.TextureSlotIndex;
			Data.TextureSlots[Data.TextureSlotIndex] = Texture;
			Data.TextureSlotIndex++;
		}

		Data.QuadVertexBufferPtr->Position = Position;
		Data.QuadVertexBufferPtr->Color = DefaultColor;
		Data.QuadVertexBufferPtr->TexCoord = { 0.0f, 0.0f };
		Data.QuadVertexBufferPtr->TexIndex = TextureIndex;
		Data.QuadVertexBufferPtr++;

		Data.QuadVertexBufferPtr->Position = { Position.x + Size.x, Position.y, 0.0f };
		Data.QuadVertexBufferPtr->Color = DefaultColor;
		Data.QuadVertexBufferPtr->TexCoord = { 1.0f, 0.0f };
		Data.QuadVertexBufferPtr->TexIndex = TextureIndex;
		Data.QuadVertexBufferPtr++;

		Data.QuadVertexBufferPtr->Position = { Position.x + Size.x, Position.y + Size.y, 0.0f };
		Data.QuadVertexBufferPtr->Color = DefaultColor;
		Data.QuadVertexBufferPtr->TexCoord = { 1.0f, 1.0f };
		Data.QuadVertexBufferPtr->TexIndex = TextureIndex;
		Data.QuadVertexBufferPtr++;

		Data.QuadVertexBufferPtr->Position = { Position.x, Position.y + Size.y, 0.0f };
		Data.QuadVertexBufferPtr->Color = DefaultColor;
		Data.QuadVertexBufferPtr->TexCoord = { 0.0f, 1.0f };
		Data.QuadVertexBufferPtr->TexIndex = TextureIndex;
		Data.QuadVertexBufferPtr++;

		Data.QuadIndexCount += 6;

#if OLD_PATH

		Data.TextureShader->Bind();

		Data.TextureShader->SetFloat4("uColor", TintColor);
		Data.TextureShader->SetFloat("uTilingFactor", TilingFactor);
		
		Texture->Bind();

		glm::mat4 Transform = glm::translate(glm::mat4(1.0f), Position) * glm::scale(glm::mat4(1.0f), { Size.x, Size.y, 1.0f });
		Data.TextureShader->SetMat4("uTransform", Transform);


		Data.VA->Bind();
		RenderCommand::DrawIndexed(Data.VA);
#endif
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec2& Position, const glm::vec2 Size, const float Rotation, const glm::vec4 Color) {
		DrawRotatedQuad(glm::vec3(Position.x, Position.y, 0.0f), Size, Rotation, Color);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec3& Position, const glm::vec2 Size, const float Rotation, const glm::vec4 Color) {
		AYK_PROFILE_FUNCTION();

		Data.TextureShader->Bind();

		Data.TextureShader->SetFloat4("uColor", Color);
		Data.TextureShader->SetFloat("uTilingFactor", 1.0f);
		Data.WhiteTexture->Bind();

		glm::mat4 Transform = glm::translate(glm::mat4(1.0f), Position)
			* glm::rotate(glm::mat4(1.0f), Rotation, glm::vec3(0.0f, 0.0f, 1.0f))
			* glm::scale(glm::mat4(1.0f), { Size.x, Size.y, 1.0f });
		Data.TextureShader->SetMat4("uTransform", Transform);


		Data.VA->Bind();
		RenderCommand::DrawIndexed(Data.VA);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec2& Position, 
		const glm::vec2 Size, const float Rotation, const Ref<Texture2D>& Texture, float TilingFactor,
		const glm::vec4& TintColor) {
		DrawRotatedQuad(glm::vec3(Position.x, Position.y, 0.0f), Size, Rotation, Texture, TilingFactor, TintColor);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec3& Position, 
		const glm::vec2 Size, const float Rotation, const Ref<Texture2D>& Texture, float TilingFactor,
		const glm::vec4& TintColor) {
		AYK_PROFILE_FUNCTION();

		Data.TextureShader->Bind();

		Data.TextureShader->SetFloat4("uColor", TintColor);
		Data.TextureShader->SetFloat("uTilingFactor", TilingFactor);

		Texture->Bind();

		glm::mat4 Transform = glm::translate(glm::mat4(1.0f), Position)
			* glm::rotate(glm::mat4(1.0f), Rotation, glm::vec3(0.0f, 0.0f, 1.0f))
			* glm::scale(glm::mat4(1.0f), { Size.x, Size.y, 1.0f });
		Data.TextureShader->SetMat4("uTransform", Transform);


		Data.VA->Bind();
		RenderCommand::DrawIndexed(Data.VA);
	}


}



