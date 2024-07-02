#ifndef __JLC_TC_current_func_DEF_H__
#define __JLC_TC_current_func_DEF_H__

#include <vector>
#include <string>

#include "common/jlc_context.h"
#include "common/debug.h"

#include "typechecker/jlc_tc_func_dcl.h"

namespace JLC::TC
{
    class JLC_FUNC_DEF_Checker : public JLC_FUNC_CD_Checker
    {
    public:
        JLC_FUNC_DEF_Checker()
            : JLC_FUNC_CD_Checker(),
              current_func_(nullptr){};

        JLC_FUNC_DEF_Checker(
            std::shared_ptr<JLCContext> context)
        {
            context_ = context;
            current_func_ = nullptr;
        };

        ~JLC_FUNC_DEF_Checker() = default;
    
    public:
        // current function object
        std::shared_ptr<JLC::FUNC::JLCFunc> current_func_;

        void visitFuncDef(FuncDef *p) override;


        // block scope
        void visitBStmt(BStmt *p);

        // declaration variables
        void visitNoInit(NoInit *p) override;
        void visitInit(Init *p) override;


    }; // class JLC_FUNC_DEF_Checker

} // namespace JLC::TC

#endif // __JLC_TC_FUNC_DEF_H__