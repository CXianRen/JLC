#ifndef __JLC_TC_UDT_DEF_H__
#define __JLC_TC_UDT_DEF_H__

#include <vector>
#include <string> 

#include "common/jlc_context.h"
#include "common/debug.h"

#include "typechecker/jlc_tc_tvisitor.h"

namespace JLC::TC
{
    class JLC_TC_UDT_DEF_Checker : public TypeVisitor
    {
    public:
        JLC_TC_UDT_DEF_Checker(){};

        JLC_TC_UDT_DEF_Checker(
            std::shared_ptr<JLCContext> context)
        {
            context_ = context;
        };

        ~JLC_TC_UDT_DEF_Checker() = default;
    public:

        /* enum */
        void visitEnum(Enum *p) override;
        /* struct */
        // void visitStruct(Struct *p) override;
        // void visitTypeDefWS(TypeDefWS *p) override;
        // /* class */
        // void visitClass(Class *p);
        // void visitClassWE(ClassWE *p);
        // /* function */
        // void visitFuncDef(FuncDef *p) override;
    };

} // namespace JLC::TC

#endif // __JLC_TC_UDT_DEF_H__