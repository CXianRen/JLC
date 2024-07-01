#include "jlc_tc_udt_dcl.h"
#include "jlc_tc_error.h"

#include "common/debug.h"

namespace JLC::TC
{
    void JLC_UDT_DC_Checker::visitProgram(Program *program)
    {
        if (program->listtopdef_)
            program->listtopdef_->accept(this);
        // check waiting list
        for (auto &struct_name : typedef_need_check_)
        {
            if (!context_->has_struct(struct_name))
            {
                // error: struct not defined
                throw JLCTCError("Struct not defined: " + struct_name);
            }
        }
        typedef_need_check_.clear();
        for (auto &class_name : class_need_check_)
        {
            if (!context_->has_class(class_name))
            {
                // error: class not defined
                throw JLCTCError("Class not defined: " + class_name);
            }
        }
        class_need_check_.clear();

        // update class inheritance
        for (auto &inherit : inherit_map_)
        {
            auto class_name = inherit.first;
            auto extends_class_name = inherit.second;
            auto class_obj = context_->get_class(class_name);
            auto extends_class_obj = context_->get_class(extends_class_name);
            class_obj->parent_class = extends_class_obj;
        }
    }

    void JLC_UDT_DC_Checker::check_user_defined_type_conflict(
        std::string type_name)
    {
        if (context_->has_enum(type_name) ||
            context_->has_class(type_name) ||
            context_->has_typedef(type_name))
        {
            // error: type already defined
            throw JLCTCError("Type already defined: " + type_name);
        }
    }

    void JLC_UDT_DC_Checker::visitEnum(Enum *enum_)
    {
        // get the enum name
        std::string enum_name = enum_->ident_;

        // check if the enum has a list of enum values
        if (context_->has_enum(enum_name))
        {
            // error: enum already defined
            throw JLCTCError("Enum already defined: " + enum_name);
        }

        check_user_defined_type_conflict(enum_name);

        // create a new enum
        auto enum_obj = std::make_shared<JLCEnum>(enum_name);

        // add the enum to the context
        context_->add_enum(enum_name, enum_obj);
    }

    void JLC_UDT_DC_Checker::visitStruct(Struct *struct_)
    {
        // get the struct name
        std::string struct_name = struct_->ident_;

        // check if the struct has a list of struct values
        if (context_->has_struct(struct_name))
        {
            // error: struct already defined
            throw JLCTCError("Struct already defined: " + struct_name);
        }

        // create a new struct
        auto struct_obj = std::make_shared<JLCStruct>(struct_name);

        context_->add_struct(struct_name, struct_obj);
    }

    void JLC_UDT_DC_Checker::visitTypeDef(TypeDef *type_def)
    {
        /**
         * typedef StructName * TypeName;
         */

        // get the type name
        std::string struct_name = type_def->ident_1;
        std::string type_name = type_def->ident_2;
        // check if the type has a list of type values
        if (context_->has_typedef(type_name))
        {
            // error: type already defined
            throw JLCTCError("Typedef defines a type already defined: " + type_name);
        }

        check_user_defined_type_conflict(type_name);

        // we will check if the struct is definied
        // in the context at the end of the type
        // declaration checking
        context_->add_typedef(type_name, struct_name);
        typedef_need_check_.push_back(struct_name);
    }

    void JLC_UDT_DC_Checker::visitTypeDefWS(TypeDefWS *type_def_ws)
    {
        /**
         * typedef Struct StructName {} TypeName;
         * typedef struct Foo_t{ int bar; } * Foo;
         */

        // get the struct name
        std::string struct_name = type_def_ws->ident_1;
        std::string type_name = type_def_ws->ident_2;

        // check if the type has a list of type values
        if (context_->has_typedef(type_name))
        {
            // error: type already defined
            throw JLCTCError("Type already defined: " + type_name);
        }

        check_user_defined_type_conflict(type_name);

        context_->add_typedef(type_name, struct_name);

        // we also to add the struct to the context
        // check if the struct has a list of struct values
        if (context_->has_struct(struct_name))
        {
            // error: struct already defined
            throw JLCTCError("Struct already defined: " + struct_name);
        }

        // create a new struct
        auto struct_obj = std::make_shared<JLCStruct>(struct_name);

        context_->add_struct(struct_name, struct_obj);
    }

    void JLC_UDT_DC_Checker::visitClass(Class *class_)
    {
        // get the class name
        std::string class_name = class_->ident_;

        // check if the class has a list of class values
        if (context_->has_class(class_name))
        {
            // error: class already defined
            throw JLCTCError("Class already defined: " + class_name);
        }

        check_user_defined_type_conflict(class_name);

        // create a new class
        auto class_obj = std::make_shared<JLCClass>(class_name);

        // add the class to the context
        context_->add_class(class_name, class_obj);
    }

    void JLC_UDT_DC_Checker::visitClassWE(ClassWE *class_we)
    {
        // get the class name
        std::string class_name = class_we->ident_1;
        std::string extends_class_name = class_we->ident_2;

        // a class can only extend another class
        if (class_name == extends_class_name)
        {
            // error: class cannot extend itself
            throw JLCTCError("Class cannot extend itself: " + class_name);
        }

        check_user_defined_type_conflict(class_name);

        // check if the class has a list of class values
        if (context_->has_class(class_name))
        {
            // error: class already defined
            throw JLCTCError("Class already defined: " + class_name);
        }

        // create a new class
        auto class_obj = std::make_shared<JLCClass>(class_name);

        context_->add_class(class_name, class_obj);

        // will check if the extends class is defined at the end
        // DEBUG_PRINT("class need check: " + extends_class_name);
        class_need_check_.push_back(extends_class_name);
        inherit_map_[class_name] = extends_class_name;
    }

} // namespace JLC::TC