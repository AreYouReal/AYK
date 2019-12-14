#include "AYK.h"

#include "imgui/imgui.h"

class ExampleLayer : public AYK::Layer {

public:
	ExampleLayer() : Layer("Example"), Camera(-1.6f, 1.6f, -.9f, .9f), CameraPosition(0.0f){
		// Generate VA -> Triangle
		TriangleVA.reset(AYK::VertexArray::Create());
		TriangleVA->Bind();

		float TriangleVertices[3 * 7] = {
			-.5f, -.5f, .0f, 1.0f, .0f, .0f, 1.0f,
			.5f, -.5f, .0f, .0f, 1.0f, .0f, 1.0f,
			.0f, .5f, .0f, .0f, .0f, 1.0f, 1.0f
		};
		std::shared_ptr<AYK::VertexBuffer> TriangleVB;
		TriangleVB.reset(AYK::VertexBuffer::Create(TriangleVertices, sizeof(TriangleVertices)));

		AYK::BufferLayout BLayout = {
			{ AYK::ShaderDataType::Float3, "aPosition", true},
			{ AYK::ShaderDataType::Float4, "aColor", false}
		};
		TriangleVB->SetLayout(BLayout);
		TriangleVA->AddVertexBuffer(TriangleVB);

		uint32_t TriangleIndices[3] = { 0, 1, 2 };
		std::shared_ptr<AYK::IndexBuffer> TriangleIB;
		TriangleIB.reset(AYK::IndexBuffer::Create(TriangleIndices, (sizeof(TriangleIndices) / sizeof(uint32_t))));
		TriangleVA->SetIndexBuffer(TriangleIB);

		// Generate VA - Square
		SquareVA.reset(AYK::VertexArray::Create());

		float SquareVertices[3 * 4] = {
			-.75f, -.75f, .0f,
			.75f, -.75f, .0f,
			.75f, .75f, .0f,
			-.75f, .75f, .0f
		};

		std::shared_ptr<AYK::VertexBuffer> SquareVB;
		SquareVB.reset(AYK::VertexBuffer::Create(SquareVertices, sizeof(SquareVertices)));
		SquareVB->SetLayout({ { AYK::ShaderDataType::Float3, "aPosition"} });
		SquareVA->AddVertexBuffer(SquareVB);

		uint32_t SquareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<AYK::IndexBuffer> SquareIB;
		SquareIB.reset(AYK::IndexBuffer::Create(SquareIndices, (sizeof(SquareIndices) / sizeof(uint32_t))));
		SquareVA->SetIndexBuffer(SquareIB);

		std::string VertexShaderSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 aPosition;
			layout(location = 1) in vec4 aColor;

			uniform mat4 uViewProjection;

			out vec4 vColor;


			void main(){
				gl_Position = uViewProjection * vec4(aPosition, 1.0);
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

		TriangleShader.reset(new AYK::Shader(VertexShaderSrc, FragmentSahderSrc));

		std::string SquareVertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 aPosition;

			uniform mat4 uViewProjection;

			void main(){
				gl_Position = uViewProjection * vec4(aPosition, 1.0);
			}
		)";

		std::string SquareFragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 oColor;

			void main(){
				oColor = vec4(0.2, 0.3, 0.8, 1.0);
			}
		)";

		SquareShader.reset(new AYK::Shader(SquareVertexSrc, SquareFragmentSrc));
	}

	void OnUpdate() override {

		if (AYK::Input::IsKeyPressed(AYK_KEY_LEFT)) {
			CameraPosition.x -= CameraSpeed;
		}else if (AYK::Input::IsKeyPressed(AYK_KEY_RIGHT)) {
			CameraPosition.x += CameraSpeed;
		}else if (AYK::Input::IsKeyPressed(AYK_KEY_UP)) {
			CameraPosition.y += CameraSpeed;
		}else if (AYK::Input::IsKeyPressed(AYK_KEY_DOWN)) {
			CameraPosition.y -= CameraSpeed;
		}
		
		
		if (AYK::Input::IsKeyPressed(AYK_KEY_E)) {
			CameraRotation -= CameraSpeed;
		} else if (AYK::Input::IsKeyPressed(AYK_KEY_Q)) {
			CameraRotation += CameraSpeed;
		}

		AYK::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		AYK::RenderCommand::Clear();

		Camera.SetPosition(CameraPosition);
		Camera.SetRotation(CameraRotation);

		AYK::Renderer::BeginScene(Camera);

		AYK::Renderer::Submit(SquareShader, SquareVA);
		AYK::Renderer::Submit(TriangleShader, TriangleVA);

		AYK::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override {	}

	void OnEvent(AYK::Event& E) override {
	}

private:

	std::shared_ptr<AYK::Shader> TriangleShader;
	std::shared_ptr<AYK::VertexArray> TriangleVA;

	std::shared_ptr<AYK::Shader> SquareShader;
	std::shared_ptr<AYK::VertexArray> SquareVA;

	AYK::OrthographicCamera Camera;
	glm::vec3 CameraPosition;
	float CameraSpeed = 0.1f;
	float CameraRotation = 0.0f;


};

class Sandbox : public AYK::Application {

public:

	Sandbox() {
		PushLayer(new ExampleLayer());
	}

	~Sandbox() {
	
	}


};

AYK::Application* CreateApplication() {
	return(new Sandbox());
}