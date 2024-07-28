#ifndef __MLLVM_LLVM_INST_H__
#define __MLLVM_LLVM_INST_H__

#include <string>

namespace MLLVM
{
    enum LLVM_INST_TYPE
    {
        // Empty line
        LLVM_EMPTY,
        // Global define
        LLVM_GLOBAL,
        // Function define
        LLVM_FUNC_START,
        // Function end
        LLVM_FUNC_END,
        // Comment
        LLVM_COMMENT,
        // Label
        LLVM_LABEL,
        // Return
        LLVM_RET,
        // Branch
        LLVM_BR,
        // Phi
        LLVM_PHI,
        // Allocate
        LLVM_ALLOCA,
        // Store
        LLVM_STORE,
        // Load
        LLVM_LOAD,
        // Call
        LLVM_CALL,
        // Add
        LLVM_ADD,
        // Sub
        LLVM_SUB,
        // Mul
        LLVM_MUL,
        // Div
        LLVM_DIV,
        // Mod
        LLVM_MOD,
        // Relop
        LLVM_RELOP,
        // UNDEFINED
        UNDEFINED
    };

    class LLVM_Inst
    {
    public:
        LLVM_Inst() : type(UNDEFINED), inst("") {}
        LLVM_Inst(
            LLVM_INST_TYPE type,
            std::string inst,
            int prefix_size = 0)
            : type(type),
              inst(inst),
              prefix_size(prefix_size)
        {
        }
        ~LLVM_Inst() = default;

        LLVM_INST_TYPE get_type() const { return type; }
        std::string get_inst() const { return inst; }
        int get_prefix_size() const { return prefix_size; }

        // copy constructor
        LLVM_Inst(const LLVM_Inst &inst)
            : type(inst.type),
              inst(inst.inst),
              prefix_size(inst.prefix_size) {}

    private:
        LLVM_INST_TYPE type;
        std::string inst;
        int prefix_size;

    }; // class LLVM_Inst

} // namespace MLLVM

#endif // __MLLVM_LLVM_INST_H__