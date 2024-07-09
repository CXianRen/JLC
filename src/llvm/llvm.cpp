#include "llvm/llvm.h"

namespace MLLVM
{

    static int prefix_size = 0;

    void set_prefix_size(int size)
    {
        prefix_size = size;
    }
    int get_prefix_size()
    {
        return prefix_size;
    }

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
        llvm_instructions.push_back(std::string(prefix_size, ' ') + "; " + comment);
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
            const std::string &llvm_field,
            const std::string &llvm_type,
            const std::string &llvm_obj_ptr,
            const int offset)
    {
        llvm_instructions.push_back(
            std::string(prefix_size, ' ') +
            llvm_field + " = getelementptr " +
            llvm_type + ", ptr " + llvm_obj_ptr +
            ", i32 0, i32 " + std::to_string(offset));
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
            std::string(prefix_size, ' ') +
            llvm_value + " = alloca " + llvm_type);
    }

    void LLVM_Context::
        gen_store_inst(
            std::string &llvm_src,
            std::string &llvm_dst,
            LLVM_Type type)
    {
        llvm_instructions.push_back(
            std::string(prefix_size, ' ') +
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
            std::string(prefix_size, ' ') +
            llvm_dst + " = load " +
            MLLVM::str(type) + ", " + "ptr" + " " + llvm_src);
    }

    /******************* call operations *******************/
    void LLVM_Context::
        gen_call_inst(
            const std::string &llvm_return_value,
            const std::string &llvm_func_name,
            const std::string &llvm_return_type,
            const std::vector<std::pair<std::string, std::string>> &llvm_args)
    {
        std::string result = std::string(prefix_size, ' ');

        if (llvm_return_value != "")
        {
            result += llvm_return_value + " = ";
        }

        result += "call " + llvm_return_type + " @" + llvm_func_name + "(";
        for (int i = 0; i < llvm_args.size(); i++)
        {
            result += llvm_args[i].first + " " + llvm_args[i].second;
            if (i != llvm_args.size() - 1)
            {
                result += ", ";
            }
        }
        result += ")";

        llvm_instructions.push_back(result);
    }

    /******************* math operations *******************/
    void LLVM_Context::
        gen_add_inst(
            const std::string &llvm_return_value,
            const std::string &llvm_value1,
            const std::string &llvm_value2,
            LLVM_Type type)
    {
        std::string add_op = "add";
        if (type == LLVM_i32)
        {
            add_op = "add";
        }
        else if (type == LLVM_double)
        {
            add_op = "fadd";
        }

        std::string result = std::string(prefix_size, ' ') +
                             llvm_return_value + " = " + add_op + " " +
                             MLLVM::str(type) + " " + llvm_value1 + ", " + llvm_value2;
        llvm_instructions.push_back(result);
    }

    void LLVM_Context::
        gen_sub_inst(
            const std::string &llvm_return_value,
            const std::string &llvm_value1,
            const std::string &llvm_value2,
            LLVM_Type type)
    {
        std::string sub_op = "sub";
        if (type == LLVM_i32)
        {
            sub_op = "sub";
        }
        else if (type == LLVM_double)
        {
            sub_op = "fsub";
        }

        std::string result = std::string(prefix_size, ' ') +
                             llvm_return_value + " = " + sub_op + " " +
                             MLLVM::str(type) + " " + llvm_value1 + ", " + llvm_value2;
        llvm_instructions.push_back(result);
    }

    void LLVM_Context::
        gen_mul_inst(
            const std::string &llvm_return_value,
            const std::string &llvm_value1,
            const std::string &llvm_value2,
            LLVM_Type type)
    {
        std::string mul_op = "mul";
        if (type == LLVM_i32)
        {
            mul_op = "mul";
        }
        else if (type == LLVM_double)
        {
            mul_op = "fmul";
        }

        std::string result = std::string(prefix_size, ' ') +
                             llvm_return_value + " = " + mul_op + " " +
                             MLLVM::str(type) + " " + llvm_value1 + ", " + llvm_value2;
        llvm_instructions.push_back(result);
    }

    void LLVM_Context::
        gen_div_inst(
            const std::string &llvm_return_value,
            const std::string &llvm_value1,
            const std::string &llvm_value2,
            LLVM_Type type)
    {
        std::string div_op = "sdiv";
        if (type == LLVM_i32)
        {
            div_op = "sdiv";
        }
        else if (type == LLVM_double)
        {
            div_op = "fdiv";
        }

        std::string result = std::string(prefix_size, ' ') +
                             llvm_return_value + " = " + div_op + " " +
                             MLLVM::str(type) + " " + llvm_value1 + ", " + llvm_value2;
        llvm_instructions.push_back(result);
    }

    void LLVM_Context::
        gen_mod_inst(
            const std::string &llvm_return_value,
            const std::string &llvm_value1,
            const std::string &llvm_value2,
            LLVM_Type type)
    {
        std::string mod_op = "srem";
        if (type == LLVM_i32)
        {
            mod_op = "srem";
        }

        std::string result = std::string(prefix_size, ' ') +
                             llvm_return_value + " = " + mod_op + " " +
                             MLLVM::str(type) + " " + llvm_value1 + ", " + llvm_value2;
        llvm_instructions.push_back(result);
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

    /******************* compare operations *******************/

    /******************* control flow operations *******************/

    void LLVM_Context::gen_return_inst(
        const std::string &llvm_return_value,
        LLVM_Type type)
    {
        if (type == LLVM_void)
        {
            llvm_instructions.push_back(
                std::string(prefix_size, ' ') +
                "ret void");
        }
        else
        {
            llvm_instructions.push_back(
                std::string(prefix_size, ' ') +
                "ret " + MLLVM::str(type) + " " + llvm_return_value);
        }
    }
} // namespace MLLVM