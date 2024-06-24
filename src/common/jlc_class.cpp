#include "jlc_class.h"

namespace JLC::CLASS
{

    std::string JLCClass::str()
    {
        std::string ret = "class " + obj_name + " {\n";
        for (auto &member : members)
        {
            ret += "    " + member.second->str() + " " + member.first + ";\n";
        }
        ret += "};\n";
        return ret;
    }

} // namespace JLC::CLASS