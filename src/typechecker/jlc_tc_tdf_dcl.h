/**
 *  TC - Type Checker
 *  TDF - TOP DEFINITION
 *  This checker is for checking top definitions'
 *  declarations including enums, structs, classes, functions.
 */
#ifndef __JLC_TC_TDF_H__
#define __JLC_TC_TDF_H__

#include <vector>
#include <string>

#include "common/jlc_context.h"
#include "common/debug.h"

#include "typechecker/jlc_tc_tvistor.h"

namespace JLC::TC
{
    class JLCTopDefinitionChecker : public TypeVisitor
    {
    public:
        JLCTopDefinitionChecker(){};

        JLCTopDefinitionChecker(
            std::shared_ptr<JLCContext> context)
        {
            context_ = context;
        };

        ~JLCTopDefinitionChecker() = default;

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

#endif // __JLC_TC_TDF_H__