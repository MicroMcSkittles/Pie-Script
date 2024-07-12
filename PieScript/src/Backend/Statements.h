#pragma once
#include <cstdint>
#include <vector>
#include "Utils.h"

enum class StatementType {
	None = 0,
	Program,
	NumericLiteral,
	StringLiteral,
	BinaryOperation
};

// Statement base class
class Statement {
public:
	virtual StatementType GetType() = 0;

	virtual uint32_t GetStartIndex() = 0;
	virtual uint32_t GetEndIndex() = 0;
	//virtual const std::vector<uint32_t>& GetLineIndexs() = 0;

	// Converts statement to string. indent is used for indenting. 
	virtual std::string to_string(std::string indent) = 0;
};

// Stores a list of Statements
class ProgramStmt : public Statement {
public:
	static Ref<ProgramStmt> Create(std::vector<Ref<Statement>> Statements);
	~ProgramStmt();

	virtual StatementType GetType() override { return StatementType::Program; }

	virtual uint32_t GetStartIndex() override;
	virtual uint32_t GetEndIndex() override;
	//virtual const std::vector<uint32_t>& GetLineIndexs() override;

	const std::vector<Ref<Statement>>& GetStatementList() const { return m_Stmts; }
	void PushStatement(Ref<Statement> stmt) { m_Stmts.push_back(stmt); }

	virtual std::string to_string(std::string indent) override;

private:
	ProgramStmt(std::vector<Ref<Statement>> Statments);

private:
	// The start index location in source code
	uint32_t m_StartIndex;
	// The end index location in source code
	uint32_t m_EndIndex;

	// A list of statements
	std::vector<Ref<Statement>> m_Stmts;
};