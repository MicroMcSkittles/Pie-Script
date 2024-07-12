#pragma once
#include <string>
#include <sstream>
#include <fstream>
#include <memory>

// Represents the number of spaces in a tab.
#define TabIndent "    "

#define Ref std::shared_ptr

// Loads file from path.
static std::string LoadFileFromPath(std::string path) {
	std::ifstream t(path);
	std::stringstream buffer;
	buffer << t.rdbuf();
	return buffer.str();
}
