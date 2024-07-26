#include "llvm_type.h"

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

} // namespace MLLVM