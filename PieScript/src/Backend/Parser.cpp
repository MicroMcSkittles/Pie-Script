#include "Parser.h"
#include "ErrorHandler.h"

std::pair<Ref<Expression>, std::string> ParseLiteral(TokenConsumer& TC) {
	// Get current token
	Token tk = TC.TokenList[TC.CurrentIndex];
	
	switch (tk.type)
	{
	case TokenType::NumericLiteral: return std::pair<Ref<Expression>, std::string>(NumericLiteralExpr::Create(tk.value, tk.location.start, tk.location.end), "");
	case TokenType::StringLiteral: return std::pair<Ref<Expression>, std::string>(StringLiteralExpr::Create(tk.value, tk.debug_value, tk.location.start, tk.location.end), "");
	// Check if current token is (
	case TokenType::OpenPeren: {
		// Check if peren is valid
		if (TC.TokenList.size() - 1 == TC.CurrentIndex) {
			return {
				Ref<Expression>(),
				GenerateTokenErrorMsg("Unexpected open parenthesis", tk.location)
			};
		}
		TC.CurrentIndex += 1;

		// Find expression inside perens.
		auto& [expr, error] = ParseAdditiveExpr(TC);
		if (!error.empty()) return { Ref<Expression>(), error };

		// Check if peren is valid
		if ((TC.TokenList.size() - 1 == TC.CurrentIndex) || (TC.TokenList[TC.CurrentIndex + 1].type != TokenType::ClosePeren)) {
			return {
				Ref<Expression>(),
				GenerateTokenErrorMsg("Expected close parenthesis",
					{
						tk.location.start,
						TC.TokenList[TC.CurrentIndex].location.start,
						tk.location.line_start,
						TC.TokenList[TC.CurrentIndex].location.line_start,
						tk.location.line_index
					})
			};
		}
		TC.CurrentIndex += 1;

		return std::pair<Ref<Expression>, std::string>(expr, "");
	}
	default: {
		return {
				Ref<Expression>(),
				GenerateTokenErrorMsg("Unknown token", tk.location)
		};
	}
	}
}

std::pair<Ref<Expression>, std::string> ParseMultiplicativeExpr(TokenConsumer& TC) {
	// Get experession left of operator.
	auto& [left, left_error] = ParseLiteral(TC);
	if (!left_error.empty()) return { Ref<Expression>(), left_error };

	// Check if token operator exists and in it's multiplicative then enter loop.
	while (TC.TokenList.size() - 1 != TC.CurrentIndex &&
		   TC.TokenList[TC.CurrentIndex + 1].type == TokenType::BinaryOperation &&
		  (TC.TokenList[TC.CurrentIndex + 1].value == "*" ||
		   TC.TokenList[TC.CurrentIndex + 1].value == "/" || 
		   TC.TokenList[TC.CurrentIndex + 1].value == "%" ||
		   TC.TokenList[TC.CurrentIndex + 1].value == "^")) {
		// Get operator
		TC.CurrentIndex += 1;
		std::string oper = TC.TokenList[TC.CurrentIndex].value;

		// Check if right expression is valid
		if (TC.TokenList.size() - 1 == TC.CurrentIndex) {
			return {
				Ref<Expression>(),
				GenerateTokenErrorMsg("Unexpected binary operator", TC.TokenList[TC.CurrentIndex].location)
			};
		}
		TC.CurrentIndex += 1;

		// Get right expression
		auto& [right, right_error] = ParseLiteral(TC);
		if (!right_error.empty()) return { Ref<Expression>(), right_error };

		// Create the binary operation expression
		left = BinaryOperationExpr::Create(left, right, oper, left->GetStartIndex(), right->GetEndIndex());
	}

	return { left, "" };
}
std::pair<Ref<Expression>, std::string> ParseAdditiveExpr(TokenConsumer& TC) {

	// Get experession left of operator.
	auto& [left, left_error] = ParseMultiplicativeExpr(TC);
	if (!left_error.empty()) return { Ref<Expression>(), left_error };

	// Check if token operator exists and in it's additive then enter loop.
	while (TC.TokenList.size() - 1 != TC.CurrentIndex &&
		   TC.TokenList[TC.CurrentIndex + 1].type == TokenType::BinaryOperation &&
		  (TC.TokenList[TC.CurrentIndex + 1].value == "+" ||
		   TC.TokenList[TC.CurrentIndex + 1].value == "-")) {
		// Get operator
		TC.CurrentIndex += 1;
		std::string oper = TC.TokenList[TC.CurrentIndex].value;

		// Check if right expression is valid
		if (TC.TokenList.size() - 1 == TC.CurrentIndex) {
			return {
				Ref<Expression>(),
				GenerateTokenErrorMsg("Unexpected binary operator", TC.TokenList[TC.CurrentIndex].location)
			};
		}
		TC.CurrentIndex += 1;

		// Get right expression
		auto& [right, right_error] = ParseMultiplicativeExpr(TC);
		if (!right_error.empty()) return { Ref<Expression>(), right_error };

		// Create the binary operation expression
		left = BinaryOperationExpr::Create(left, right, oper, left->GetStartIndex(), right->GetEndIndex());
	}

	return { left, "" };
}

std::pair<Ref<ProgramStmt>, std::string> Parse(const std::vector<Token>& tokenList) {
	TokenConsumer TC;
	TC.TokenList = tokenList;
	TC.CurrentIndex = 0;

	std::vector<Ref<Statement>> statements;

	for (; TC.CurrentIndex < TC.TokenList.size(); ++TC.CurrentIndex) {
		auto& [stmt, error] = ParseAdditiveExpr(TC);
		if (!error.empty()) return { Ref<ProgramStmt>(), error };

		statements.push_back(stmt);
	}

	return { ProgramStmt::Create(statements), "" };
}