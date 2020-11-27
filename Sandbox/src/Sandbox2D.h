#pragma once

#include "AYK.h"

#include "ParticleSystem.h"

class Sandbox2D : public AYK::Layer {
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(AYK::Timestep Timestep) override;
	virtual void OnImGuiRender() override;
	void OnEvent(AYK::Event& E) override;


private:

	AYK::OrthographicCameraController CameraController;

	AYK::Ref<AYK::VertexArray> VA;
	AYK::Ref<AYK::Shader> FlatColorShader;

	AYK::Ref<AYK::Texture2D> CheckerboardTexture;

	AYK::Ref<AYK::Texture2D> SpriteSheet;

	AYK::Ref<AYK::SubTexture2D> StairsTexture;


	glm::vec4 SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };

	ParticleProps Particle;
	ParticleSystem PSystem;
};