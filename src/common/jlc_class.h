#ifndef __JLC_CLASS_H__
#define __JLC_CLASS_H__

#include "jlc_type.h"
#include "jlc_struct.h"

#include <memory.h>

namespace JLC::CLASS
{
    class JLCClass : public STRUCT::JLCStruct
    {
    public:
        JLCClass(const std::string &name) : STRUCT::JLCStruct(name),
                                            parent_class(nullptr){};
        JLCClass(const std::string &name,
                 std::shared_ptr<JLCClass> parent_class)
            : STRUCT::JLCStruct(name),
              parent_class(parent_class){};
        std::string str();
        // inherit class
        std::shared_ptr<JLCClass> parent_class;

        bool has_member(const std::string &name) override;

        std::shared_ptr<TYPE::JLCType>
        get_member_type(const std::string &name);

        int get_member_index(const std::string &name);

        std::vector<std::string> functions;

        void add_function(const std::string &name);

        int get_function_index(const std::string &name);
    };

} // namespace JLC::CLASS

#endif // __JLC_CLASS_H__