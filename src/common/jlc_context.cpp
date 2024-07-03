#include "common/jlc_context.h"

namespace JLC::CONTEXT
{

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