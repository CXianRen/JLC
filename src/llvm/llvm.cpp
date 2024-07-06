#include "llvm/llvm.h"

namespace MLLVM
{
    std::string str(const LLVM_Type type)
    {
        switch (type)
        {
        case LLVM_i1:
            return "i1";
        case LLVM_i32:
            return "i32";
        case LLVM_double:
            return "double";
        case LLVM_ptr:
            return "ptr";
        case LLVM_void:
            return "void";
        default:
            return "unknown";
        }
    }

    LLVM_Context::LLVM_Context()
    {
        name_counter = 0;
    }

    LLVM_Context::~LLVM_Context()
    {
    }

    void LLVM_Context::
        gen_comment(std::string comment)
    {
        llvm_instructions.push_back("; " + comment);
    }

    std::string LLVM_Context::
        gen_name(std::string var_name)
    {
        return "%" + var_name + std::to_string(name_counter++);
    }

    void LLVM_Context::
        gen_alloc_inst(
            std::string &llvm_value,
            LLVM_Type type)
    {
        llvm_instructions.push_back(
            llvm_value + " = alloca " + MLLVM::str(type));
    }

    void LLVM_Context::
        gen_store_inst(
            std::string &llvm_src,
            std::string &llvm_dst,
            LLVM_Type type)
    {
        llvm_instructions.push_back(
            "store " +
            MLLVM::str(type) + " " + llvm_src +
            ", " + "ptr" + " " + llvm_dst);
    }

    void LLVM_Context::
        gen_load_inst(
            std::string &llvm_src,
            std::string &llvm_dst,
            LLVM_Type type)
    {
        llvm_instructions.push_back(
            llvm_dst + " = load " +
            MLLVM::str(type) + ", " + "ptr" + " " + llvm_src);
    }

    std::string LLVM_Context::str()
    {
        std::string result;
        for (auto &inst : llvm_instructions)
        {
            result += inst + "\n";
        }
        return result;
    }
} // namespace MLLVM