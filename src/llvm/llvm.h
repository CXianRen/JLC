#ifndef __LLVM_H__
#define __LLVM_H__

#include <vector>
#include <string>
#include <map>
namespace MLLVM
{

    void set_prefix_size(int size);
    int get_prefix_size();

    enum LLVM_Type
    {
        LLVM_i1,
        LLVM_i32,
        LLVM_double,
        LLVM_ptr,
        LLVM_void
    };
    std::string str(const LLVM_Type type);

    const std::map<LLVM_Type, std::string> LLVM_Type_Size_map = {
        {LLVM_i1, "1"},
        {LLVM_i32, "4"},
        {LLVM_double, "8"},
        {LLVM_ptr, "8"},
        {LLVM_void, "0"}};

    class LLVM_Context
    {

    public:
        LLVM_Context();
        ~LLVM_Context();

    public:
        std::vector<std::string> llvm_instructions;

        int name_counter;

    public:
        void reset_name_counter()
        {
            name_counter = 0;
        }

    public:
        void gen_comment(std::string comment);

        std::string gen_name(std::string var_name);

        /******** define type ********/

        /*
         * Generate a type definition
         * like:
         * %struct.type = type { i32, i32 }
         */

        void gen_define_type(
            const std::string &llvm_type,
            const std::vector<std::string> &llvm_elements);

        /**
         * Generate a getelementptr instruction
         * like:
         * %field = getelementptr %type, ptr %obj_ptr, i32 0, i32 0
         */
        void gen_offset_field_in_type(
            const std::string &llvm_field,
            const std::string &llvm_type,
            const std::string &llvm_obj_ptr,
            const int offset);

        /***
         * Generate a global constant variable
         * like:
         * @var_name = constant i32 10
         */
        void gen_global_const_var(
            const std::string &llvm_var_name,
            const std::string &llvm_type,
            const std::string &llvm_value);

        /**
         * Generate a declare function instruction
         * like:
         * declare i32 @func_name(i32, i32)
         */
        void gen_declare_func(
            const std::string &llvm_func_name,
            const std::string &llvm_return_type,
            const std::vector<std::string> &llvm_args);

        /*
         *  Generate a define function instruction
         *  like:
         *  define i32 @func_name(i32 %arg1, i32 %arg2) {
         */
        void gen_define_func_start(
            const std::string &llvm_func_name,
            const std::string &llvm_return_type,
            const std::vector<std::string> &llvm_args);

        void gen_label(const std::string &label)
        {
            llvm_instructions.push_back(label + ":");
        }

        /*
         * Generate a define function end instruction
         * like:
         * }
         */
        void gen_define_func_end()
        {
            llvm_instructions.push_back("}");
        }
        /******** memory operations ********/

        /*
         * Generate an alloca instruction
         * like:
         * %var_name = alloca i32
         */
        void gen_alloc_inst(
            const std::string &llvm_value,
            const LLVM_Type type);

        void gen_alloc_inst(
            const std::string &llvm_value,
            const std::string &llvm_type);

        /*
         * Generate a store instruction
         * like:
         * store i32 10, i32* %var_name
         * store type src, ptr dst
         */
        void gen_store_inst(
            std::string &llvm_src,
            std::string &llvm_dst,
            LLVM_Type type);

        /**
         * Generate a load instruction
         * like:
         * %var = load i32, ptr %var_pointer
         * dst = load type, ptr src
         */
        void gen_load_inst(
            std::string &llvm_src,
            std::string &llvm_dst,
            LLVM_Type type);

        /********* call operations *********/

        /**
         * Generate a call instruction
         * like:
         * %var = call i32 @func_name(i32 10, i32 20)
         */

        void gen_call_inst(
            const std::string &llvm_return_value,
            const std::string &llvm_func_name,
            const std::string &llvm_return_type,
            const std::vector<std::pair<std::string, std::string>> &llvm_args);

        /******** math operations ********/

        /**
         * Generate an add instruction
         * like:
         * %var = add i32 10, i32 20
         */

        void gen_add_inst(
            const std::string &llvm_return_value,
            const std::string &llvm_value1,
            const std::string &llvm_value2,
            LLVM_Type type);

        void gen_sub_inst(
            const std::string &llvm_return_value,
            const std::string &llvm_value1,
            const std::string &llvm_value2,
            LLVM_Type type);

        void gen_mul_inst(
            const std::string &llvm_return_value,
            const std::string &llvm_value1,
            const std::string &llvm_value2,
            LLVM_Type type);

        void gen_div_inst(
            const std::string &llvm_return_value,
            const std::string &llvm_value1,
            const std::string &llvm_value2,
            LLVM_Type type);

        void gen_mod_inst(
            const std::string &llvm_return_value,
            const std::string &llvm_value1,
            const std::string &llvm_value2,
            LLVM_Type type);

        /********* compare operations *********/

    public:
        std::string str();

    }; // class LLVM_Context

}

#endif // __LLVM_H__