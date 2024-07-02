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

    // define variables no init
    {
        std::string input_str = "int f(){ int a; int b; double c,d;}";

        init_checker();

        // check the parse tree
        run_checker();

        // @need a better way to check the result, currently vars will be released after the function is done
        // check the result
        // auto func_obj = context->get_func(
        //     context->get_scope_name("f", func_def_checker->GLOBAL_SCOPE));

        // // check the variables
        // DEBUG_PRINT(func_obj->str());(
        // TEST_ASSERT(func_obj->has_var("a"));
        // TEST_ASSERT(func_obj->has_var("b"));)
        // TEST_ASSERT(func_obj->has_var("c"));
        // TEST_ASSERT(func_obj->has_var("d"));
    }
    // redefined variable in a scope
    {

        std::string input_str = "int f(){ int a; int b; double a;}";

        init_checker();

        // check the parse tree
        parse_tree->accept(type_decl_checker.get());
        parse_tree->accept(func_decl_checker.get());
        parse_tree->accept(type_def_checker.get());

        TEST_EXPECT_EXCEPTION(
            parse_tree->accept(func_def_checker.get()));
    }
    // shadow parameter
    {
        std::string input_str = "int f(int a){ double a; int b;}";

        init_checker();
        // check the parse tree
        run_checker();
    }
    // shadow outer variable
    {
        std::string input_str = "int f(int a){ double a; int b; {double b;{int a;}}}";

        init_checker();

        // check the parse tree
        run_checker();
    }
    // with initialization
    {
        std::string input_str = "int f(int a){int a, b=1; double c=0.0, d; }";
        init_checker();

        // check the parse tree
        run_checker();
    }
    // void type
    {
        std::string input_str = "int f(int a){int a, b=1; void c, d; }";
        init_checker();

        // check the parse tree
        parse_tree->accept(type_decl_checker.get());
        parse_tree->accept(func_decl_checker.get());
        parse_tree->accept(type_def_checker.get());
        TEST_EXPECT_EXCEPTION(
            parse_tree->accept(func_def_checker.get()));
    }
    // array
    {
        std::string input_str = "int f(){int[] a; int[][]b;}";
        init_checker();

        // check the parse tree
        run_checker();
    }
    // struct
    {
        std::string input_str = "typedef struct a_t{int a;}  * A; \n"
                                "int f(){A a;}";
        init_checker();

        // check the parse tree
        run_checker();
    }
    // enum
    {
        std::string input_str = "enum A {a,b,c}; \n"
                                "int f(){A a;}";
        init_checker();

        // check the parse tree
        run_checker();
    }
    // class
    {
        std::string input_str = "class A {int a;} \n"
                                "int f(){A a;}";
        init_checker();

        // check the parse tree
        run_checker();
    }

    TEST_PASS();
}