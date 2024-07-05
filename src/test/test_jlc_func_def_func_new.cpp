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
    // new struct
    {
        std::string input_str = "typedef struct A_t { int x; }* A;\n"
                                "void f(){ A a = new A_t;}";

        init_checker();

        // check the parse tree
        run_checker();
    }
    // new a undefined struct type
    {
        std::string input_str = "void f(){ A a = new A_t;}";

        init_checker();

        // check the parse tree
        TEST_EXPECT_EXCEPTION(
            run_checker());
    }
    // new a class
    {
        std::string input_str = "class A { int x; }\n"
                                "void f(){ A a = new A;}";

        init_checker();

        // check the parse tree
        run_checker();
    }
    // new a undefined class type
    {
        std::string input_str = "void f(){ A a = new A;}";

        init_checker();

        // check the parse tree
        TEST_EXPECT_EXCEPTION(
            run_checker());
    }
    // new basic type array
    {
        std::string input_str = "void f(){ int[] a = new int[10];}";

        init_checker();

        // check the parse tree
        run_checker();
    }
    // new basic two dimension array
    {
        std::string input_str = "void f(){ int[][] a = new int[10][10];}";

        init_checker();

        // check the parse tree
        run_checker();
    }
    // invalid array size
    {
        std::string input_str = "void f(){ int[] a = new int[1.0];}";

        init_checker();

        // check the parse tree
        TEST_EXPECT_EXCEPTION(
            run_checker());
    }
    // invalid array size
    {
        std::string input_str = "double f2(){return 0.0;} \n"
                                "void f(){ int[][] a = new int[1][f2()];}";

        init_checker();

        // check the parse tree
        TEST_EXPECT_EXCEPTION(
            run_checker());
    }
    // new struct array
    {
        std::string input_str = "typedef struct A_t { int x; }* A;\n"
                                "void f(){ A[] a = new A[10];}";

        init_checker();

        // check the parse tree
        run_checker();
    }
    // new class array
    {
        std::string input_str = "class A { int x; }\n"
                                "void f(){ A[] a = new A[10];}";

        init_checker();

        // check the parse tree
        run_checker();
    }
    // new struct two dimension array
    {
        std::string input_str = "typedef struct A_t { int x; }* A;\n"
                                "void f(){ A[][] a = new A[10][10];}";

        init_checker();

        // check the parse tree
        run_checker();
    }
    // new class two dimension array
    {
        std::string input_str = "class A { int x; }\n"
                                "void f(){ A[][] a = new A[10][10];}";

        init_checker();

        // check the parse tree
        run_checker();
    }
    // new struct array with invalid size
    {
        std::string input_str = "typedef struct A_t { int x; }* A;\n"
                                "void f(){ A[] a = new A[1.0];}";

        init_checker();

        // check the parse tree
        TEST_EXPECT_EXCEPTION(
            run_checker());
    }

    TEST_PASS();
}