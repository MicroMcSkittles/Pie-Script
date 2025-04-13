#include "Expressions.h"

// NumericLiteralExpr ==========================

Ref<NumericLiteralExpr> NumericLiteralExpr::Create(std::string Value, uint32_t StartIndex, uint32_t EndIndex)
{
	return Ref<NumericLiteralExpr>(new NumericLiteralExpr(Value, StartIndex, EndIndex));
}

NumericLiteralExpr::NumericLiteralExpr(std::string Value, uint32_t StartIndex, uint32_t EndIndex)
	: m_Value(Value), m_StartIndex(StartIndex), m_EndIndex(EndIndex) { 
	if (m_Value.find('.') != std::string::npos) m_Type = Double;
	else m_Type = Int;
}
NumericLiteralExpr::~NumericLiteralExpr()
{
}

uint32_t NumericLiteralExpr::GetStartIndex()
{
	return m_StartIndex;
}
uint32_t NumericLiteralExpr::GetEndIndex()
{
	return m_EndIndex;
}

std::string NumericLiteralExpr::to_string(std::string indent)
{
	std::stringstream ss;

	ss << indent << "Numeric Literal Expression {\n";
	ss << indent + TabIndent << "Location { " << m_StartIndex << ", " << m_EndIndex << " }\n";
	ss << indent + TabIndent << "" << m_Value << "\n";
	ss << indent << "}";
	return ss.str();
}

// StringLiteralExpr ===========================

Ref<StringLiteralExpr> StringLiteralExpr::Create(std::string Value, std::string DebugValue, uint32_t StartIndex, uint32_t EndIndex)
{
	return Ref<StringLiteralExpr>(new StringLiteralExpr(Value, DebugValue, StartIndex, EndIndex));
}

StringLiteralExpr::StringLiteralExpr(std::string Value, std::string DebugValue, uint32_t StartIndex, uint32_t EndIndex)
	: m_Value(Value), m_DebugValue(DebugValue), m_StartIndex(StartIndex), m_EndIndex(EndIndex) { }
StringLiteralExpr::~StringLiteralExpr()
{
}

uint32_t StringLiteralExpr::GetStartIndex()
{
	return m_StartIndex;
}

uint32_t StringLiteralExpr::GetEndIndex()
{
	return m_EndIndex;
}

std::string StringLiteralExpr::to_string(std::string indent)
{
	std::stringstream ss;

	ss << indent << "String Literal Expression {\n";
	ss << indent + TabIndent << "Location { " << m_StartIndex << ", " << m_EndIndex << " }\n";
	ss << indent + TabIndent << m_DebugValue << "\n";
	ss << indent <<"}";

	return ss.str();
}

// BinaryOperationExpr ================================

Ref<BinaryOperationExpr> BinaryOperationExpr::Create(Ref<Expression> Left, Ref<Expression> Right, std::string Oper, uint32_t StartIndex, uint32_t EndIndex)
{
	return Ref<BinaryOperationExpr>(new BinaryOperationExpr(Left, Right, Oper, StartIndex, EndIndex));
}

BinaryOperationExpr::BinaryOperationExpr(Ref<Expression> Left, Ref<Expression> Right, std::string Oper, uint32_t StartIndex, uint32_t EndIndex)
	: m_Left(Left), m_Right(Right), m_Oper(Oper), m_StartIndex(StartIndex), m_EndIndex(EndIndex) { }
BinaryOperationExpr::~BinaryOperationExpr() { }

uint32_t BinaryOperationExpr::GetStartIndex()
{
	return m_StartIndex;
}

uint32_t BinaryOperationExpr::GetEndIndex()
{
	return m_EndIndex;
}

std::string BinaryOperationExpr::to_string(std::string indent)
{
	std::stringstream ss;

	ss << indent << "Binary Operation Expression {\n";
	ss << indent + TabIndent << "Location { " << m_StartIndex << ", " << m_EndIndex << " }\n";
	ss << indent + TabIndent << "Operator: " << m_Oper << "\n";

	ss << indent + TabIndent << "Left Expression {\n";
	ss << m_Left->to_string(indent + TabIndent + TabIndent) << "\n";
	ss << indent + TabIndent << "}\n";

	ss << indent + TabIndent << "Right Expression {\n";
	ss << m_Right->to_string(indent + TabIndent + TabIndent) << "\n";
	ss << indent + TabIndent << "}\n";

	ss << indent << "}";

	return ss.str();
}

