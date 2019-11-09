#pragma once

#include "Core.h"
#include "Window.h"
#include "AYK/LayerStack.h"
#include "AYK/Events/Event.h"
#include "AYK/Events/ApplicationEvent.h"

#include "AYK/ImGui/ImGuiLayer.h"

#include "AYK/Renderer/Shader.h"

namespace AYK {
	class AYK_API Application {
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& E);

		void PushLayer(Layer* LayerToPush);
		void PushOverlay(Layer* OverlayToPush);


		inline static Application& Get() { return(*Instance); }

		inline Window& GetWindow() { return(*WindowPtr); }

	private:
		//bool OnWindowClose(WindowCloseEvent& E);


		std::unique_ptr<Window> WindowPtr;
		ImGuiLayer* ImGuiLayerPtr;
		bool bRunning = true;
		LayerStack LStack;

		unsigned int VertexArray, VertexBuffer, IndexBuffer;

		std::unique_ptr<Shader> ShaderExample;


		static Application* Instance;
	};

}



