#include "AYK/Window.h"

#include "GLFW/glfw3.h"

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

	private:
		virtual void Init(const WindowProps& PropsToSet);
		virtual void Shutdown();
	private:
		GLFWwindow* WindowHandle;

		struct WindowData {
			std::string Title;
			unsigned int Widht, Height;
			bool bVSync;
			EventCallbackFunc EventCallback;
		};

		WindowData WData;
	};


}