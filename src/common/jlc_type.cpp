#include "jlc_type.h"

namespace JLC::TYPE
{

    std::string JLCType::str()
    {
        switch (type)
        {
        case INT:
            return "int";
        case DOUB:
            return "double";
        case BOOL:
            return "bool";
        case VOID:
            return "void";
        case CHAR:
            return "char";
        case STRING:
            return "string";
        case ENUM:
            return "enum " + obj_name;
        case STRUCT:
            return "struct " + obj_name;
        case CLASS:
        {
            if (base_type)
            {
                return "class " + obj_name + " : " + base_type->str();
            }
            else
            {
                return "class " + obj_name;
            }   
        }

        case ARRAY:
            return base_type->str() + "[]";
        case UNDEFINED:
            return "undefined";
        default:
            return "unknown";
        }
    }

    bool JLCType::operator!=(const JLCType &t) const
    {
        return !(*this == t);
    }

    bool JLCType::operator==(const JLCType &t) const
    {
        if (type != t.type)
            return false;

        if (type == ARRAY)
        {
            if (!base_type || !t.base_type)
                return false;
            if (*base_type == UNDEFINED || *t.base_type == UNDEFINED)
                return false;
            if (*base_type != *t.base_type)
            {
                return false;
            }
            return true;
        }
        if (type == ENUM || type == STRUCT)
            return obj_name == t.obj_name;

        // if type is class, child class can be assigned to parent class
        if (type == CLASS)
        {
            if (obj_name == t.obj_name)
                return true;

            // check if t is a child class of this
            auto t_base = t.base_type;
            while (t_base)
            {
                if (t_base->obj_name == obj_name)
                    return true;
                t_base = t_base->base_type;
            }
            return false;
        }

        return true;
    }

} // namespace JLC::TYPE