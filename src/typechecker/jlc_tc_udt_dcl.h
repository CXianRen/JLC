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

#include "parser/Skeleton.H"

namespace JLC::TC
{
    using namespace JLC::TYPE;
    using namespace JLC::ENUM;
    using namespace JLC::STRUCT;
    using namespace JLC::CLASS;
    using namespace JLC::FUNC;
    using namespace JLC::CONTEXT;

    class JLC_UDT_DC_Checker : public Skeleton
    {
    public:
        JLC_UDT_DC_Checker(){};

        JLC_UDT_DC_Checker(
            std::shared_ptr<JLCContext> context)
        {
            context_ = context;
        };

        ~JLC_UDT_DC_Checker() = default;

        // context
        std::shared_ptr<JLC::CONTEXT::JLCContext>
            context_;

    public:
        /*
         * make sure there is not name conflict
         * between enum, class, and typedef.
         * Why here is not necessary to check struct?
         * Because struct type is not used directly in JLC,
         * it is used in typedef.
         */

        // chekcer selfdefined functions
        void check_user_defined_type_conflict(std::string type_name);

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