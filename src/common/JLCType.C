#include "context.H"
#include "util.h"

std::string to_string(type_enum t)
{
	switch (t)
	{
	case INT:
		return "int";
	case DOUB:
		return "double";
	case BOOL:
		return "bool";
	case VOID:
		return "void";
	case FUN:
		return "fun"; // not actually used
	case CHAR:
		return "char"; // not actually used
	case STRING:
		return "string"; // not actually used
	case ARRAY:
		return "array";
	case STRUCT:
		return "struct";
	case UNDEFINED:
		return "undefined";
	}
	return "unknown";
}

std::string to_string(const JLCType &t)
{
	if (t.type != ARRAY && t.type != STRUCT)
	{
		return to_string(t.type);
	}
	if (t.type == ARRAY)
	{
		std::string res = to_string(t.base_type);
		for (int i = 0; i < t.dimension; i++)
		{
			res += "[]";
		}
		return res;
	}
	if (t.type == STRUCT)
	{  
		// std::cout<< "t.name: " << t.name << "\n";
		return std::string("struct ") + t.name;
	}
	return "unknown";
}

bool is_basic_type(const std::string ident)
{
	if (ident == "int" || ident == "double" || ident == "bool")
	{
		return true;
	}
	return false;
}

bool JLCType::operator==(const JLCType &t) const
{
	// basic type
	if (type != t.type)
	{
		return false;
	}
	// array
	if (type == ARRAY)
	{
		if (base_type != t.base_type || dimension != t.dimension)
		{
			return false;
		}
	}
	if (type == STRUCT)
	{
		if (name != t.name)
		{
			return false;
		}
	}
	return true;
}
