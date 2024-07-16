#include <iostream>

#include "llvm/llvm.h"
#include "common/test.h"

#include "common/debug.h"

int main(int argc, char **argv)
{

    // test llvm type to string
    {
        TEST_ASSERT_STR_EQ(MLLVM::str(MLLVM::LLVM_i1), "i1");
        TEST_ASSERT_STR_EQ(MLLVM::str(MLLVM::LLVM_i32), "i32");
        TEST_ASSERT_STR_EQ(MLLVM::str(MLLVM::LLVM_double), "double");
        TEST_ASSERT_STR_EQ(MLLVM::str(MLLVM::LLVM_ptr), "ptr");
        TEST_ASSERT_STR_EQ(MLLVM::str(MLLVM::LLVM_void), "void");
    }

    // test gen comment
    {
        MLLVM::LLVM_Context context;
        context.gen_comment("test comment");
        std::string result = context.llvm_instructions->back();
        std::string expected = "; test comment";
        TEST_ASSERT_STR_EQ(result, expected);
    }

    // test name generation
    {
        MLLVM::LLVM_Context context;
        std::string result = context.gen_name("var");
        std::string expected = "%var0";
        TEST_ASSERT_STR_EQ(result, expected);

        result = context.gen_name("var");
        expected = "%var1";
        TEST_ASSERT_STR_EQ(result, expected);
    }

    // reset name counter
    {
        MLLVM::LLVM_Context context;
        context.reset_name_counter();
        std::string result = context.gen_name("var");
        std::string expected = "%var0";
        TEST_ASSERT_STR_EQ(result, expected);
    }

    // test alloca instruction
    {
        MLLVM::LLVM_Context context;
        std::string llvm_value = "%var0";
        context.gen_alloc_inst(llvm_value, MLLVM::LLVM_i32);
        std::string result = context.llvm_instructions->back();
        ;
        std::string expected = "%var0 = alloca i32";
        TEST_ASSERT_STR_EQ(result, expected);
    }

    // test store instruction
    {
        MLLVM::LLVM_Context context;
        std::string llvm_src = "10";
        std::string llvm_dst = "%var0";
        context.gen_store_inst(llvm_src, llvm_dst, MLLVM::LLVM_i32);
        std::string result = context.llvm_instructions->back();
        std::string expected = "store i32 10, ptr %var0";
        TEST_ASSERT_STR_EQ(result, expected);
    }

    // test load instruction
    {
        MLLVM::LLVM_Context context;
        std::string llvm_dst = "%var";
        std::string llvm_src = "%var_pointer";
        context.gen_load_inst(llvm_src, llvm_dst, MLLVM::LLVM_i32);
        std::string result = context.llvm_instructions->back();
        std::string expected = "%var = load i32, ptr %var_pointer";
        TEST_ASSERT_STR_EQ(result, expected);
    }

    // test llvm type definition
    {
        MLLVM::LLVM_Context context;
        std::string llvm_type = "%struct.type";
        std::vector<std::string> llvm_elements = {"i32", "i32"};
        context.gen_define_type(llvm_type, llvm_elements);
        std::string result = context.llvm_instructions->back();
        std::string expected = "%struct.type = type { i32, i32 }";
        TEST_ASSERT_STR_EQ(result, expected);
    }

    // test llvm access field in type
    {
        MLLVM::LLVM_Context context;
        std::string llvm_type = "%struct.A";
        std::string llvm_field = "%field";
        std::string llvm_struct_pointer = "%obj_a";
        int offset = 0;
        context.gen_offset_field_in_type(
            llvm_field,
            llvm_type,
            llvm_struct_pointer,
            offset);
        std::string result = context.llvm_instructions->back();
        std::string expected = "%field = getelementptr %struct.A, ptr %obj_a, i32 0, i32 0";
        TEST_ASSERT_STR_EQ(result, expected);
    }

    // test llvm global constant variable
    {
        MLLVM::LLVM_Context context;
        std::string llvm_var_name = "var_name";
        std::string llvm_type = "i32";
        std::string llvm_value = "10";
        context.gen_global_const_var(llvm_var_name, llvm_type, llvm_value);
        std::string result = context.global_def->back();
        std::string expected = "@var_name = constant i32 10";
        TEST_ASSERT_STR_EQ(result, expected);
    }

    // test declare function instruction
    {
        MLLVM::LLVM_Context context;
        std::string llvm_func_name = "func_name";
        std::string llvm_return_type = "i32";
        std::vector<std::string> llvm_args = {"i32", "i32"};
        context.gen_declare_func(llvm_func_name, llvm_return_type, llvm_args);
        std::string result = context.llvm_instructions->back();
        std::string expected = "declare i32 @func_name(i32, i32)";
        TEST_ASSERT_STR_EQ(result, expected);
    }

    // test llvm function definition start
    {
        MLLVM::LLVM_Context context;
        std::string llvm_func_name = "func_name";
        std::string llvm_return_type = "i32";
        std::vector<std::string> llvm_args = {"i32 %x", "i32 %x"};
        context.gen_define_func_start(llvm_func_name, llvm_return_type, llvm_args);
        std::string result = context.llvm_instructions->back();
        std::string expected = "define i32 @func_name(i32 %x, i32 %x) {";
        TEST_ASSERT_STR_EQ(result, expected);
    }

    // test llvm function definition end
    {
        MLLVM::LLVM_Context context;
        context.gen_define_func_end();
        std::string result = context.llvm_instructions->back();
        std::string expected = "}";
        TEST_ASSERT_STR_EQ(result, expected);
    }

    // test llvm label
    {
        MLLVM::LLVM_Context context;
        std::string label = "entry";
        context.gen_label(label);
        std::string result = context.llvm_instructions->back();
        std::string expected = "entry:";
        TEST_ASSERT_STR_EQ(result, expected);
    }

    // test llvm gen func call
    {
        MLLVM::LLVM_Context context;
        std::string llvm_return_value = "%var";
        std::string llvm_func_name = "func_name";
        std::string llvm_return_type = "i32";
        std::vector<std::pair<std::string, std::string>> llvm_args = {{"i32", "10"}, {"i32", "20"}};
        context.gen_call_inst(llvm_return_value, llvm_func_name, llvm_return_type, llvm_args);
        std::string result = context.llvm_instructions->back();
        std::string expected = "%var = call i32 @func_name(i32 10, i32 20)";
        TEST_ASSERT_STR_EQ(result, expected);
    }

    /********** test math operations **********/
    // test llvm add instruction int
    {
        MLLVM::LLVM_Context context;
        std::string llvm_dst = "%var";
        std::string llvm_op1 = "10";
        std::string llvm_op2 = "20";
        context.gen_add_inst(llvm_dst, llvm_op1, llvm_op2, MLLVM::LLVM_i32);
        std::string result = context.llvm_instructions->back();
        std::string expected = "%var = add i32 10, 20";
        TEST_ASSERT_STR_EQ(result, expected);
    }
    // test llvm add instruction double
    {
        MLLVM::LLVM_Context context;
        std::string llvm_dst = "%var";
        std::string llvm_op1 = "10";
        std::string llvm_op2 = "20";
        context.gen_add_inst(llvm_dst, llvm_op1, llvm_op2, MLLVM::LLVM_double);
        std::string result = context.llvm_instructions->back();
        std::string expected = "%var = fadd double 10, 20";
        TEST_ASSERT_STR_EQ(result, expected);
    }

    // test llvm sub instruction int
    {
        MLLVM::LLVM_Context context;
        std::string llvm_dst = "%var";
        std::string llvm_op1 = "10";
        std::string llvm_op2 = "20";
        context.gen_sub_inst(llvm_dst, llvm_op1, llvm_op2, MLLVM::LLVM_i32);
        std::string result = context.llvm_instructions->back();
        std::string expected = "%var = sub i32 10, 20";
        TEST_ASSERT_STR_EQ(result, expected);
    }

    // test llvm sub instruction double
    {
        MLLVM::LLVM_Context context;
        std::string llvm_dst = "%var";
        std::string llvm_op1 = "10";
        std::string llvm_op2 = "20";
        context.gen_sub_inst(llvm_dst, llvm_op1, llvm_op2, MLLVM::LLVM_double);
        std::string result = context.llvm_instructions->back();
        std::string expected = "%var = fsub double 10, 20";
        TEST_ASSERT_STR_EQ(result, expected);
    }

    // test llvm mul instruction int
    {
        MLLVM::LLVM_Context context;
        std::string llvm_dst = "%var";
        std::string llvm_op1 = "10";
        std::string llvm_op2 = "20";
        context.gen_mul_inst(llvm_dst, llvm_op1, llvm_op2, MLLVM::LLVM_i32);
        std::string result = context.llvm_instructions->back();
        std::string expected = "%var = mul i32 10, 20";
        TEST_ASSERT_STR_EQ(result, expected);
    }

    // test llvm mul instruction double
    {
        MLLVM::LLVM_Context context;
        std::string llvm_dst = "%var";
        std::string llvm_op1 = "10";
        std::string llvm_op2 = "20";
        context.gen_mul_inst(llvm_dst, llvm_op1, llvm_op2, MLLVM::LLVM_double);
        std::string result = context.llvm_instructions->back();
        std::string expected = "%var = fmul double 10, 20";
        TEST_ASSERT_STR_EQ(result, expected);
    }

    // test llvm div instruction int
    {
        MLLVM::LLVM_Context context;
        std::string llvm_dst = "%var";
        std::string llvm_op1 = "10";
        std::string llvm_op2 = "20";
        context.gen_div_inst(llvm_dst, llvm_op1, llvm_op2, MLLVM::LLVM_i32);
        std::string result = context.llvm_instructions->back();
        std::string expected = "%var = sdiv i32 10, 20";
        TEST_ASSERT_STR_EQ(result, expected);
    }
    // test llvm div instruction double
    {
        MLLVM::LLVM_Context context;
        std::string llvm_dst = "%var";
        std::string llvm_op1 = "10";
        std::string llvm_op2 = "20";
        context.gen_div_inst(llvm_dst, llvm_op1, llvm_op2, MLLVM::LLVM_double);
        std::string result = context.llvm_instructions->back();
        std::string expected = "%var = fdiv double 10, 20";
        TEST_ASSERT_STR_EQ(result, expected);
    }

    TEST_PASS();
}