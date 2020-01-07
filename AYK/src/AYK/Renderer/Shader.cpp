#include "aykpch.h"
#include "Shader.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace AYK {
	Ref<Shader> Shader::Create(const std::string& FilePath) {
		switch (Renderer::GetAPI()) {
			case RendererAPI::API::OpenGL: return(std::make_shared<OpenGLShader>(FilePath));
			default:
			AYK_CORE_ASSERT(false, "RendererAPI is not supported!");
			return nullptr;
		}
	}
	Ref<Shader> Shader::Create(const std::string& Name, const std::string& VertexSource, const std::string& FragmentSource) {
		switch (Renderer::GetAPI()) {
			case RendererAPI::API::OpenGL: return(std::make_shared<OpenGLShader>(Name, VertexSource, FragmentSource));
		default:
			AYK_CORE_ASSERT(false, "RendererAPI is not supported!");
			return nullptr;
		}
	}

	void ShaderLibrary::Add(const std::string& Name, const Ref<Shader>& NewShader) {
		AYK_CORE_ASSERT(!Exists(Name), "Shader already exists!");
		Shaders[Name] = NewShader;
	}

	void ShaderLibrary::Add(const Ref<Shader>& NewShader) {
		Add(NewShader->GetName(), NewShader);
	}

	AYK::Ref<AYK::Shader> ShaderLibrary::Load(const std::string& FilePath) {
		auto NewShader = Shader::Create(FilePath);
		Add(NewShader);
		return(NewShader);
	}

	AYK::Ref<AYK::Shader> ShaderLibrary::Load(const std::string& Name, const std::string& FilePath) {
		auto NewShader = Shader::Create(FilePath);
		Add(Name, NewShader);
		return(NewShader);
	}

	Ref<Shader> ShaderLibrary::Get(const std::string& Name) {
		AYK_CORE_ASSERT(Exists(Name), "Shader not found!");
		return(Shaders[Name]);
	}

	bool ShaderLibrary::Exists(const std::string& Name) {
		return(Shaders.find(Name) != Shaders.end());
	}

}

