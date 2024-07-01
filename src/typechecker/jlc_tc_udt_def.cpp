#include "typechecker/jlc_tc_udt_def.h"

namespace JLC::TC
{
    void JLC_TC_UDT_DEF_Checker::visitEnum(Enum *enum_)
    {
        // enum name
        std::string enum_name = enum_->ident_;

        // get enum object
        auto enum_obj = context_->get_enum(enum_name);

        if (enum_obj == nullptr)
        {
            // throw error
            throw JLCTCError("Enum object not found: " + enum_name);
        }

        // add the enum object to the context
        if (enum_->listeval_)
        {
            auto &list_e_val = enum_->listeval_;
            for (ListEVal::iterator i = list_e_val->begin();
                 i != list_e_val->end();
                 ++i)
            {
                // DEBUG_PRINT("Enum value: " << static_cast<EnumValue *>(*i)->ident_);
                std::string enum_val =
                    static_cast<EnumValue *>(*i)->ident_;

                // check if the enum value is already defined
                if (enum_obj->has_member(enum_val))
                {
                    // error: enum value already defined
                    throw JLCTCError("Enum value already defined: " + enum_val);
                }

                // add the enum value to the enum object
                enum_obj->add_member(enum_val);
            }
        }
    }

    void JLC_TC_UDT_DEF_Checker::visitStruct(Struct *struct_)
    {
        // struct name
        std::string struct_name = struct_->ident_;
        // DEBUG_PRINT("Struct: " << struct_name);
        // get struct object
        current_struct_obj_ = context_->get_struct(struct_name);

        if (current_struct_obj_ == nullptr)
        {
            // throw error
            throw JLCTCError("Struct object not found: " + struct_name);
        }

        // call parent class
        TypeVisitor::visitStruct(struct_);
    }

    void JLC_TC_UDT_DEF_Checker::visitTypeDefWS(TypeDefWS *type_def_ws)
    {
        // struct name
        std::string struct_name = type_def_ws->ident_1;

        // get struct object
        current_struct_obj_ = context_->get_struct(struct_name);

        if (current_struct_obj_ == nullptr)
        {
            // throw error
            throw JLCTCError("Struct object not found: " + struct_name);
        }

        // call parent class
        TypeVisitor::visitTypeDefWS(type_def_ws);
    }
    
    // class
    void JLC_TC_UDT_DEF_Checker::visitClass(Class *class_)
    {
        // class name
        std::string class_name = class_->ident_;
        // DEBUG_PRINT("Class: " << class_name);
        // get class object
        current_struct_obj_ = context_->get_class(class_name);

        if (current_struct_obj_ == nullptr)
        {
            // throw error
            throw JLCTCError("Class object not found: " + class_name);
        }

        // call parent class
        TypeVisitor::visitClass(class_);
    }

    void JLC_TC_UDT_DEF_Checker::visitClassWE(ClassWE *class_we)
    {
        // class name
        std::string class_name = class_we->ident_1;

        // get class object
        current_struct_obj_ = context_->get_class(class_name);

        if (current_struct_obj_ == nullptr)
        {
            // throw error
            throw JLCTCError("Class object not found: " + class_name);
        }

        // call parent class
        TypeVisitor::visitClassWE(class_we);
    }

    void JLC_TC_UDT_DEF_Checker::visitMemberDef(MemberDef *member_def)
    {
        /* Code For MemberDef Goes Here */

        if (member_def->type_)
            member_def->type_->accept(this);
        // get type
        auto member_type =
            std::make_shared<JLC::TYPE::JLCType>(g_type_);

        // void type member is not allowed
        if (member_type->type == JLC::TYPE::type_enum::VOID)
        {
            // throw error
            throw JLCTCError("void type member is not allowed");
        }

        auto list_mem_item = member_def->listmemitem_;
        for (ListMemItem::iterator i = list_mem_item->begin(); i != list_mem_item->end(); ++i)
        {
            // DEBUG_PRINT("Member: " << ((MemberItem *)(*i))->ident_);
            std::string member_name =
                ((MemberItem *)(*i))->ident_;

            // check if the member is already defined
            if (current_struct_obj_->has_member(member_name))
            {
                // error: member already defined
                throw JLCTCError("Member already defined: " + member_name);
            }

            // add the member to the struct object
            // DEBUG_PRINT("Member type: " << member_type->str());
            current_struct_obj_->add_member(member_name, member_type);
        }
    }
} // namespace JLC::TC