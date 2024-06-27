#include "typechecker/jlc_tc_tdf_dcl.h"
#include "typechecker/jlc_tc_error.h"
#include "common/test.h"

#include "parser/Parser.H"
#include "parser/Absyn.H"
#include "ParserError.H"

#include <iostream>
#include <string>

int main(int argc, char **argv)
{
    Prog *parse_tree = NULL;
    {
        std::string input_str = "enum Color { RED, GREEN, BLUE }; ";
        // convert a string to file object
        FILE *input = fmemopen((void *)input_str.c_str(), input_str.size(), "r");

        try
        {
            parse_tree = pProg(input);
        }
        catch (parse_error &e)
        {
            std::cerr << "Parse error on line " << e.getLine() << "\n";
            TEST_FAIL();
            return -1;
        }
        if (parse_tree == NULL)
        {
            TEST_FAIL();
            return -1;
        }

        // create a type checker
        // new context
        auto context = std::make_shared<JLC::CONTEXT::JLCContext>();

        auto checker =
            std::make_shared<JLC::TC::JLCTopDefinitionChecker>(context);

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

        // convert a string to file object
        FILE *input = fmemopen((void *)input_str.c_str(), input_str.size(), "r");

        try
        {
            parse_tree = pProg(input);
        }
        catch (parse_error &e)
        {
            std::cerr << "Parse error on line " << e.getLine() << "\n";
            TEST_FAIL();
            return -1;
        }
        if (parse_tree == NULL)
        {
            TEST_FAIL();
            return -1;
        }

        // create a type checker
        // new context
        auto context = std::make_shared<JLC::CONTEXT::JLCContext>();

        auto checker =
            std::make_shared<JLC::TC::JLCTopDefinitionChecker>(context);

        TEST_EXPECT_EXCEPTION(
            parse_tree->accept(checker.get());)
    }
    // // redefined value
    // {
    //     std::string input_str = "enum Color { RED, GREEN, RED };";

    //     // convert a string to file object
    //     FILE *input = fmemopen((void *)input_str.c_str(), input_str.size(), "r");

    //     try
    //     {
    //         parse_tree = pProg(input);
    //     }
    //     catch (parse_error &e)
    //     {
    //         std::cerr << "Parse error on line " << e.getLine() << "\n";
    //         TEST_FAIL();
    //         return -1;
    //     }
    //     if (parse_tree == NULL)
    //     {
    //         TEST_FAIL();
    //         return -1;
    //     }

    //     // create a type checker
    //     // new context
    //     auto context = std::make_shared<JLC::CONTEXT::JLCContext>();

    //     auto checker =
    //         std::make_shared<JLC::TC::JLCTopDefinitionChecker>(context);

    //     TEST_EXPECT_EXCEPTION(
    //         parse_tree->accept(checker.get());)
    // }
    TEST_PASS();
    return 0;
}