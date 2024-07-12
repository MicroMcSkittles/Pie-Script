#include "Tokenizer.h"

std::string TokenListToString(std::vector<Token> token_list)
{
	std::stringstream ss;

	// Convert each token to string than push to ss.
	for (int i = 0; i < token_list.size(); ++i) {
		ss << token_list[i].to_string();
		if (token_list.size()-1 != i) ss << ",\n";
		else ss << "\n";
	}

	return ss.str();
}

// Creates error messages
std::string GenerateErrorMsg(const std::string& error, Location loc) {
	std::stringstream error_stream;

	error_stream << (loc.line_index + 1) << ") ";
	int line_offset = error_stream.str().size();
	error_stream << loc.line << '\n';
	for (uint32_t i = 0; i < loc.line.size() + line_offset; ++i) {
		if (i == loc.start + line_offset || i == loc.end + line_offset) {
			error_stream << "^";
		}
		else if (loc.start + line_offset < i && i < loc.end + line_offset) {
			error_stream << "=";
		}
		else {
			error_stream << "-";
		}
	}
	error_stream << '\n';
	error_stream << error;

	return error_stream.str();
}

using ReturnValue = std::pair<std::vector<Token>, std::string>;

std::pair<std::vector<Token>, std::string> Tokenize(std::string source)
{
	std::stringstream source_stream(source);

	// Stores a list of all lines in source
	std::vector<std::string> lines;

	// Get all lines from source
	std::string line;
	while (std::getline(source_stream, line, '\n')) {
		lines.push_back(line);
	}

	std::vector<Token> token_list;
	std::string error;

	// Loop through every line in source
	uint32_t line_index = 0;
	uint32_t source_index_offset = 0;
	for (; line_index < lines.size(); ++line_index) {
		std::string current_line = lines[line_index];
		uint32_t source_index = source_index_offset + line_index;

		// Loop through every character in current line
		uint32_t char_index = 0;
		for (; char_index < current_line.size(); ++char_index) {
			char current_char = current_line[char_index];

			// Check if current line is a comment
			if (current_char == '@') {
				// Skip the rest of the characters on current line
				break;
			}

			// Check if current char is a binary expression
			else if (current_char == '+' || current_char == '-' || current_char == '^' ||
				current_char == '*' || current_char == '/' || current_char == '%') {
				// Push binary operation token to token list
				token_list.push_back(Token(
					TokenType::BinaryOperation,
					Location(char_index, char_index, current_line, line_index),
					std::string(1, current_char)
				));
			}
			else if (current_char == '=') {
				// Push equal token to token list
				token_list.push_back(Token(
					TokenType::Equals,
					Location(char_index, char_index, current_line, line_index)
				));
			}
			else if (current_char == '(') {
				// Push open peren token to token list
				token_list.push_back(Token(
					TokenType::OpenPeren,
					Location(char_index, char_index, current_line, line_index)
				));
			}
			else if (current_char == ')') {
				// Push close peren token to token list
				token_list.push_back(Token(
					TokenType::ClosePeren,
					Location(char_index, char_index, current_line, line_index)
				));
			}

			// Check if current char is " then proccess string
			else if (current_char == '\"') {
				uint32_t start_index = char_index;
				char_index += 1;
				// Check if source_index is valid
				if (char_index >= current_line.size()) {

					//Handle Error
					return ReturnValue({ }, GenerateErrorMsg(
						"Unexpected quotation character", 
						{ start_index, start_index, current_line, line_index }));
				}
				current_char = current_line[char_index];

				char last_char = ' '; // stores last char in the loop to add end line char support
				std::string string_literal;
				std::string debug_string_literal;
				while (current_char != '\"' || char_index == current_line.size()) {
					if (last_char == '\\' && current_char == 'n') {
						string_literal.pop_back();
						string_literal.push_back('\n');
					}
					else {
						string_literal.push_back(current_char);
					}
					debug_string_literal.push_back(current_char);
					char_index += 1;
					last_char = current_char;
					if (char_index == current_line.size()) {
						//Handle Error
						return ReturnValue({ }, GenerateErrorMsg(
							"Expected quotation character",
							{ start_index, char_index - 1, current_line, line_index }));
					}
						
					current_char = current_line[char_index];
				}

				// Push string token to token list
				Token tk = Token(
					TokenType::StringLiteral,
					Location(start_index, current_char, current_line, line_index),
					string_literal
				);
				tk.debug_value = debug_string_literal;
				token_list.push_back(tk);
			}
			// Check if current char is numeric
			else if (isdigit(current_char)) {
				int start_index = char_index;

				std::string numeric_literal;
				while (isdigit(current_char) && char_index != current_line.size()) {
					numeric_literal.push_back(current_char);
					char_index += 1;
					current_char = current_line[char_index];
				}
				char_index -= 1;

				// Push numeric token to token list
				token_list.push_back(Token(
					TokenType::NumericLiteral,
					Location(start_index, current_char, current_line, line_index),
					numeric_literal
				));
			}
			// Check if current char is a letter
			else if (isalpha(current_char)) {
				int start_index = char_index;

				std::string identifier;
				while (isalnum(current_char) && char_index != current_line.size()) {
					identifier.push_back(current_char);
					char_index += 1;
					current_char = current_line[char_index];
				}
				char_index -= 1;

				// Check if identifier is a keyword
				if (Keywords.count(identifier)) {
					// Push keyword to token list
					token_list.push_back(Token(
						Keywords[identifier],
						Location(start_index, current_char, current_line, line_index)
					));
				}
				else {
					// Push numeric token to token list
					token_list.push_back(Token(
						TokenType::Identifier,
						Location(start_index, current_char, current_line, line_index),
						identifier
					));
				}
			}
		}
		
		source_index_offset += current_line.size();
	}

	return std::pair<std::vector<Token>, std::string>(token_list, error);
}
