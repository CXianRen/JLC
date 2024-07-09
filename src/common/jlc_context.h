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

        // defined typedef (alias for pointer type)
        std::map<std::string, std::string> typedefs;

        // defined class
        std::map<std::string, std::shared_ptr<JLC::CLASS::JLCClass>> classes;

        // defined function
        std::map<std::string, std::shared_ptr<JLC::FUNC::JLCFunc>> funcs;

        std::map<std::string, std::vector<std::string>> scope_funcs_map;

        // api for enum
        void add_enum(const std::string &name,
                      std::shared_ptr<JLC::ENUM::JLCEnum> e)
        {
            enums[name] = e;
        }

        bool has_enum(const std::string &name)
        {
            return enums.find(name) != enums.end();
        }

        std::shared_ptr<JLC::ENUM::JLCEnum>
        get_enum(const std::string &name)
        {
            if (!has_enum(name))
            {
                return nullptr;
            }
            return enums[name];
        }

        // api for typedef
        void add_typedef(const std::string &name,
                         const std::string &type)
        {
            typedefs[name] = type;
        }

        bool has_typedef(const std::string &name)
        {
            return typedefs.find(name) != typedefs.end();
        }

        std::string get_typedef_type(const std::string &name)
        {
            if (!has_typedef(name))
            {
                return "";
            }
            return typedefs[name];
        }

        // api for struct
        void add_struct(const std::string &name,
                        std::shared_ptr<JLC::STRUCT::JLCStruct> s)
        {
            structs[name] = s;
        }

        bool has_struct(const std::string &name)
        {
            return structs.find(name) != structs.end();
        }

        std::shared_ptr<JLC::STRUCT::JLCStruct>
        get_struct(const std::string &name)
        {
            if (!has_struct(name))
            {
                return nullptr;
            }
            return structs[name];
        }

        // api for class

        void add_class(const std::string &name,
                       std::shared_ptr<JLC::CLASS::JLCClass> c)
        {
            classes[name] = c;
        }

        bool has_class(const std::string &name)
        {
            return classes.find(name) != classes.end();
        }

        std::shared_ptr<JLC::CLASS::JLCClass>
        get_class(const std::string &name)
        {
            if (!has_class(name))
            {
                return nullptr;
            }
            return classes[name];
        }

        // api for function
        std::string get_scope_name(
            std::string func_name, std::string scope)
        {
            if (scope == "global")
            {
                return func_name;
            }

            return scope + "::" + func_name;
        }

        void add_func(const std::string &name,
                      std::shared_ptr<JLC::FUNC::JLCFunc> f)
        {
            funcs[name] = f;
        }

        bool has_func(const std::string &name)
        {
            return funcs.find(name) != funcs.end();
        }

        std::shared_ptr<JLC::FUNC::JLCFunc>
        get_func(const std::string &name)
        {
            if (!has_func(name))
            {
                return nullptr;
            }
            return funcs[name];
        }

        void add_func_to_scope(std::string scope, std::string func_name)
        {
            if (scope_funcs_map.find(scope) == scope_funcs_map.end())
            {
                scope_funcs_map[scope] = std::vector<std::string>();
            }
            scope_funcs_map[scope].push_back(func_name);
        }

        std::vector<std::string> get_funcs_in_scope(std::string scope)
        {
            if (scope_funcs_map.find(scope) == scope_funcs_map.end())
            {
                return std::vector<std::string>();
            }
            return scope_funcs_map[scope];
        }

        std::string str();

    }; // class JLCContext
} // namespace JLC::CONTEXT

#endif // __JLC_CONTEXT_H__