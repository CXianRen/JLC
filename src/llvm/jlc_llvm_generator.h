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

    public:
        /**** override skeleton ****/
        void visitProgram(Program *p) override
        {
            add_internal_func();
            add_udt();
            TypeVisitor::visitProgram(p);
        }

        void visitFuncDef(FuncDef *p) override;




    }; // class LLVMGenerator

} // namespace JLC::LLVM

#endif // __JLC_LLVM_GENERATOR_H__