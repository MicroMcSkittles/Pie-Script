#include "ErrorHandler.h"
#include <iomanip>

namespace {
	static std::string s_Source;
	static std::vector<std::string> s_Lines; // Stores each line in source in a separate string

	struct LineBounds {
		uint32_t start;
		uint32_t end;
	};
	static std::vector<LineBounds> s_LineBounds; // Stores where each line starts and ends in the source string

	// Finds the line index from the source index.
	uint32_t FindLineIndex(uint32_t source_index) {
		for (int i = 0; i < s_LineBounds.size(); ++i) {
			if (s_LineBounds[i].start <= source_index && source_index <= s_LineBounds[i].end) {
				return i;
			}
		}
	}
}

void SetErrorSourceContext(const std::string& source)
{
	s_Source = source;

	s_Lines.clear();
	s_LineBounds.clear();
	std::string line;
	std::stringstream ss(s_Source);

	uint32_t start_index = 0;

	// Store each line and line bounds
	while (std::getline(ss, line, '\n')) {
		LineBounds lb;
		lb.start = start_index;
		lb.end = start_index + line.size();
		start_index += line.size() + 1;
		s_LineBounds.push_back(lb);
		s_Lines.push_back(line);
	}
}

std::string GenerateTokenErrorMsg(const std::string& error, Location loc)
{
	std::stringstream error_stream;

	// Push back line
	error_stream << (loc.line_index + 1) << ") ";
	int line_offset = error_stream.str().size();
	error_stream << s_Lines[loc.line_index] << '\n';

	// Generate arrow that points to error
	for (uint32_t i = 0; i < s_Lines[loc.line_index].size() + line_offset; ++i) {
		if (i == loc.line_start + line_offset || i == loc.line_end + line_offset) {
			error_stream << "^";
		}
		else if (loc.line_start + line_offset < i && i < loc.line_end + line_offset) {
			error_stream << "=";
		}
		else {
			error_stream << "-";
		}
	}
	error_stream << '\n';
	error_stream << error;

	return error_stream.str();
}

std::string GenerateRuntimeErrorMsg(Ref<Statement> stmt, const std::string& message)
{
	// Find every line that the statement is on
	uint32_t start_line_index = FindLineIndex(stmt->GetStartIndex());
	uint32_t end_line_index = FindLineIndex(stmt->GetEndIndex());

	// Push back line
	int LineIndexMaxSize = log10(end_line_index + 1);
	std::stringstream error_stream;
	for (int i = start_line_index; i <= end_line_index; ++i) {
		error_stream << std::left << std::setw(LineIndexMaxSize + 1) << i + 1 << " ) " << s_Lines[i] << "\n";
	}
	error_stream << message;

	return error_stream.str();
}
