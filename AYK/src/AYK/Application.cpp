#include "aykpch.h"
#include "Application.h"

#include "AYK/Log.h"

#include "Events/ApplicationEvent.h"

#include <glad/glad.h>

#include "Input.h"


namespace AYK {

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

	Application* Application::Instance = nullptr;

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType Type) {
		switch (Type) {
			case AYK::ShaderDataType::Float: 
			case AYK::ShaderDataType::Float2:
			case AYK::ShaderDataType::Float3:
			case AYK::ShaderDataType::Float4:
			case AYK::ShaderDataType::Mat3:
			case AYK::ShaderDataType::Mat4:
			return(GL_FLOAT);
			case AYK::ShaderDataType::Int:
			case AYK::ShaderDataType::Int2:
			case AYK::ShaderDataType::Int3:
			case AYK::ShaderDataType::Int4:
			return(GL_INT);
			case AYK::ShaderDataType::Bool: 			
			return(GL_BOOL);
		}
		AYK_CORE_ASSERT(false, "Unknown ShderDataType");
		return(0);
	}

	Application::Application(){
		AYK_CORE_ASSERT(!Instance, "Application already exists!");
		Instance = this;

		WindowPtr = std::unique_ptr<Window>( Window::Create() );
		WindowPtr->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

		ImGuiLayerPtr = new ImGuiLayer();
		PushOverlay(ImGuiLayerPtr);

		
		glGenVertexArrays(1, &VertexArray);
		glBindVertexArray(VertexArray);


		float Vertices[3 * 7] = {
			-.5f, -.5f, .0f, 1.0f, .0f, .0f, 1.0f,
			.5f, -.5f, .0f, .0f, 1.0f, .0f, 1.0f,
			.0f, .5f, .0f, .0f, .0f, 1.0f, 1.0f
		};

		MyVertexBuffer.reset(VertexBuffer::Create(Vertices, sizeof(Vertices)));

		{
			BufferLayout BLayout = {
				{ ShaderDataType::Float3, "aPosition", true},
				{ ShaderDataType::Float4, "aColor", false}
			};

			MyVertexBuffer->SetLayout(BLayout);
		}

		uint32_t CurrentIndex = 0;
		const auto& VertexBufferLayout = MyVertexBuffer->GetLayout();
		for (const auto& E : VertexBufferLayout) {
			glEnableVertexAttribArray(CurrentIndex);
			glVertexAttribPointer(CurrentIndex++, 
				E.GetComponentCount(), 
				ShaderDataTypeToOpenGLBaseType(E.Type), 
				E.Normalized ? GL_TRUE : GL_FALSE, 
				VertexBufferLayout.GetStride(),
				(const void*)E.Offset);
		}

		uint32_t Indices[3] = { 0, 1, 2 };
		uint32_t IndexCount = sizeof(Indices) / sizeof(uint32_t);
		MyIndexBuffer.reset(IndexBuffer::Create(Indices, IndexCount));

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

		ShaderExample.reset(new Shader(VertexShaderSrc, FragmentSahderSrc ));
	}
	
	Application::~Application(){
	}
	
	void Application::Run() {

		while (bRunning) {
			glClearColor(.1f, .1f, .1f, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			ShaderExample->Bind();
			glBindVertexArray(VertexArray);
			glDrawElements(GL_TRIANGLES, MyIndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

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