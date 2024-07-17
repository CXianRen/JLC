#include "common/jlc_context.h"
#include <algorithm>
namespace JLC::CONTEXT
{

    std::vector<std::string> JLCContext::
        gen_funcs_list_of_class(std::string class_name)
    {
        std::vector<std::string> res;

        std::shared_ptr<JLC::CLASS::JLCClass>
            c = classes[class_name];

        std::vector<std::shared_ptr<JLC::CLASS::JLCClass>> class_list;
        std::shared_ptr<JLC::CLASS::JLCClass> p = c;
        while (p)
        {
            class_list.push_back(p);
            p = p->parent_class;
        }
        // iterate the class list from root to inherit class
        for (int i = class_list.size() - 1; i >= 0; i--)
        {
            auto &c = class_list[i];
            auto funcs = get_funcs_in_scope(c->obj_name);

            for (auto &f : funcs)
            {
                // check if the function is already in the list
                bool found = false;
                for (auto &r : res)
                {
                    // remove the scope name
                    auto name = r.substr(r.find_first_of('_') + 1);
                    if (name == f)
                    {
                        r = get_scope_name(f, c->obj_name);
                        found = true;
                        break;
                    }
                }
                if (found)
                {
                    continue;
                }
                res.push_back(get_scope_name(f, c->obj_name));
            }
        }
        return res;
    }

    std::string JLCContext::str()
    {
        // print enums
        std::string res = "ENUMS\n";
        for (auto &e : enums)
        {
            res += e.first + ":\n";
            res += e.second->str();
            res += "\n";
        }

        // print structs
        res += "STRUCTS:\n";
        for (auto &s : structs)
        {
            res += s.first + ":\n";
            res += s.second->str();
            res += "\n";
        }

        // print typedefs
        res += "TYPEDEFS:\n";
        for (auto &t : typedefs)
        {
            res += t.first + ":\n";
            res += t.second + "\n";
            res += "\n";
        }

        // print classes
        res += "CLASSES:\n";
        for (auto &c : classes)
        {
            res += c.first + ":\n";
            res += c.second->str();
            res += "\n";
        }

        // print functions
        res += "FUNCTIONS:\n";
        for (auto &f : funcs)
        {
            res += f.first + ":\n";
            res += f.second->str();
            res += "\n";
        }
        return res;
    }

} // namespace JLC::CONTEXT