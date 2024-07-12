#include "Statements.h"

Ref<ProgramStmt> ProgramStmt::Create(std::vector<Ref<Statement>> Statments)
{
	return Ref<ProgramStmt>(new ProgramStmt(Statments));
}

ProgramStmt::ProgramStmt(std::vector<Ref<Statement>> Statments)
	: m_Stmts(Statments) {
	// Get start and end from statement 
	m_StartIndex = m_Stmts[0]->GetStartIndex();
	m_EndIndex = m_Stmts[Statments.size() - 1]->GetEndIndex();
}
ProgramStmt::~ProgramStmt()
{
}

uint32_t ProgramStmt::GetStartIndex()
{
	return m_StartIndex;
}

uint32_t ProgramStmt::GetEndIndex()
{
	return m_EndIndex;
}

std::string ProgramStmt::to_string(std::string indent)
{
	std::stringstream ss;
	ss << indent << "Program Statement {\n";
	ss << indent + TabIndent << "Location { " << m_StartIndex << ", " << m_EndIndex << " }\n";

	for (auto& s : m_Stmts) {
		ss << s->to_string(indent + TabIndent) << "\n";
	}

	ss << indent << "}";

	return ss.str();
}

