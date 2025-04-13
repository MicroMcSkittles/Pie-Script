#pragma once
#include "Utils.h"

enum class RuntimeValueType {
	None = 0,
	Int,
	Double,
	String
};

class RuntimeValue {
public:
	static Ref<RuntimeValue> Create(const std::string& value, RuntimeValueType type) {
		return Ref<RuntimeValue>(new RuntimeValue(value, type));
	}

	RuntimeValueType GetType() { return m_Type; }
	std::string GetValue() { return m_Value; }

	std::string to_string() {
		std::stringstream ss;
		ss << RTValueToStr(m_Type) << ": ( " << m_Value << " )";
		return ss.str();
	}

private:
	RuntimeValue(const std::string& value, RuntimeValueType type)
		: m_Value(value), m_Type(type) { }

private:
	// Converts RuntimeValueType to String
	std::string RTValueToStr(RuntimeValueType value) {
		switch (value)
		{
		case RuntimeValueType::Int: return "Int";
		case RuntimeValueType::Double: return "Double";
		case RuntimeValueType::String: return "String";
		case RuntimeValueType::None: return "";
		};
		return "";
	}

private:
	std::string m_Value;
	RuntimeValueType m_Type;
};