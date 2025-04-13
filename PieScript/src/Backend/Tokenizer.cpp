#include "Tokenizer.h"
#include "ErrorHandler.h"

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

using ReturnValue = std::pair<std::vector<Token>, std::string>;

ReturnValue Tokenize(std::string source)
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
			
			// Check if current char is white space
			else if (isspace(current_char)) {
				continue;
			}

			// Check if current char is a binary expression
			else if (current_char == '+' || current_char == '-' || current_char == '^' || 
				current_char == '*' || current_char == '/' || current_char == '%') {
				// Push binary operation token to token list
				token_list.push_back(Token(
					TokenType::BinaryOperation,
					Location(source_index_offset + char_index, source_index_offset + char_index, char_index, char_index, line_index),
					std::string(1, current_char)
				));
			}
			else if (current_char == '=') {
				// Push equal token to token list
				token_list.push_back(Token(
					TokenType::Equals,
					Location(source_index_offset + char_index, source_index_offset + char_index, char_index, char_index, line_index)
				));
			}
			else if (current_char == '(') {
				// Push open peren token to token list
				token_list.push_back(Token(
					TokenType::OpenPeren,
					Location(source_index_offset + char_index, source_index_offset + char_index, char_index, char_index, line_index)
				));
			}
			else if (current_char == ')') {
				// Push close peren token to token list
				token_list.push_back(Token(
					TokenType::ClosePeren,
					Location(source_index_offset + char_index, source_index_offset + char_index, char_index, char_index, line_index)
				));
			}

			// Check if current char is " then proccess string
			else if (current_char == '\"') {
				uint32_t start_index = char_index;
				char_index += 1;
				// Check if source_index is valid
				if (char_index >= current_line.size()) {

					//Handle Error
					return ReturnValue({ }, GenerateTokenErrorMsg(
						"Unexpected quotation character", 
						{ source_index_offset + start_index, source_index_offset + start_index, start_index, start_index, line_index }));
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
						return ReturnValue({ }, GenerateTokenErrorMsg(
							"Expected quotation character",
							{ source_index_offset + start_index, source_index_offset + (char_index - 1), start_index, char_index - 1, line_index }));
					}
						
					current_char = current_line[char_index];
				}

				// Push string token to token list
				Token tk = Token(
					TokenType::StringLiteral,
					Location(source_index_offset + start_index, source_index_offset + char_index, start_index, char_index, line_index),
					string_literal
				);
				tk.debug_value = debug_string_literal;
				token_list.push_back(tk);
			}
			// Check if current char is numeric
			else if (isdigit(current_char)) {
				uint32_t start_index = char_index;

				bool period_flag = false;
				std::string numeric_literal;
				while ((isdigit(current_char) || current_char == '.') && char_index != current_line.size()) {
					
					// If theres more then one period then call an error
					if (current_char == '.' && period_flag == false) period_flag = true;
					else if (current_char == '.' && period_flag) {
						return ReturnValue({ }, GenerateTokenErrorMsg(
							"Unexpected period",
							{ source_index_offset + char_index, source_index_offset + char_index, char_index, char_index, line_index }));
					}

					numeric_literal.push_back(current_char);
					char_index += 1;
					current_char = current_line[char_index];
				}
				char_index -= 1;

				// Push numeric token to token list
				token_list.push_back(Token(
					TokenType::NumericLiteral,
					Location(source_index_offset + start_index, source_index_offset + char_index, start_index, char_index, line_index),
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
						Location(source_index_offset + start_index, source_index_offset + char_index, start_index, char_index, line_index)
					));
				}
				else {
					// Push numeric token to token list
					token_list.push_back(Token(
						TokenType::Identifier,
						Location(source_index_offset + start_index, source_index_offset + char_index, start_index, char_index, line_index),
						identifier
					));
				}
			}
			// Create error message if char is not recognized
			else {
				return ReturnValue({ }, GenerateTokenErrorMsg(
					"Unknown character",
					{ source_index_offset + char_index, source_index_offset + char_index, char_index, char_index, line_index }));
			}
		}
		
		source_index_offset += current_line.size() + 1;
	}

	return std::pair<std::vector<Token>, std::string>(token_list, error);
}
