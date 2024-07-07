#include <iostream>

#include "llvm/llvm.h"
#include "common/test.h"

#include "common/debug.h"

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

    // test llvm type definition
    {
        MLLVM::LLVM_Context context;
        std::string llvm_type = "\%struct.type";
        std::vector<std::string> llvm_elements = {"i32", "i32"};
        context.gen_define_type(llvm_type, llvm_elements);
        std::string result = context.llvm_instructions.back();
        std::string expected = "\%struct.type = type { i32, i32 }";
        DEBUG_PRINT("result  : " + result);
        DEBUG_PRINT("expected: " + expected);
        TEST_ASSERT(result == expected);
    }

    // test llvm access field in type
    {
        MLLVM::LLVM_Context context;
        std::string llvm_type = "\%struct.type";
        std::string llvm_field = "\%field";
        int offset = 0;
        context.gen_offset_field_in_type(llvm_type, llvm_field, offset);
        std::string result = context.llvm_instructions.back();
        std::string expected = "\%field = getelementptr \%struct.type, ptr \%struct_pointer, i32 0, i32 0";
        DEBUG_PRINT("result  : " + result);
        DEBUG_PRINT("expected: " + expected);
        TEST_ASSERT(result == expected);
    }

    // test llvm global constant variable
    {
        MLLVM::LLVM_Context context;
        std::string llvm_var_name = "var_name";
        std::string llvm_type = "i32";
        std::string llvm_value = "10";
        context.gen_global_const_var(llvm_var_name, llvm_type, llvm_value);
        std::string result = context.llvm_instructions.back();
        std::string expected = "@var_name = constant i32 10";
        DEBUG_PRINT("result  : " + result);
        DEBUG_PRINT("expected: " + expected);
        TEST_ASSERT(result == expected);
    }

    // test declare function instruction
    {
        MLLVM::LLVM_Context context;
        std::string llvm_func_name = "func_name";
        std::string llvm_return_type = "i32";
        std::vector<std::string> llvm_args = {"i32", "i32"};
        context.gen_declare_func(llvm_func_name, llvm_return_type, llvm_args);
        std::string result = context.llvm_instructions.back();
        std::string expected = "declare i32 @func_name(i32, i32)";
        DEBUG_PRINT("result  : " + result);
        DEBUG_PRINT("expected: " + expected);
        TEST_ASSERT(result == expected);
    }

    // test llvm function definition start
    {
        MLLVM::LLVM_Context context;
        std::string llvm_func_name = "func_name";
        std::string llvm_return_type = "i32";
        std::vector<std::string> llvm_args = {"i32", "i32"};
        context.gen_define_func_start(llvm_func_name, llvm_return_type, llvm_args);
        std::string result = context.llvm_instructions.back();
        std::string expected = "define i32 @func_name(i32, i32) {";
        DEBUG_PRINT("result  : " + result);
        DEBUG_PRINT("expected: " + expected);
        TEST_ASSERT(result == expected);
    }

    // test llvm function definition end
    {
        MLLVM::LLVM_Context context;
        context.gen_define_func_end();
        std::string result = context.llvm_instructions.back();
        std::string expected = "}";
        DEBUG_PRINT("result  : " + result);
        DEBUG_PRINT("expected: " + expected);
        TEST_ASSERT(result == expected);
    }

    TEST_PASS();
}