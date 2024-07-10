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

        void push_llvm_value_stack()
        {
            g_llvm_value_stack_.push_back(
                std::map<std::string, std::string>());
        }

        void pop_llvm_value_stack()
        {
            g_llvm_value_stack_.pop_back();
        }

        void add_var_llvm_value(const std::string &var_name,
                                const std::string &llvm_value)
        {
            g_llvm_value_stack_.back()[var_name] = llvm_value;
        }

        std::string get_var_llvm_value(const std::string &var_name)
        {
            for (auto it = g_llvm_value_stack_.rbegin();
                 it != g_llvm_value_stack_.rend();
                 ++it)
            {
                if (it->find(var_name) != it->end())
                {
                    return it->at(var_name);
                }
            }
            return "";
        }

    public:
        std::string g_llvm_value_;
        std::vector<
            std::map<std::string, std::string>>
            g_llvm_value_stack_;

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
                auto str_name = "str_" + std::to_string(const_string_llvm_value_map_.size());
                // new a constant string
                llvm_context_.gen_global_const_var(
                    str_name,
                    std::string("[") +
                        std::to_string(const_string.size() + 1) +
                        std::string(" x i8]"),
                    "c\"" + const_string + "\\00\"");
                const_string_llvm_value_map_[const_string] = "@" + str_name;
            }
            g_llvm_value_ = const_string_llvm_value_map_[const_string];
        }

        /**** function ****/
        void visitFuncDef(FuncDef *p) override;
        void visitBStmt(BStmt *p);

        void visitEApp(EApp *p) override;
        // void visitEFunc(EFunc *p) override;

        /*** variable declaration ***/
        void visitNoInit(NoInit *p) override;
        void visitInit(Init *p) override;
        void visitENewObj(ENewObj *p) override;
        void visitENewBArr(ENewBArr *p) override;
        void visitENewOArr(ENewOArr *p) override;

        /*** variable access ***/
        bool left_value_;
        void visitAss(Ass *p) override;
        void visitEVar(EVar *p) override;

        void visitEpropety(Epropety *p) override;
        void visitEArrow(EArrow *p) override;
        void visitEAcc(EAcc *p) override;

        /* math operation */
        void visitEInc(EInc *p) override;   // ++
        void visitEDecr(EDecr *p) override; // --
        void visitENeg(ENeg *p) override;   // -
        void visitEMul(EMul *p) override;   // x / mod
        void visitEAdd(EAdd *p) override;   // + -
        // void visitERel(ERel *p) override;   // > < <= == >= !=
        // void visitEAnd(EAnd *p) override;   // &&
        // void visitEOr(EOr *p) override;     // ||
        // void visitENot(ENot *p) override;   // !

        /* logic operation */

        /* return and flow control */
        void visitRet(Ret *p) override;
        void visitVRet(VRet *p) override;

        /*** print original code ***/
        void visitDecl(Decl *p) override;

        void visitSExp(SExp *p) override;

    }; // class LLVMGenerator

} // namespace JLC::LLVM

#endif // __JLC_LLVM_GENERATOR_H__