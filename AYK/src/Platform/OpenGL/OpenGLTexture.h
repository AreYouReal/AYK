#pragma once

#include "AYK/Renderer/Texture.h"

namespace AYK {

	class OpenGLTexture2D : public Texture2D {
	public:
		OpenGLTexture2D(const std::string& Path);
		virtual ~OpenGLTexture2D();

		virtual uint32_t GetWidth() const override { return(Width); }
		virtual uint32_t GetHeight() const override { return(Height); }

		virtual void Bind(uint32_t Slot = 0) const override;

	private:

		std::string	FilePath;
		uint32_t	Width;
		uint32_t	Height;
		uint32_t	RendererID;

	};

}