#ifndef __JLC_FUNC_H__
#define __JLC_FUNC_H__

#include <string>
#include <vector>

#include "jlc_var.h"
#include "jlc_type.h"
#include "jlc_blk.h"

namespace JLC::FUNC
{
    class JLCFunc
    {
    public:
        std::string name;
        std::shared_ptr<JLC::TYPE::JLCType> return_type;
        std::vector<JLC::VAR::JLCVar> args;

        JLCFunc(const std::string &name,
                std::shared_ptr<JLC::TYPE::JLCType> return_type)
            : name(name), return_type(return_type) {}

        void add_arg(JLC::VAR::JLCVar arg)
        {
            args.push_back(arg);
        }

        bool is_exist_arg(const std::string &name);

        JLC::VAR::JLCVar &get_arg(const std::string &name);

        // block
        std::vector<JLC::BLK::JLCBlk> blks;

        // new block
        void push_blk()
        {
            JLC::BLK::JLCBlk blk;
            blks.push_back(blk);
        }

        void pop_blk()
        {
            blks.pop_back();
        }

        void add_var(JLC::VAR::JLCVar var)
        {
            blks.back().add_var(var);
        }

        bool is_exist_var(const std::string &name);

        JLC::VAR::JLCVar &get_var(const std::string &name);

        std::string str();
    }; // class JLCFunc

} // namespace JLC::FUNC

#endif // __JLC_FUNC_H__