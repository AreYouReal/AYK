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
		float TilingFactor;
	};

	struct Renderer2DData {
		static const uint32_t MaxQuads = 2000;
		static const uint32_t MaxVertices = MaxQuads * 4;
		static const uint32_t MaxIndices = MaxQuads * 6;
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

		glm::vec4 QuadVertexPositons[4];

		Renderer2D::Statistics Stats;
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
			{ ShaderDataType::Float, "aTexIndex"},
			{ShaderDataType::Float, "aTilingFactor"}
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
		uint32_t BlackTextureData = 0xff000000;
		Data.WhiteTexture->SetData(&WhiteTextureData, sizeof(uint32_t));

		int32_t Samplers[Data.MaxTextureSlots];
		for (uint32_t i = 0; i < Data.MaxTextureSlots; ++i) {
			Samplers[i] = i;
		}
		Data.TextureShader = Shader::Create("assets/shaders/Texture.glsl");
		Data.TextureShader->Bind();
		Data.TextureShader->SetIntArray("uTextures", Samplers, Data.MaxTextureSlots);
		
		Data.TextureSlots[0] = Data.WhiteTexture;

		Data.QuadVertexPositons[0] = {-0.5f, -0.5f, 0.0f, 1.0f};
		Data.QuadVertexPositons[1] = { 0.5f, -0.5f, 0.0f, 1.0f };
		Data.QuadVertexPositons[2] = { 0.5f, 0.5f, 0.0f, 1.0f };
		Data.QuadVertexPositons[3] = { -0.5f, 0.5f, 0.0f, 1.0f };
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

		++Data.Stats.DrawCalls;
	}

	void Renderer2D::FlushAndReset() {
		EndScene();
		Data.QuadVertexBufferPtr = Data.QuadVertexBufferBase;
		Data.QuadIndexCount = 0;

		Data.TextureSlotIndex = 1;
	}

	void Renderer2D::DrawQuad(const glm::vec2& Position, const glm::vec2 Size, const glm::vec4 Color) {
		DrawQuad({ Position.x, Position.y, 0.0f }, Size, Color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& Position, const glm::vec2 Size, const glm::vec4 Color) {
		AYK_PROFILE_FUNCTION();
		
		if (Data.QuadIndexCount >= Renderer2DData::MaxIndices) {
			FlushAndReset();
		}

		const float TextureIndex = 0.0f; // White texture 
		const float TilingFactor = 1.0f;
		
		glm::mat4 Transform = glm::translate(glm::mat4(1.0f), Position) * glm::scale(glm::mat4(1.0f), { Size.x, Size.y, 1.0f });
		
		Data.QuadVertexBufferPtr->Position = Transform * Data.QuadVertexPositons[0];;
		Data.QuadVertexBufferPtr->Color = Color;
		Data.QuadVertexBufferPtr->TexCoord = {0.0f, 0.0f};
		Data.QuadVertexBufferPtr->TilingFactor = TilingFactor;
		Data.QuadVertexBufferPtr->TexIndex = TextureIndex;

		Data.QuadVertexBufferPtr++;

		Data.QuadVertexBufferPtr->Position = Transform * Data.QuadVertexPositons[1];
		Data.QuadVertexBufferPtr->Color = Color;
		Data.QuadVertexBufferPtr->TexCoord = { 1.0f, 0.0f };
		Data.QuadVertexBufferPtr->TexIndex = TextureIndex;
		Data.QuadVertexBufferPtr->TilingFactor = TilingFactor;
		Data.QuadVertexBufferPtr++;

		Data.QuadVertexBufferPtr->Position = Transform * Data.QuadVertexPositons[2];
		Data.QuadVertexBufferPtr->Color = Color;
		Data.QuadVertexBufferPtr->TexCoord = { 1.0f, 1.0f };
		Data.QuadVertexBufferPtr->TexIndex = TextureIndex;
		Data.QuadVertexBufferPtr->TilingFactor = TilingFactor;
		Data.QuadVertexBufferPtr++;

		Data.QuadVertexBufferPtr->Position = Transform * Data.QuadVertexPositons[3];
		Data.QuadVertexBufferPtr->Color = Color;
		Data.QuadVertexBufferPtr->TexCoord = { 0.0f, 1.0f };
		Data.QuadVertexBufferPtr->TexIndex = TextureIndex;
		Data.QuadVertexBufferPtr->TilingFactor = TilingFactor;
		Data.QuadVertexBufferPtr++;

		Data.QuadIndexCount += 6;

		++Data.Stats.QuadCount;
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

		constexpr float x = 7, y = 6;
		constexpr float SheetWidth = 2560.0f, SheetHeight = 1664.0f;
		constexpr float SpriteWidth = 128.0f, SpriteHeight = 128.0f;

		constexpr size_t QuadVertexCount = 4;
		constexpr glm::vec4 Color = { 1.0f, 1.0f, 1.0f, 1.0f };
		constexpr glm::vec2 TextureCoords[] = { 
			{ (x * SpriteWidth) / SheetWidth, (y * SpriteHeight) / SheetHeight }, 
			{ ((x + 1) * SpriteWidth) / SheetWidth, (y * SpriteHeight) / SheetHeight },
			{ ((x + 1) * SpriteWidth) / SheetWidth, ((y + 1) * SpriteHeight) / SheetHeight },
			{ (x * SpriteWidth) / SheetWidth, ((y + 1) * SpriteHeight) / SheetHeight }
		};

		if (Data.QuadIndexCount >= Renderer2DData::MaxIndices) {
			FlushAndReset();
		}

		float TextureIndex = 0.0f;

		for (uint32_t i = 1; i < Data.TextureSlotIndex; ++i) {
			if (*Data.TextureSlots[i].get() == *Texture.get()) {
				TextureIndex = (float)i;
				break;
			}
		}

		if (TextureIndex == 0.0f) {
			if (Data.TextureSlotIndex >= Renderer2DData::MaxTextureSlots) {
				FlushAndReset();
			}
			TextureIndex = (float)Data.TextureSlotIndex;
			Data.TextureSlots[Data.TextureSlotIndex] = Texture;
			Data.TextureSlotIndex++;
		}

		glm::mat4 Transform = glm::translate(glm::mat4(1.0f), Position) 
			* glm::scale(glm::mat4(1.0f), { Size.x, Size.y, 1.0f });

		for (size_t i = 0; i < QuadVertexCount; ++i) {
			Data.QuadVertexBufferPtr->Position = Transform * Data.QuadVertexPositons[i];
			Data.QuadVertexBufferPtr->Color = Color;
			Data.QuadVertexBufferPtr->TexCoord = TextureCoords[i];
			Data.QuadVertexBufferPtr->TexIndex = TextureIndex;
			Data.QuadVertexBufferPtr->TilingFactor = TilingFactor;
			Data.QuadVertexBufferPtr++;
		}

		Data.QuadIndexCount += 6;

		++Data.Stats.QuadCount;
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec2& Position, const glm::vec2 Size, const float Rotation, const glm::vec4 Color) {
		DrawRotatedQuad(glm::vec3(Position.x, Position.y, 0.0f), Size, Rotation, Color);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec3& Position, const glm::vec2 Size, const float Rotation, const glm::vec4 Color) {
		AYK_PROFILE_FUNCTION();

		if (Data.QuadIndexCount >= Renderer2DData::MaxIndices) {
			FlushAndReset();
		}

		const float TextureIndex = 0.0f;
		const float TilingFactor = 1.0f;

		glm::mat4 Transform = glm::translate(glm::mat4(1.0f), Position)
			* glm::rotate(glm::mat4(1.0f), Rotation, { 0.0f, 0.0f, 1.0f })
			* glm::scale(glm::mat4(1.0f), { Size.x, Size.y, 1.0f });


		Data.QuadVertexBufferPtr->Position = Transform * Data.QuadVertexPositons[0];
		Data.QuadVertexBufferPtr->Color = Color;
		Data.QuadVertexBufferPtr->TexCoord = { 0.0f, 0.0f };
		Data.QuadVertexBufferPtr->TexIndex = TextureIndex;
		Data.QuadVertexBufferPtr->TilingFactor = TilingFactor;
		Data.QuadVertexBufferPtr++;

		Data.QuadVertexBufferPtr->Position = Transform * Data.QuadVertexPositons[1];
		Data.QuadVertexBufferPtr->Color = Color;
		Data.QuadVertexBufferPtr->TexCoord = { 1.0f, 0.0f };
		Data.QuadVertexBufferPtr->TexIndex = TextureIndex;
		Data.QuadVertexBufferPtr->TilingFactor = TilingFactor;
		Data.QuadVertexBufferPtr++;

		Data.QuadVertexBufferPtr->Position = Transform * Data.QuadVertexPositons[2];
		Data.QuadVertexBufferPtr->Color = Color;
		Data.QuadVertexBufferPtr->TexCoord = { 1.0f, 1.0f };
		Data.QuadVertexBufferPtr->TexIndex = TextureIndex;
		Data.QuadVertexBufferPtr->TilingFactor = TilingFactor;
		Data.QuadVertexBufferPtr++;

		Data.QuadVertexBufferPtr->Position = Transform * Data.QuadVertexPositons[3];
		Data.QuadVertexBufferPtr->Color = Color;
		Data.QuadVertexBufferPtr->TexCoord = { 0.0f, 1.0f };
		Data.QuadVertexBufferPtr->TexIndex = TextureIndex;
		Data.QuadVertexBufferPtr->TilingFactor = TilingFactor;
		Data.QuadVertexBufferPtr++;

		Data.QuadIndexCount += 6;

		++Data.Stats.QuadCount;
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

		if (Data.QuadIndexCount >= Renderer2DData::MaxIndices) {
			FlushAndReset();
		}

		constexpr glm::vec4 DefaultColor = { 1.0f, 1.0f, 1.0f, 1.0f };

		float TextureIndex = 0.0f;

		for (uint32_t i = 1; i < Data.TextureSlotIndex; ++i) {
			if (*Data.TextureSlots[i].get() == *Texture.get()) {
				TextureIndex = (float)i;
			}
		}

		if (TextureIndex == 0.0f) {
			TextureIndex = (float)Data.TextureSlotIndex;
			Data.TextureSlots[Data.TextureSlotIndex] = Texture;
			Data.TextureSlotIndex++;
		}

		glm::mat4 Transform = glm::translate(glm::mat4(1.0f), Position)
			* glm::rotate(glm::mat4(1.0f), Rotation, { 0.0f, 0.0f, 1.0f })
			* glm::scale(glm::mat4(1.0f), { Size.x, Size.y, 1.0f});


		Data.QuadVertexBufferPtr->Position = Transform * Data.QuadVertexPositons[0];
		Data.QuadVertexBufferPtr->Color = DefaultColor;
		Data.QuadVertexBufferPtr->TexCoord = { 0.0f, 0.0f };
		Data.QuadVertexBufferPtr->TexIndex = TextureIndex;
		Data.QuadVertexBufferPtr->TilingFactor = TilingFactor;
		Data.QuadVertexBufferPtr++;

		Data.QuadVertexBufferPtr->Position = Transform * Data.QuadVertexPositons[1];
		Data.QuadVertexBufferPtr->Color = DefaultColor;
		Data.QuadVertexBufferPtr->TexCoord = { 1.0f, 0.0f };
		Data.QuadVertexBufferPtr->TexIndex = TextureIndex;
		Data.QuadVertexBufferPtr->TilingFactor = TilingFactor;
		Data.QuadVertexBufferPtr++;

		Data.QuadVertexBufferPtr->Position = Transform * Data.QuadVertexPositons[2];
		Data.QuadVertexBufferPtr->Color = DefaultColor;
		Data.QuadVertexBufferPtr->TexCoord = { 1.0f, 1.0f };
		Data.QuadVertexBufferPtr->TexIndex = TextureIndex;
		Data.QuadVertexBufferPtr->TilingFactor = TilingFactor;
		Data.QuadVertexBufferPtr++;

		Data.QuadVertexBufferPtr->Position = Transform * Data.QuadVertexPositons[3]; 
		Data.QuadVertexBufferPtr->Color = DefaultColor;
		Data.QuadVertexBufferPtr->TexCoord = { 0.0f, 1.0f };
		Data.QuadVertexBufferPtr->TexIndex = TextureIndex;
		Data.QuadVertexBufferPtr->TilingFactor = TilingFactor;
		Data.QuadVertexBufferPtr++;

		Data.QuadIndexCount += 6;

		++Data.Stats.QuadCount;
	}


	AYK::Renderer2D::Statistics Renderer2D::GetStats(){
		return(Data.Stats);
	}

	void Renderer2D::ResetStats(){
		memset(&Data.Stats, 0, sizeof(Statistics));
	}

}



