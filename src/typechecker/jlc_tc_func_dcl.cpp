#include "typechecker/jlc_tc_func_dcl.h"

namespace JLC::TC
{

    void JLC_FUNC_CD_Checker::add_inner_func()
    {
        // printInt
        auto func_name = context_->get_scope_name("printInt", GLOBAL_SCOPE);
        auto func = std::make_shared<JLC::FUNC::JLCFunc>(
            func_name, std::make_shared<JLC::TYPE::JLCType>(VOID));
        func->add_arg(JLC::VAR::JLCVar("x", std::make_shared<JLC::TYPE::JLCType>(INT)));

        context_->add_func(func_name, func);

        // printString
        func_name = context_->get_scope_name("printString", GLOBAL_SCOPE);
        func = std::make_shared<JLC::FUNC::JLCFunc>(
            func_name, std::make_shared<JLC::TYPE::JLCType>(VOID));
        func->add_arg(JLC::VAR::JLCVar("x", std::make_shared<JLC::TYPE::JLCType>(STRING)));

        context_->add_func(func_name, func);

        // printDouble
        func_name = context_->get_scope_name("printDouble", GLOBAL_SCOPE);
        func = std::make_shared<JLC::FUNC::JLCFunc>(
            func_name, std::make_shared<JLC::TYPE::JLCType>(VOID));
        func->add_arg(JLC::VAR::JLCVar("x", std::make_shared<JLC::TYPE::JLCType>(DOUB)));

        context_->add_func(func_name, func);

        // readInt
        func_name = context_->get_scope_name("readInt", GLOBAL_SCOPE);
        func = std::make_shared<JLC::FUNC::JLCFunc>(
            func_name, std::make_shared<JLC::TYPE::JLCType>(INT));

        context_->add_func(func_name, func);

        // readDouble
        func_name = context_->get_scope_name("readDouble", GLOBAL_SCOPE);
        func = std::make_shared<JLC::FUNC::JLCFunc>(
            func_name, std::make_shared<JLC::TYPE::JLCType>(DOUB));

        context_->add_func(func_name, func);
    }

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

        // DEBUG_PRINT("Function name: " + func_name_with_scope);

        // check if function is already defined
        if (context_->has_func(func_name_with_scope))
        {
            std::string error_msg =
                "Function " +
                func_name + " is already defined in scope " +
                func_scope_;
            throw JLCTCError(error_msg);
        }

        // add function to context
        auto func = std::make_shared<JLC::FUNC::JLCFunc>(
            func_name_with_scope, return_type);

        context_->add_func(func_name_with_scope, func);

        // add arguments to function
        auto list_arg = func_def->listarg_;
        for (ListArg::iterator i = list_arg->begin();
             i != list_arg->end();
             ++i)
        {
            auto argument = (Argument *)(*i);
            std::string arg_name = argument->ident_;

            // check if argument is already defined
            if (func->has_arg(arg_name))
            {
                std::string error_msg =
                    "Argument " +
                    arg_name + " is already defined in function " +
                    func_name_with_scope;
                throw JLCTCError(error_msg);
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
                throw JLCTCError(error_msg);
            }
            // new arg
            JLC::VAR::JLCVar arg(arg_name, arg_type);

            // add arg to function
            func->add_arg(arg);
        }
    }

} // namespace JLC::TC