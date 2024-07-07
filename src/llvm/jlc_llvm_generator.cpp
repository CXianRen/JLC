#include "llvm/jlc_llvm_generator.h"
#include "common/jlc_error.h"

namespace JLC::LLVM
{

    MLLVM::LLVM_Type LLVMGenerator::
        jlc_type2llvm_type(const JLCType &type)
    {
        switch (type.type)
        {
        case type_enum::INT:
            return MLLVM::LLVM_i32;
        case type_enum::DOUB:
            return MLLVM::LLVM_double;
        case type_enum::BOOL:
            return MLLVM::LLVM_i1;
        case type_enum::VOID:
            return MLLVM::LLVM_void;
        case type_enum::STRING:
            return MLLVM::LLVM_ptr;
        case type_enum::ENUM:
            return MLLVM::LLVM_i32;
        case type_enum::STRUCT:
            return MLLVM::LLVM_ptr;
        case type_enum::CLASS:
            return MLLVM::LLVM_ptr;
        default:
        {
            throw JLCError(
                "jlc_type2llvm_type: unknown type: " +
                type.str());
        }
        }
    }

    void LLVMGenerator::
        add_internal_func()
    {
        // add printInt declaration
        llvm_context_.gen_declare_func(
            "printInt",
            "void",
            {"i32"});
        // add printDouble declaration
        llvm_context_.gen_declare_func(
            "printDouble",
            "void",
            {"double"});

        // add printString declaration
        llvm_context_.gen_declare_func(
            "printString",
            "void",
            {"ptr"});
        
        // add readInt declaration
        llvm_context_.gen_declare_func(
            "readInt",
            "i32",
            {});

        // add readDouble declaration
        llvm_context_.gen_declare_func(
            "readDouble",
            "double",
            {});
    }

    void LLVMGenerator::gen_enum_type(std::shared_ptr<JLCEnum> e)
    {
        for (auto &pair : e->members)
        {
            llvm_context_.gen_global_const_var(
                e->obj_name + "_" + pair.first,
                "i32",
                std::to_string(pair.second));
        }
    }

    void LLVMGenerator::gen_struct_type(std::shared_ptr<JLCStruct> s)
    {
        std::vector<std::string> elements;
        for (auto &pair : s->members)
        {
            elements.push_back(
                str(jlc_type2llvm_type(*pair.second)));
        }
        llvm_context_.gen_define_type(std::string("\%struct.") + s->obj_name, elements);
    }

    void LLVMGenerator::gen_class_type(std::shared_ptr<JLCClass> c)
    {
        std::vector<std::string> elements;
        for (auto &pair : c->members)
        {
            elements.push_back(
                str(jlc_type2llvm_type(*pair.second)));
        }
        llvm_context_.gen_define_type(std::string("\%class.") + c->obj_name, elements);
    }

} // namespace JLC::LLVM