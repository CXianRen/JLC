#include "common/jlc_blk.h"

#include <stdexcept>

namespace JLC::BLK
{
    bool JLCBlk::is_exist_var(const std::string &name)
    {
        for (auto &v : vars)
        {
            if (v.name == name)
            {
                return true;
            }
        }
        return false;
    }

    JLC::VAR::JLCVar &JLCBlk::get_var(const std::string &name)
    {
        for (auto &v : vars)
        {
            if (v.name == name)
            {
                return v;
            }
        }
        throw std::runtime_error("Variable " + name + " not found");
    }

    std::string JLCBlk::str()
    {
        std::string s = "Block:\n";
        for (auto &v : vars)
        {
            s += "\t" + v.str() + "\n";
        }
        return s;
    }
} // namespace JLC::BLK