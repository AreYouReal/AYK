#include "aykpch.h"
#include "Sandbox2D.h"

#include "imgui/imgui.h"

#include <glm/gtc/type_ptr.hpp>

static const uint32_t SMapWidth = 24; 
static const char* MapTiles =
"WWWWWWWWWWWWWWWWWWWWWWWW"
"WWWWWWWWWWWWWWWWWWWWWWWW"
"WWWWWWWWWWWDDDDWWWWWWWWW"
"WWWWWWWWDDDWWWDDWWWWWWWW"
"WWWWWWDDDDDWWWDDWWWWWWWW"
"WWWWWDDDDDDWWWWWDDWWWWWW"
"WWWWDWWWWWXXDDDDDDWWWWWW"
"WWWDWWWWDDDDDDDDWWWWWWWW"
"WWWWDDDDDDDDDDDDWWWWWWWW"
"WWWWWWWDDDDDDDDWWWWWWWWW"
"WWWWWWWWWDDDDDWWWWWWWWWW"
"WWWWWWWWWWWDDWWWWWWWWWWW"
"WWWWWWWWWWWDDWWWWWWWWWWW"
"WWWWWWWWWWWWWWWWWWWWWWWW";

Sandbox2D::Sandbox2D() : Layer("Sandbox2D"), CameraController(1280.0f / 720.0f){ }

void Sandbox2D::OnAttach() {
	AYK_PROFILE_FUNCTION();

	CheckerboardTexture = AYK::Texture2D::Create("assets/textures/checkerboard.png");

	SpriteSheet = AYK::Texture2D::Create("assets/game/textures/RPGpack_sheet_2X.png");

	StairsTexture = AYK::SubTexture2D::CreateFromCoords(SpriteSheet, { 0, 11 }, {128, 128});

	MapWidth = SMapWidth;
	MapHeight = strlen(MapTiles) / MapWidth;

	TextureMap['D'] = AYK::SubTexture2D::CreateFromCoords(SpriteSheet, { 6, 11 }, { 128, 128 });
	TextureMap['W'] = AYK::SubTexture2D::CreateFromCoords(SpriteSheet, { 11, 11 }, { 128, 128 });

	Particle.ColorBegin = { 254/255.0f, 212 / 255.0f, 123 / 255.0f, 1.0f };
	Particle.ColorEnd = { 254 / 255.0f, 109 / 255.0f, 41 / 255.0f, 1.0f };
	Particle.SizeBegin = 0.5f;
	Particle.SizeVariation = 0.3f;
	Particle.SizeEnd = 0.0f;
	Particle.Velocity = { 0.0f, 0.0f };
	Particle.VelocityVariation = { 3.0f, 1.0f };
	Particle.Position = { 0.0f, 0.0f };

	CameraController.SetZoomLevel(5.0f);
}

void Sandbox2D::OnDetach() {
	AYK_PROFILE_FUNCTION();
}

void Sandbox2D::OnUpdate(AYK::Timestep Timestep) {

	AYK_PROFILE_FUNCTION();

	CameraController.OnUpdate(Timestep);

	AYK::Renderer2D::ResetStats();

	{
		AYK_PROFILE_SCOPE("Render Prep");

		AYK::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		AYK::RenderCommand::Clear();
	}




	if (AYK::Input::IsMouseButtonPressed(AYK_MOUSE_BUTTON_LEFT)) {
		auto [x, y] = AYK::Input::GetMousePosition();
		auto Width = AYK::Application::Get().GetWindow().GetWidth();
		auto Height = AYK::Application::Get().GetWindow().GetHeight();

		auto Bounds = CameraController.GetBounds();
		auto Pos = CameraController.GetCamera().GetPosition();
		x = (x / Width) * Bounds.GetWight() - Bounds.GetWight() * 0.5f;
		y = Bounds.GetHeight() * 0.5f - (y / Height) * Bounds.GetHeight();
		Particle.Position = { x + Pos.x, y + Pos.y };
		
		for (int i = 0; i < 50; ++i) {
			PSystem.Emit(Particle);
		}

	}

	PSystem.OnUpdate(Timestep);
	PSystem.OnRender(CameraController.GetCamera());

	AYK::Renderer2D::BeginScene(CameraController.GetCamera());


	for (uint32_t y = 0; y < MapHeight; ++y) {
		for (uint32_t x = 0; x < MapWidth; ++x) {
			char TileType = MapTiles[x + y * MapWidth];
			AYK::Ref<AYK::SubTexture2D> Texture;
			if (TextureMap.find(TileType) != TextureMap.end()) {
				Texture = TextureMap[TileType];
			} else {
				Texture = StairsTexture;
			}
			AYK::Renderer2D::DrawQuad({x - MapWidth / 2.0f, y - MapHeight/2.0f, 0.5f }, { 1.0f, 1.0f }, Texture);
		}
	}
	AYK::Renderer2D::EndScene();

}

void Sandbox2D::OnImGuiRender() {

	ImGui::Begin("Settings");

	auto stats = AYK::Renderer2D::GetStats();
	ImGui::Text("Renderer2D Stats:");
	ImGui::Text("Draw Calls: %d", stats.DrawCalls);
	ImGui::Text("Quads: %d", stats.QuadCount);
	ImGui::Text("Vertices: %d", stats.GetTotalVErtexCount());
	ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

	ImGui::ColorEdit4("Square Color", glm::value_ptr(SquareColor));

	ImGui::End();
	


}

void Sandbox2D::OnEvent(AYK::Event& E) {
	CameraController.OnEvent(E);
}

