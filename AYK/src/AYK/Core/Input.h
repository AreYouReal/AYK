#pragma once

#include "AYK/Core/Core.h"

namespace AYK {

	class AYK_API Input{
		
	public:
		inline static bool IsKeyPressed(int Keycode) { return(Instance->IskeyPressedImpl(Keycode)); }
		inline static bool IsMouseButtonPressed(int Button) { return(Instance->IsMouseButtonPressedImpl(Button)); }
		inline static std::pair<float, float> GetMousePosition() { return(Instance->GetMousePositionImpl()); }
		inline static float GetMouseX() { return(Instance->GetMouseXImpl()); }
		inline static float GetMouseY() { return(Instance->GetMouseYImpl()); }

	protected:
		virtual bool IskeyPressedImpl(int Keycode) = 0;
		virtual bool IsMouseButtonPressedImpl(int Button) = 0;
		virtual std::pair<float, float> GetMousePositionImpl() = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;
	
	private:
		static Input* Instance;



	};

}
