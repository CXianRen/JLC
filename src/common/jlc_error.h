#ifndef __JLC_ERROR_H__
#define __JLC_ERROR_H__

#include <stdexcept>

namespace JLC
{
    class JLCError : public std::runtime_error
    {
    public:
        JLCError(const std::string &msg)
            : std::runtime_error(msg) {}
    };
}

#endif // __JLC_ERROR_H__