

#include "Shader.h"

#include "glad/glad.h"

#include "engine/core/Utils.h"

#include <iostream>

namespace UnknownEngine {
	Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath) {
		vertexCode = ReadFromFile(vertexPath);
		fragmentCode = ReadFromFile(fragmentPath);

		Compile();
	}

	Shader::~Shader() {}

	void Shader::Compile() {
		//Vertex shader setup
		unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
		const char* vertexCodeChar = vertexCode.c_str();
		glShaderSource(vertexShader, 1, &vertexCodeChar, NULL);
		glCompileShader(vertexShader);

		int success;
		char infoLog[512];
		//Check for erros
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success); 
		if (!success) {
			glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		}

		//Fragment shader setup
		unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		const char* fragmentCodeChar = fragmentCode.c_str();
		glShaderSource(fragmentShader, 1, &fragmentCodeChar, NULL);
		glCompileShader(fragmentShader); 
		//Check for erros
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success); 
		if (!success) {
			glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_ERROR\n" << infoLog << std::endl; 
		}

		//Linking Shaders
		shaderProgram = glCreateProgram(); 
		glAttachShader(shaderProgram, vertexShader); 
		glAttachShader(shaderProgram, fragmentShader);
		glLinkProgram(shaderProgram);
		//Check for errors
		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		}
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}

	void Shader::Run() const {
		glUseProgram(shaderProgram);  
	}
}