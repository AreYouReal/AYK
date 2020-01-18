#pragma once

#include "AYK/Core/Input.h"

namespace AYK {

	class WindowsInput : public Input {

	protected:
		virtual bool IskeyPressedImpl(int Keycode) override;
		virtual bool IsMouseButtonPressedImpl(int Button) override;
		virtual float GetMouseXImpl() override;
		virtual float GetMouseYImpl() override;
		virtual std::pair<float, float> GetMousePositionImpl() override;
	};

}



