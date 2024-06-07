#pragma once
#include <vector>
#include "Token.h"

// Converts a list of tokens to a string
std::string TokenListToString(std::vector<Token> token_list);

// Takes in source code and returns a list of tokens
std::vector<Token> Tokenize(std::string source);