#pragma once
#include <string>
#include <sstream>
#include <fstream>

// Loads file from path.
std::string LoadFileFromPath(std::string path) {
	std::ifstream t(path);
	std::stringstream buffer;
	buffer << t.rdbuf();
	return buffer.str();
}
