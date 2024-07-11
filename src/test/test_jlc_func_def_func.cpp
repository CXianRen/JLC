#include "typechecker/jlc_tc_udt_def.h"
#include "typechecker/jlc_tc_udt_dcl.h"
#include "typechecker/jlc_tc_func_dcl.h"
#include "typechecker/jlc_tc_func_def.h"
#include "common/jlc_context.h"
#include "common/test.h"

#include <iostream>
#include <string>

#define init_checker()                                              \
    auto parse_tree = gen_ast(input_str);                           \
    auto context = std::make_shared<JLC::CONTEXT::JLCContext>();    \
    auto type_decl_checker =                                        \
        std::make_shared<JLC::TC::JLC_UDT_DC_Checker>(context);     \
    auto func_decl_checker =                                        \
        std::make_shared<JLC::TC::JLC_FUNC_CD_Checker>(context);    \
    auto type_def_checker =                                         \
        std::make_shared<JLC::TC::JLC_TC_UDT_DEF_Checker>(context); \
    auto func_def_checker =                                         \
        std::make_shared<JLC::TC::JLC_FUNC_DEF_Checker>(context);

#define run_checker()                            \
    parse_tree->accept(type_decl_checker.get()); \
    parse_tree->accept(func_decl_checker.get()); \
    parse_tree->accept(type_def_checker.get());  \
    parse_tree->accept(func_def_checker.get());

int main(int argc, char **argv)
{

    // call global function
    {
        std::string input_str = "int f(){return 0;} void f2() {int a = f();}";

        init_checker();

        // check the parse tree
        run_checker();
    }
    // call undefined function
    {
        std::string input_str = "void f2() {int a = f();}";

        init_checker();

        // check the parse tree
        TEST_EXPECT_EXCEPTION(
            run_checker());
    }
    // function parameter
    {
        std::string input_str = "int f(int a){return a;} void f2() {int a = f(1);}";

        init_checker();

        // check the parse tree
        run_checker();
    }
    // more function parameters
    {
        std::string input_str = "int f(int a, int b){return a+b;} void f2() {int a = f(1, 2);}";

        init_checker();

        // check the parse tree
        run_checker();
    }
    // pass wrong number of parameters
    {
        std::string input_str = "int f(int a, int b){return a+b;} void f2() {int a = f(1);}";

        init_checker();

        // check the parse tree
        TEST_EXPECT_EXCEPTION(
            run_checker());
    }
    // pass wrong type of parameters
    {
        std::string input_str =
            "int f(int a, int b){return a+b;} void f2() {int a = f(1, 2.0);}";

        init_checker();

        // check the parse tree
        TEST_EXPECT_EXCEPTION(
            run_checker());
    }

    // pass more than the needed parameters
    {
        std::string input_str =
            "int f(int a){return a;} void f2() {int a = f(1, 2);}";

        init_checker();

        // check the parse tree
        TEST_EXPECT_EXCEPTION(
            run_checker());
    }

    // access member function
    {

        std::string input_str =
            "class A {int a; int access_a(){return a;}}\n"
            "void f2() {A a; int b = a.access_a();}";

        init_checker();

        // check the parse tree
        run_checker();
    }
    // access member function with parameters
    {

        std::string input_str =
            "class A {int a; int access_a(int b){return a+b;}}\n"
            "void f2() {A a; int b = a.access_a(1);}";

        init_checker();

        // check the parse tree
        run_checker();
    }

    TEST_PASS();
}