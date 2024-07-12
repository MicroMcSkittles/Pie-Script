#include "Token.h"

std::map<TokenType, std::string> TokenTypeStrings = {
	{TokenType::None, "None"},
	{TokenType::EndLine, "End Line"},
	{TokenType::NumericLiteral, "Numeric Literal"},
	{TokenType::StringLiteral, "String Literal"},
	{TokenType::Identifier, "Identifier"},
	{TokenType::BinaryOperation, "Binary Operation"},
	{TokenType::Equals, "Equals ="},
	{TokenType::OpenPeren, "Open Peren ("},
	{TokenType::ClosePeren, "Close Peren )"},
	{TokenType::Var, "Var Keyword"},
};

std::map<std::string, TokenType> Keywords = {
	{"var", TokenType::Var}, // Used for defining variables.
};