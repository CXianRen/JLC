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

        /******** memory operations ********/
        
        /*
         * Generate an alloca instruction
         * like:
         * %var_name = alloca i32
         */
        void gen_alloc_inst(
            std::string &llvm_value,
            LLVM_Type type);

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