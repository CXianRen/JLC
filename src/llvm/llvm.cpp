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

    /******************* basic functions *******************/
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

    /******************* define type *******************/

    void LLVM_Context::
        gen_define_type(
            const std::string &llvm_type,
            const std::vector<std::string> &llvm_elements)
    {
        std::string result = llvm_type + " = type {";
        for (int i = 0; i < llvm_elements.size(); i++)
        {
            result += " " + llvm_elements[i];
            if (i != llvm_elements.size() - 1)
            {
                result += ",";
            }
        }
        result += " }";
        llvm_instructions.push_back(result);
    }

    void LLVM_Context::
        gen_offset_field_in_type(
            const std::string &llvm_type,
            const std::string &llvm_field,
            const int offset)
    {
        llvm_instructions.push_back(
            llvm_field + " = getelementptr " +
            llvm_type + ", ptr %struct_pointer, i32 0, i32 " + std::to_string(offset));
    }

    void LLVM_Context::
        gen_global_const_var(
            const std::string &llvm_var_name,
            const std::string &llvm_type,
            const std::string &llvm_value)
    {
        llvm_instructions.push_back(
            "@" + llvm_var_name + " = constant " + llvm_type + " " + llvm_value);
    }

    void LLVM_Context::
        gen_declare_func(
            const std::string &llvm_func_name,
            const std::string &llvm_return_type,
            const std::vector<std::string> &llvm_args)
    {
        std::string result = "declare " + llvm_return_type + " @" + llvm_func_name + "(";
        for (int i = 0; i < llvm_args.size(); i++)
        {
            result += llvm_args[i];
            if (i != llvm_args.size() - 1)
            {
                result += ", ";
            }
        }
        result += ")";
        llvm_instructions.push_back(result);
    }

    void LLVM_Context::
        gen_define_func_start(
            const std::string &llvm_func_name,
            const std::string &llvm_return_type,
            const std::vector<std::string> &llvm_args)
    {
        std::string result = "define " + llvm_return_type + " @" + llvm_func_name + "(";
        for (int i = 0; i < llvm_args.size(); i++)
        {
            result += llvm_args[i];
            if (i != llvm_args.size() - 1)
            {
                result += ", ";
            }
        }
        result += ") {";
        llvm_instructions.push_back(result);
    }

    /******************* memory operations *******************/
    void LLVM_Context::
        gen_alloc_inst(
            const std::string &llvm_value,
            const LLVM_Type type)
    {
        gen_alloc_inst(llvm_value, MLLVM::str(type));
    }

    void LLVM_Context::
        gen_alloc_inst(
            const std::string &llvm_value,
            const std::string &llvm_type)
    {
        llvm_instructions.push_back(
            llvm_value + " = alloca " + llvm_type);
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
            // check if the instruction is a label
            if (inst.back() == ':')
            {
                result += inst + "\n";
                continue;
            }
            else
            {
                result += "\t" + inst + "\n";
            }
        }
        return result;
    }
} // namespace MLLVM