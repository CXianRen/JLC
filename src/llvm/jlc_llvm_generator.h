#ifndef __JLC_LLVM_GENERATOR_H__
#define __JLC_LLVM_GENERATOR_H__

#include <vector>
#include <string>
#include <memory>

#include "llvm/llvm.h"

#include "common/jlc_context.h"
#include "common/debug.h"

#include "typechecker/jlc_tc_func_def.h"

namespace JLC::LLVM
{

    using namespace JLC::CONTEXT;
    using namespace JLC::ENUM;
    using namespace JLC::STRUCT;
    using namespace JLC::CLASS;
    using namespace JLC::FUNC;
    using namespace JLC::BLK;
    using namespace JLC::VAR;
    using namespace JLC::TYPE;
    using namespace JLC::TC;

    class LLVMGenerator : public JLC_FUNC_DEF_Checker
    {
    public:
        LLVMGenerator(
            std::shared_ptr<JLCContext>
                context)
        {
            context_ = context;
        }

        ~LLVMGenerator()
        {
        }

    public:
        std::string llvm_value_;

        MLLVM::LLVM_Context llvm_context_;

        void add_internal_func();

        void add_udt();

    private:
        /**** class internal ****/

        MLLVM::LLVM_Type jlc_type2llvm_type(const JLCType &type);

        void gen_enum_type(std::shared_ptr<JLCEnum> e);

        void gen_struct_type(std::shared_ptr<JLCStruct> s);

        void gen_class_type(std::shared_ptr<JLCClass> c);

        int get_obj_size(const std::string &obj_name);

    public:
        std::string g_llvm_value_;

        /**** override skeleton ****/
        void visitProgram(Program *p) override
        {
            add_internal_func();
            add_udt();
            TypeVisitor::visitProgram(p);
        }

        /****  immediate value ****/
        void visitELitNull(ELitNull *p) override
        {
            g_llvm_value_ = "null";
            TypeVisitor::visitELitNull(p);
        }

        void visitELitInt(ELitInt *e_lit_int) override
        {
            g_llvm_value_ = std::to_string(e_lit_int->integer_);
            TypeVisitor::visitELitInt(e_lit_int);
        }

        void visitELitDoub(ELitDoub *e_lit_doub) override
        {
            g_llvm_value_ = std::to_string(e_lit_doub->double_);
            TypeVisitor::visitELitDoub(e_lit_doub);
        }

        void visitELitTrue(ELitTrue *e_lit_true) override
        {
            g_llvm_value_ = "1";
            TypeVisitor::visitELitTrue(e_lit_true);
        }

        void visitELitFalse(ELitFalse *e_lit_false) override
        {
            g_llvm_value_ = "0";
            TypeVisitor::visitELitFalse(e_lit_false);
        }

        std::map<std::string, std::string> const_string_llvm_value_map_;
        void visitEString(EString *e_string) override
        {
            TypeVisitor::visitEString(e_string);
            // new a constant string
            // check if the string is already in the map
            auto const_string = e_string->string_;
            if (const_string_llvm_value_map_.find(const_string) ==
                const_string_llvm_value_map_.end())
            {
                // new a constant string
                llvm_context_.gen_global_const_var(
                    "str_" + std::to_string(const_string_llvm_value_map_.size()),
                    std::string("[") +
                        std::to_string(const_string.size() + 1) +
                        std::string(" x i8]"),
                    "c\"" + const_string + "\\00\"");
            }
            g_llvm_value_ = const_string_llvm_value_map_[const_string];
        }

        /**** function definition ****/
        void visitFuncDef(FuncDef *p) override;

        /*** variable declaration ***/
        void visitNoInit(NoInit *p) override;
        void visitInit(Init *p) override;
        void visitENewObj(ENewObj *p) override;
        void visitENewBArr(ENewBArr *p) override;
        // void visitENewOArr(ENewOArr *p) override;

    }; // class LLVMGenerator

} // namespace JLC::LLVM

#endif // __JLC_LLVM_GENERATOR_H__