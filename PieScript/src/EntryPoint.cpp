#include <iostream>
#include "Backend/Tokenizer.h"
#include "Backend/Parser.h"
#include "Frontend/Runtime.h"
#include "ErrorHandler.h"

int main() {
	// Load source from file
	std::string source = LoadFileFromPath("scripts/ExampleProgram.pie");
	// Give source to error handeler
	SetErrorSourceContext(source);
	std::cout << GenerateOutputSourceString(source) << std::endl << std::endl;

	// Create token list, then check for errors
	auto& [token_list, token_error] = Tokenize(source);
	if (!token_error.empty()) {
		std::cout << token_error << '\n';
		return 0;
	}
	std::cout << TokenListToString(token_list) << std::endl << std::endl;

	// Parse token list, then check for errors
	auto& [program, parse_error] = Parse(token_list);
	if (!parse_error.empty()) {
		std::cout << parse_error << '\n';
		return 0;
	}
	std::cout << program->to_string("") << std::endl << std::endl;

	// Interprate program, then check for errors
	auto& [exit_code, runtime_error] = Interp(program);
	if (!runtime_error.empty()) {
		std::cout << runtime_error << '\n';
		return 0;
	}
	std::cout << exit_code->to_string() << "\n";

	return 0;
}