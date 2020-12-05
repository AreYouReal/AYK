#pragma once

#include <glm/glm.hpp>

#include "Texture.h"

namespace AYK {

	class SubTexture2D {

	public:
		SubTexture2D(const Ref<Texture2D>& Tex, const glm::vec2& Min, const glm::vec2& Max);

		const Ref<Texture2D> GetTexture() const { return(Tex); }
		const glm::vec2* GetTexCoords() const { return(TexCoords); }

		static Ref<SubTexture2D> CreateFromCoords(const Ref<Texture2D>& Tex, const glm::vec2& Coords, const glm::vec2& CellSize, const glm::vec2& SpriteSize = {1, 1});

	private:

		Ref<Texture2D> Tex;
		glm::vec2 TexCoords[4];

	};

}