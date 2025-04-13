#pragma once
#include <string>
#include <sstream>
#include <fstream>
#include <memory>
#include <vector>
#include <iomanip>

// Represents the number of spaces in a tab.
#define TabIndent "    "

#define Ref std::shared_ptr

// Loads file from path.
static std::string LoadFileFromPath(const std::string& path) {
	std::ifstream t(path);
	std::stringstream buffer;
	buffer << t.rdbuf();
	return buffer.str();
}

// Creates a string that show the line numbers for strings 
static std::string GenerateOutputSourceString(const std::string& source) {
	std::stringstream source_stream(source);
	std::stringstream output_stream;
	
	// Stores a list of all lines in source
	std::vector<std::string> lines;

	// Get all lines from source
	std::string line;
	while (std::getline(source_stream, line, '\n')) {
		lines.push_back(line);
	}

	int LineIndexMaxSize = log10(lines.size());
	for (int i = 0; i < lines.size(); ++i) {
		output_stream << std::left << std::setw(LineIndexMaxSize + 1) << i + 1 << " ) " << lines[i] << "\n";
	}

	return output_stream.str();
}
