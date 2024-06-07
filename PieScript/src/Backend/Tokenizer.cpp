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

std::vector<Token> Tokenize(std::string source)
{
	std::vector<Token> token_list;
	int source_index = 0;

	for (; source_index < source.size(); ++source_index) {
		char current_char = source[source_index];
		
		// Check if current line is a comment
		if (current_char == '@') {
			// Skip every char on current line
			while (current_char != '\n' || source_index == source.size()) {
				source_index += 1;
				current_char = source[source_index];
			}
		}
		// Check if current char is a binary expression
		else if (current_char == '+' || current_char == '-' || current_char == '^' ||
			current_char == '*' || current_char == '/' || current_char == '%') {
			// Push binary operation token to token list
			token_list.push_back(Token(
				TokenType::BinaryOperation,
				source_index, source_index,
				std::string(1, current_char)
			));
		}
		else if (current_char == '=') {
			// Push equal token to token list
			token_list.push_back(Token(
				TokenType::Equals,
				source_index, source_index
			));
		}
		else if (current_char == '(') {
			// Push open peren token to token list
			token_list.push_back(Token(
				TokenType::OpenPeren,
				source_index, source_index
			));
		}
		else if (current_char == ')') {
			// Push close peren token to token list
			token_list.push_back(Token(
				TokenType::ClosePeren,
				source_index, source_index
			));
		}
		// Check if current char is " then proccess string
		else if (current_char == '\"') {
			int start_index = source_index;
			source_index += 1;
			// Check if source_index is valid
			if (source_index >= source.size()) {
				//TODO: Add error handling.
				exit(-1);
			}
			current_char = source[source_index];

			//TODO: Add end line support
			char last_char = ' '; // stores last char in the loop to add end line char support
			std::string string_literal;
			std::string debug_string_literal;
			while (current_char != '\"' || source_index == source.size()) {
				if (last_char == '\\' && current_char == 'n') {
					string_literal.pop_back();
					string_literal.push_back('\n');
				}
				else {
					string_literal.push_back(current_char);
				}
				debug_string_literal.push_back(current_char);
				source_index += 1;
				last_char = current_char;
				current_char = source[source_index];
			}

			// Check if source_index is valid
			if (source_index >= source.size()) {
				//TODO: Add error handling.
				exit(-1);
			}

			// Push string token to token list
			Token tk = Token(
				TokenType::StringLiteral,
				start_index, source_index,
				string_literal
			);
			tk.debug_value = debug_string_literal;
			token_list.push_back(tk);
		}
		// Check if current char is numeric
		else if (isdigit(current_char)) {
			int start_index = source_index;

			std::string numeric_literal;
			while (isdigit(current_char) && source_index != source.size()) {
				numeric_literal.push_back(current_char);
				source_index += 1;
				current_char = source[source_index];
			}
			source_index -= 1;

			// Check if source_index is valid
			if (source_index >= source.size()) {
				//TODO: Add error handling.
				exit(-1);
			}

			// Push numeric token to token list
			token_list.push_back(Token(
				TokenType::NumericLiteral,
				start_index, source_index,
				numeric_literal
			));
		}
		// Check if current char is a letter
		else if (isalpha(current_char)) {
			int start_index = source_index;

			std::string identifier;
			while (isalnum(current_char) && source_index != source.size()) {
				identifier.push_back(current_char);
				source_index += 1;
				current_char = source[source_index];
			}
			source_index -= 1;

			// Check if source_index is valid
			if (source_index >= source.size()) {
				//TODO: Add error handling.
				exit(-1);
			}

			// Check if identifier is a keyword
			if (Keywords.count(identifier)) {
				// Push keyword to token list
				token_list.push_back(Token(
					Keywords[identifier],
					start_index, source_index
				));
			}
			else {
				// Push numeric token to token list
				token_list.push_back(Token(
					TokenType::Identifier,
					start_index, source_index,
					identifier
				));
			}
		}
	}

	return token_list;
}
