#include "aykpch.h"
#include "ImGuiLayer.h"

#include "imgui.h"
#include "Platform/OpenGL/IMGuiOpenGLRenderer.h"

#include "AYK/Application.h"


// TEMP
#include <GLFW/glfw3.h>
#include <glad/glad.h>


namespace AYK {

	ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer"){	}

	ImGuiLayer::~ImGuiLayer() {	}

	void ImGuiLayer::OnAttach() {
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGuiIO& IO = ImGui::GetIO();
		IO.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		IO.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		// TEMPORARY: should eventually use AYK key codes
		IO.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
		IO.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
		IO.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
		IO.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
		IO.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
		IO.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
		IO.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
		IO.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
		IO.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
		IO.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
		IO.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
		IO.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
		IO.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
		IO.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
		IO.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
		IO.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
		IO.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
		IO.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
		IO.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
		IO.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
		IO.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;
			   
		ImGui_ImplOpenGL3_Init("#version 410");
	}

	void ImGuiLayer::OnDetach()	{
		
	}

	void ImGuiLayer::OnUpdate() {

		ImGuiIO& IO = ImGui::GetIO();
		Application& AYKApp = Application::Get();
		IO.DisplaySize = ImVec2(AYKApp.GetWindow().GetWidth(), AYKApp.GetWindow().GetHeight());

		float CurrentTime = (float)glfwGetTime();
		IO.DeltaTime = Time > 0.0f ? (CurrentTime - Time) : (1.0f / 60.0f);
		Time = CurrentTime;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		static bool Show = true;
		ImGui::ShowDemoWindow(&Show);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void ImGuiLayer::OnEvent(Event& E){
		EventDispatcher Dispatcher(E);

		Dispatcher.Dispatch<MouseButtonPressedEvent>(AYK_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonPressedEvent));
		Dispatcher.Dispatch<MouseButtonReleasedEvent>(AYK_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonReleasedEvent));
		Dispatcher.Dispatch<MouseMovedEvent>(AYK_BIND_EVENT_FN(ImGuiLayer::OnMouseMovedEvent));
		Dispatcher.Dispatch<MouseScrolledEvent>(AYK_BIND_EVENT_FN(ImGuiLayer::OnMouseScrolledEvent));
		Dispatcher.Dispatch<KeyPressedEvent>(AYK_BIND_EVENT_FN(ImGuiLayer::OnKeyPressedEvent));
		Dispatcher.Dispatch<KeyReleaseEvent>(AYK_BIND_EVENT_FN(ImGuiLayer::OnKeyReleasedEvent));
		Dispatcher.Dispatch<KeyTypedEvent>(AYK_BIND_EVENT_FN(ImGuiLayer::OnKeyTypedEvent));
		Dispatcher.Dispatch<WindowResizeEvent>(AYK_BIND_EVENT_FN(ImGuiLayer::OnWindowResizedEvent));
	}

	bool ImGuiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent& E) {
		ImGuiIO& IO = ImGui::GetIO();
		IO.MouseDown[E.GetMouseButton()] = true;
		return(false);
	}

	bool ImGuiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& E) {
		ImGuiIO& IO = ImGui::GetIO();
		IO.MouseDown[E.GetMouseButton()] = false;
		return(false);
	}

	bool ImGuiLayer::OnMouseMovedEvent(MouseMovedEvent& E) {
		ImGuiIO& IO = ImGui::GetIO();
		IO.MousePos = ImVec2(E.GetX(), E.GetY());
		return(false);
	}

	bool ImGuiLayer::OnMouseScrolledEvent(MouseScrolledEvent& E) {
		ImGuiIO& IO = ImGui::GetIO();
		IO.MouseWheelH += E.GetXOffset();
		IO.MouseWheel += E.GetYOffset();
		return(false);
	}

	bool ImGuiLayer::OnKeyPressedEvent(KeyPressedEvent& E) {
		ImGuiIO& IO = ImGui::GetIO();
		IO.KeysDown[E.GetKeyCode()] = true;
		IO.KeyCtrl	= IO.KeysDown[GLFW_KEY_LEFT_CONTROL]|| IO.KeysDown[GLFW_KEY_RIGHT_CONTROL];
		IO.KeyShift = IO.KeysDown[GLFW_KEY_LEFT_SHIFT]	|| IO.KeysDown[GLFW_KEY_RIGHT_SHIFT];
		IO.KeyAlt	= IO.KeysDown[GLFW_KEY_LEFT_ALT]	|| IO.KeysDown[GLFW_KEY_RIGHT_ALT];
		IO.KeySuper = IO.KeysDown[GLFW_KEY_LEFT_SUPER]	|| IO.KeysDown[GLFW_KEY_RIGHT_SUPER];
		return(false);
	}

	bool ImGuiLayer::OnKeyReleasedEvent(KeyReleaseEvent& E) {
		ImGuiIO& IO = ImGui::GetIO();
		IO.KeysDown[E.GetKeyCode()] = false;
		return(false);
	}

	bool ImGuiLayer::OnKeyTypedEvent(KeyTypedEvent& E) {
		ImGuiIO& IO = ImGui::GetIO();
		int CharCode = E.GetKeyCode();
		if (CharCode > 0 && CharCode < 0x10000) {
			IO.AddInputCharacter((unsigned short)CharCode);
		}
		return(false);
	}

	bool ImGuiLayer::OnWindowResizedEvent(WindowResizeEvent& E) {
		ImGuiIO& IO = ImGui::GetIO();
		IO.DisplaySize = ImVec2(E.GetWidth(), E.GetHeight());
		IO.DisplayFramebufferScale = ImVec2(1, 1);
		glViewport(0, 0, E.GetWidth(), E.GetHeight());
		return(false);
	}

}