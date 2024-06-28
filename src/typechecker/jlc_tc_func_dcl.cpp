#include "typechecker/jlc_tc_func_dcl.h"

namespace JLC::TC
{

    void JLC_FUNC_CD_Checker::visitGFuncDef(GFuncDef *p)
    {
        set_scope(GLOBAL_SCOPE);
        TypeVisitor::visitGFuncDef(p);
    }

    void JLC_FUNC_CD_Checker::visitClass(Class *p)
    {
        set_scope(p->ident_);
        TypeVisitor::visitClass(p);
    }
    void JLC_FUNC_CD_Checker::visitClassWE(ClassWE *p)
    {
        set_scope(p->ident_1);
        TypeVisitor::visitClassWE(p);
    }

    void JLC_FUNC_CD_Checker::visitFuncDef(FuncDef *func_def)
    {
        // get the return type of the function
        if (func_def->type_)
            func_def->type_->accept(this);

        auto return_type =
            std::make_shared<JLC::TYPE::JLCType>(g_type_);

        // get the function name
        std::string func_name = func_def->ident_;
        auto func_name_with_scope =
            context_->get_scope_name(func_name,
                                     func_scope_);

        // check if function is already defined
        if (context_->is_exist_func(func_name_with_scope))
        {
            std::string error_msg =
                "Function " +
                func_name + " is already defined in scope " +
                func_scope_;
            throw std::runtime_error(error_msg);
        }

        // add function to context
        auto func = std::make_shared<JLC::FUNC::JLCFunc>(
            func_name_with_scope, return_type);

        // add arguments to function
        auto list_arg = func_def->listarg_;
        for (ListArg::iterator i = list_arg->begin();
             i != list_arg->end();
             ++i)
        {
            auto argument = (Argument *)(*i);
            std::string arg_name = argument->ident_;

            // check if argument is already defined
            if (func->is_exist_arg(arg_name))
            {
                std::string error_msg =
                    "Argument " +
                    arg_name + " is already defined in function " +
                    func_name_with_scope;
                throw std::runtime_error(error_msg);
            }

            argument->type_->accept(this);
            auto arg_type =
                std::make_shared<JLC::TYPE::JLCType>(g_type_);

            // check if argument type is not void
            if (*arg_type == JLC::TYPE::JLCType(VOID))
            {
                std::string error_msg =
                    "Argument " +
                    arg_name + " in function " +
                    func_name_with_scope +
                    " cannot be of type void";
                throw std::runtime_error(error_msg);
            }
            // new arg
            JLC::VAR::JLCVar arg(arg_name, arg_type);

            // add arg to function
            func->add_arg(arg);
        }
    }

} // namespace JLC::TC