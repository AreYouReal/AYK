#include "aykpch.h"
#include "OpenGLTexture.h"

#include "stb_image.h"

#include <glad/glad.h>

namespace AYK {

	OpenGLTexture2D::OpenGLTexture2D(const std::string& Path) : FilePath(Path) {
		int W, H, Channels;
		stbi_uc* data = stbi_load(Path.c_str(), &W, &H, &Channels, 0);
		AYK_CORE_ASSERT(data, "Failed to load image!");
		Width = W;
		Height = H;

		glCreateTextures(GL_TEXTURE_2D, 1, &RendererID);
		glTextureStorage2D(RendererID, 1, GL_RGB8, Width, Height);

		glTexParameteri(RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(RendererID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTextureSubImage2D(RendererID, 0, 0, 0, Width, Height, GL_RGB, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);
	}

	OpenGLTexture2D::~OpenGLTexture2D() {
		glDeleteTextures(1, &RendererID);
	}

	void OpenGLTexture2D::Bind(uint32_t Slot) const {
		glBindTextureUnit(Slot, RendererID);
	}

}



