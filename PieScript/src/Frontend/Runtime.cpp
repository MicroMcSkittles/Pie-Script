#include "Runtime.h"
#include "ErrorHandler.h"

std::pair<Ref<RuntimeValue>, std::string> InterpNumaricLiteral(Ref<NumericLiteralExpr> numericLiteral)
{
	// Finds out if numaric literal is a double or int
	if (numericLiteral->IsDouble()) return { RuntimeValue::Create(numericLiteral->GetValue(), RuntimeValueType::Double), "" };
	else if (numericLiteral->IsInt()) return { RuntimeValue::Create(numericLiteral->GetValue(), RuntimeValueType::Int), "" };
	return { {}, GenerateRuntimeErrorMsg(numericLiteral, "? Numaric Literal should not exist") };
}

std::pair<Ref<RuntimeValue>, std::string> InterpBinaryOperation(Ref<BinaryOperationExpr> binaryOperation)
{
	// Get left and right expressions, then check for errors
	auto& [leftExpr, leftErr] = Interp(binaryOperation->GetLeftExpr());
	auto& [rightExpr, rightErr] = Interp(binaryOperation->GetRightExpr());

	if (!leftErr.empty()) { return { Ref<RuntimeValue>(), leftErr }; }
	if (!rightErr.empty()) { return { Ref<RuntimeValue>(), rightErr }; }

	// Get binary operations operator
	std::string oper = binaryOperation->GetOperator();

	// If left and right expressions are numaric
	if ((leftExpr->GetType() == RuntimeValueType::Double || leftExpr->GetType() == RuntimeValueType::Int) &&
		(rightExpr->GetType() == RuntimeValueType::Double || rightExpr->GetType() == RuntimeValueType::Int)) {
		// Get values from left and right expression
		double left = std::stod(leftExpr->GetValue());
		double right = std::stod(rightExpr->GetValue());

		double rslt = 0;
		RuntimeValueType rslt_type =
			(leftExpr->GetType() == RuntimeValueType::Int && rightExpr->GetType() == RuntimeValueType::Int)
			? RuntimeValueType::Int : RuntimeValueType::Double;
		
		if (oper == "+") rslt = left + right; 
		else if (oper == "-") rslt = left - right;
		else if (oper == "*") rslt = left * right;
		else if (oper == "/") rslt = left / right;
		else if (oper == "%") {
			// If either left or right expressions are not ints then % operator can't be used
			if (leftExpr->GetType() != RuntimeValueType::Int) return { {}, GenerateRuntimeErrorMsg(binaryOperation, "Left experession must be an int in a modulus operation") };
			else if (rightExpr->GetType() != RuntimeValueType::Int) return { {}, GenerateRuntimeErrorMsg(binaryOperation, "Right experession must be an int in a modulus operation") };
			rslt = (int)left % (int)right;
			rslt_type = RuntimeValueType::Int;
		}
		else if (oper == "^") {
			// If right expression is not a int then ^ operator can't be used
			if (rightExpr->GetType() != RuntimeValueType::Int) return { {}, GenerateRuntimeErrorMsg(binaryOperation, "Right experession must be an int in a power operation") };
			
			// raise left expression to the power of right expression
			rslt = left;
			for (int i = 1; i < (int)right; ++i) {
				rslt *= left;
			}

			rslt_type = leftExpr->GetType();
		}

		// Return result with the correct type
		std::stringstream ss;
		if (rslt_type == RuntimeValueType::Int) ss << (int)rslt;
		else if(rslt_type == RuntimeValueType::Double) ss << rslt;
		return { RuntimeValue::Create(ss.str(), leftExpr->GetType()), "" };
	}

	return { Ref<RuntimeValue>(), "" };
}

std::pair<Ref<RuntimeValue>, std::string> InterpProgram(Ref<ProgramStmt> program)
{
	std::pair<Ref<RuntimeValue>, std::string> rslt;

	// Loop through each statement in program
	for (auto& stmt : program->GetStatementList()) {
		rslt = Interp(stmt);
		if (!rslt.second.empty()) {
			return rslt;
		}
	}

	return rslt;
}

std::pair<Ref<RuntimeValue>, std::string> Interp(Ref<Statement> stmt)
{
	switch (stmt->GetType())
	{
	case StatementType::Program: return InterpProgram(std::dynamic_pointer_cast<ProgramStmt>(stmt));
	case StatementType::BinaryOperation: return InterpBinaryOperation(std::dynamic_pointer_cast<BinaryOperationExpr>(stmt));
	case StatementType::NumericLiteral: return InterpNumaricLiteral(std::dynamic_pointer_cast<NumericLiteralExpr>(stmt));
	case StatementType::StringLiteral: 
		return { RuntimeValue::Create(
			std::dynamic_pointer_cast<StringLiteralExpr>(stmt)->GetValue(),
			RuntimeValueType::String
		), "" };
	}

	return { Ref<RuntimeValue>(), "" };
}
