
#pragma once

#include <string>

namespace UnknownEngine {
	class Shader {
	public:
		Shader(const std::string& vertexPath, const std::string& fragmentPath);
		~Shader();

		void Run() const;

	private:
		void Compile();

		unsigned int shaderProgram;
		std::string vertexCode;
		std::string fragmentCode;
	};
}