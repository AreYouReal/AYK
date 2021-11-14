#include "aykpch.h"
#include "AYK/Core/Input.h"

#include "AYK/Core/Application.h"
#include "GLFW/glfw3.h"

namespace AYK {

	bool Input::IsKeyPressed(int Keycode){
		GLFWwindow* Wnd = static_cast<GLFWwindow*>( Application::Get().GetWindow().GetNativeWindow() );
		int State = glfwGetKey(Wnd, Keycode);
		return(State == GLFW_PRESS || State == GLFW_REPEAT);
	}

	bool Input::IsMouseButtonPressed(int Button)	{
		GLFWwindow* Wnd = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		int State = glfwGetMouseButton(Wnd, Button);
		return(State == GLFW_PRESS);
	}

	float Input::GetMouseX()	{
		auto [X, Y] = GetMousePosition();
		return(X);
	}

	float Input::GetMouseY()	{
		auto [X, Y] = GetMousePosition();
		return(Y);
	}

	std::pair<float, float> Input::GetMousePosition(){
		GLFWwindow* Wnd = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double X, Y;
		glfwGetCursorPos(Wnd, &X, &Y);
		return{ (float)X, (float)Y };
	}

}