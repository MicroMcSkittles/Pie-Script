#pragma once
#include "Backend/Expressions.h"
#include "RuntimeValue.h"

// Interprets numaric literal experessions
std::pair<Ref<RuntimeValue>, std::string> InterpNumaricLiteral(Ref<NumericLiteralExpr> numericLiteral);
// Interprets binary operation experessions
std::pair<Ref<RuntimeValue>, std::string> InterpBinaryOperation(Ref<BinaryOperationExpr> binaryOperation);
// Interprets program statements
std::pair<Ref<RuntimeValue>, std::string> InterpProgram(Ref<ProgramStmt> program);
// Interprets a statement
std::pair<Ref<RuntimeValue>, std::string> Interp(Ref<Statement> stmt);