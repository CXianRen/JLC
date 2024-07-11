#include "typechecker/jlc_tc_udt_def.h"
#include "typechecker/jlc_tc_udt_dcl.h"
#include "common/jlc_context.h"
#include "common/test.h"

#include <iostream>
#include <string>

int main(int argc, char **argv)
{
    // define an class
    {
        std::string input_str = "class Color { int r; int g; int b; }";

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
        TEST_ASSERT(context->has_class("Color") == true);

        auto class_obj = context->get_class("Color");
        TEST_ASSERT(class_obj != nullptr);
        TEST_ASSERT(class_obj->obj_name == "Color");
        TEST_ASSERT(class_obj->has_member("r") == true);
        TEST_ASSERT(class_obj->has_member("g") == true);
        TEST_ASSERT(class_obj->has_member("b") == true);

        // check the member type
        TEST_ASSERT(*class_obj->get_member_type("r") ==
                    JLC::TYPE::JLCType(JLC::TYPE::type_enum::INT));
    }
    // define a class inherited from another class
    {
        std::string input_str = "class Color { int r; int g; int b; }\n"
                                "class Color2 extends Color { int a; }";

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
        TEST_ASSERT(context->has_class("Color") == true);
        TEST_ASSERT(context->has_class("Color2") == true);

        auto class_obj = context->get_class("Color2");
        TEST_ASSERT(class_obj != nullptr);

        TEST_ASSERT(class_obj->obj_name == "Color2");
        TEST_ASSERT(class_obj->has_member("r") == true);
        TEST_ASSERT(class_obj->has_member("g") == true);
        TEST_ASSERT(class_obj->has_member("b") == true);

        TEST_ASSERT(class_obj->has_member("a") == true);

        // check parent class
        TEST_ASSERT(class_obj->parent_class->has_member("a") == false);
    }
    TEST_PASS();
}