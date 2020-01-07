#pragma once

#include <string>
#include <unordered_map>

namespace AYK {

	class Shader {

	public:

		virtual ~Shader() = default;
	
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual const std::string& GetName() const = 0;

		static Ref<Shader> Create(const std::string& FilePath);
		static Ref<Shader> Create(const std::string& Name, const std::string& VertexSource, const std::string& FragmentSource);
	
	
	};


	class ShaderLibrary {
	public:

		void Add(const std::string& Name, const Ref<Shader>& NewShader);
		void Add(const Ref<Shader>& NewShader);
		Ref<Shader> Load(const std::string& FilePath);
		Ref<Shader> Load(const std::string& Name, const std::string& FilePath);

		Ref<Shader> Get(const std::string& Name);

		bool Exists(const std::string& Name);

	private:
		std::unordered_map<std::string, Ref<Shader>> Shaders;
	};

}