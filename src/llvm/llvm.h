#ifndef __LLVM_H__
#define __LLVM_H__

#include <vector>
#include <string>

namespace MLLVM
{
    enum LLVM_Type
    {
        LLVM_i1,
        LLVM_i32,
        LLVM_double,
        LLVM_ptr,
        LLVM_void
    };
    std::string str(const LLVM_Type type);

    class LLVM_Context
    {

    public:
        LLVM_Context();
        ~LLVM_Context();

    public:
        std::vector<std::string> llvm_instructions;

        int name_counter;

    public:
        void reset_name_counter() { name_counter = 0; }

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
         * %field = getelementptr %type, ptr* %struct_pointer, i32 0, i32 0
         */
        void gen_offset_field_in_type(
            const std::string &llvm_type,
            const std::string &llvm_field,
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

        /******** math operations ********/

    public:
        std::string str();

    }; // class LLVM_Context

}

#endif // __LLVM_H__