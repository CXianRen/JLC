/**
 *  TC - Type Checker
 *  TDF - TOP DEFINITION
 *  This checker is for checking and
 *  collecting all the top-level definitions
 *  including enums, structs, classes, functions.
 */
#ifndef __JLC_TC_TDF_H__
#define __JLC_TC_TDF_H__

#include "parser/Skeleton.H"
#include "common/jlc_context.h"
#include "common/debug.h"

namespace JLC::TC
{
    using namespace JLC::TYPE;
    using namespace JLC::ENUM;
    using namespace JLC::STRUCT;
    using namespace JLC::CLASS;
    using namespace JLC::FUNC;
    using namespace JLC::CONTEXT;

    class JLCTopDefinitionChecker : public Skeleton
    {
    public:
        JLCTopDefinitionChecker()
        {
            context_ =
                std::make_shared<JLCContext>();
        };

        JLCTopDefinitionChecker(
            std::shared_ptr<JLCContext> context)
            : context_(context){};

        ~JLCTopDefinitionChecker() = default;

    private:
        // context
        std::shared_ptr<JLCContext>
            context_;

    public:
        // chekcer selfdefined functions

    public:
        // override visitor functions

        /* enum */
        void visitEnum(Enum *p) override;

        /* struct */
    };
} // namespace JLC::TC

#endif // __JLC_TC_TDF_H__