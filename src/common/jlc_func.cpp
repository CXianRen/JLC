#include "common/jlc_func.h"

#include <stdexcept>

namespace JLC::FUNC
{

    bool JLCFunc::is_exist_arg(const std::string &name)
    {
        for (auto &a : args)
        {
            if (a.name == name)
            {
                return true;
            }
        }
        return false;
    }

    JLC::VAR::JLCVar &JLCFunc::get_arg(const std::string &name)
    {
        for (auto &a : args)
        {
            if (a.name == name)
            {
                return a;
            }
        }
        throw std::runtime_error("Argument " + name + " not found");
    }

    bool JLCFunc::is_exist_var(const std::string &name)
    {
        for (auto &b : blks)
        {
            if (b.is_exist_var(name))
            {
                return true;
            }
        }
        // check if the variable is an argument
        if (is_exist_arg(name))
        {
            return true;
        }
        return false;
    }

    JLC::VAR::JLCVar &JLCFunc::get_var(const std::string &name)
    {
        for (auto &b : blks)
        {
            if (b.is_exist_var(name))
            {
                return b.get_var(name);
            }
        }
        // check if the variable is an argument
        if (is_exist_arg(name))
        {
            return get_arg(name);
        }
        throw std::runtime_error("Variable " + name + " not found");
    }

    std::string JLCFunc::str()
    {
        std::string s = "Function: " + name + "\n";
        s += "Return type: " + return_type->str() + "\n";
        // arguments
        s += "Arguments:\n";
        for (auto &a : args)
        {
            s += "\t\t" + a.str() + "\n";
        }
        // blocks
        s += "Blocks:\n";
        for (auto &b : blks)
        {
            s += b.str();
        }
        return s;
    }

} // namespace JLC::FUNC