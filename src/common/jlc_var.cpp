#include "common/jlc_var.h"

namespace JLC::VAR
{
    std::string JLCVar::str()
    {
        return type->str() + " " + name + ";";
    }
} // namespace JLC::VAR