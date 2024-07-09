#include "jlc_struct.h"

namespace JLC::STRUCT
{

    void JLCStruct::add_member(const std::string &name,
                               std::shared_ptr<TYPE::JLCType> type)
    {
        members.push_back(std::make_pair(name, type));
    }

    std::shared_ptr<TYPE::JLCType>
    JLCStruct::get_member_type(const std::string &name)
    {
        for (auto &member : members)
        {
            if (member.first == name)
            {
                return member.second;
            }
        }
        return nullptr;
    }

    int JLCStruct::
        get_member_index(const std::string &name)
    {
        for (int i = 0; i < members.size(); i++)
        {
            if (members[i].first == name)
            {
                return i;
            }
        }
        return -1;
    }

    std::string JLCStruct::str()
    {
        std::string ret = "struct " + obj_name + " {\n";
        for (auto &member : members)
        {
            ret += "    " + member.second->str() + " " + member.first + ";\n";
        }
        ret += "};\n";
        return ret;
    }

} // namespace JLC::STRUCT