#ifndef __JLC_CLASS_H__
#define __JLC_CLASS_H__

#include "jlc_type.h"
#include "jlc_struct.h"

namespace JLC::CLASS
{
    class JLCClass : public STRUCT::JLCStruct
    {
    public:
        JLCClass(const std::string &name) : STRUCT::JLCStruct(name){};        
        std::string str();
    };

} // namespace JLC::CLASS

#endif // __JLC_CLASS_H__