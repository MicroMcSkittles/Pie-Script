#include <iostream>
#include "Backend/Tokenizer.h"
#include "Utils.h"

int main() {
	
	// This is VERY temporary
	std::string source = LoadFileFromPath("scripts/ExampleProgram.ps");
	std::cout << source << std::endl << std::endl;

	std::vector<Token> token_list = Tokenize(source);

	std::cout << TokenListToString(token_list) << std::endl;

	return 0;
}