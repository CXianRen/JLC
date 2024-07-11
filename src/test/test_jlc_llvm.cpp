#include "typechecker/jlc_tc_udt_def.h"
#include "typechecker/jlc_tc_udt_dcl.h"
#include "typechecker/jlc_tc_func_dcl.h"
#include "typechecker/jlc_tc_func_def.h"
#include "llvm/jlc_llvm_generator.h"
#include "common/jlc_context.h"
#include "common/test.h"
#include "common/debug.h"

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
    // test enum type
    {
        std::string input_str = "enum Color { RED, GREEN, BLUE };";
        init_checker();
        run_checker();
        auto llvm_gen = std::make_shared<JLC::LLVM::LLVMGenerator>(context);
        llvm_gen->add_udt();

        TEST_ASSERT_INT_EQ(llvm_gen->llvm_context_.global_def.size(), 3);
        TEST_ASSERT_STR_EQ(llvm_gen->llvm_context_.global_def[0],
                           "@Color_RED = constant i32 0");
        TEST_ASSERT_STR_EQ(llvm_gen->llvm_context_.global_def[1],
                           "@Color_GREEN = constant i32 1");
        TEST_ASSERT_STR_EQ(llvm_gen->llvm_context_.global_def[2],
                           "@Color_BLUE = constant i32 2");
    }
    // test struct type
    {
        std::string input_str = "struct Point { int x; int y; };";
        init_checker();
        run_checker();
        auto llvm_gen = std::make_shared<JLC::LLVM::LLVMGenerator>(context);
        llvm_gen->add_udt();

        TEST_ASSERT_INT_EQ(llvm_gen->llvm_context_.llvm_instructions.size(), 1);
        TEST_ASSERT_STR_EQ(llvm_gen->llvm_context_.llvm_instructions[0],
                           "%struct.Point = type { i32, i32 }");
    }
    // test class type
    {
        std::string input_str = "class Point { int x; int y; }";
        init_checker();
        run_checker();
        auto llvm_gen = std::make_shared<JLC::LLVM::LLVMGenerator>(context);
        llvm_gen->add_udt();

        TEST_ASSERT_INT_EQ(llvm_gen->llvm_context_.llvm_instructions.size(), 1);
        TEST_ASSERT_STR_EQ(llvm_gen->llvm_context_.llvm_instructions[0],
                           "%class.Point = type { i32, i32 }");
    }

    // test internal function decleration
    {
        std::string input_str = "void f(){}";
        init_checker();
        run_checker();

        auto llvm_gen = std::make_shared<JLC::LLVM::LLVMGenerator>(context);
        llvm_gen->add_internal_func();

        TEST_ASSERT(llvm_gen->llvm_context_.llvm_instructions.size() > 0);
        TEST_ASSERT_STR_EQ(llvm_gen->llvm_context_.llvm_instructions[0],
                           "declare void @printInt(i32)");

        TEST_ASSERT_STR_EQ(llvm_gen->llvm_context_.llvm_instructions[1],
                           "declare void @printDouble(double)");

        TEST_ASSERT_STR_EQ(llvm_gen->llvm_context_.llvm_instructions[2],
                           "declare void @printString(ptr)");

        TEST_ASSERT_STR_EQ(llvm_gen->llvm_context_.llvm_instructions[3],
                           "declare i32 @readInt()");

        TEST_ASSERT_STR_EQ(llvm_gen->llvm_context_.llvm_instructions[4],
                           "declare double @readDouble()");
    }

    // test define variable
    {
        std::string input_str = "void f(){ int x; }";
        init_checker();
        run_checker();

        auto llvm_gen = std::make_shared<JLC::LLVM::LLVMGenerator>(context);
        parse_tree->accept(llvm_gen.get());

        auto result = llvm_gen->llvm_context_.llvm_instructions;
        TEST_ASSERT_STR_EQ(result[result.size() - 2], "%x0 = alloca i32");
    }
    // define a struct variable
    {
        std::string input_str = "typedef struct Point { int x; int y; }* Point;\n"
                                "void f(){ Point p; }";
        init_checker();
        run_checker();

        auto llvm_gen = std::make_shared<JLC::LLVM::LLVMGenerator>(context);
        parse_tree->accept(llvm_gen.get());

        auto result = llvm_gen->llvm_context_.llvm_instructions;
        TEST_ASSERT_STR_EQ(result[result.size() - 2], "%p0 = alloca ptr");
    }
    // define a class variable
    {
        std::string input_str = "class Point { int x; int y; }\n"
                                "void f(){ Point p; }";
        init_checker();
        run_checker();

        auto llvm_gen = std::make_shared<JLC::LLVM::LLVMGenerator>(context);
        parse_tree->accept(llvm_gen.get());

        auto result = llvm_gen->llvm_context_.llvm_instructions;
        TEST_ASSERT_STR_EQ(result[result.size() - 2], "%p0 = alloca ptr");
    }
    // define a array variable
    {
        std::string input_str = "void f(){ int[] x; }";
        init_checker();
        run_checker();

        auto llvm_gen = std::make_shared<JLC::LLVM::LLVMGenerator>(context);
        parse_tree->accept(llvm_gen.get());

        auto result = llvm_gen->llvm_context_.llvm_instructions;
        TEST_ASSERT_STR_EQ(result[result.size() - 2], "%x0 = alloca ptr");
    }
    // defina a int with initial number
    {
        std::string input_str = "void f(){ int x = 10; }";
        init_checker();
        run_checker();

        auto llvm_gen = std::make_shared<JLC::LLVM::LLVMGenerator>(context);
        parse_tree->accept(llvm_gen.get());

        auto result = llvm_gen->llvm_context_.llvm_instructions;
        TEST_ASSERT_STR_EQ(result[result.size() - 2],
                           "store i32 10, ptr %x0");
    }
    // define a double with initial number
    {
        std::string input_str = "void f(){ double x = 10.0; }";
        init_checker();
        run_checker();

        auto llvm_gen = std::make_shared<JLC::LLVM::LLVMGenerator>(context);
        parse_tree->accept(llvm_gen.get());

        auto result = llvm_gen->llvm_context_.llvm_instructions;
        TEST_ASSERT_STR_EQ(result[result.size() - 2],
                           "store double 10.000000, ptr %x0");
    }
    // define a class with null
    {
        std::string input_str = "class Point { int x; int y; }\n"
                                "void f(){ Point p = (Point)null; }";
        init_checker();
        run_checker();

        auto llvm_gen = std::make_shared<JLC::LLVM::LLVMGenerator>(context);
        parse_tree->accept(llvm_gen.get());

        auto result = llvm_gen->llvm_context_.llvm_instructions;
        TEST_ASSERT_STR_EQ(result[result.size() - 2],
                           "store ptr null, ptr %p0");
    }
    // define a struct with null
    {
        std::string input_str = "typedef struct Point { int x; int y; }* Point;\n"
                                "void f(){ Point p = (Point)null; }";
        init_checker();
        run_checker();

        auto llvm_gen = std::make_shared<JLC::LLVM::LLVMGenerator>(context);
        parse_tree->accept(llvm_gen.get());

        auto result = llvm_gen->llvm_context_.llvm_instructions;
        TEST_ASSERT_STR_EQ(result[result.size() - 2],
                           "store ptr null, ptr %p0");
    }
    // init with new
    {
        std::string input_str = "class Point { int x; int y; }\n"
                                "void f(){ Point p = new Point; }";
        init_checker();
        run_checker();

        auto llvm_gen = std::make_shared<JLC::LLVM::LLVMGenerator>(context);
        parse_tree->accept(llvm_gen.get());

        auto result = llvm_gen->llvm_context_.llvm_instructions;
        TEST_ASSERT_STR_EQ(result[result.size() - 3],
                           "%tmp1 = call ptr @calloc(i32 8, i32 1)");

        TEST_ASSERT_STR_EQ(result[result.size() - 2],
                           "store ptr %tmp1, ptr %p0");
    }

    TEST_PASS();
}
