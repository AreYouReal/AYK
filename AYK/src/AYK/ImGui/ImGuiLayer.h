#pragma once 

#include "AYK/Layer.h"
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
		virtual void OnImGuiRender() override;
		
		void Begin();
		void End();

	private:

		float Time;

	};

}