#pragma once
#include "Expressions.h"
#include "Tokenizer.h"

struct TokenConsumer {
	std::vector<Token> TokenList;
	int CurrentIndex;
};

// Parse all literal expressions
std::pair<Ref<Expression>, std::string> ParseLiteral(TokenConsumer& TC);

std::pair<Ref<Expression>, std::string> ParseMultiplicativeExpr(TokenConsumer& TC);
std::pair<Ref<Expression>, std::string> ParseAdditiveExpr(TokenConsumer& TC);

// Generates a Program Statment from token list
std::pair<Ref<ProgramStmt>, std::string> Parse(const std::vector<Token>& tokenList);