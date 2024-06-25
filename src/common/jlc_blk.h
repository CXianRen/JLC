#ifndef __JLC_BLK_H__
#define __JLC_BLK_H__

#include <string>
#include <vector>

#include "jlc_var.h"

namespace JLC::BLK
{
    class JLCBlk
    {
    public:
        std::vector<JLC::VAR::JLCVar> vars;

        JLCBlk() = default;

        void add_var(JLC::VAR::JLCVar var)
        {
            vars.push_back(var);
        }

        // check if the variable is declared
        bool is_exist_var(const std::string &name);

        // get variable by name
        JLC::VAR::JLCVar &get_var(const std::string &name);

        std::string str();

    }; // class JLCBlk

} // namespace JLC::BLK

#endif // __JLC_BLK_H__