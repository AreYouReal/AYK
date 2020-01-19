#include <AYK.h>
#include <AYK/Core/EntryPoint.h>

#include "Platform/OpenGL/OpenGLShader.h" 

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Sandbox2D.h"

class ExampleLayer : public AYK::Layer {

public:
	ExampleLayer() : Layer("Example"), CameraController(1280.0f / 720.0f, true), SquarePosition(0.0f){
		// Generate VA -> Triangle
		TriangleVA = AYK::VertexArray::Create();
		TriangleVA->Bind();

		float TriangleVertices[3 * 7] = {
			-.5f, -.5f, .0f, 1.0f, .0f, .0f, 1.0f,
			.5f, -.5f, .0f, .0f, 1.0f, .0f, 1.0f,
			.0f, .5f, .0f, .0f, .0f, 1.0f, 1.0f
		};
		AYK::Ref<AYK::VertexBuffer> TriangleVB;
		TriangleVB.reset(AYK::VertexBuffer::Create(TriangleVertices, sizeof(TriangleVertices)));

		AYK::BufferLayout BLayout = {
			{ AYK::ShaderDataType::Float3, "aPosition", true},
			{ AYK::ShaderDataType::Float4, "aColor", false}
		};
		TriangleVB->SetLayout(BLayout);
		TriangleVA->AddVertexBuffer(TriangleVB);

		uint32_t TriangleIndices[3] = { 0, 1, 2 };
		AYK::Ref<AYK::IndexBuffer> TriangleIB;
		TriangleIB.reset(AYK::IndexBuffer::Create(TriangleIndices, (sizeof(TriangleIndices) / sizeof(uint32_t))));
		TriangleVA->SetIndexBuffer(TriangleIB);

		// Generate VA - Square
		SquareVA = AYK::VertexArray::Create();

		float SquareVertices[5 * 4] = {
			-.5f, -.5f, .0f, 0.0f, 0.0f,
			 .5f, -.5f, .0f, 1.0f, 0.0f,
			 .5f,  .5f, .0f, 1.0f, 1.0f,
			-.5f,  .5f, .0f, 0.0f, 1.0f
		};

		AYK::Ref<AYK::VertexBuffer> SquareVB;
		SquareVB.reset(AYK::VertexBuffer::Create(SquareVertices, sizeof(SquareVertices)));
		SquareVB->SetLayout({ { AYK::ShaderDataType::Float3, "aPosition"},
			{ AYK::ShaderDataType::Float2, "aTexCoord"} });
		SquareVA->AddVertexBuffer(SquareVB);

		uint32_t SquareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		AYK::Ref<AYK::IndexBuffer> SquareIB;
		SquareIB.reset(AYK::IndexBuffer::Create(SquareIndices, (sizeof(SquareIndices) / sizeof(uint32_t))));
		SquareVA->SetIndexBuffer(SquareIB);

		std::string VertexShaderSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 aPosition;
			layout(location = 1) in vec4 aColor;

			uniform mat4 uViewProjection;
			uniform mat4 uTransform;

			out vec4 vColor;


			void main(){
				gl_Position = uViewProjection * uTransform * vec4(aPosition, 1.0);
				vColor = aColor;
			}
		)";

		std::string FragmentSahderSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 oColor;

			in vec4 vColor;

			void main(){
				oColor = vColor;
			}
		)";

		TriangleShader = (AYK::Shader::Create("VertexPosColor", VertexShaderSrc, FragmentSahderSrc));

		std::string FlatColorShaderVertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 aPosition;

			uniform mat4 uViewProjection;
			uniform mat4 uTransform;

			void main(){
				gl_Position = uViewProjection * uTransform * vec4(aPosition, 1.0);
			}
		)";

		std::string FlatColorShaderFragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 oColor;

			uniform vec3 uColor;

			void main(){
				oColor = vec4( uColor, 1.0 );
			}
		)";

		FlatColorShader = (AYK::Shader::Create("FlatColor", FlatColorShaderVertexSrc, FlatColorShaderFragmentSrc));


		auto TextureShader = AllShaders.Load("assets/shaders/Texture.glsl");
	
		Texture = AYK::Texture2D::Create("assets/textures/checkerboard.png");
		ChernoLogoTexture = AYK::Texture2D::Create("assets/textures/ChernoLogo.png");

		std::dynamic_pointer_cast<AYK::OpenGLShader>(TextureShader)->Bind();
		std::dynamic_pointer_cast<AYK::OpenGLShader>(TextureShader)->UploadUniformInt("uTexture", 0);
	}

	void OnUpdate(AYK::Timestep Timestep) override {

		CameraController.OnUpdate(Timestep);

		//AYK_TRACE("Delta time: {0}s  {1}ms", Timestep.GetSeconds(), Timestep.GetMilliseconds());


		AYK::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		AYK::RenderCommand::Clear();

		AYK::Renderer::BeginScene(CameraController.GetCamera());

		static glm::mat4 Scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		std::dynamic_pointer_cast<AYK::OpenGLShader>(FlatColorShader)->Bind();
		std::dynamic_pointer_cast<AYK::OpenGLShader>(FlatColorShader)->UploadUniformFloat3("uColor", SquareColor);

		for (int y = 0; y < 10; ++y) {
			for (int x = 0; x < 10; ++x) {
				SquarePosition = glm::vec3(0.11f * x, y * 0.11f, 0.0f);
				glm::mat4 SquareTransform = glm::translate(glm::mat4(1.0f), SquarePosition);				
				AYK::Renderer::Submit(FlatColorShader, SquareVA, SquareTransform * Scale);
			}
		}
		Texture->Bind();
		
		auto TextureShader = AllShaders.Get("Texture");
		
		AYK::Renderer::Submit(TextureShader, SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		ChernoLogoTexture->Bind();
		AYK::Renderer::Submit(TextureShader, SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		// Triangle
		//AYK::Renderer::Submit(TriangleShader, TriangleVA);

		AYK::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override {	
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(SquareColor));
		ImGui::End();
	}

	void OnEvent(AYK::Event& E) override {
		CameraController.OnEvent(E);
	}

private:

	AYK::ShaderLibrary AllShaders;

	AYK::Ref<AYK::Shader> TriangleShader;
	AYK::Ref<AYK::VertexArray> TriangleVA;

	AYK::Ref<AYK::Shader> FlatColorShader;
	AYK::Ref<AYK::VertexArray> SquareVA;

	AYK::Ref<AYK::Texture2D> Texture, ChernoLogoTexture;

	AYK::OrthographicCameraController CameraController;

	glm::vec3 SquarePosition;
	float SquareSpeed = 1.0f;

	glm::vec3 SquareColor = {0.2f, 0.3f, 0.8f};
};

class Sandbox : public AYK::Application {

public:

	Sandbox() {
		//PushLayer(new ExampleLayer());
		PushLayer(new Sandbox2D());
	}

	~Sandbox() {
	
	}


};

AYK::Application* CreateApplication() {
	return(new Sandbox());
}