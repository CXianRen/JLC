#ifndef __JLC_VAR_H__
#define __JLC_VAR_H__
#include <string>
#include <memory>

#include "jlc_type.h"

namespace JLC::VAR
{
    class JLCVar
    {
    public:
        std::string name;
        std::shared_ptr<JLC::TYPE::JLCType> type;

        JLCVar(const std::string &name,
               std::shared_ptr<JLC::TYPE::JLCType> type) : name(name),
                                                           type(type){};

        // get type
        std::shared_ptr<JLC::TYPE::JLCType> get_type() { return type; }

        std::string str();
    }; // class JLCVar
}

#endif // __JLC_VAR_H__