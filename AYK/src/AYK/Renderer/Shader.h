#pragma once

namespace AYK {

	class Shader {

	public:

		virtual ~Shader() = default;
	
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		static Shader* Create(const std::string& FilePath);
		static Shader* Create(const std::string& VertexSource, const std::string& FragmentSource);
	};

}