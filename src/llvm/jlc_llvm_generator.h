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
            for (auto &pair : context_->enums)
            {
                gen_enum_type(pair.second);
            }
            for (auto &pair : context_->structs)
            {
                gen_struct_type(pair.second);
            }
            for (auto &pair : context_->classes)
            {
                gen_class_type(pair.second);
            }
        }

        ~LLVMGenerator()
        {
        }

    public:
        std::string llvm_value_;

        MLLVM::LLVM_Context llvm_context_;

    private:
        /**** class internal ****/

        MLLVM::LLVM_Type jlc_type2llvm_type(const JLCType &type);

        void gen_enum_type(std::shared_ptr<JLCEnum> e);

        void gen_struct_type(std::shared_ptr<JLCStruct> s);

        void gen_class_type(std::shared_ptr<JLCClass> c);

    public:
        /**** override skeleton ****/

    }; // class LLVMGenerator

} // namespace JLC::LLVM

#endif // __JLC_LLVM_GENERATOR_H__