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
    // assign int to int
    {
        std::string input_str = "int f(){ int x = 1; x = 2; return x;}";

        init_checker();

        // check the parse tree
        run_checker();
    }

    // assign double to double
    {
        std::string input_str = "int f(){ double x = 1.0; x = 2.0; return 0;}";

        init_checker();

        // check the parse tree
        run_checker();
    }
    // assign int to double
    {
        std::string input_str = "void f(){ double x; x = 2;}";

        init_checker();

        // check the parse tree
        TEST_EXPECT_EXCEPTION(
            run_checker());
    }
    // assign bool to int
    {
        std::string input_str = "int f(){ int x; x = true; return x;}";

        init_checker();

        // check the parse tree
        TEST_EXPECT_EXCEPTION(
            run_checker());
    }
    // assign array to array
    {
        std::string input_str = "void f(){ int[] x; x = new int[10];}";

        init_checker();

        // check the parse tree
        run_checker();
    }
    // assing 2 dim array of a 3 dim array to a 2 dim array
    {
        std::string input_str = "void f(){ int[][] x; int[][][] y; x = y[0];}";

        init_checker();

        // check the parse tree
        run_checker();
    }
    // access dim out of the array
    {
        std::string input_str = "void f(){ int[] x; x[1][1] = 1;}";

        init_checker();

        // check the parse tree
        TEST_EXPECT_EXCEPTION(
            run_checker());
    }
    // assign array element to array element
    {
        std::string input_str = "void f(){ double[] x; x[1] = x[2];}";

        init_checker();

        // check the parse tree
        run_checker();
    }
    TEST_PASS();
}