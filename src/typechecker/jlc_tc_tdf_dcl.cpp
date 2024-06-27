#include "jlc_tc_tdf_dcl.h"
#include "jlc_tc_error.h"

namespace JLC::TC
{
    void JLCTopDefinitionChecker::visitEnum(Enum *enum_)
    {
        // get the enum name
        std::string enum_name = enum_->ident_;

        // check if the enum has a list of enum values
        if (context_->is_exist_enum(enum_name))
        {
            // error: enum already defined
            throw JLCTCError("Enum already defined: " + enum_name);
        }

        // create a new enum
        auto enum_obj = std::make_shared<JLCEnum>(enum_name);

        // if (enum_->listeval_)
        // {
        //     auto &list_e_val = enum_->listeval_;
        //     for (ListEVal::iterator i = list_e_val->begin();
        //          i != list_e_val->end();
        //          ++i)
        //     {
        //         std::string enum_val =
        //             static_cast<EnumValue *>(*i)->ident_;

        //         // check if the enum value is already defined
        //         if (enum_obj->has_member(enum_val))
        //         {
        //             // error: enum value already defined
        //             throw JLCTCError("Enum value already defined: " + enum_val);
        //         }

        //         // add the enum value to the enum object
        //         enum_obj->add_member(enum_val);
        //     }
        // }
        // add the enum to the context
        context_->add_enum(enum_name, enum_obj);
    }

    void JLCTopDefinitionChecker::visitStruct(Struct *struct_)
    {
        // get the struct name
        std::string struct_name = struct_->ident_;

        // check if the struct has a list of struct values
        if (context_->is_exist_struct(struct_name))
        {
            // error: struct already defined
            throw JLCTCError("Struct already defined: " + struct_name);
        }

        // create a new struct
        auto struct_obj = std::make_shared<JLCStruct>(struct_name);

        context_->add_struct(struct_name, struct_obj);
    }

    void JLCTopDefinitionChecker::visitTypeDef(TypeDef *type_def)
    {
        /**
         * typedef StructName * TypeName;
         */

        // get the type name
        std::string struct_name = type_def->ident_1;
        std::string type_name = type_def->ident_2;
        // check if the type has a list of type values
        if (context_->is_exist_typedef(type_name))
        {
            // error: type already defined
            throw JLCTCError("Type already defined: " + type_name);
        }

        // we will check if the struct is definied
        // in the context at the end of the type
        // declaration checking
        context_->add_typedef(type_name, struct_name);
        typedef_need_check_.push_back(type_name);
    }

    void JLCTopDefinitionChecker::visitTypeDefWS(TypeDefWS *type_def_ws)
    {
        /**
         * typedef Struct StructName {} TypeName;
         * typedef struct Foo_t{ int bar; } * Foo;
         */

        // get the struct name
        std::string struct_name = type_def_ws->ident_1;
        std::string type_name = type_def_ws->ident_2;

        // check if the type has a list of type values
        if (context_->is_exist_typedef(type_name))
        {
            // error: type already defined
            throw JLCTCError("Type already defined: " + type_name);
        }

        context_->add_typedef(type_name, struct_name);

        // we also to add the struct to the context
        // check if the struct has a list of struct values
        if (context_->is_exist_struct(struct_name))
        {
            // error: struct already defined
            throw JLCTCError("Struct already defined: " + struct_name);
        }

        // create a new struct
        auto struct_obj = std::make_shared<JLCStruct>(struct_name);
        context_->add_struct(struct_name, struct_obj);
    }

    void JLCTopDefinitionChecker::visitClass(Class *class_)
    {
        // get the class name
        std::string class_name = class_->ident_;

        // check if the class has a list of class values
        if (context_->is_exist_class(class_name))
        {
            // error: class already defined
            throw JLCTCError("Class already defined: " + class_name);
        }

        // create a new class
        auto class_obj = std::make_shared<JLCClass>(class_name);

        context_->add_class(class_name, class_obj);
    }

    void JLCTopDefinitionChecker::visitClassWE(ClassWE *class_we)
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

        // check if the class has a list of class values
        if (context_->is_exist_class(class_name))
        {
            // error: class already defined
            throw JLCTCError("Class already defined: " + class_name);
        }

        // create a new class
        auto class_obj = std::make_shared<JLCClass>(class_name);

        context_->add_class(class_name, class_obj);

        // will check if the extends class is defined at the end
        class_need_check_.push_back(class_name);
    }


} // namespace JLC::TC