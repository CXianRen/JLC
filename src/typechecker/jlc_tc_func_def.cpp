#include "typechecker/jlc_tc_func_def.h"
#include "typechecker/jlc_tc_error.h"

namespace JLC::TC
{
    void JLC_FUNC_DEF_Checker::
        visitFuncDef(FuncDef *func_def)
    {
        std::string func_name = func_def->ident_;
        auto func_name_with_scope =
            context_->get_scope_name(func_name,
                                     func_scope_);

        current_func_ =
            context_->get_func(func_name_with_scope);

        if (current_func_ == nullptr)
        {
            // error
            throw JLC::TC::JLCTCError(
                "Function " + func_name + " not found in the context");
        }

        // function body scope start
        current_func_->push_blk();
        JLC::TC::TypeVisitor::visitFuncDef(func_def);
        // function body scope end
        current_func_->pop_blk();
    }

    void JLC_FUNC_DEF_Checker::
        visitBStmt(BStmt *b_stmt)
    {
        // block scope start
        current_func_->push_blk();
        JLC::TC::TypeVisitor::visitBStmt(b_stmt);
        // block scope end
        current_func_->pop_blk();
    }

    void JLC_FUNC_DEF_Checker::
        visitNoInit(NoInit *no_init)
    {
        auto var_type =
            std::make_shared<JLC::TYPE::JLCType>(g_type_);

        // not void type
        if (var_type->type == JLC::TYPE::type_enum::VOID)
        {
            // error
            throw JLC::TC::JLCTCError(
                "Variable type cannot be void");
        }

        auto var_name = no_init->ident_;

        // check if the variable
        // is already defined in the current scope
        if (current_func_->blks.back().has_var(var_name))
        {
            // error
            throw JLC::TC::JLCTCError(
                "Variable " + var_name +
                " already defined in the current scope");
        }

        // DEBUG_PRINT("add variable: " << var_name << " type: " << var_type->str()
        //  << " to function: " << current_func_->name);

        // add the variable to the current scope
        current_func_->add_var(
            JLC::VAR::JLCVar(
                var_name,
                var_type));
    }

    void JLC_FUNC_DEF_Checker::
        visitInit(Init *init)
    {
        /* Code For Init Goes Here */

        auto var_type =
            std::make_shared<JLC::TYPE::JLCType>(g_type_);

        if (var_type->type == JLC::TYPE::type_enum::VOID)
        {
            // error
            throw JLC::TC::JLCTCError(
                "Variable type cannot be void");
        }

        auto var_name = init->ident_;
        // if the variable the name is same as custom type
        // then it is a illegal variable name

        // check if the variable
        // is already defined in the current scope
        if (current_func_->blks.back().has_var(var_name))
        {
            // error
            throw JLC::TC::JLCTCError(
                "Variable " + var_name +
                " already defined in the current scope");
        }

        if (init->expr_)
            init->expr_->accept(this);
        auto init_type =
            std::make_shared<JLC::TYPE::JLCType>(g_type_);

        // check if the variable type
        // is the same as the init type
        if ((*var_type) != (*init_type))
        {
            // error
            throw JLC::TC::JLCTCError(
                "Variable " + var_name + " type is " + var_type->str() +
                " type is not the same as the init type " + init_type->str());
        }

        // add the variable to the current scope
        current_func_->add_var(
            JLC::VAR::JLCVar(var_name, var_type));
    }

    void JLC_FUNC_DEF_Checker::
        visitEVar(EVar *e_var)
    {
        auto var_name = e_var->ident_;
        // check if variable is defined

        /*
         * we regard enum as a virtual global variable
         * so that we can access the enum member by dot operator
         */
        if (context_->has_enum(var_name))
        {
            auto enum_obj = context_->get_enum(var_name);
            if (enum_obj == nullptr)
            {
                // error
                throw JLC::TC::JLCTCError(
                    "Enum " + var_name + " not found in the context");
            }
            g_type_ =
                JLC::TYPE::JLCType(
                    JLC::TYPE::type_enum::ENUM, var_name);
            return;
        }

        if (!current_func_->has_var(var_name))
        {
            // error
            throw JLC::TC::JLCTCError(
                "Variable " + var_name +
                " not defined in function " + current_func_->name);
        }

        auto var = current_func_->get_var(var_name);

        // set the type of the variable
        g_type_ = *var.type;
    }

    void JLC_FUNC_DEF_Checker::
        visitEpropety(Epropety *epropety)
    {
        if (epropety->expr_)
            epropety->expr_->accept(this);
        auto obj_type = g_type_;

        auto prop_name = epropety->ident_;

        // length property for array
        if (prop_name == "length")
        {
            if (obj_type.type != JLC::TYPE::type_enum::ARRAY)
            {
                // error
                throw JLC::TC::JLCTCError(
                    "Property length is not defined for type " +
                    obj_type.str());
            }

            // set the type of the property
            g_type_ = JLC::TYPE::JLCType(JLC::TYPE::type_enum::INT);
            return;
        }
        // enum
        if (obj_type.type == JLC::TYPE::type_enum::ENUM)
        {
            auto type_name = obj_type.obj_name;
            auto enum_obj = context_->get_enum(type_name);
            if (enum_obj == nullptr)
            {
                // error
                throw JLC::TC::JLCTCError(
                    "Enum " + type_name + " not found in the context");
            }

            if (!enum_obj->has_member(prop_name))
            {
                // error
                throw JLC::TC::JLCTCError(
                    "Property " + prop_name +
                    " is not defined for enum " + type_name);
            }
            // do not set the type of the property
            g_type_ = g_type_;
            return;
        }

        // struct
        if (obj_type.type == JLC::TYPE::type_enum::STRUCT)
        {
            auto type_name = obj_type.obj_name;
            auto struct_obj = context_->get_struct(type_name);
            if (struct_obj == nullptr)
            {
                // error
                throw JLC::TC::JLCTCError(
                    "Struct " + type_name + " not found in the context");
            }

            if (!struct_obj->has_member(prop_name))
            {
                // error
                throw JLC::TC::JLCTCError(
                    "Property " + prop_name +
                    " is not defined for struct " + type_name);
            }

            auto member = struct_obj->get_member_type(prop_name);
            if (member == nullptr)
            {
                // error
                throw JLC::TC::JLCTCError(
                    "Property " + prop_name +
                    " is not defined for struct " + type_name);
            }
            g_type_ = *member;
            return;
        }

        // class
        if (obj_type.type == JLC::TYPE::type_enum::CLASS)
        {
            auto type_name = obj_type.obj_name;
            auto class_obj = context_->get_class(type_name);
            if (class_obj == nullptr)
            {
                // error
                throw JLC::TC::JLCTCError(
                    "Class " + type_name + " not found in the context");
            }

            if (!class_obj->has_member(prop_name))
            {
                // error
                throw JLC::TC::JLCTCError(
                    "Property " + prop_name +
                    " is not defined for class " + type_name);
            }

            auto member = class_obj->get_member_type(prop_name);
            if (member == nullptr)
            {
                // error
                throw JLC::TC::JLCTCError(
                    "Property " + prop_name +
                    " is not defined for class " + type_name);
            }
            g_type_ = *member;
            return;
        }
        // show not reach here
        throw JLC::TC::JLCTCError(
            "Property " + prop_name +
            " is not defined for type " + obj_type.str());
    }

} // namespace JLC::TC