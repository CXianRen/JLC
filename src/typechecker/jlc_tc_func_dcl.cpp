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

    void JLC_FUNC_CD_Checker::
        check_overload_fucntion()
    {
        // check overload function
        for (auto &pair : context_->classes)
        {
            auto class_name = pair.first;
            auto class_obj = context_->get_class(class_name);
            // get all functions in the class
            auto funcs = context_->get_funcs_in_scope(class_name);
            for (auto &func_name : funcs)
            {
                // check if the function is overloaded
                auto parent_class = class_obj->parent_class;
                while (parent_class != nullptr)
                {
                    auto parent_class_name = parent_class->obj_name;
                    auto parent_funcs = context_->get_funcs_in_scope(parent_class_name);
                    for (auto &parent_func_name : parent_funcs)
                    {
                        if (func_name == parent_func_name)
                        {
                            // check overload function has the same return type and arguments
                            auto func = context_->get_func(
                                context_->get_scope_name(func_name, class_name));

                            auto parent_func = context_->get_func(
                                context_->get_scope_name(func_name, parent_class_name));

                            if (*func->return_type != *parent_func->return_type)
                            {
                                // error: return type is different
                                throw JLCTCError(
                                    "Return type of function " +
                                    func_name + " in class " +
                                    class_name + " :'" + func->return_type->str() +
                                    "' is different from parent class " +
                                    parent_class_name + " :'" +
                                    parent_func->return_type->str() + "'");
                            }

                            if (func->args.size() != parent_func->args.size())
                            {
                                // error: number of arguments is different
                                throw JLCTCError(
                                    "Number of arguments of function " +
                                    func_name + " in class " +
                                    class_name + ":(" +
                                    std::to_string(func->args.size()) + ")" +
                                    " is different from parent class " +
                                    parent_class_name + ":(" +
                                    std::to_string(parent_func->args.size()) + ")");
                            }

                            for (size_t i = 0; i < func->args.size(); i++)
                            {
                                if (func->args[i].type != parent_func->args[i].type)
                                {
                                    // error: argument type is different
                                    throw JLCTCError(
                                        "Argument type of function " +
                                        func_name + " in class " +
                                        class_name + " :'" + func->args[i].type->str() +
                                        "' is different from parent class " +
                                        parent_class_name + " :'" +
                                        parent_func->args[i].type->str() +
                                        "'");
                                }
                            }
                        }
                    }
                    parent_class = parent_class->parent_class;
                }
            }
        }
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

        // if main function, check if return type is INT
        if (func_name == "main" && *return_type != JLC::TYPE::JLCType(INT))
        {
            std::string error_msg =
                "Main function must have return type INT";
            throw JLCTCError(error_msg);
        }

        // add function to context
        auto func = std::make_shared<JLC::FUNC::JLCFunc>(
            func_name_with_scope, return_type);

        context_->add_func(func_name_with_scope, func);

        context_->add_func_to_scope(func_scope_, func_name);

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