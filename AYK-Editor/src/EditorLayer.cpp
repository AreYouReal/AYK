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


	AYK::FramebufferSpecification FBSpec;
	FBSpec.Width = 1280;
	FBSpec.Height = 720;
	Framebuff = AYK::Framebuffer::Create(FBSpec);
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

		Framebuff->Bind();

		AYK::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		AYK::RenderCommand::Clear();
	}

	//{

	//	float static Rotation = 0.0f;
	//	Rotation += Timestep * 3.0f;

	//	AYK_PROFILE_SCOPE("Render Draw");
	//	AYK::Renderer2D::BeginScene(CameraController.GetCamera());

	//	AYK::Renderer2D::DrawRotatedQuad({ 1.0f, 0.0f }, { 0.8f, 0.8f }, glm::radians(-45.0f), { 0.8f, 0.2f, 0.3f, 1.0f });

	//	AYK::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { .8f, .8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
	//	AYK::Renderer2D::DrawQuad({ .5f, -0.5f }, { .5f, .75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
	//	AYK::Renderer2D::DrawRotatedQuad({-2.0f, 0.0f, -0.1f}, {10.0f, 10.0f}, Rotation, CheckerboardTexture, 10.0f);

	//	AYK::Renderer2D::EndScene();

	//	AYK::Renderer2D::BeginScene(CameraController.GetCamera());
	//	for (float y = -5.0f; y < 5.0f; y += 0.5f) {
	//		for (float x = -5.0f; x < 5.0f; x += 0.5f) {
	//			glm::vec4 color = { (x + 5.0f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f, .5f};
	//			AYK::Renderer2D::DrawQuad({ x, y }, { 0.45f, 0.45f }, color);
	//		}
	//	}
	//	AYK::Renderer2D::EndScene();

	//}


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
	Framebuff->Unbind();

}

void Sandbox2D::OnImGuiRender() {


	// Note: Switch this to true to enable dockspace
	static bool dockingEnabled = false;
	if (dockingEnabled)
	{
		static bool dockspaceOpen = true;
		static bool opt_fullscreen_persistant = true;
		bool opt_fullscreen = opt_fullscreen_persistant;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

		// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
		// because it would be confusing to have two docking targets within each others.
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (opt_fullscreen)
		{
			ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->Pos);
			ImGui::SetNextWindowSize(viewport->Size);
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}

		// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background and handle the pass-thru hole, so we ask Begin() to not render a background.
		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;

		// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
		// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive, 
		// all active windows docked into it will lose their parent and become undocked.
		// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise 
		// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
		ImGui::PopStyleVar();

		if (opt_fullscreen)
			ImGui::PopStyleVar(2);

		// DockSpace
		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				// Disabling fullscreen would allow the window to be moved to the front of other windows, 
				// which we can't undo at the moment without finer window depth/z control.
				//ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen_persistant);

				if (ImGui::MenuItem("Exit")) AYK::Application::Get().Close();
				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}

		ImGui::Begin("Settings");

		auto stats = AYK::Renderer2D::GetStats();
		ImGui::Text("Renderer2D Stats:");
		ImGui::Text("Draw Calls: %d", stats.DrawCalls);
		ImGui::Text("Quads: %d", stats.QuadCount);
		ImGui::Text("Vertices: %d", stats.GetTotalVErtexCount());
		ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

		ImGui::ColorEdit4("Square Color", glm::value_ptr(SquareColor));

		uint32_t textureID = Framebuff->GetColorAttachmentRendererID();
		ImGui::Image((void*)textureID, ImVec2{ 256.0f, 256.0f });
		ImGui::End();

		ImGui::End();
	}
	else
	{
		ImGui::Begin("Settings");

		auto stats = AYK::Renderer2D::GetStats();
		ImGui::Text("Renderer2D Stats:");
		ImGui::Text("Draw Calls: %d", stats.DrawCalls);
		ImGui::Text("Quads: %d", stats.QuadCount);
		ImGui::Text("Vertices: %d", stats.GetTotalVErtexCount());
		ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

		ImGui::ColorEdit4("Square Color", glm::value_ptr(SquareColor));

		uint32_t textureID = Framebuff->GetColorAttachmentRendererID();
		ImGui::Image((void*)textureID, ImVec2{ 256.0f, 256.0f });
		ImGui::End();
	}


}

void Sandbox2D::OnEvent(AYK::Event& E) {
	CameraController.OnEvent(E);
}

