
#include "Utils.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <direct.h>  // for _getcwd on Windows
#include <string>

std::string getCurrentWorkingDirectory() {
	char cwd[1024];
	if (_getcwd(cwd, sizeof(cwd)) != NULL) {  // NOTE: _getcwd on Windows
		return std::string(cwd);
	}
	else {
		std::cerr << "ERROR::GETTING::CWD!" << std::endl;
		return "";
	}
}

std::string getProjectRoot() {
	std::string cwd = getCurrentWorkingDirectory();

	if (cwd.empty()) {
		return "";
	}

	size_t pos = cwd.find("build");
	if (pos != std::string::npos) {
		cwd = cwd.substr(0, pos);
	}

	return cwd;
}

std::string ReadFromFile(const std::string& relativeFilePath) {
	std::string projectRoot = getProjectRoot();
	if (projectRoot.empty()) {
		return "";
	}

	std::string fullPath = projectRoot + relativeFilePath;

	std::ifstream file(fullPath);
	if (!file.is_open()) {
		std::cerr << "ERROR::OPENING:FILE::" << fullPath << std::endl;
		return "";
	}

	std::stringstream buffer;
	buffer << file.rdbuf();
	return buffer.str();
}
