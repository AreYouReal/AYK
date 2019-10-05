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

		void OnAttach();
		void OnDetach();
		void OnUpdate();
		void OnEvent(Event& E);

	private:

		float Time;

	private:

		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& E);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& E);
		bool OnMouseMovedEvent(MouseMovedEvent& E);
		bool OnMouseScrolledEvent(MouseScrolledEvent& E);
		bool OnKeyPressedEvent(KeyPressedEvent& E);
		bool OnKeyReleasedEvent(KeyReleaseEvent& E);
		bool OnKeyTypedEvent(KeyTypedEvent& E);
		bool OnWindowResizedEvent(WindowResizeEvent& E);

	};

}