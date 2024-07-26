#ifndef __LLVM_H__
#define __LLVM_H__

#include <vector>
#include <string>
#include <map>
#include <memory>
#include "common/debug.h"

#include "llvm/llvm_type.h"

#include "llvm/llvm_inst.h"

#include "llvm/llvm_insert_point.h"

namespace MLLVM
{

    typedef LLVM_Insertion_Point<LLVM_Inst> LLVM_IP;

    void set_prefix_size(int size);
    int get_prefix_size();

    class LLVM_Context
    {

    public:
        LLVM_Context();
        ~LLVM_Context();

    public:
        std::shared_ptr<LLVM_IP> llvm_instructions;
        std::shared_ptr<LLVM_IP> global_def;
        std::shared_ptr<LLVM_IP> res;

        int name_counter;

    public:
        void reset_name_counter()
        {
            name_counter = 0;
        }

        std::shared_ptr<LLVM_IP> new_insert_point(std::string label)
        {
            std::string label_with_id = label + "_" + std::to_string(name_counter++);
            return std::make_shared<LLVM_IP>(llvm_instructions, label_with_id);
        }

        std::shared_ptr<LLVM_IP> get_current_insert_point()
        {
            return llvm_instructions;
        }

        void set_insert_point(std::shared_ptr<LLVM_IP> insert_point)
        {
            // check ip only contains comments and labels
            bool is_empty = true;
            for (auto it = llvm_instructions->begin(); it != llvm_instructions->end(); ++it)
            {
                if (it->get_type() != LLVM_COMMENT && it->get_type() != LLVM_LABEL)
                {
                    is_empty = false;
                    break;
                }
            }
            if (is_empty)
            {
                // br from current insert point to the new insert point
                gen_br_inst(insert_point->label);
            }

            release_insert_point(llvm_instructions);
            llvm_instructions = insert_point;
            gen_label(insert_point->label);
        }

        void release_insert_point(std::shared_ptr<LLVM_IP> insert_point)
        {
            for (auto it = insert_point->begin(); it != insert_point->end(); ++it)
            {
                res->push_back(*it);
            }
        }

        bool end_with_term_inst(std::shared_ptr<LLVM_IP> insert_point)
        {
            if (insert_point->size() == 0)
            {
                return false;
            }

            auto it = insert_point->end();
            // find the last non-comment instruction
            while (it != insert_point->begin())
            {
                it--;
                if (it->get_type() != LLVM_COMMENT)
                {
                    if (it->get_type() == LLVM_RET || it->get_type() == LLVM_BR)
                    {
                        return true;
                    }
                }
            }
            return false;
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

        void gen_offset_field_in_type(
            const std::string &llvm_field,
            const std::string &llvm_type,
            const std::string &llvm_obj_ptr,
            const std::string offset);

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
            llvm_instructions->push_back(LLVM_Inst(LLVM_LABEL, label + ":"));
        }

        /*
         * Generate a define function end instruction
         * like:
         * }
         */
        void gen_define_func_end()
        {
            llvm_instructions->push_back(
                LLVM_Inst(LLVM_FUNC_END, "}"));
        }

        /******** other op ********/

        void gen_custom_inst(const std::string &inst);

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
            const std::string &llvm_src,
            const std::string &llvm_dst,
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

        void gen_call_fptr_inst(
            const std::string &llvm_return_value,
            const std::string &llvm_func_ptr,
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
        // ! == != > < <= >=
        void gen_not_inst(
            const std::string &llvm_return_value,
            const std::string &llvm_value,
            LLVM_Type type);

        void gen_equ_inst(
            const std::string &llvm_return_value,
            const std::string &llvm_value1,
            const std::string &llvm_value2,
            LLVM_Type type);

        void gen_ne_inst(
            const std::string &llvm_return_value,
            const std::string &llvm_value1,
            const std::string &llvm_value2,
            LLVM_Type type);

        void gen_lth_inst(
            const std::string &llvm_return_value,
            const std::string &llvm_value1,
            const std::string &llvm_value2,
            LLVM_Type type);

        void gen_le_inst(
            const std::string &llvm_return_value,
            const std::string &llvm_value1,
            const std::string &llvm_value2,
            LLVM_Type type);

        void gen_gth_inst(
            const std::string &llvm_return_value,
            const std::string &llvm_value1,
            const std::string &llvm_value2,
            LLVM_Type type);

        void gen_ge_inst(
            const std::string &llvm_return_value,
            const std::string &llvm_value1,
            const std::string &llvm_value2,
            LLVM_Type type);

        /********* control flow operations *********/
        void gen_br_inst(
            const std::string &llvm_label);

        void gen_cond_br_inst(
            const std::string &llvm_cond,
            const std::string &llvm_true_label,
            const std::string &llvm_false_label);

        /***
         * Generate a phi instruction
         * like:
         * %var = phi i32 [ %var1, %label1 ], [ %var2, %label2 ]
         */
        void gen_phi_inst(
            const std::string &llvm_return_value,
            const std::string &type,
            const std::string &llvm_var1,
            const std::string &llvm_label1,
            const std::string &llvm_var2,
            const std::string &llvm_label2);

        /**
         * Generate a return instruction
         * like:
         * ret i32 10
         */
        void gen_return_inst(
            const std::string &llvm_return_value,
            LLVM_Type type);

    public:
        std::string str();

    }; // class LLVM_Context

}

#endif // __LLVM_H__