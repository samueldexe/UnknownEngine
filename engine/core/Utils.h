
#pragma once

#include <string>

std::string getCurrentWorkingDirectory();

std::string getProjectRoot();

std::string ReadFromFile(const std::string& relativeFilePath);