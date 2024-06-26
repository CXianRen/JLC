#ifndef __JLC_TC_ERROR_H__
#define __JLC_TC_ERROR_H__

#include <stdexcept>
#include <string>

namespace JLC::TC
{
    class JLCTCError : public std::runtime_error
    {
    public:
        JLCTCError(const std::string &msg)
            : std::runtime_error(msg) {}
    };
}

#endif