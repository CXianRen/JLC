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

    // define an struct
    {
        std::string input_str = "struct Color { int r; int g; int b; };";

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
        TEST_ASSERT(context->has_struct("Color") == true);
        auto struct_obj = context->get_struct("Color");
        TEST_ASSERT(struct_obj != nullptr);
        TEST_ASSERT(struct_obj->obj_name == "Color");
        TEST_ASSERT(struct_obj->has_member("r") == true);
        TEST_ASSERT(struct_obj->has_member("g") == true);
        TEST_ASSERT(struct_obj->has_member("b") == true);

        // check the member type
        TEST_ASSERT(*struct_obj->get_member_type("r") ==
                    JLC::TYPE::JLCType(JLC::TYPE::type_enum::INT));
    }
    // redefined member
    {
        std::string input_str = "struct Color { int r; int r; int b; };";

        auto parse_tree = gen_ast(input_str);

        // create a type checker
        // new context
        auto context = std::make_shared<JLC::CONTEXT::JLCContext>();

        auto decl_checker =
            std::make_shared<JLC::TC::JLC_UDT_DC_Checker>(context);

        auto def_checker =
            std::make_shared<JLC::TC::JLC_TC_UDT_DEF_Checker>(context);

        TEST_EXPECT_EXCEPTION({
            // check the parse tree
            parse_tree->accept(decl_checker.get());
            parse_tree->accept(def_checker.get());
        });
    }
    // void type member is not allowed
    {
        std::string input_str = "struct Color { int r; int g; void b; };";

        auto parse_tree = gen_ast(input_str);

        // create a type checker
        // new context
        auto context = std::make_shared<JLC::CONTEXT::JLCContext>();

        auto decl_checker =
            std::make_shared<JLC::TC::JLC_UDT_DC_Checker>(context);

        auto def_checker =
            std::make_shared<JLC::TC::JLC_TC_UDT_DEF_Checker>(context);

        TEST_EXPECT_EXCEPTION({
            // check the parse tree
            parse_tree->accept(decl_checker.get());
            parse_tree->accept(def_checker.get());
        });
    }
    // struct * member
    {
        std::string input_str = "struct Color { int r; int g; int b; };\n"
                                "typedef struct Color * ColorPtr;\n"
                                "struct Person { ColorPtr color; };\n";

        auto parse_tree = gen_ast(input_str);

        // create a type checker
        // new context
        auto context = std::make_shared<JLC::CONTEXT::JLCContext>();

        auto decl_checker =
            std::make_shared<JLC::TC::JLC_UDT_DC_Checker>(context);

        auto def_checker =
            std::make_shared<JLC::TC::JLC_TC_UDT_DEF_Checker>(context);

        parse_tree->accept(decl_checker.get());
        parse_tree->accept(def_checker.get());

        // check the result
        TEST_ASSERT(context->has_struct("Color") == true);
        TEST_ASSERT(context->has_struct("Person") == true);
        TEST_ASSERT(context->has_typedef("ColorPtr") == true);
        // check the member type
        auto person_obj = context->get_struct("Person");
        TEST_ASSERT(person_obj->has_member("color") == true);
        TEST_ASSERT(*person_obj->get_member_type("color") ==
                    JLC::TYPE::JLCType(JLC::TYPE::type_enum::STRUCT, "Color"));
    }
    // enum member
    {
        std::string input_str = "enum Color { RED, GREEN, BLUE };\n"
                                "struct Person { Color color; };\n";

        auto parse_tree = gen_ast(input_str);

        // create a type checker
        // new context
        auto context = std::make_shared<JLC::CONTEXT::JLCContext>();

        auto decl_checker =
            std::make_shared<JLC::TC::JLC_UDT_DC_Checker>(context);

        auto def_checker =
            std::make_shared<JLC::TC::JLC_TC_UDT_DEF_Checker>(context);

        parse_tree->accept(decl_checker.get());
        parse_tree->accept(def_checker.get());

        // check the result
        TEST_ASSERT(context->has_enum("Color") == true);
        TEST_ASSERT(context->has_struct("Person") == true);
        // check the member type
        auto person_obj = context->get_struct("Person");
        TEST_ASSERT(person_obj->has_member("color") == true);
        TEST_ASSERT(*person_obj->get_member_type("color") ==
                    JLC::TYPE::JLCType(JLC::TYPE::type_enum::ENUM, "Color"));
    }
    // class member @todo
    {
    }
    // typedef struct {} *
    {
        std::string input_str = "typedef struct Color {int r, g, b;} * ColorPtr;";

        auto parse_tree = gen_ast(input_str);

        // create a type checker
        // new context
        auto context = std::make_shared<JLC::CONTEXT::JLCContext>();

        auto decl_checker =
            std::make_shared<JLC::TC::JLC_UDT_DC_Checker>(context);

        auto def_checker =
            std::make_shared<JLC::TC::JLC_TC_UDT_DEF_Checker>(context);

        parse_tree->accept(decl_checker.get());
        parse_tree->accept(def_checker.get());

        // check the result
        TEST_ASSERT(context->has_struct("Color") == true);
        TEST_ASSERT(context->has_typedef("ColorPtr") == true);
        // check the member type
        auto struct_obj = context->get_struct("Color");
        TEST_ASSERT(struct_obj != nullptr);
        TEST_ASSERT(struct_obj->obj_name == "Color");
        TEST_ASSERT(struct_obj->has_member("r") == true);
        TEST_ASSERT(struct_obj->has_member("g") == true);
        TEST_ASSERT(struct_obj->has_member("b") == true);

        // check the member type
        TEST_ASSERT(*struct_obj->get_member_type("r") ==
                    JLC::TYPE::JLCType(JLC::TYPE::type_enum::INT));
    }
    TEST_PASS();
}