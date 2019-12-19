#include "AYK.h"

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>

class ExampleLayer : public AYK::Layer {

public:
	ExampleLayer() : Layer("Example"), Camera(-1.6f, 1.6f, -.9f, .9f), CameraPosition(0.0f), SquarePosition(0.0f){
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
			-.5f, -.5f, .0f,
			 .5f, -.5f, .0f,
			 .5f,  .5f, .0f,
			-.5f,  .5f, .0f
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

		TriangleShader.reset(new AYK::Shader(VertexShaderSrc, FragmentSahderSrc));

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

			uniform vec4 uColor;

			void main(){
				oColor = uColor;
			}
		)";

		FlatColorShader.reset(new AYK::Shader(FlatColorShaderVertexSrc, FlatColorShaderFragmentSrc));
	}

	void OnUpdate(AYK::Timestep Timestep) override {

		//AYK_TRACE("Delta time: {0}s  {1}ms", Timestep.GetSeconds(), Timestep.GetMilliseconds());

		float CameraOffset = CameraSpeed * Timestep;

		if (AYK::Input::IsKeyPressed(AYK_KEY_LEFT)) {
			CameraPosition.x -= CameraOffset;
		}else if (AYK::Input::IsKeyPressed(AYK_KEY_RIGHT)) {
			CameraPosition.x += CameraOffset;
		}
		
		if (AYK::Input::IsKeyPressed(AYK_KEY_UP)) {
			CameraPosition.y += CameraOffset;
		}else if (AYK::Input::IsKeyPressed(AYK_KEY_DOWN)) {
			CameraPosition.y -= CameraOffset;
		}
		
		if (AYK::Input::IsKeyPressed(AYK_KEY_E)) {
			CameraRotation -= CameraOffset * 100;
		} else if (AYK::Input::IsKeyPressed(AYK_KEY_Q)) {
			CameraRotation += CameraOffset * 100;
		}

		float SquareOffset = SquareSpeed * Timestep;
		if (AYK::Input::IsKeyPressed(AYK_KEY_A)) {
			SquarePosition.x -= SquareOffset;
		} else if (AYK::Input::IsKeyPressed(AYK_KEY_D)) {
			SquarePosition.x += SquareOffset;
		}
		
		if (AYK::Input::IsKeyPressed(AYK_KEY_W)) {
			SquarePosition.y += SquareOffset;
		} else if (AYK::Input::IsKeyPressed(AYK_KEY_S)) {
			SquarePosition.y -= SquareOffset;
		}

		AYK::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		AYK::RenderCommand::Clear();

		Camera.SetPosition(CameraPosition);
		Camera.SetRotation(CameraRotation);

		AYK::Renderer::BeginScene(Camera);


		static glm::mat4 Scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f, 0.1f, 0.1f));

		glm::vec4 RedColor(.8f, .2f, .3f, 1.0f);
		glm::vec4 BlueColor(.2f, .3f, .8f, 1.0f);


		for (int y = 0; y < 30; ++y) {
			for (int x = 0; x < 30; ++x) {
				SquarePosition = glm::vec3(0.11f * x, y * 0.11f, 0.0f);
				glm::mat4 SquareTransform = glm::translate(glm::mat4(1.0f), SquarePosition);
				
				FlatColorShader->UploadUniformFloat4( "uColor", ((x % 2 == 0) ? RedColor : BlueColor));
				
				AYK::Renderer::Submit(FlatColorShader, SquareVA, SquareTransform * Scale);
			}
		}

		AYK::Renderer::Submit(TriangleShader, TriangleVA);

		AYK::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override {	}

	void OnEvent(AYK::Event& E) override {
	}

private:

	std::shared_ptr<AYK::Shader> TriangleShader;
	std::shared_ptr<AYK::VertexArray> TriangleVA;

	std::shared_ptr<AYK::Shader> FlatColorShader;
	std::shared_ptr<AYK::VertexArray> SquareVA;

	AYK::OrthographicCamera Camera;
	glm::vec3 CameraPosition;
	float CameraSpeed = 1.0f;
	float CameraRotation = 0.0f;


	glm::vec3 SquarePosition;
	float SquareSpeed = 1.0f;
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