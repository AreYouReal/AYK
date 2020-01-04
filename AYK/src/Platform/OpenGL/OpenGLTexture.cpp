#include "aykpch.h"
#include "OpenGLTexture.h"

#include "stb_image.h"

#include <glad/glad.h>

namespace AYK {

	OpenGLTexture2D::OpenGLTexture2D(const std::string& Path) : FilePath(Path) {
		int W, H, Channels;
		stbi_set_flip_vertically_on_load(1);
		stbi_uc* data = stbi_load(Path.c_str(), &W, &H, &Channels, 0);
		AYK_CORE_ASSERT(data, "Failed to load image!");
		Width = W;
		Height = H;

		GLenum InternalFormat = 0;
		GLenum DataFormat = 0;
		if (Channels == 4) {
			InternalFormat = GL_RGBA8;
			DataFormat = GL_RGBA;
		} else if (Channels == 3) {
			InternalFormat = GL_RGB8;
			DataFormat = GL_RGB;
		}

		AYK_CORE_ASSERT(InternalFormat & DataFormat, "Format not supported!" );

		glCreateTextures(GL_TEXTURE_2D, 1, &RendererID);
		glTextureStorage2D(RendererID, 1, InternalFormat, Width, Height);

		glTextureParameteri(RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureSubImage2D(RendererID, 0, 0, 0, Width, Height, DataFormat, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);
	}

	OpenGLTexture2D::~OpenGLTexture2D() {
		glDeleteTextures(1, &RendererID);
	}

	void OpenGLTexture2D::Bind(uint32_t Slot) const {
		glBindTextureUnit(Slot, RendererID);
	}

}



