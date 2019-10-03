#pragma once 

#include "AYK/Layer.h"

namespace AYK {

	class AYK_API ImGuiLayer : public Layer {
		
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach();
		void OnDetach();
		void OnUpdate();
		void OnEvent(Event& E);

	private:

		float Time;
	};

}