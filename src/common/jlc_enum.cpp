#include "jlc_enum.h"

namespace JLC::ENUM
{

    void JLCEnum::add_member(const std::string &name)
    {
        members.push_back(std::make_pair(name, members.size()));
    }

    int JLCEnum::get_member_value(const std::string &name)
    {
        for (auto &member : members)
        {
            if (member.first == name)
            {
                return member.second;
            }
        }
        return -1;
    }

    bool JLCEnum::has_member(const std::string &name)
    {
        for (auto &member : members)
        {
            if (member.first == name)
            {
                return true;
            }
        }
        return false;
    }

    std::string JLCEnum::str()
    {
        std::string ret = "enum " + obj_name + " {\n";
        for (auto &member : members)
        {
            ret += "    " + member.first + " = " + std::to_string(member.second) + ",\n";
        }
        ret += "};\n";
        return ret;
    }
}