#include "aykpch.h"
#include "Shader.h"

#include <glad/glad.h>

AYK::Shader::Shader(const std::string& VertexSource, const std::string& FragmentSource){

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

	const GLchar* source = VertexSource.c_str();
	glShaderSource(vertexShader, 1, &source, 0);
	glCompileShader(vertexShader);

	GLint isCompiled = 0;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)	{
		GLint maxLength = 0;
		glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);
		std::vector<GLchar> infoLog(maxLength);
		glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);
		glDeleteShader(vertexShader);
		AYK_CORE_ERROR("{0}", infoLog.data());
		AYK_CORE_ASSERT(false, "Vertex shader compilation failure!");
		return;
	}

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	source = (const GLchar*)FragmentSource.c_str();
	glShaderSource(fragmentShader, 1, &source, 0);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE) {
		GLint maxLength = 0;
		glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);
		std::vector<GLchar> infoLog(maxLength);
		glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);
		glDeleteShader(fragmentShader);
		// Either of them. Don't leak shaders.
		glDeleteShader(vertexShader);

		AYK_CORE_ERROR("{0}", infoLog.data());
		AYK_CORE_ASSERT(false, "Fragment shader compilation failure!");
		return;
	}

	RendererID = glCreateProgram();
	glAttachShader(RendererID, vertexShader);
	glAttachShader(RendererID, fragmentShader);
	glLinkProgram(RendererID);


	GLint isLinked = 0;
	glGetProgramiv(RendererID, GL_LINK_STATUS, (int*)&isLinked);
	if (isLinked == GL_FALSE) {
		GLint maxLength = 0;
		glGetProgramiv(RendererID, GL_INFO_LOG_LENGTH, &maxLength);
		std::vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(RendererID, maxLength, &maxLength, &infoLog[0]);

		// We don't need the program anymore.
		glDeleteProgram(RendererID);
		// Don't leak shaders either.
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		AYK_CORE_ERROR("{0}", infoLog.data());
		AYK_CORE_ASSERT(false, "Shader link failure!");
		return;
	}
	glDetachShader(RendererID, vertexShader);
	glDetachShader(RendererID, fragmentShader);
}

AYK::Shader::~Shader(){
	glDeleteProgram(RendererID);
}

void AYK::Shader::Bind() const {
	glUseProgram(RendererID);
}

void AYK::Shader::Unbind() const {
	glUseProgram(0);
}
