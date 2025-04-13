#pragma once
#include "Utils.h"
#include "Backend/Token.h"
#include "Backend/Statements.h"

// Lets the error handler generate error messages with the source
void SetErrorSourceContext(const std::string& source);

// Uses token location struct to generate a error message
std::string GenerateTokenErrorMsg(const std::string& error, Location loc);

// Uses statement location to generate a error message
std::string GenerateRuntimeErrorMsg(Ref<Statement> stmt, const std::string& message);