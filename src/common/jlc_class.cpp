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

    std::shared_ptr<TYPE::JLCType> JLCClass::
        get_member_type(const std::string &name)
    {
        for (auto &member : members)
        {
            if (member.first == name)
            {
                return member.second;
            }
        }
        if (parent_class)
        {
            return parent_class->get_member_type(name);
        }
        return nullptr;
    }

    int JLCClass::
        get_member_index(const std::string &name)
    {
        // inherit list
        std::vector<std::shared_ptr<JLCClass>> class_list;
        std::shared_ptr<JLCClass> p = parent_class;
        while (p)
        {
            class_list.push_back(p);
            p = p->parent_class;
        }

        // iterate the inherit list to find the member and return the index
        int idx = 1; // skip the type id field
        for (int i = class_list.size() - 1; i >= 0; i--)
        {
            auto &c = class_list[i];
            for (auto &member : c->members)
            {
                if (member.first == name)
                {
                    return idx;
                }
                idx++;
            }
        }
        for (auto &member : members)
        {
            if (member.first == name)
            {
                return idx;
            }
            idx++;
        }

        return -1;
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