#pragma once

#include <string>
#include <glm/glm.hpp>

namespace AYK {

	class Shader {

	public:

		Shader(const std::string& VertexSource, const std::string& FragmentSource);
		~Shader();
	
		void Bind() const;
		void Unbind() const;

		void UploadUniformMat4(const std::string& Name, const glm::mat4& Matrix);
	
	private:

		uint32_t RendererID;
	
	};

}