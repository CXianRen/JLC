#include "typechecker/jlc_tc_udt_def.h"
#include "typechecker/jlc_tc_udt_dcl.h"
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

int main(int argc, char **argv)
{

    PrintAbsyn *p = new PrintAbsyn();
    ShowAbsyn *s = new ShowAbsyn();

    // define an enmu
    {
        std::string input_str = "enum Color { RED, GREEN, BLUE };";

        auto parse_tree = gen_ast(input_str);

        // create a type checker
        // new context
        auto context = std::make_shared<JLC::CONTEXT::JLCContext>();

        auto decl_checker =
            std::make_shared<JLC::TC::JLC_UDT_DC_Checker>(context);

        auto def_checker =
            std::make_shared<JLC::TC::JLC_TC_UDT_DEF_Checker>(context);

        // check the parse tree
        parse_tree->accept(decl_checker.get());
        parse_tree->accept(def_checker.get());

        // check the result
        TEST_ASSERT(context->has_enum("Color") == true);
        auto enum_obj = context->get_enum("Color");
        TEST_ASSERT(enum_obj->obj_name == "Color");
        TEST_ASSERT(enum_obj->has_member("RED") == true);
        TEST_ASSERT(enum_obj->has_member("GREEN") == true);
        TEST_ASSERT(enum_obj->has_member("BLUE") == true);
        TEST_ASSERT(enum_obj->has_member("BLACK") == false);
    }
    // redefined enum value
    {
        std::string input_str = "enum Color { RED, GREEN, BLUE, RED };";

        auto parse_tree = gen_ast(input_str);

        // new context
        auto context = std::make_shared<JLC::CONTEXT::JLCContext>();

        // create a type checker
        auto decl_checker =
            std::make_shared<JLC::TC::JLC_UDT_DC_Checker>(context);

        auto def_checker =
            std::make_shared<JLC::TC::JLC_TC_UDT_DEF_Checker>(context);

        // check the parse tree
        TEST_EXPECT_EXCEPTION(
            {
                parse_tree->accept(decl_checker.get());
                parse_tree->accept(def_checker.get());
            });
    }
    // same value but not in a enum
    {
        std::string input_str = "enum Color { RED, GREEN, BLUE };"
                                "enum Color2 { RED, GREEN, BLUE };";

        auto parse_tree = gen_ast(input_str);

        // new context
        auto context = std::make_shared<JLC::CONTEXT::JLCContext>();

        // create a type checker
        auto decl_checker =
            std::make_shared<JLC::TC::JLC_UDT_DC_Checker>(context);

        auto def_checker =
            std::make_shared<JLC::TC::JLC_TC_UDT_DEF_Checker>(context);
        parse_tree->accept(decl_checker.get());
        parse_tree->accept(def_checker.get());
        
        // check the parse tree
        TEST_ASSERT(context->has_enum("Color") == true);
        auto enum_obj = context->get_enum("Color");
        TEST_ASSERT(enum_obj->obj_name == "Color");
        TEST_ASSERT(enum_obj->has_member("RED") == true);
        TEST_ASSERT(enum_obj->has_member("GREEN") == true);
        TEST_ASSERT(enum_obj->has_member("BLUE") == true);
        TEST_ASSERT(enum_obj->has_member("BLACK") == false);

        TEST_ASSERT(context->has_enum("Color2") == true);
        auto enum_obj2 = context->get_enum("Color2");
        TEST_ASSERT(enum_obj2->obj_name == "Color2");
        TEST_ASSERT(enum_obj2->has_member("RED") == true);
        TEST_ASSERT(enum_obj2->has_member("GREEN") == true);
        TEST_ASSERT(enum_obj2->has_member("BLUE") == true);
        TEST_ASSERT(enum_obj2->has_member("BLACK") == false);
    }
    TEST_PASS();
}