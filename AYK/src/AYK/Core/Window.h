#pragma once

#include "aykpch.h"

#include "AYK/Core/Base.h"
#include "AYK/Events/Event.h"


namespace AYK {
	
	struct WindowProps {
		std::string Title;
		uint32_t Width;
		uint32_t Height;

		WindowProps(const std::string& TitleToSet = "AYK Engine", unsigned int W = 1280, unsigned int H = 720)
		: Title(TitleToSet), Width(W), Height(H){ }

	};


	// Interface representing a desktop system based Window
	class AYK_API Window {
	
	public:
		using EventCallbackFunc = std::function<void(Event&)>;

		virtual ~Window() {}

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		// Window attributes
		virtual void SetEventCallback(const EventCallbackFunc& Callback) = 0;
		virtual void SetVSync(bool Enabled) = 0;
		virtual bool IsVSync() const = 0;

		virtual void* GetNativeWindow() const = 0;

		static Window* Create(const WindowProps& Props = WindowProps());


	};

}