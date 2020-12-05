#include "aykpch.h"
#include "SubTexture2D.h"

namespace AYK {


	SubTexture2D::SubTexture2D(const Ref<Texture2D>& Tex, const glm::vec2& Min, const glm::vec2& Max) : Tex(Tex) {
		TexCoords[0] = { Min.x, Min.y };
		TexCoords[1] = { Max.x, Min.y };
		TexCoords[2] = { Max.x, Max.y };
		TexCoords[3] = { Min.x, Max.y };
	}


	Ref<SubTexture2D> SubTexture2D::CreateFromCoords(const Ref<Texture2D>& Tex, const glm::vec2& Coords, const glm::vec2& CellSize, const glm::vec2& SpriteSize) {
		glm::vec2 Min = { (Coords.x * CellSize.x) / Tex->GetWidth(), (Coords.y * CellSize.y) / Tex->GetHeight() };
		glm::vec2 Max = { ((Coords.x + SpriteSize.x) * CellSize.x) / Tex->GetWidth(), ((Coords.y + SpriteSize.y) * CellSize.y) / Tex->GetHeight() };
		return( CreateRef<SubTexture2D>(Tex, Min, Max));
	}

}