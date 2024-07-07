#include "typechecker/jlc_tc_udt_def.h"
#include "typechecker/jlc_tc_udt_dcl.h"
#include "typechecker/jlc_tc_func_dcl.h"
#include "typechecker/jlc_tc_func_def.h"
#include "llvm/jlc_llvm_generator.h"
#include "common/jlc_context.h"
#include "common/test.h"
#include "common/debug.h"

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
    // test enum type
    {
        std::string input_str = "enum Color { RED, GREEN, BLUE };";
        init_checker();
        run_checker();
        auto llvm_gen = std::make_shared<JLC::LLVM::LLVMGenerator>(context);

        TEST_ASSERT(llvm_gen->llvm_context_.llvm_instructions.size() == 3);
        DEBUG_PRINT(llvm_gen->llvm_context_.llvm_instructions[0]);
        TEST_ASSERT(llvm_gen->llvm_context_.llvm_instructions[0] ==
                    "@Color_RED = constant i32 0");
        DEBUG_PRINT(llvm_gen->llvm_context_.llvm_instructions[1]);
        TEST_ASSERT(llvm_gen->llvm_context_.llvm_instructions[1] ==
                    "@Color_GREEN = constant i32 1");
        DEBUG_PRINT(llvm_gen->llvm_context_.llvm_instructions[2]);
        TEST_ASSERT(llvm_gen->llvm_context_.llvm_instructions[2] ==
                    "@Color_BLUE = constant i32 2");
    }
    // test struct type
    {
        std::string input_str = "struct Point { int x; int y; };";
        init_checker();
        run_checker();
        auto llvm_gen = std::make_shared<JLC::LLVM::LLVMGenerator>(context);

        TEST_ASSERT(llvm_gen->llvm_context_.llvm_instructions.size() == 1);
        DEBUG_PRINT(llvm_gen->llvm_context_.llvm_instructions[0]);
        TEST_ASSERT(llvm_gen->llvm_context_.llvm_instructions[0] ==
                    "\%struct.Point = type { i32, i32 }");
    }
    // test class type
    {
        std::string input_str = "class Point { int x; int y; }";
        init_checker();
        run_checker();
        auto llvm_gen = std::make_shared<JLC::LLVM::LLVMGenerator>(context);

        TEST_ASSERT(llvm_gen->llvm_context_.llvm_instructions.size() == 1);
        DEBUG_PRINT(llvm_gen->llvm_context_.llvm_instructions[0]);
        TEST_ASSERT(llvm_gen->llvm_context_.llvm_instructions[0] ==
                    "\%class.Point = type { i32, i32 }");
    }

    TEST_PASS();
}
