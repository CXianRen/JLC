#include "jlc_class.h"
#include "common/debug.h"


namespace JLC::CLASS
{

    bool JLCClass::has_member(const std::string &name)
    {
        if (JLC::STRUCT::JLCStruct::has_member(name))
        {
            return true;
        }
        if (parent_class)
        {
            return parent_class->has_member(name);
        }
        return false;
    }

    std::string JLCClass::str()
    {
        std::string ret = "class " + obj_name;
        if (parent_class)
        {
            ret = ret + " extends " + parent_class->obj_name;
        }
        ret = ret + " {\n";
        for (auto &member : members)
        {
            ret += "    " + member.second->str() + " " + member.first + ";\n";
        }
        ret += "};\n";
        return ret;
    }

} // namespace JLC::CLASS