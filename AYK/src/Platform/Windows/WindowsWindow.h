#include "AYK/Core/Window.h"
#include "AYK/Renderer/GraphicsContext.h"

#include <GLFW/glfw3.h>

namespace AYK {

	class WindowsWindow : public Window {

	public:
		WindowsWindow(const WindowProps& Props);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return(WData.Widht); }
		inline unsigned int GetHeight() const override { return(WData.Height); }

		// Window attribute
		inline void SetEventCallback(const EventCallbackFunc& Callback) override { WData.EventCallback = Callback; }

		void SetVSync(bool Enabled) override;
		bool IsVSync() const override;

		inline virtual void* GetNativeWindow() const { return(WindowHandle); }

	private:
		virtual void Init(const WindowProps& PropsToSet);
		virtual void Shutdown();
	private:
		GLFWwindow* WindowHandle;

		GraphicsContext* GContext;

		struct WindowData {
			std::string Title;
			unsigned int Widht, Height;
			bool bVSync;
			EventCallbackFunc EventCallback;
		};

		WindowData WData;
	};


}