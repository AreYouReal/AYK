#include "aykpch.h"
#include "Application.h"

#include "AYK/Log.h"

#include "Events/ApplicationEvent.h"

#include "AYK/Renderer/Renderer.h"

#include "Input.h"


namespace AYK {

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

	Application* Application::Instance = nullptr;

	Application::Application(){
		AYK_CORE_ASSERT(!Instance, "Application already exists!");
		Instance = this;

		WindowPtr = std::unique_ptr<Window>( Window::Create() );
		WindowPtr->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

		ImGuiLayerPtr = new ImGuiLayer();
		PushOverlay(ImGuiLayerPtr);


		// Generate VA -> Triangle
		TriangleVA.reset(VertexArray::Create());
		TriangleVA->Bind();

		float TriangleVertices[3 * 7] = {
			-.5f, -.5f, .0f, 1.0f, .0f, .0f, 1.0f,
			.5f, -.5f, .0f, .0f, 1.0f, .0f, 1.0f,
			.0f, .5f, .0f, .0f, .0f, 1.0f, 1.0f
		};
		std::shared_ptr<VertexBuffer> TriangleVB;
		TriangleVB.reset(VertexBuffer::Create(TriangleVertices, sizeof(TriangleVertices)));

		BufferLayout BLayout = {
			{ ShaderDataType::Float3, "aPosition", true},
			{ ShaderDataType::Float4, "aColor", false}
		};
		TriangleVB->SetLayout(BLayout);
		TriangleVA->AddVertexBuffer(TriangleVB);

		uint32_t TriangleIndices[3] = { 0, 1, 2 };
		std::shared_ptr<IndexBuffer> TriangleIB;
		TriangleIB.reset(IndexBuffer::Create(TriangleIndices, (sizeof(TriangleIndices) / sizeof(uint32_t))));
		TriangleVA->SetIndexBuffer(TriangleIB);

		// Generate VA - Square
		SquareVA.reset(VertexArray::Create());

		float SquareVertices[3 * 4] = {
			-.75f, -.75f, .0f,
			.75f, -.75f, .0f,
			.75f, .75f, .0f, 
			-.75f, .75f, .0f
		};

		std::shared_ptr<VertexBuffer> SquareVB;
		SquareVB.reset(VertexBuffer::Create(SquareVertices, sizeof(SquareVertices)));
		SquareVB->SetLayout({ { ShaderDataType::Float3, "aPosition"} });
		SquareVA->AddVertexBuffer(SquareVB);

		uint32_t SquareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<IndexBuffer> SquareIB;
		SquareIB.reset(IndexBuffer::Create(SquareIndices, (sizeof(SquareIndices) / sizeof(uint32_t))));
		SquareVA->SetIndexBuffer(SquareIB);

		std::string VertexShaderSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 aPosition;
			layout(location = 1) in vec4 aColor;

			out vec4 vColor;


			void main(){
				gl_Position = vec4(aPosition, 1.0);
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

		TriangleShader.reset(new Shader(VertexShaderSrc, FragmentSahderSrc ));

		std::string SquareVertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 aPosition;

			void main(){
				gl_Position = vec4(aPosition, 1.0);
			}
		)";

		std::string SquareFragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 oColor;

			void main(){
				oColor = vec4(0.2, 0.3, 0.8, 1.0);
			}
		)";

		SquareShader.reset(new Shader(SquareVertexSrc, SquareFragmentSrc));

	}
	
	Application::~Application(){
	}
	
	void Application::Run() {

		while (bRunning) {

			RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
			RenderCommand::Clear();

			Renderer::BeginScene();
			
			SquareShader->Bind();
			Renderer::Submit(SquareVA);
			
			TriangleShader->Bind();
			Renderer::Submit(TriangleVA);

			Renderer::EndScene();

			SquareVA->Bind();
			RenderCommand::DrawIndexed(SquareVA);

			TriangleVA->Bind();
			RenderCommand::DrawIndexed(TriangleVA);

			for (Layer* L : LStack) {
				L->OnUpdate();
			}

			ImGuiLayerPtr->Begin();
			for (Layer* L : LStack) { L->OnImGuiRender(); }
			ImGuiLayerPtr->End();

			WindowPtr->OnUpdate();
		}
	}

	//bool Application::OnWindowClose(WindowCloseEvent& E) {
	//	bRunning = false;
	//	return false;
	//}

	void Application::OnEvent(Event& E){
		EventDispatcher Dispactcher(E);
		Dispactcher.Dispatch<WindowCloseEvent>([=](WindowCloseEvent& E) -> bool {
			bRunning = false;
			return(true);
		});
	
		//AYK_CORE_TRACE("{0}", E);

		for (auto it = LStack.end(); it != LStack.begin();) {
			(*--it)->OnEvent(E);
			if (E.bHandled) {
				break;
			}
		}

	}

	void Application::PushLayer(Layer* LayerToPush){
		LStack.PushLayer(LayerToPush);
		LayerToPush->OnAttach();
	}

	void Application::PushOverlay(Layer* OverlayToPush){ 
		LStack.PushOverlay(OverlayToPush);
		OverlayToPush->OnAttach();
	}



}