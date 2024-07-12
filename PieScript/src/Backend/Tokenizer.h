#pragma once
#include <vector>
#include "Token.h"

// Converts a list of tokens to a string
std::string TokenListToString(std::vector<Token> token_list);

// Creates a error message
std::string GenerateErrorMsg(const std::string& error, Location loc);

// Takes in source code and returns a list of tokens
std::pair<std::vector<Token>, std::string> Tokenize(std::string source);