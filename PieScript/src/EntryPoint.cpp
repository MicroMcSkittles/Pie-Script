#include <iostream>
#include "Backend/Tokenizer.h"
#include "Backend/Parser.h"
#include "Utils.h"

int main() {
	
	// This is VERY temporary
	std::string source = LoadFileFromPath("scripts/ExampleProgram.pie");
	std::cout << source << std::endl << std::endl;

	auto& [token_list, token_error] = Tokenize(source);
	if (!token_error.empty()) {
		std::cout << token_error << '\n';
		return 0;
	}
	std::cout << TokenListToString(token_list) << std::endl << std::endl;

	auto& [program, parse_error] = Parse(token_list);
	if (!parse_error.empty()) {
		std::cout << parse_error << '\n';
		return 0;
	}
	std::cout << program->to_string("") << std::endl << std::endl;

	return 0;
}