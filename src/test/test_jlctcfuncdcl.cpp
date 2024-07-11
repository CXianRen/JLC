#include "typechecker/jlc_tc_func_dcl.h"
#include "typechecker/jlc_tc_error.h"
#include "common/test.h"

#include <iostream>
#include <string>


int main(int argc, char **argv)
{
    // global defined functions
    {
        std::string input_str = "int foo(int a) { return a; }";

        auto parse_tree = gen_ast(input_str);

        // create a type checker
        // new context
        auto context = std::make_shared<JLC::CONTEXT::JLCContext>();

        auto checker =
            std::make_shared<JLC::TC::JLC_FUNC_CD_Checker>(context);
        // check the parse tree
        parse_tree->accept(checker.get());

        // check the result
        auto name = context->get_scope_name("foo", "global");
        TEST_ASSERT(name == "foo");
        TEST_ASSERT(context->has_func(name) == true);
        TEST_ASSERT(context->get_func(name)->name == name);

        // check return type
        auto func = context->get_func(name);
        TEST_ASSERT(*func->return_type ==
                    JLC::TYPE::JLCType(JLC::TYPE::type_enum::INT));
        // check arguments number
        TEST_ASSERT(func->args.size() == 1);
        // check argument type
        TEST_ASSERT(*func->args[0].get_type() ==
                    JLC::TYPE::JLCType(JLC::TYPE::type_enum::INT));
    }
    // redefine function
    {
        std::string input_str = "int foo(int a) { return a; } int foo(int a) { return a; }";

        auto parse_tree = gen_ast(input_str);

        // create a type checker
        // new context
        auto context = std::make_shared<JLC::CONTEXT::JLCContext>();

        auto checker =
            std::make_shared<JLC::TC::JLC_FUNC_CD_Checker>(context);
        // check the parse tree
        TEST_EXPECT_EXCEPTION(
            parse_tree->accept(checker.get()));
    }
    // local defined functions (class methods)
    {
        std::string input_str =
            "class A { int foo(int a) { return a; } }";

        auto parse_tree = gen_ast(input_str);

        // create a type checker
        // new context
        auto context =
            std::make_shared<JLC::CONTEXT::JLCContext>();

        auto checker =
            std::make_shared<JLC::TC::JLC_FUNC_CD_Checker>(context);
        // check the parse tree
        parse_tree->accept(checker.get());

        // check the result
        auto name = context->get_scope_name("foo", "A");
        TEST_ASSERT(name == "A::foo");
        TEST_ASSERT(context->has_func(name) == true);
        TEST_ASSERT(context->get_func(name)->name == name);

        // check return type
        auto func = context->get_func(name);
        TEST_ASSERT(*func->return_type ==
                    JLC::TYPE::JLCType(JLC::TYPE::type_enum::INT));
        // check arguments number
        TEST_ASSERT(func->args.size() == 1);
        // check argument type
        TEST_ASSERT(*func->args[0].get_type() ==
                    JLC::TYPE::JLCType(JLC::TYPE::type_enum::INT));
    }
    // global function has same name as class method
    {
        std::string input_str =
            "int foo(int a) { return a; }"
            "class A { int foo(int a) { return a; } }";

        auto parse_tree = gen_ast(input_str);

        // create a type checker
        // new context
        auto context =
            std::make_shared<JLC::CONTEXT::JLCContext>();

        auto checker =
            std::make_shared<JLC::TC::JLC_FUNC_CD_Checker>(context);

        parse_tree->accept(checker.get());

        // check the parse tree
        TEST_ASSERT(
            context->has_func("foo") == true);
        TEST_ASSERT(
            context->has_func("A::foo") == true);
    }
    // different class's method has same name
    {
        std::string input_str =
            "class A { int foo(int a) { return a; } }"
            "class B { int foo(int a) { return a; } }";

        auto parse_tree = gen_ast(input_str);

        // create a type checker
        // new context
        auto context =
            std::make_shared<JLC::CONTEXT::JLCContext>();

        auto checker =
            std::make_shared<JLC::TC::JLC_FUNC_CD_Checker>(context);

        parse_tree->accept(checker.get());

        // check the parse tree
        TEST_ASSERT(
            context->has_func("A::foo") == true);
        TEST_ASSERT(
            context->has_func("B::foo") == true);
    }
    // void parameter is not allowed
    {
        std::string input_str = "int foo(void x) { return 0; }";

        auto parse_tree = gen_ast(input_str);

        // create a type checker
        // new context
        auto context =
            std::make_shared<JLC::CONTEXT::JLCContext>();

        auto checker =
            std::make_shared<JLC::TC::JLC_FUNC_CD_Checker>(context);

        // check the parse tree
        TEST_EXPECT_EXCEPTION(
            parse_tree->accept(checker.get()));
    }
    // parameters with same name
    {
        std::string input_str = "int foo(int a, int a) { return 0; }";

        auto parse_tree = gen_ast(input_str);

        // create a type checker
        // new context
        auto context =
            std::make_shared<JLC::CONTEXT::JLCContext>();

        auto checker =
            std::make_shared<JLC::TC::JLC_FUNC_CD_Checker>(context);

        // check the parse tree
        TEST_EXPECT_EXCEPTION(
            parse_tree->accept(checker.get()));
    }
    // main function must have return type INT
    {
        std::string input_str = "void main() { return; }";

        auto parse_tree = gen_ast(input_str);

        // create a type checker
        // new context
        auto context =
            std::make_shared<JLC::CONTEXT::JLCContext>();

        auto checker =
            std::make_shared<JLC::TC::JLC_FUNC_CD_Checker>(context);

        // check the parse tree
        TEST_EXPECT_EXCEPTION(
            parse_tree->accept(checker.get()));
    }
    // main function must have return type INT
    {
        std::string input_str = "int main() { return 0; }";

        auto parse_tree = gen_ast(input_str);

        // create a type checker
        // new context
        auto context =
            std::make_shared<JLC::CONTEXT::JLCContext>();

        auto checker =
            std::make_shared<JLC::TC::JLC_FUNC_CD_Checker>(context);

        // check the parse tree
        parse_tree->accept(checker.get());
    }

    TEST_PASS();
}