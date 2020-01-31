#pragma once

#include <AYK/Renderer/Shader.h>
#include <glm/glm.hpp>

#include <unordered_map>

// TODO: Remove!
typedef unsigned int GLenum;

namespace AYK {

	class OpenGLShader : public Shader {

	public:

		OpenGLShader(const std::string& FilePath);
		OpenGLShader(const std::string& NameToSet, const std::string& VertexSource, const std::string& FragmentSource);
		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void SetFloat3(const std::string& Name, const glm::vec3& Value) override;
		virtual void SetFloat4(const std::string& Name, const glm::vec4& Value) override;
		virtual void SetMat4(const std::string& Name, const glm::mat4& Value) override;

		virtual const std::string& GetName() const override { return(Name); }

		void UploadUniformInt(const std::string& Name, int Values);

		void UploadUniformFloat(const std::string& Name, float Values);
		void UploadUniformFloat2(const std::string& Name, const glm::vec2& Values);
		void UploadUniformFloat3(const std::string& Name, const glm::vec3& Values);
		void UploadUniformFloat4(const std::string& Name, const glm::vec4& Values);

		void UploadUniformMat3(const std::string& Name, const glm::mat3& Matrix);
		void UploadUniformMat4(const std::string& Name, const glm::mat4& Matrix);


	private:
		std::string ReadFile(const std::string& FilePath);
		std::unordered_map<GLenum, std::string> PreProcess(const std::string& Source);
		void Compile(const std::unordered_map<GLenum, std::string>& ShaderSources);

	private:

		uint32_t RendererID;
		std::string Name;
	};

}