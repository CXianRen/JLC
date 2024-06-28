#ifndef __JLC_TC_FUNC_DCL_H__
#define __JLC_TC_FUNC_DCL_H__

#include <vector>
#include <string>

#include "common/jlc_context.h"
#include "common/debug.h"

#include "typechecker/jlc_tc_tvisitor.h"

namespace JLC::TC
{

    class JLC_FUNC_CD_Checker : public TypeVisitor
    {
    public:
        JLC_FUNC_CD_Checker(){};

        JLC_FUNC_CD_Checker(
            std::shared_ptr<JLCContext> context)
        {
            context_ = context;
        };

        ~JLC_FUNC_CD_Checker() = default;

    public:
        const std::string GLOBAL_SCOPE = "global";

        std::string func_scope_;
        void set_scope(const std::string &scope)
        {
            func_scope_ = scope;
        }

        std::string get_scope()
        {
            return func_scope_;
        }

    public:
        // override visitor functions

        /* function */
        void visitGFuncDef(GFuncDef *p) override;
        void visitClass(Class *p) override;
        void visitClassWE(ClassWE *p) override;

        void visitFuncDef(FuncDef *p) override;
    };

} // namespace JLC::TC

#endif // __JLC_TC_FUNC_DCL_H__