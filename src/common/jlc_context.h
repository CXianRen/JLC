#ifndef __JLC_CONTEXT_H__
#define __JLC_CONTEXT_H__

#include <map>
#include <string>
#include <vector>
#include <memory>

#include "common/jlc_type.h"
#include "common/jlc_var.h"
#include "common/jlc_enum.h"
#include "common/jlc_struct.h"
#include "common/jlc_class.h"
#include "common/jlc_blk.h"
#include "common/jlc_func.h"

namespace JLC::CONTEXT
{
    class JLCContext
    {
    public:
        JLCContext() = default;
        // defined enum;
        std::map<std::string, std::shared_ptr<JLC::ENUM::JLCEnum>> enums;

        // defined struct
        std::map<std::string, std::shared_ptr<JLC::STRUCT::JLCStruct>> structs;

        // defined class
        std::map<std::string, std::shared_ptr<JLC::CLASS::JLCClass>> classes;

        // defined function
        std::map<std::string, std::shared_ptr<JLC::FUNC::JLCFunc>> funcs;

        // api for enum
        void add_enum(const std::string &name,
                      std::shared_ptr<JLC::ENUM::JLCEnum> e)
        {
            enums[name] = e;
        }

        bool is_exist_enum(const std::string &name)
        {
            return enums.find(name) != enums.end();
        }

        std::shared_ptr<JLC::ENUM::JLCEnum>
        get_enum(const std::string &name)
        {
            return enums[name];
        }

        // api for struct
        void add_struct(const std::string &name,
                        std::shared_ptr<JLC::STRUCT::JLCStruct> s)
        {
            structs[name] = s;
        }

        bool is_exist_struct(const std::string &name)
        {
            return structs.find(name) != structs.end();
        }

        std::shared_ptr<JLC::STRUCT::JLCStruct>
        get_struct(const std::string &name)
        {
            return structs[name];
        }

        // api for class

        void add_class(const std::string &name,
                       std::shared_ptr<JLC::CLASS::JLCClass> c)
        {
            classes[name] = c;
        }

        bool is_exist_class(const std::string &name)
        {
            return classes.find(name) != classes.end();
        }

        std::shared_ptr<JLC::CLASS::JLCClass>
        get_class(const std::string &name)
        {
            return classes[name];
        }

        // api for function
        void add_func(const std::string &name,
                      std::shared_ptr<JLC::FUNC::JLCFunc> f)
        {
            funcs[name] = f;
        }

        bool is_exist_func(const std::string &name)
        {
            return funcs.find(name) != funcs.end();
        }

        std::shared_ptr<JLC::FUNC::JLCFunc>
        get_func(const std::string &name)
        {
            return funcs[name];
        }

        std::string str();

    }; // class JLCContext
} // namespace JLC::CONTEXT

#endif // __JLC_CONTEXT_H__