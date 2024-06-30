#ifndef __JLC_TC_TVISTOR_H__
#define __JLC_TC_TVISTOR_H__

#include "parser/Skeleton.H"

#include "common/jlc_context.h"
#include "common/debug.h"
#include "jlc_tc_error.h"

namespace JLC::TC
{
    using namespace JLC::TYPE;
    using namespace JLC::ENUM;
    using namespace JLC::STRUCT;
    using namespace JLC::CLASS;
    using namespace JLC::FUNC;
    using namespace JLC::CONTEXT;

    class TypeVisitor : public Skeleton
    {

    public:
        TypeVisitor(){};

        TypeVisitor(
            std::shared_ptr<JLCContext> context) : context_(context){};

        ~TypeVisitor() = default;

        JLCType g_type_;

        // context
        std::shared_ptr<JLC::CONTEXT::JLCContext>
            context_;

        void visitInt(Int *p) override
        {
            g_type_ = JLCType(type_enum::INT);
        }
        void visitDoub(Doub *p) override
        {
            g_type_ = JLCType(type_enum::DOUB);
        }
        void visitBool(Bool *p) override
        {
            g_type_ = JLCType(type_enum::BOOL);
        }
        void visitVoid(Void *p) override
        {
            g_type_ = JLCType(type_enum::VOID);
        }

        // enum, struct, class
        void visitObjT(ObjT *obj_t) override
        {
            // get the type name
            std::string type_name = obj_t->ident_;

            // check the type of the objectT
            if (context_->has_enum(type_name))
            {
                g_type_ = JLCType(type_enum::ENUM, type_name);
            }
            else if (context_->has_class(type_name))
            {
                g_type_ = JLCType(type_enum::CLASS, type_name);
            }
            else if (context_->has_typedef(type_name))
            {
                g_type_ = JLCType(type_enum::STRUCT, type_name);
            }
            else
            {
                // error: type not defined
                throw JLCTCError("Type not defined: " + type_name);
            }
        }

        // array
        void visitArray(Array *array) override
        {
            if (array->type_)
                array->type_->accept(this);
            auto temp_type = g_type_;

            // new a base type
            auto base_type = std::make_shared<JLCType>(temp_type);

            if (array->bracketsopt_)
                array->bracketsopt_->accept(this);

            g_type_ = JLCType(ARRAY, base_type);
        }
    }; // class TypeVisitor

} // JLC::TC

#endif // __JLC_TC_TVISTOR_H__