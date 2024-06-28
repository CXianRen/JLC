/**
 *  TC - Type Checker
 *  UDT_DC - user defined type declaration
 *  This checker is for checking top type
 *  declarations including enums, structs, classes.
 */
#ifndef __JLC_TC_UDT_DC_H__
#define __JLC_TC_UDT_DC_H__

#include <vector>
#include <string>

#include "common/jlc_context.h"
#include "common/debug.h"

#include "typechecker/jlc_tc_tvistor.h"

namespace JLC::TC
{
    class JLC_UDT_DC_Checker : public TypeVisitor
    {
    public:
        JLC_UDT_DC_Checker(){};

        JLC_UDT_DC_Checker(
            std::shared_ptr<JLCContext> context)
        {
            context_ = context;
        };

        ~JLC_UDT_DC_Checker() = default;

    public:
        // chekcer selfdefined functions

    public:
        // override visitor functions
        void visitProgram(Program *p);

        /* enum */
        void visitEnum(Enum *p) override;

        /* struct */
        void visitStruct(Struct *p) override;

        /* typedef */
        void visitTypeDef(TypeDef *p) override;
        void visitTypeDefWS(TypeDefWS *p) override;
        std::vector<std::string> typedef_need_check_;

        /* class */
        void visitClass(Class *p) override;
        void visitClassWE(ClassWE *p) override;
        std::vector<std::string> class_need_check_;
    };
} // namespace JLC::TC

#endif // __JLC_TC_UDT_DC_H__