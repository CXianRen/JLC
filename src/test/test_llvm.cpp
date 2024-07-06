#include <iostream>

#include "llvm/llvm.h"
#include "common/test.h"

int main(int argc, char **argv)
{

    // test llvm type to string
    {
        TEST_ASSERT(MLLVM::str(MLLVM::LLVM_i1) == "i1");
        TEST_ASSERT(MLLVM::str(MLLVM::LLVM_i32) == "i32");
        TEST_ASSERT(MLLVM::str(MLLVM::LLVM_double) == "double");
        TEST_ASSERT(MLLVM::str(MLLVM::LLVM_ptr) == "ptr");
        TEST_ASSERT(MLLVM::str(MLLVM::LLVM_void) == "void");
    }

    // test gen comment
    {
        MLLVM::LLVM_Context context;
        context.gen_comment("test comment");
        std::string result = context.str();
        std::string expected = "; test comment\n";
        TEST_ASSERT(result == expected);
    }

    // test name generation
    {
        MLLVM::LLVM_Context context;
        std::string result = context.gen_name("var");
        std::string expected = "%var0";
        TEST_ASSERT(result == expected);

        result = context.gen_name("var");
        expected = "%var1";
        TEST_ASSERT(result == expected);
    }

    // reset name counter
    {
        MLLVM::LLVM_Context context;
        context.reset_name_counter();
        std::string result = context.gen_name("var");
        std::string expected = "%var0";
        TEST_ASSERT(result == expected);
    }

    // test alloca instruction
    {
        MLLVM::LLVM_Context context;
        std::string llvm_value = "%var0";
        context.gen_alloc_inst(llvm_value, MLLVM::LLVM_i32);
        std::string result = context.llvm_instructions.back();
        ;
        std::string expected = "%var0 = alloca i32";
        TEST_ASSERT(result == expected);
    }

    // test store instruction
    {
        MLLVM::LLVM_Context context;
        std::string llvm_src = "10";
        std::string llvm_dst = "%var0";
        context.gen_store_inst(llvm_src, llvm_dst, MLLVM::LLVM_i32);
        std::string result = context.llvm_instructions.back();
        std::string expected = "store i32 10, ptr %var0";
        TEST_ASSERT(result == expected);
    }

    // test load instruction
    {
        MLLVM::LLVM_Context context;
        std::string llvm_dst = "%var";
        std::string llvm_src = "%var_pointer";
        context.gen_load_inst(llvm_src, llvm_dst, MLLVM::LLVM_i32);
        std::string result = context.llvm_instructions.back();
        std::string expected = "%var = load i32, ptr %var_pointer";
        TEST_ASSERT(result == expected);
    }

    TEST_PASS();
}