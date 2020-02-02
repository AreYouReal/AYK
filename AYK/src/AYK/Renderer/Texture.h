#pragma once

#include "AYK/Core/Core.h"
#include <string>

namespace AYK {

	class Texture {
	public:
		virtual ~Texture() = default;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		virtual void Bind(uint32_t Slot = 0) const = 0;

	};


	class Texture2D : public Texture {
	public:
		static Ref<Texture2D> Create(uint32_t Width, uint32_t Height);
		static Ref<Texture2D> Create(const std::string& Path);

	};




}