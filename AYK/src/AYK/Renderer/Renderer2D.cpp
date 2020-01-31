#include "aykpch.h"
#include "Renderer2D.h"

#include "VertexArray.h"
#include "Shader.h"

#include "RenderCommand.h"

#include <glm/gtc/matrix_transform.hpp>

namespace AYK {

	struct Renderer2DStorage {
		Ref<VertexArray> VA;
		Ref<Shader> FlatShader;
	};

	static Renderer2DStorage* Data;

	void Renderer2D::Init() {

		Data = new Renderer2DStorage();

		Data->VA = VertexArray::Create();

		float SquareVertices[5 * 4] = {
			-.5f, -.5f, .0f,
			 .5f, -.5f, .0f,
			 .5f,  .5f, .0f,
			-.5f,  .5f, .0f
		};

		Ref<VertexBuffer> VB;
		VB.reset(VertexBuffer::Create(SquareVertices, sizeof(SquareVertices)));
		VB->SetLayout({ { ShaderDataType::Float3, "aPosition"} });
		Data->VA->AddVertexBuffer(VB);

		uint32_t SquareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Ref<IndexBuffer> IB;
		IB.reset(IndexBuffer::Create(SquareIndices, (sizeof(SquareIndices) / sizeof(uint32_t))));
		Data->VA->SetIndexBuffer(IB);

		Data->FlatShader = (Shader::Create("assets/shaders/FlatColor.glsl"));
	}

	void Renderer2D::Shutdown() {
		delete Data;
	}

	void Renderer2D::BeginScene(const OrthographicCamera& Cam) {
		Data->FlatShader->Bind();
		Data->FlatShader->SetMat4("uViewProjection", Cam.GetViewProjectionMatrix());
	}

	void Renderer2D::EndScene() {

	}

	void Renderer2D::DrawQuad(const glm::vec2& Position, const glm::vec2 Size, const glm::vec4 Color) {
		DrawQuad({ Position.x, Position.y, 0.0f }, Size, Color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& Position, const glm::vec2 Size, const glm::vec4 Color) {
		Data->FlatShader->Bind();
		Data->FlatShader->SetFloat4("uColor", Color);
		
		
		glm::mat4 Transform = glm::translate(glm::mat4(1.0f), Position) * glm::scale(glm::mat4(1.0f), { Size.x, Size.y, 1.0f });
		Data->FlatShader->SetMat4("uTransform", Transform);


		Data->VA->Bind();
		RenderCommand::DrawIndexed(Data->VA);
	}

}



