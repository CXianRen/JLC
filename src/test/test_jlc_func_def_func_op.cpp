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
    // ++ op
    {
        std::string input_str = "void f(){ int x; x = x++;}";

        init_checker();
        run_checker();
    }
    // -- op
    {
        std::string input_str = "void f(){ int x; x = x--;}";

        init_checker();
        run_checker();
    }
    // ++ op on double
    {
        std::string input_str = "void f(){ double x; x = x++;}";

        init_checker();
        TEST_EXPECT_EXCEPTION(
            run_checker());
    }
    // -- op on double
    {
        std::string input_str = "void f(){ double x; x = x--;}";

        init_checker();
        TEST_EXPECT_EXCEPTION(
            run_checker());
    }
    // - op
    {
        std::string input_str = "void f(){ int x; x = -x;}";

        init_checker();
        run_checker();
    }
    // - op on double
    {
        std::string input_str = "void f(){ double x; x = -x;}";

        init_checker();
        run_checker();
    }
    // - op on boolean
    {
        std::string input_str = "void f(){ boolean x; x = -x;}";

        init_checker();
        TEST_EXPECT_EXCEPTION(
            run_checker());
    }
    // ! op
    {
        std::string input_str = "void f(){ boolean x; x = !x;}";

        init_checker();
        run_checker();
    }
    // ! op on int
    {
        std::string input_str = "void f(){ int x; x = !x;}";

        init_checker();
        TEST_EXPECT_EXCEPTION(
            run_checker());
    }
    // ! op on double
    {
        std::string input_str = "void f(){ double x; x = !x;}";

        init_checker();
        TEST_EXPECT_EXCEPTION(
            run_checker());
    }
    // * op
    {
        std::string input_str = "void f(){ int x; x = x*x;}";

        init_checker();
        run_checker();
    }
    // * op on double
    {
        std::string input_str = "void f(){ double x; x = x*x;}";

        init_checker();
        run_checker();
    }
    // * op on boolean
    {
        std::string input_str = "void f(){ boolean x; x = x*x;}";

        init_checker();
        TEST_EXPECT_EXCEPTION(
            run_checker());
    }
    // / op
    {
        std::string input_str = "void f(){ int x; x = x/x;}";

        init_checker();
        run_checker();
    }
    // / op on double
    {
        std::string input_str = "void f(){ double x; x = x/x;}";

        init_checker();
        run_checker();
    }
    // / op on boolean
    {
        std::string input_str = "void f(){ boolean x; x = x/x;}";

        init_checker();
        TEST_EXPECT_EXCEPTION(
            run_checker());
    }
    // mod op
    {
        std::string input_str = "void f(){ int x; x = x\%x;}";

        init_checker();
        run_checker();
    }
    // mod op on double
    {
        std::string input_str = "void f(){ double x; x = x\%x;}";

        init_checker();
        TEST_EXPECT_EXCEPTION(
            run_checker());
    }
    // type not equal
    {
        std::string input_str = "void f(){ int x; double y; x = x+y;}";

        init_checker();
        TEST_EXPECT_EXCEPTION(
            run_checker());
    }
    // + op
    {
        std::string input_str = "void f(){ int x; x = x+x;}";

        init_checker();
        run_checker();
    }

    // + op on double
    {
        std::string input_str = "void f(){ double x; x = x+x;}";

        init_checker();
        run_checker();
    }

    // + op on boolean
    {
        std::string input_str = "void f(){ boolean x; x = x+x;}";

        init_checker();
        TEST_EXPECT_EXCEPTION(
            run_checker());
    }

    // - op
    {
        std::string input_str = "void f(){ int x; x = x-x;}";

        init_checker();
        run_checker();
    }

    // - op on double
    {
        std::string input_str = "void f(){ double x; x = x-x;}";

        init_checker();
        run_checker();
    }

    // - op on boolean
    {
        std::string input_str = "void f(){ boolean x; x = x-x;}";

        init_checker();
        TEST_EXPECT_EXCEPTION(
            run_checker());
    }

    // < op
    {
        std::string input_str = "void f(){ int x; boolean y; y = x<x;}";

        init_checker();
        run_checker();
    }

    // < op on double
    {
        std::string input_str = "void f(){ double x; boolean y; y = x<x;}";

        init_checker();
        run_checker();
    }

    // < op on boolean
    {
        std::string input_str = "void f(){ boolean x; boolean y; y = x<x;}";

        init_checker();
        TEST_EXPECT_EXCEPTION(
            run_checker());
    }

    // > op
    {
        std::string input_str = "void f(){ int x; boolean y; y = x>x;}";

        init_checker();
        run_checker();
    }

    // > op on double
    {
        std::string input_str = "void f(){ double x; boolean y; y = x>x;}";

        init_checker();
        run_checker();
    }

    // > op on boolean
    {
        std::string input_str = "void f(){ boolean x; boolean y; y = x>x;}";

        init_checker();
        TEST_EXPECT_EXCEPTION(
            run_checker());
    }

    // <= op
    {
        std::string input_str = "void f(){ int x; boolean y; y = x<=x;}";

        init_checker();
        run_checker();
    }

    // <= op on double
    {
        std::string input_str = "void f(){ double x; boolean y; y = x<=x;}";

        init_checker();
        run_checker();
    }

    // <= op on boolean
    {
        std::string input_str = "void f(){ boolean x; boolean y; y = x<=x;}";

        init_checker();
        TEST_EXPECT_EXCEPTION(
            run_checker());
    }

    // >= op
    {
        std::string input_str = "void f(){ int x; boolean y; y = x>=x;}";

        init_checker();
        run_checker();
    }

    // >= op on double
    {
        std::string input_str = "void f(){ double x; boolean y; y = x>=x;}";

        init_checker();
        run_checker();
    }

    // >= op on boolean
    {
        std::string input_str = "void f(){ boolean x; boolean y; y = x>=x;}";

        init_checker();
        TEST_EXPECT_EXCEPTION(
            run_checker());
    }

    // == op
    {
        std::string input_str = "void f(){ int x; boolean y; y = x==x;}";

        init_checker();
        run_checker();
    }

    // == op on double
    {
        std::string input_str = "void f(){ double x; boolean y; y = x==x;}";

        init_checker();
        run_checker();
    }

    // == op on boolean
    {
        std::string input_str = "void f(){ boolean x; boolean y; y = x==x;}";

        init_checker();
        run_checker();
    }

    // && op
    {
        std::string input_str = "void f(){ boolean x; boolean y; y = x&&x;}";

        init_checker();
        run_checker();
    }

    // && op on int
    {
        std::string input_str = "void f(){ int x; boolean y; y = x&&x;}";

        init_checker();
        TEST_EXPECT_EXCEPTION(
            run_checker());
    }

    // || op
    {
        std::string input_str = "void f(){ boolean x; boolean y; y = x||x;}";

        init_checker();
        run_checker();
    }

    // || op on int
    {
        std::string input_str = "void f(){ int x; boolean y; y = x||x;}";

        init_checker();
        TEST_EXPECT_EXCEPTION(
            run_checker());
    }
    
    // cast ()
    {
        std::string input_str = "void f(){ int x; double y; y = (double)x;}";

        init_checker();
        run_checker();
    }
    // case null
    {
        std::string input_str = "void f(){ int x; double y; y = (double)null;}";

        init_checker();
        run_checker();
    }

    TEST_PASS();
}