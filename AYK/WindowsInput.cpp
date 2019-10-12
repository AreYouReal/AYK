#include "aykpch.h"
#include "WindowsInput.h"

#include "AYK/Application.h"
#include "GLFW/glfw3.h"

namespace AYK {

	Input* Input::Instance = new WindowsInput();

	bool WindowsInput::IskeyPressedImpl(int Keycode){
		GLFWwindow* Wnd = static_cast<GLFWwindow*>( Application::Get().GetWindow().GetNativeWindow() );
		int State = glfwGetKey(Wnd, Keycode);
		return(State == GLFW_PRESS || State == GLFW_REPEAT);
	}

	bool WindowsInput::IsMouseButtonPressedImpl(int Button)	{
		GLFWwindow* Wnd = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		int State = glfwGetMouseButton(Wnd, Button);
		return(State == GLFW_PRESS);
	}

	float WindowsInput::GetMouseXImpl()	{
		auto [X, Y] = GetMousePositionImpl();
		return(X);
	}

	float WindowsInput::GetMouseYImpl()	{
		auto [X, Y] = GetMousePositionImpl();
		return(Y);
	}

	std::pair<float, float> WindowsInput::GetMousePositionImpl(){
		GLFWwindow* Wnd = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double X, Y;
		glfwGetCursorPos(Wnd, &X, &Y);
		return{ X, Y };
	}

}