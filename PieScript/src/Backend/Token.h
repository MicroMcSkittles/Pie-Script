#pragma once
#include <string>
#include <sstream>
#include <map>

enum class TokenType {
	None = 0,
	EndLine,
	NumericLiteral, // Number Type
	StringLiteral,  // String Type
	Identifier,		// The name of a variable, function, or struct
	BinaryOperation,
	Equals,			// =
	OpenPeren,		// (
	ClosePeren,		// )
	Var,			// Var Keyword
};

// Every TokenType mapped to a descriptive string.
extern std::map<TokenType, std::string> TokenTypeStrings;

// Every key word mapped to its TokenType.
extern std::map<std::string, TokenType> Keywords;

// Stores were a token is
struct Location {
	uint32_t start;			 // Index into line at start of token file used for error handling.
	uint32_t end;			 // Index into line at end of token file used for error handling.
	std::string line;		 // The line the token is on
	uint32_t line_index;	 // Were the line is in source

	Location(uint32_t start, uint32_t end, std::string line, uint32_t line_index)
		: start(start), end(end), line(line), line_index(line_index) { }
};

struct Token {
	TokenType type;
	std::string value;		 // Holds any data needed for token
	std::string debug_value; // Holds any data needed for token to be displayed during error.
	Location location;
	
	// Converts token to string for debuging.
	std::string to_string() const {
		if (value != "") {
			std::stringstream ss;
			ss << "{ " 
				<< TokenTypeStrings[type] << ", " 
				<< debug_value
				<< " }: loc { "
				<< location.start << ", " << location.end << " }";
			return ss.str();
		}
		else {
			std::stringstream ss;
			ss << "{ "
				<< TokenTypeStrings[type]
				<< " }: loc { "
				<< location.start << ", " << location.end << " }";
			return ss.str();
		}
	}

	Token(TokenType type, Location location, std::string value = "")
		: type(type), value(value), debug_value(value), location(location) { }
};