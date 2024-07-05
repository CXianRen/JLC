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
                // DEBUG_PRINT("Class: " + type_name);

                std::vector<std::string> class_list;
                auto class_obj = context_->get_class(type_name);
                while (class_obj != nullptr)
                {
                    class_list.push_back(class_obj->obj_name);
                    // DEBUG_PRINT("Class e: " + class_obj->obj_name);
                    class_obj = class_obj->parent_class;
                }
                auto rtype = JLCType(type_enum::CLASS, class_list.back(), nullptr);
                for (int i = class_list.size() - 2; i >= 0; i--)
                {
                    rtype = JLCType(type_enum::CLASS, class_list[i],
                                    std::make_shared<JLCType>(rtype));
                }
                g_type_ = rtype;
            }
            else if (context_->has_typedef(type_name))
            {
                auto real_type_name = context_->get_typedef_type(type_name);
                g_type_ = JLCType(type_enum::STRUCT, real_type_name);
            }
            else if (context_->has_struct(type_name))
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
        // visit immediate value
        void visitELitNull(ELitNull *p) override
        {
            // null can be any type if
            // it is assigned to a pointer type object
        }

        void visitELitInt(ELitInt *e_lit_int)
        {
            /* Code For ELitInt Goes Here */

            visitInteger(e_lit_int->integer_);
            g_type_ = JLCType(type_enum::INT);
        }

        void visitELitDoub(ELitDoub *e_lit_doub)
        {
            /* Code For ELitDoub Goes Here */

            g_type_ = JLCType(type_enum::DOUB);
        }

        void visitELitTrue(ELitTrue *e_lit_true)
        {
            g_type_ = JLCType(type_enum::BOOL);
        }

        void visitELitFalse(ELitFalse *e_lit_false)
        {
            g_type_ = JLCType(type_enum::BOOL);
        }

        void visitEString(EString *e_string)
        {
            g_type_ = JLCType(type_enum::STRING);
        }

    }; // class TypeVisitor
} // JLC::TC

#endif // __JLC_TC_TVISTOR_H__