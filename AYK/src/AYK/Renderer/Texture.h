#pragma once

#include "AYK/Core/Base.h"
#include <string>

namespace AYK {

	class Texture {
	public:
		virtual ~Texture() = default;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;
		virtual uint32_t GetRendererID() const = 0;

		virtual void SetData(void* Data, uint32_t Size) = 0;

		virtual void Bind(uint32_t Slot = 0) const = 0;

		virtual bool operator==(const Texture& Other) const = 0;

	};


	class Texture2D : public Texture {
	public:
		static Ref<Texture2D> Create(uint32_t Width, uint32_t Height);
		static Ref<Texture2D> Create(const std::string& Path);

		

	};




}