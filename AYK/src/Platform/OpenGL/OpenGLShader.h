#pragma once

#include <AYK/Renderer/Shader.h>
#include <glm/glm.hpp>

namespace AYK {

	class OpenGLShader : public Shader {

	public:

		OpenGLShader(const std::string& VertexSource, const std::string& FragmentSource);
		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		void UploadUniformInt(const std::string& Name, int Values);

		void UploadUniformFloat(const std::string& Name, float Values);
		void UploadUniformFloat2(const std::string& Name, const glm::vec2& Values);
		void UploadUniformFloat3(const std::string& Name, const glm::vec3& Values);
		void UploadUniformFloat4(const std::string& Name, const glm::vec4& Values);

		void UploadUniformMat3(const std::string& Name, const glm::mat3& Matrix);
		void UploadUniformMat4(const std::string& Name, const glm::mat4& Matrix);


	private:

		uint32_t RendererID;

	};

}