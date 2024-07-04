#include "typechecker/jlc_tc_udt_def.h"
#include "typechecker/jlc_tc_udt_dcl.h"
#include "typechecker/jlc_tc_func_dcl.h"
#include "typechecker/jlc_tc_func_def.h"
#include "common/jlc_context.h"
#include "common/test.h"

#include "parser/Parser.H"
#include "Printer.H"
#include "parser/Absyn.H"
#include "ParserError.H"

#include <iostream>
#include <string>

Prog *gen_ast(std::string input_str)
{
    // convert a string to file object
    FILE *input = fmemopen((void *)input_str.c_str(), input_str.size(), "r");

    Prog *parse_tree = nullptr;
    try
    {
        parse_tree = pProg(input);
    }
    catch (parse_error &e)
    {
        std::cerr << "Parse error on line " << e.getLine() << "\n";
        TEST_FAIL();
        exit(-1);
    }
    if (parse_tree == NULL)
    {
        TEST_FAIL();
        exit(-1);
    }
    return parse_tree;
}

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
        std::string input_str = "int f(){return 0;} int main() {int a = f();}";

        init_checker();

        // check the parse tree
        run_checker();
    }
    // call undefined function
    {
        std::string input_str = "int main() {int a = f();}";

        init_checker();

        // check the parse tree
        TEST_EXPECT_EXCEPTION(
            run_checker());
    }
    // function parameter
    {
        std::string input_str = "int f(int a){return a;} int main() {int a = f(1);}";

        init_checker();

        // check the parse tree
        run_checker();
    }
    // more function parameters
    {
        std::string input_str = "int f(int a, int b){return a+b;} int main() {int a = f(1, 2);}";

        init_checker();

        // check the parse tree
        run_checker();
    }
    // pass wrong number of parameters
    {
        std::string input_str = "int f(int a, int b){return a+b;} int main() {int a = f(1);}";

        init_checker();

        // check the parse tree
        TEST_EXPECT_EXCEPTION(
            run_checker());
    }
    // pass wrong type of parameters
    {
        std::string input_str =
            "int f(int a, int b){return a+b;} int main() {int a = f(1, 2.0);}";

        init_checker();

        // check the parse tree
        TEST_EXPECT_EXCEPTION(
            run_checker());
    }

    // pass more than the needed parameters
    {
        std::string input_str =
            "int f(int a){return a;} int main() {int a = f(1, 2);}";

        init_checker();

        // check the parse tree
        TEST_EXPECT_EXCEPTION(
            run_checker());
    }

    // access member function
    {

        std::string input_str =
            "class A {int a; int access_a(){return a;}}\n"
            "int main() {A a; int b = a.access_a();}";

        init_checker();

        // check the parse tree
        run_checker();
    }
    // access member function with parameters
    {

        std::string input_str =
            "class A {int a; int access_a(int b){return a+b;}}\n"
            "int main() {A a; int b = a.access_a(1);}";

        init_checker();

        // check the parse tree
        run_checker();
    }

    TEST_PASS();
}