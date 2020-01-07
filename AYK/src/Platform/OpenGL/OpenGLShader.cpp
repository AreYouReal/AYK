#include "aykpch.h"
#include "OpenGLShader.h"

#include <fstream>
#include <glad/glad.h>

#include <glm/gtc/type_ptr.hpp>


namespace AYK {
	

	static GLenum ShaderTypeFromString(const std::string& TypeStr) {
		if (TypeStr == "vertex") {
			return(GL_VERTEX_SHADER);
		} else if (TypeStr == "fragment" || TypeStr == "pixel") {
			return(GL_FRAGMENT_SHADER);
		}
		AYK_CORE_ASSERT(false, "Unknown shader type!");
		return(0);
	}

	OpenGLShader::OpenGLShader(const std::string& FilePath) {
		std::string ShaderSource = ReadFile(FilePath);
		std::unordered_map<GLenum, std::string> ShaderSources = PreProcess(ShaderSource);
		Compile(ShaderSources);
	}

	OpenGLShader::OpenGLShader(const std::string& VertexSource, const std::string& FragmentSource) {
		std::unordered_map<GLenum, std::string> Sources;
		Sources[GL_VERTEX_SHADER] = VertexSource;
		Sources[GL_FRAGMENT_SHADER] = FragmentSource;
		Compile(Sources);
	}

	OpenGLShader::~OpenGLShader() {
		glDeleteProgram(RendererID);
	}

	void OpenGLShader::Bind() const {
		glUseProgram(RendererID);
	}

	void OpenGLShader::Unbind() const {
		glUseProgram(0);
	}

	void OpenGLShader::UploadUniformInt(const std::string& Name, int Values) {
		GLint Location = glGetUniformLocation(RendererID, Name.c_str());
		glUniform1i(Location, Values);
	}

	void OpenGLShader::UploadUniformFloat(const std::string& Name, float Values) {
		GLint Location = glGetUniformLocation(RendererID, Name.c_str());
		glUniform1f(Location, Values);
	}

	void OpenGLShader::UploadUniformFloat2(const std::string& Name, const glm::vec2& Values) {
		GLint Location = glGetUniformLocation(RendererID, Name.c_str());
		glUniform2fv(Location, 1, glm::value_ptr(Values));
	}

	void OpenGLShader::UploadUniformFloat4(const std::string& Name, const glm::vec4& Values) {
		GLint Location = glGetUniformLocation(RendererID, Name.c_str());
		glUniform4fv(Location, 1, glm::value_ptr(Values));
	}

	void OpenGLShader::UploadUniformFloat3(const std::string& Name, const glm::vec3& Values) {
		GLint Location = glGetUniformLocation(RendererID, Name.c_str());
		glUniform3fv(Location, 1, glm::value_ptr(Values));
	}

	void OpenGLShader::UploadUniformMat3(const std::string& Name, const glm::mat3& Matrix) {
		GLint Location = glGetUniformLocation(RendererID, Name.c_str());
		glUniformMatrix3fv(Location, 1, GL_FALSE, glm::value_ptr(Matrix));
	}

	void OpenGLShader::UploadUniformMat4(const std::string& Name, const glm::mat4& Matrix) {
		GLint Location = glGetUniformLocation(RendererID, Name.c_str());
		glUniformMatrix4fv(Location, 1, GL_FALSE, glm::value_ptr(Matrix));
	}

	std::string OpenGLShader::ReadFile(const std::string& FilePath) {
		std::string Result;
		std::ifstream in(FilePath, std::ios::in, std::ios::binary);
		if (in) {
			in.seekg(0, std::ios::end);
			Result.resize(in.tellg());
			in.seekg(0, std::ios::beg);
			in.read(&Result[0], Result.size());
			in.close();
		}
		else {
			AYK_CORE_ERROR("Could not open file '{0}'", FilePath);
		}

		return(Result);
	}

	std::unordered_map<GLenum, std::string> OpenGLShader::PreProcess(const std::string& Source) {
		std::unordered_map<GLenum, std::string> ShaderSources;


		const char* TypeToken = "#type";
		size_t TypeTokenLength = strlen(TypeToken);
		size_t Pos = Source.find(TypeToken, 0);
		while (Pos != std::string::npos) {
			size_t EOL = Source.find_first_of("\r\n", Pos);
			AYK_CORE_ASSERT(EOL != std::string::npos, "Syntax error!");
			size_t Begin = Pos + TypeTokenLength + 1;
			std::string Type = Source.substr(Begin, EOL - Begin);
			GLenum ShaderType = ShaderTypeFromString(Type);
			AYK_CORE_ASSERT(ShaderType, "Invalid shader type specifier!");

			size_t NextLinePos = Source.find_first_not_of("\r\n", EOL);
			Pos = Source.find(TypeToken, NextLinePos);
			ShaderSources[ShaderType] = Source.substr(NextLinePos, Pos - (NextLinePos == std::string::npos ? Source.size() - 1 : NextLinePos));
		}
		return(ShaderSources);
	}

	void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string>& ShaderSources) {
		
		GLuint ProgramID = glCreateProgram();
		std::vector<GLuint> GLShaderIDs(ShaderSources.size());
		for (auto& KeyValue : ShaderSources) {
			GLenum ShaderType = KeyValue.first;
			const std::string& ShaderSource = KeyValue.second;

			GLuint Shader = glCreateShader(ShaderType);
			const GLchar* SSource = ShaderSource.c_str();
			glShaderSource(Shader, 1, &SSource, 0);
			glCompileShader(Shader);

			GLint isCompiled = 0;
			glGetShaderiv(Shader, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE) {
				GLint maxLength = 0;
				glGetShaderiv(Shader, GL_INFO_LOG_LENGTH, &maxLength);
				
				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(Shader, maxLength, &maxLength, &infoLog[0]);
				glDeleteShader(Shader);

				AYK_CORE_ERROR("{0}", infoLog.data());
				AYK_CORE_ASSERT(false, "Shader compilation failure!");
				return;
			}

			glAttachShader(ProgramID, Shader);
			GLShaderIDs.push_back(Shader);
		}

		glLinkProgram(ProgramID);

		GLint isLinked = 0;
		glGetProgramiv(ProgramID, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE) {
			GLint maxLength = 0;
			glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &maxLength);
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(ProgramID, maxLength, &maxLength, &infoLog[0]);

			glDeleteProgram(ProgramID);

			for (GLuint Shader : GLShaderIDs) {
				glDeleteShader(Shader);
			}

			AYK_CORE_ERROR("{0}", infoLog.data());
			AYK_CORE_ASSERT(false, "Shader link failure!");
			return;
		}

		for (GLuint Shader : GLShaderIDs) {
			glDetachShader(ProgramID, Shader);
		}
		
		RendererID = ProgramID;
	}

}
