#include "aykpch.h"
#include "Renderer2D.h"

#include "VertexArray.h"
#include "Shader.h"

#include "RenderCommand.h"

#include <glm/gtc/matrix_transform.hpp>

namespace AYK {

	struct Renderer2DStorage {
		Ref<VertexArray> VA;
		Ref<Shader> TextureShader;
		Ref<Texture2D> WhiteTexture;
	};

	static Renderer2DStorage* Data;

	void Renderer2D::Init() {

		AYK_PROFILE_FUNCTION();

		Data = new Renderer2DStorage();

		Data->VA = VertexArray::Create();

		float SquareVertices[5 * 4] = {
			-.5f, -.5f, .0f, 0.0f, 0.0f,
			 .5f, -.5f, .0f, 1.0f, 0.0f,
			 .5f,  .5f, .0f, 1.0f, 1.0f,
			-.5f,  .5f, .0f, 0.0f, 1.0f
		};

		Ref<VertexBuffer> VB;
		VB.reset(VertexBuffer::Create(SquareVertices, sizeof(SquareVertices)));
		VB->SetLayout({ 
			{ ShaderDataType::Float3, "aPosition"},
			{ ShaderDataType::Float2, "aTexCoord"}
			});
		Data->VA->AddVertexBuffer(VB);

		uint32_t SquareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Ref<IndexBuffer> IB;
		IB.reset(IndexBuffer::Create(SquareIndices, (sizeof(SquareIndices) / sizeof(uint32_t))));
		Data->VA->SetIndexBuffer(IB);

		Data->WhiteTexture = Texture2D::Create(1, 1);
		uint32_t WhiteTextureData = 0xffffffff;
		Data->WhiteTexture->SetData(&WhiteTextureData, sizeof(uint32_t));

		Data->TextureShader = Shader::Create("assets/shaders/Texture.glsl");
		Data->TextureShader->Bind();
		Data->TextureShader->SetInt("UTexture", 0);
	}

	void Renderer2D::Shutdown() {
		AYK_PROFILE_FUNCTION();

		delete Data;
	}

	void Renderer2D::BeginScene(const OrthographicCamera& Cam) {
		AYK_PROFILE_FUNCTION();

		Data->TextureShader->Bind();
		Data->TextureShader->SetMat4("uViewProjection", Cam.GetViewProjectionMatrix());
	}

	void Renderer2D::EndScene() {
		AYK_PROFILE_FUNCTION();
	}

	void Renderer2D::DrawQuad(const glm::vec2& Position, const glm::vec2 Size, const glm::vec4 Color) {
		DrawQuad({ Position.x, Position.y, 0.0f }, Size, Color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& Position, const glm::vec2 Size, const glm::vec4 Color) {
		AYK_PROFILE_FUNCTION();

		Data->TextureShader->SetFloat4("uColor", Color);
		Data->TextureShader->SetFloat("uTilingTexture", 1.0f);
		Data->WhiteTexture->Bind();

		glm::mat4 Transform = glm::translate(glm::mat4(1.0f), Position) * glm::scale(glm::mat4(1.0f), { Size.x, Size.y, 1.0f });
		Data->TextureShader->SetMat4("uTransform", Transform);

		Data->VA->Bind();
		RenderCommand::DrawIndexed(Data->VA);
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

		Data->TextureShader->Bind();

		Data->TextureShader->SetFloat4("uColor", TintColor);
		Data->TextureShader->SetFloat("uTilingFactor", TilingFactor);
		
		Texture->Bind();

		glm::mat4 Transform = glm::translate(glm::mat4(1.0f), Position) * glm::scale(glm::mat4(1.0f), { Size.x, Size.y, 1.0f });
		Data->TextureShader->SetMat4("uTransform", Transform);


		Data->VA->Bind();
		RenderCommand::DrawIndexed(Data->VA);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec2& Position, const glm::vec2 Size, const float Rotation, const glm::vec4 Color) {
		DrawRotatedQuad(glm::vec3(Position.x, Position.y, 0.0f), Size, Rotation, Color);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec3& Position, const glm::vec2 Size, const float Rotation, const glm::vec4 Color) {
		AYK_PROFILE_FUNCTION();

		Data->TextureShader->Bind();

		Data->TextureShader->SetFloat4("uColor", Color);
		Data->TextureShader->SetFloat("uTilingFactor", 1.0f);
		Data->WhiteTexture->Bind();

		glm::mat4 Transform = glm::translate(glm::mat4(1.0f), Position)
			* glm::rotate(glm::mat4(1.0f), Rotation, glm::vec3(0.0f, 0.0f, 1.0f))
			* glm::scale(glm::mat4(1.0f), { Size.x, Size.y, 1.0f });
		Data->TextureShader->SetMat4("uTransform", Transform);


		Data->VA->Bind();
		RenderCommand::DrawIndexed(Data->VA);
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

		Data->TextureShader->Bind();

		Data->TextureShader->SetFloat4("uColor", TintColor);
		Data->TextureShader->SetFloat("uTilingFactor", TilingFactor);

		Texture->Bind();

		glm::mat4 Transform = glm::translate(glm::mat4(1.0f), Position)
			* glm::rotate(glm::mat4(1.0f), Rotation, glm::vec3(0.0f, 0.0f, 1.0f))
			* glm::scale(glm::mat4(1.0f), { Size.x, Size.y, 1.0f });
		Data->TextureShader->SetMat4("uTransform", Transform);


		Data->VA->Bind();
		RenderCommand::DrawIndexed(Data->VA);
	}


}



