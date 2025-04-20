

#include "Shader.h"

#include "glad/glad.h"

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

namespace UnknownEngine {
	std::string ReadFromFile(std::string filePath) {
		std::ifstream file(filePath);
		std::stringstream buffer;
		buffer << file.rdbuf();
		return buffer.str();
	}

	Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath) {
		vertexCode = ReadFromFile(vertexPath);
		fragmentCode = ReadFromFile(fragmentPath);

		Compile();
	}

	Shader::~Shader() {}

	Shader::Compile() {
		//Vertex shader setup
		unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexCode.c_str(), NULL);
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
		glShaderSource(fragmentShader, 1, &fragmentCode.c_str(), NULL);
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

	Shader::Run() const {
		glUseProgram(shaderProgram);  
	}
}