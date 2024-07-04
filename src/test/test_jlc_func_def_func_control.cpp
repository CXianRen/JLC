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
    // if statement
    {
        std::string input_str = "int f(){ if (true) return 1; return 0;}";

        init_checker();

        // check the parse tree
        run_checker();
    }
    // if
    {
        std::string input_str = "void f(){ if (1) {int x;}}";

        init_checker();

        // check the parse tree
        TEST_EXPECT_EXCEPTION(run_checker());
    }
    // if else
    {
        std::string input_str = "void f(){ if (false) {int x;} else {int y;}}";

        init_checker();

        // check the parse tree
        run_checker();
    }
    // if else if
    {
        std::string input_str = "void f(){ if (1) {int x;} else if (true) {int y;}}";

        init_checker();

        // check the parse tree
        TEST_EXPECT_EXCEPTION(run_checker());
    }

    // while
    {
        std::string input_str = "void f(){ while (true) {int x;}}";

        init_checker();

        // check the parse tree
        run_checker();
    }

    // while
    {
        std::string input_str = "void f(){ while (1) {int x;}}";

        init_checker();

        // check the parse tree
        TEST_EXPECT_EXCEPTION(run_checker());
    }

    // for each statement
    {
        std::string input_str = "void f(){ int[] a = new int[10]; for (int x : a) {}}";

        init_checker();

        // check the parse tree
        run_checker();
    }
    // for each statement
    {
        std::string input_str = "void f(){ int[] a = new int[10]; int b; for (int x : b) {}}";

        init_checker();

        // check the parse tree
        TEST_EXPECT_EXCEPTION(run_checker());
    }
    // for each statement
    {
        std::string input_str = "void f(){ int[][] a = new int[10][10]; for (int x : a) {}}";

        init_checker();

        // check the parse tree
        TEST_EXPECT_EXCEPTION(run_checker());
    }
    // variable shadowing in for each statement
    {
        std::string input_str = "void f(){ double b; int[] a = new int[10]; for (int b : a) {int c =b;}}";

        init_checker();

        // check the parse tree
        run_checker();
    }

    TEST_PASS();
}