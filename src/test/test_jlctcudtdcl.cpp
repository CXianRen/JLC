#include "typechecker/jlc_tc_udt_dcl.h"
#include "typechecker/jlc_tc_error.h"
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

int main(int argc, char **argv)
{
    PrintAbsyn *p = new PrintAbsyn();
    ShowAbsyn *s = new ShowAbsyn();

    {
        std::string input_str = "enum Color { RED, GREEN, BLUE }; ";

        auto parse_tree = gen_ast(input_str);

        // create a type checker
        // new context
        auto context = std::make_shared<JLC::CONTEXT::JLCContext>();

        auto checker =
            std::make_shared<JLC::TC::JLC_UDT_DC_Checker>(context);

        // check the parse tree
        try
        {
            parse_tree->accept(checker.get());
        }
        catch (JLC::TC::JLCTCError &e)
        {
            std::cerr << e.what() << std::endl;
        }

        // check if the enum is added to the context
        TEST_ASSERT(context->is_exist_enum("Color") == true);
    }
    // redefined enum
    {
        std::string input_str = "enum Color { RED, GREEN, BLUE };"
                                "enum Color { RED, GREEN, BLUE }; ";

        auto parse_tree = gen_ast(input_str);

        // create a type checker
        // new context
        auto context = std::make_shared<JLC::CONTEXT::JLCContext>();

        auto checker =
            std::make_shared<JLC::TC::JLC_UDT_DC_Checker>(context);

        TEST_EXPECT_EXCEPTION(
            parse_tree->accept(checker.get());)
    }

    /** struct **/
    {
        std::string input_str = "struct Point { int x; int y; }; ";

        auto parse_tree = gen_ast(input_str);

        // create a type checker
        // new context
        auto context = std::make_shared<JLC::CONTEXT::JLCContext>();

        auto checker =
            std::make_shared<JLC::TC::JLC_UDT_DC_Checker>(context);

        // check the parse tree
        try
        {
            parse_tree->accept(checker.get());
        }
        catch (JLC::TC::JLCTCError &e)
        {
            std::cerr << e.what() << std::endl;
        }

        // check if the struct is added to the context
        TEST_ASSERT(context->is_exist_struct("Point") == true);
    }
    // redefined struct
    {

        std::string input_str = "struct Point { int x; int y; };"
                                "struct Point { int x; int y; }; ";

        auto parse_tree = gen_ast(input_str);

        // create a type checker
        // new context
        auto context = std::make_shared<JLC::CONTEXT::JLCContext>();

        auto checker =
            std::make_shared<JLC::TC::JLC_UDT_DC_Checker>(context);

        TEST_EXPECT_EXCEPTION(
            parse_tree->accept(checker.get());)
    }
    // typedef with struct
    {

        std::string input_str = "typedef struct Point_t { int a;} * Point; ";
        auto parse_tree = gen_ast(input_str);

        auto context = std::make_shared<JLC::CONTEXT::JLCContext>();

        auto checker =
            std::make_shared<JLC::TC::JLC_UDT_DC_Checker>(context);

        // check the parse tree
        try
        {
            parse_tree->accept(checker.get());
        }
        catch (JLC::TC::JLCTCError &e)
        {
            std::cerr << e.what() << std::endl;
        }

        // check if the struct is added to the context
        TEST_ASSERT(context->is_exist_struct("Point_t") == true);
        TEST_ASSERT(context->is_exist_typedef("Point") == true);
    }
    // typedef without struct
    {
        std::string input_str = "typedef struct Foo_t * Foo; \n"
                                "struct Foo_t{ int bar; };";
        auto parse_tree = gen_ast(input_str);

        auto context = std::make_shared<JLC::CONTEXT::JLCContext>();

        auto checker =
            std::make_shared<JLC::TC::JLC_UDT_DC_Checker>(context);

        // check the parse tree
        try
        {
            parse_tree->accept(checker.get());
        }
        catch (JLC::TC::JLCTCError &e)
        {
            std::cerr << e.what() << std::endl;
        }
        TEST_ASSERT(context->is_exist_struct("Foo_t") == true);
        TEST_ASSERT(context->is_exist_typedef("Foo") == true);
    }
    // only typedef
    {
        // typedef without struct
        // typedef struct Foo_t * Foo;
        std::string input_str = "typedef struct Foo_t * Foo; \n";

        auto parse_tree = gen_ast(input_str);

        auto context = std::make_shared<JLC::CONTEXT::JLCContext>();

        auto checker =
            std::make_shared<JLC::TC::JLC_UDT_DC_Checker>(context);

        // expect an exception
        TEST_EXPECT_EXCEPTION(
            parse_tree->accept(checker.get());)
    }

    /** class **/
    // a class without extends
    {
        std::string input_str = "class Foo { } ";
        auto parse_tree = gen_ast(input_str);
        auto context = std::make_shared<JLC::CONTEXT::JLCContext>();
        auto checker =
            std::make_shared<JLC::TC::JLC_UDT_DC_Checker>(context);

        parse_tree->accept(checker.get());

        TEST_ASSERT(context->is_exist_class("Foo") == true);
        TEST_ASSERT(context->is_exist_class("Bar") == false);
    }
    // a class with extends
    {

        std::string input_str = "class Foo extends Bar { }"
                                "class Bar { }";

        auto parse_tree = gen_ast(input_str);
        auto context = std::make_shared<JLC::CONTEXT::JLCContext>();
        auto checker =
            std::make_shared<JLC::TC::JLC_UDT_DC_Checker>(context);

        parse_tree->accept(checker.get());
        TEST_ASSERT(context->is_exist_class("Foo") == true);
        TEST_ASSERT(context->is_exist_class("Bar") == true);
    }
    // a class with extends but not defined
    {
        std::string input_str = "class Foo extends Bar { }";

        auto parse_tree = gen_ast(input_str);
        auto context = std::make_shared<JLC::CONTEXT::JLCContext>();
        auto checker =
            std::make_shared<JLC::TC::JLC_UDT_DC_Checker>(context);

        TEST_EXPECT_EXCEPTION(
            parse_tree->accept(checker.get());)
    }
    // a class with extends itself
    {
        std::string input_str = "class Foo extends Foo { } ";

        auto parse_tree = gen_ast(input_str);
        auto context = std::make_shared<JLC::CONTEXT::JLCContext>();
        auto checker =
            std::make_shared<JLC::TC::JLC_UDT_DC_Checker>(context);

        TEST_EXPECT_EXCEPTION(
            parse_tree->accept(checker.get());)
    }

    // same name class and struct or enum, type name conflict
    {
        std::string input_str = "class Foo { } \n "
                                "enum Foo { RED, GREEN, BLUE }; ";

        auto parse_tree = gen_ast(input_str);
        auto context = std::make_shared<JLC::CONTEXT::JLCContext>();
        auto checker =
            std::make_shared<JLC::TC::JLC_UDT_DC_Checker>(context);

        TEST_EXPECT_EXCEPTION(
            parse_tree->accept(checker.get());)
    }
    TEST_PASS();
    return 0;
}