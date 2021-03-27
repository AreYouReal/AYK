#pragma once

#include "AYK.h"

namespace AYK {

	class EditorLayer : public Layer {
	public:
		EditorLayer();
		virtual ~EditorLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		void OnUpdate(Timestep Timestep) override;
		virtual void OnImGuiRender() override;
		void OnEvent(Event& E) override;


	private:

		OrthographicCameraController CameraController;

		Ref<AYK::VertexArray> VA;
		Ref<AYK::Shader> FlatColorShader;
		Ref<AYK::Texture2D> CheckerboardTexture;

		glm::vec4 SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };

		Ref<AYK::Framebuffer> Framebuff;

	};

}

