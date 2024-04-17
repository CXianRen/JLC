#include "context.H"

std::string to_string(type_enum t) {
  switch(t) {
    case INT: return "int";
    case DOUB: return "double";
    case BOOL: return "bool";
    case VOID: return "void";
    case FUN: return "fun";
    case CHAR: return "char";
    case STRING: return "string";
    case ARRAY: return "array";
    case UNDEFINED: return "undefined";
  }
  return "unknown";
}

std::string to_string(const JLCType & t) {
  if(t.type != ARRAY) {
    return to_string(t.type);
  }
  std::string res = to_string(t.base_type);
  for(int i = 0; i < t.dimension; i++) {
    res += "[]";
  }
  return res;
}

bool JLCType::operator==(const JLCType &t) const	{
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
    return true;	
}
