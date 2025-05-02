
#pragma once

#include <vector>
#include <string>

namespace UnknownEngine {
	struct Mesh {
		std::vector<float> vertices; 
		std::vector<unsigned int> indices; 

		//Later both normal and uv coordinates 

		void LoadFromFile(const std::string& filePath);
	};
}