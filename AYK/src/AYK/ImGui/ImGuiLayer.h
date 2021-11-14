#pragma once 

#include "AYK/Core/Layer.h"
#include <AYK/Events/KeyEvent.h>
#include <AYK/Events/MouseEvent.h>
#include "AYK/Events/ApplicationEvent.h"

namespace AYK {

	class AYK_API ImGuiLayer : public Layer {
		
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnEvent(Event& e) override;
		
		void Begin();
		void End();

		void SetBlockEvent(bool bNewValue) { bBlockEvents = bNewValue; }

	private:

		bool bBlockEvents = true;

		float Time;

	};

}