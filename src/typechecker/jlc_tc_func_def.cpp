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
                "Variable " + var_name +
                " type is not the same as the init type");
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

} // namespace JLC::TC