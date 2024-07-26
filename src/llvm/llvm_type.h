#ifndef __MLLVM_TYPE_H__
#define __MLLVM_TYPE_H__
#include <vector>
#include <string>
#include <map>
#include <memory>

namespace MLLVM
{

    enum LLVM_Type
    {
        LLVM_i1,
        LLVM_i32,
        LLVM_double,
        LLVM_ptr,
        LLVM_void
    };

    const std::map<LLVM_Type, std::string>
        LLVM_Type_Size_map = {
            {LLVM_i1, "1"},
            {LLVM_i32, "4"},
            {LLVM_double, "8"},
            {LLVM_ptr, "8"},
            {LLVM_void, "0"}};

    std::string str(const LLVM_Type type);
}

#endif // __MLLVM_TYPE_H__
