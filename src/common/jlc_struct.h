#ifndef __JLC_STRUCT_H__
#define __JLC_STRUCT_H__

#include "jlc_type.h"

#include <string>
#include <vector>
#include <memory>

namespace JLC::STRUCT
{
    class JLCStruct
    {
    public:
        std::string struct_name;
        std::vector<std::pair<std::string,
                              std::shared_ptr<TYPE::JLCType>>>
            members;

        // int size = 0;

        JLCStruct(const std::string &name) : struct_name(name){};

        void add_member(const std::string &name,
                        std::shared_ptr<TYPE::JLCType> type);

        std::shared_ptr<TYPE::JLCType>
        get_member_type(const std::string &name);

        std::string str();
    };

} // namespace JLC::STRUCT

#endif // __JLC_STRUCT_H__