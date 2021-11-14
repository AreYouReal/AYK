#pragma once

#include "AYK/Core/Base.h"

namespace AYK {

	class AYK_API Input{
		
	public:
		static bool IsKeyPressed(int Keycode);
		static bool IsMouseButtonPressed(int Button);
		static std::pair<float, float> GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();

	};

}
