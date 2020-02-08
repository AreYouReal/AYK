#pragma once

#include "OrthographicCamera.h"
#include "Texture.h"

namespace AYK {

	class Renderer2D {
	public:

		static void Init();
		static void Shutdown();

		static void BeginScene(const OrthographicCamera& Cam);
		static void EndScene();

		// Primitives
		static void DrawQuad(const glm::vec2& Position, const glm::vec2 Size, const glm::vec4 Color);
		static void DrawQuad(const glm::vec3& Position, const glm::vec2 Size, const glm::vec4 Color);

		static void DrawQuad(const glm::vec2& Position, const glm::vec2 Size, const Ref<Texture2D>& Texture, float TilingFactor = 1.0f, const glm::vec4& TintColor = glm::vec4(1.0f));
		static void DrawQuad(const glm::vec3& Position, const glm::vec2 Size, const Ref<Texture2D>& Texture, float TilingFactor = 1.0f, const glm::vec4& TintColor = glm::vec4(1.0f));

		static void DrawRotatedQuad(const glm::vec2& Position, const glm::vec2 Size, const float Rotation, const glm::vec4 Color);
		static void DrawRotatedQuad(const glm::vec3& Position, const glm::vec2 Size, const float Rotation, const glm::vec4 Color);

		static void DrawRotatedQuad(const glm::vec2& Position, const glm::vec2 Size, const float Rotation, const Ref<Texture2D>& Texture, float TilingFactor = 1.0f, const glm::vec4& TintColor = glm::vec4(1.0f));
		static void DrawRotatedQuad(const glm::vec3& Position, const glm::vec2 Size, const float Rotation, const Ref<Texture2D>& Texture, float TilingFactor = 1.0f, const glm::vec4& TintColor = glm::vec4(1.0f));

	};


}