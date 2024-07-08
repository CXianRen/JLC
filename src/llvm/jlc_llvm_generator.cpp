#include "llvm/jlc_llvm_generator.h"
#include "common/jlc_error.h"

#include "Printer.H"

static PrintAbsyn *p = new PrintAbsyn();

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
        case type_enum::ARRAY:
            return MLLVM::LLVM_ptr;
        default:
        {
            throw JLCError(
                "jlc_type2llvm_type: unknown type: " +
                type.str());
        }
        }
    }

    int LLVMGenerator::
        get_obj_size(const std::string &obj_name)
    {
        // if the obj is a struct or class
        auto obj = context_->get_struct(obj_name);
        if (obj == nullptr)
        {
            obj = context_->get_class(obj_name);
        }
        if (obj == nullptr)
        {
            throw JLCError(
                "get_obj_size: unknown obj: " +
                obj_name);
        }

        int size = 0;
        for (auto &pair : obj->members)
        {
            auto llvm_type = jlc_type2llvm_type(*pair.second);
            if (MLLVM::LLVM_Type_Size_map.find(llvm_type) ==
                MLLVM::LLVM_Type_Size_map.end())
            {
                throw JLCError(
                    "get_obj_size: unknown type: " +
                    pair.second->str());
            }
            size += std::stoi(MLLVM::LLVM_Type_Size_map.at(llvm_type));
        }
        return size;
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

        // malloc
        llvm_context_.gen_declare_func(
            "malloc",
            "ptr",
            {"i32"});

        llvm_context_.gen_declare_func(
            "gen_nda",
            "ptr",
            {"ptr", "i32", "i32"});
    }

    void LLVMGenerator::
        add_udt()
    {
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

    void LLVMGenerator::
        gen_enum_type(std::shared_ptr<JLCEnum> e)
    {
        for (auto &pair : e->members)
        {
            llvm_context_.gen_global_const_var(
                e->obj_name + "_" + pair.first,
                "i32",
                std::to_string(pair.second));
        }
    }

    void LLVMGenerator::
        gen_struct_type(std::shared_ptr<JLCStruct> s)
    {
        std::vector<std::string> elements;
        for (auto &pair : s->members)
        {
            elements.push_back(
                str(jlc_type2llvm_type(*pair.second)));
        }
        llvm_context_.gen_define_type(std::string("\%struct.") + s->obj_name, elements);
    }

    void LLVMGenerator::
        gen_class_type(std::shared_ptr<JLCClass> c)
    {
        std::vector<std::string> elements;
        for (auto &pair : c->members)
        {
            elements.push_back(
                str(jlc_type2llvm_type(*pair.second)));
        }
        llvm_context_.gen_define_type(std::string("\%class.") + c->obj_name, elements);
    }

    /****** override ******/
    /*** FUNC_DEF ***/
    void LLVMGenerator::
        visitFuncDef(FuncDef *func_def)
    {
        std::string func_name = func_def->ident_;
        auto func_name_with_scope =
            context_->get_scope_name(func_name,
                                     func_scope_);

        current_func_ =
            context_->get_func(func_name_with_scope);

        // function declaration start
        llvm_context_.reset_name_counter();
        llvm_context_.gen_define_func_start(
            func_name,
            str(jlc_type2llvm_type(*current_func_->return_type)),
            {});

        // entry label
        llvm_context_.gen_label("entry");

        // function body scope start
        current_func_->push_blk();

        JLC::TC::TypeVisitor::visitFuncDef(func_def);

        // function body scope end
        current_func_->pop_blk();

        // function declaration end
        llvm_context_.gen_define_func_end();
    }

    /*** Definiton ***/
    void LLVMGenerator::
        visitNoInit(NoInit *no_init)
    {
        legal_expr_ = true;

        auto var_type =
            std::make_shared<JLC::TYPE::JLCType>(g_type_);

        auto var_name = no_init->ident_;

        // add the variable to the current scope
        current_func_->add_var(
            JLC::VAR::JLCVar(
                var_name,
                var_type));

        // get llvm_name
        auto llvm_name = llvm_context_.gen_name(var_name);

        // gen alloca instruction
        // baisc type
        if (var_type->type == JLC::TYPE::type_enum::INT ||
            var_type->type == JLC::TYPE::type_enum::DOUB ||
            var_type->type == JLC::TYPE::type_enum::BOOL ||
            var_type->type == JLC::TYPE::type_enum::STRING)
        {
            llvm_context_.gen_alloc_inst(
                llvm_name,
                jlc_type2llvm_type(*var_type));
            return;
        }
        // if struct class array, the obj is a pointer
        if (var_type->type == JLC::TYPE::type_enum::STRUCT ||
            var_type->type == JLC::TYPE::type_enum::CLASS ||
            var_type->type == JLC::TYPE::type_enum::ARRAY)
        {
            llvm_context_.gen_alloc_inst(
                llvm_name,
                jlc_type2llvm_type(*var_type));
            return;
        }
    }

    void LLVMGenerator::
        visitInit(Init *init)
    {
        auto decl_type = g_type_;

        auto var_type =
            std::make_shared<JLC::TYPE::JLCType>(g_type_);

        auto var_name = init->ident_;

        // gen alloc inst
        auto llvm_name = llvm_context_.gen_name(var_name);
        llvm_context_.gen_alloc_inst(
            llvm_name,
            jlc_type2llvm_type(*var_type));

        if (init->expr_)
            init->expr_->accept(this);
        auto llvm_value = g_llvm_value_;

        // gen store inst
        llvm_context_.gen_store_inst(
            llvm_value,
            llvm_name,
            jlc_type2llvm_type(*var_type));

        current_func_->add_var(
            JLC::VAR::JLCVar(var_name, var_type));

        g_type_ = decl_type;
    }

    void LLVMGenerator::
        visitENewObj(ENewObj *e_new_obj)
    {
        if (e_new_obj->otype_)
            e_new_obj->otype_->accept(this);
        auto type = g_type_;

        std::string obj_name = type.obj_name;
        std::string llvm_value_type;
        int obj_size = get_obj_size(obj_name);

        // malloc
        auto llvm_return_value = llvm_context_.gen_name("tmp");
        llvm_context_.gen_call_inst(
            llvm_return_value,
            "malloc",
            "ptr",
            {{"i32", std::to_string(obj_size)}});

        // store the return value to the llvm_value
        g_llvm_value_ = llvm_return_value;
    }

    void LLVMGenerator::
        visitENewBArr(ENewBArr *e_new_b_arr)
    {
        if (e_new_b_arr->btype_)
            e_new_b_arr->btype_->accept(this);

        auto type = g_type_;

        std::vector<std::string> llvm_dim_values;

        auto list_dim_expr = e_new_b_arr->listdimexpr_;
        for (ListDimExpr::iterator i = list_dim_expr->begin();
             i != list_dim_expr->end();
             ++i)
        {
            (*i)->accept(this);
            llvm_dim_values.push_back(g_llvm_value_);
        }

        int dim = list_dim_expr->size();

        auto e_type = jlc_type2llvm_type(type);

        std::string e_type_size =
            MLLVM::LLVM_Type_Size_map.at(e_type);

        llvm_context_.gen_comment("multi-dimensional array");

        // gen dims array
        auto llvm_dims_array_type = "[" + std::to_string(dim) + " x " + "i32" + "]";
        auto llvm_dims_array_name = llvm_context_.gen_name("pdims");
        llvm_context_.gen_alloc_inst(
            llvm_dims_array_name,
            llvm_dims_array_type);

        for (int i = 0; i < dim; i++)
        {
            auto llvm_name = llvm_context_.gen_name("e_i" + std::to_string(i) + "_");
            llvm_context_.gen_offset_field_in_type(
                llvm_name,
                llvm_dims_array_type,
                llvm_dims_array_name,
                i);

            // store the dim value
            llvm_context_.gen_store_inst(
                llvm_dim_values[i],
                llvm_name,
                MLLVM::LLVM_i32);
        }

        // call gen_nda
        auto llvm_return_value = llvm_context_.gen_name("tmp");
        llvm_context_.gen_call_inst(
            llvm_return_value,
            "gen_nda",
            "ptr",
            {{"ptr", llvm_dims_array_name},
             {"i32", std::to_string(dim)},
             {"i32", e_type_size}});

        g_llvm_value_ = llvm_return_value;
    }

    void LLVMGenerator::
        visitENewOArr(ENewOArr *e_new_o_arr)
    {
        if (e_new_o_arr->otype_)
            e_new_o_arr->otype_->accept(this);
        auto type = g_type_;

        std::vector<std::string> llvm_dim_values;
        auto list_dim_expr = e_new_o_arr->listdimexpr_;
        for (ListDimExpr::iterator i = list_dim_expr->begin();
             i != list_dim_expr->end(); ++i)
        {
            (*i)->accept(this);
            llvm_dim_values.push_back(g_llvm_value_);
        }

        int dim = list_dim_expr->size();
        auto e_type = jlc_type2llvm_type(type);

        std::string e_type_size = std::to_string(get_obj_size(type.obj_name));

        llvm_context_.gen_comment("multi-dimensional array");
        llvm_context_.gen_comment("object " + type.obj_name + " size: " + e_type_size);

        // gen dims array
        auto llvm_dims_array_type = "[" + std::to_string(dim) + " x " + "i32" + "]";
        auto llvm_dims_array_name = llvm_context_.gen_name("pdims");
        llvm_context_.gen_alloc_inst(
            llvm_dims_array_name,
            llvm_dims_array_type);

        for (int i = 0; i < dim; i++)
        {
            auto llvm_name = llvm_context_.gen_name("e_i" + std::to_string(i) + "_");
            llvm_context_.gen_offset_field_in_type(
                llvm_name,
                llvm_dims_array_type,
                llvm_dims_array_name,
                i);

            // store the dim value
            llvm_context_.gen_store_inst(
                llvm_dim_values[i],
                llvm_name,
                MLLVM::LLVM_i32);
        }

        // call gen_nda
        auto llvm_return_value = llvm_context_.gen_name("tmp");
        llvm_context_.gen_call_inst(
            llvm_return_value,
            "gen_nda",
            "ptr",
            {{"ptr", llvm_dims_array_name},
             {"i32", std::to_string(dim)},
             {"i32", e_type_size}});

        g_llvm_value_ = llvm_return_value;
    }

    /**** print original code ****/
    void LLVMGenerator::
        visitDecl(Decl *decl)
    {
        auto code = std::string(p->print(decl));
        code.pop_back(); // remove the last '\n'

        llvm_context_.gen_comment(code);
        TypeVisitor::visitDecl(decl);
    }

} // namespace JLC::LLVM