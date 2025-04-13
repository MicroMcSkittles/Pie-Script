#pragma once
#include "Statements.h"

// Expression base class
class Expression : public Statement {
public:
	virtual StatementType GetType() = 0;

	virtual uint32_t GetStartIndex() = 0;
	virtual uint32_t GetEndIndex() = 0;

	// Converts statement to string. indent is used for indenting. 
	virtual std::string to_string(std::string indent) = 0;
};

class NumericLiteralExpr : public Expression {
public:
	static Ref<NumericLiteralExpr> Create(std::string Value, uint32_t StartIndex, uint32_t EndIndex);
	~NumericLiteralExpr();

	virtual StatementType GetType() override { return StatementType::NumericLiteral; }

	virtual uint32_t GetStartIndex() override;
	virtual uint32_t GetEndIndex() override;

	// Converts statement to string. indent is used for indenting. 
	virtual std::string to_string(std::string indent) override;

	bool IsInt() { return m_Type == Int; }
	bool IsDouble() { return m_Type == Double; }
	const std::string& GetValue() const { return m_Value; }

private:
	NumericLiteralExpr(std::string Value, uint32_t StartIndex, uint32_t EndIndex);

private:
	// The start index location in source code
	uint32_t m_StartIndex;
	// The end index location in source code
	uint32_t m_EndIndex;

	// Is the number a Float, Double, or Int
	enum {
		None = 0,
		Int,
		Float,
		Double
	};
	int m_Type;

	// The number stored as a string.
	std::string m_Value;
};

class StringLiteralExpr : public Expression {
public:
	static Ref<StringLiteralExpr> Create(std::string Value, std::string DebugValue, uint32_t StartIndex, uint32_t EndIndex);
	~StringLiteralExpr();

	virtual StatementType GetType() override { return StatementType::StringLiteral; }

	virtual uint32_t GetStartIndex() override;
	virtual uint32_t GetEndIndex() override;

	// Converts statement to string. indent is used for indenting. 
	virtual std::string to_string(std::string indent) override;

	const std::string& GetValue() const { return m_Value; }

private:
	StringLiteralExpr(std::string Value, std::string DebugValue, uint32_t StartIndex, uint32_t EndIndex);

private:
	// The start index location in source code
	uint32_t m_StartIndex;
	// The end index location in source code
	uint32_t m_EndIndex;

	// The stored value.
	std::string m_Value;
	std::string m_DebugValue;
};

class BinaryOperationExpr : public Expression {
public:
	static Ref<BinaryOperationExpr> Create(Ref<Expression> Left, Ref<Expression> Right, std::string Oper, uint32_t StartIndex, uint32_t EndIndex);
	~BinaryOperationExpr();

	virtual StatementType GetType() override { return StatementType::BinaryOperation; }

	virtual uint32_t GetStartIndex() override;
	virtual uint32_t GetEndIndex() override;

	const std::string& GetOperator() { return m_Oper; }
	Ref<Expression> GetLeftExpr() { return m_Left; }
	Ref<Expression> GetRightExpr() { return m_Right; }

	// Converts statement to string. indent is used for indenting. 
	virtual std::string to_string(std::string indent) override;

private:
	BinaryOperationExpr(Ref<Expression> Left, Ref<Expression> Right, std::string Oper, uint32_t StartIndex, uint32_t EndIndex);

private:
	// The start index location in source code
	uint32_t m_StartIndex;
	// The end index location in source code
	uint32_t m_EndIndex;

	// Stores the operator as a string
	std::string m_Oper;

	// The expression to the left of the operator
	Ref<Expression> m_Left;
	// The expression to the Right of the operator
	Ref<Expression> m_Right;
};