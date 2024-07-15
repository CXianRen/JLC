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

        // malloc
        llvm_context_.gen_declare_func(
            "calloc",
            "ptr",
            {"i32", "i32"});

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
        push_llvm_value_stack();

        JLC::TC::TypeVisitor::visitFuncDef(func_def);

        // function body scope end
        current_func_->pop_blk();
        pop_llvm_value_stack();

        // function declaration end
        llvm_context_.gen_define_func_end();
    }

    void LLVMGenerator::
        visitBStmt(BStmt *b_stmt)
    {
        // block scope start
        current_func_->push_blk();
        push_llvm_value_stack();
        JLC::TC::TypeVisitor::visitBStmt(b_stmt);
        // block scope end
        current_func_->pop_blk();
        pop_llvm_value_stack();
    }

    void LLVMGenerator::
        visitEApp(EApp *e_app)
    {
        auto func_name = e_app->ident_;
        func_name =
            context_->get_scope_name(func_name,
                                     GLOBAL_SCOPE);
        auto func_obj = context_->get_func(func_name);

        if (func_obj == nullptr)
        {
            // error
            throw JLC::TC::JLCTCError(
                "Function " + func_name + " not found in the context");
        }

        // gen function call
        std::vector<std::pair<std::string, std::string>> llvm_args;
        auto list_expr = e_app->listexpr_;
        for (size_t idx = 0; idx < list_expr->size(); idx++)
        {
            auto arg_expr = list_expr->at(idx);
            arg_expr->accept(this);
            auto arg_type = g_type_;
            llvm_args.push_back(
                {MLLVM::str(jlc_type2llvm_type(arg_type)),
                 g_llvm_value_});
        }

        std::string llvm_return_value = "";
        if (func_obj->return_type->type != JLC::TYPE::VOID)
        {
            llvm_return_value = llvm_context_.gen_name("tmp");
        }

        llvm_context_.gen_call_inst(
            llvm_return_value,
            func_name,
            MLLVM::str(jlc_type2llvm_type(*func_obj->return_type)),
            llvm_args);

        g_type_ = *func_obj->return_type;
        // g_llvm_value_ = llvm_return_value;
        set_global_llvm_value(llvm_return_value);
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
        // if struct class array, the obj is a pointer
        llvm_context_.gen_alloc_inst(
            llvm_name,
            jlc_type2llvm_type(*var_type));

        // add the variable to the llvm_value stack
        add_var_llvm_value(var_name, llvm_name);
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

        // add the variable to the llvm_value stack
        add_var_llvm_value(var_name, llvm_name);

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
            "calloc",
            "ptr",
            {{"i32", std::to_string(obj_size)},
             {"i32", "1"}});

        // store the return value to the llvm_value
        // g_llvm_value_ = llvm_return_value;
        set_global_llvm_value(llvm_return_value);
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

        // g_llvm_value_ = llvm_return_value;
        set_global_llvm_value(llvm_return_value);
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

        std::string e_type_size =
            MLLVM::LLVM_Type_Size_map.at(e_type);

        llvm_context_.gen_comment("multi-dimensional array");
        llvm_context_.gen_comment("object " + type.obj_name + " ptr size:" + e_type_size);

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

        // g_llvm_value_ = llvm_return_value;
        set_global_llvm_value(llvm_return_value);
    }

    /************** variable access ***************/
    void LLVMGenerator::
        visitAss(Ass *ass)
    {
        auto code = std::string(p->print(ass));
        code.pop_back();
        llvm_context_.gen_comment(code);

        left_value_ = true;
        if (ass->expr_1)
            ass->expr_1->accept(this);
        left_value_ = false;

        auto type = g_type_;
        // DEBUG_PRINT("type:" << type.str());

        auto left_llvm_value = g_llvm_value_;

        if (ass->expr_2)
            ass->expr_2->accept(this);
        auto right_llvm_value = g_llvm_value_;

        // gen store instruction
        llvm_context_.gen_store_inst(
            right_llvm_value,
            left_llvm_value,
            jlc_type2llvm_type(type));
    }

    void LLVMGenerator::
        visitEVar(EVar *e_var)
    {
        auto var_name = e_var->ident_;

        if (context_->has_enum(var_name))
        {
            auto enum_obj = context_->get_enum(var_name);
            g_type_ =
                JLC::TYPE::JLCType(
                    JLC::TYPE::type_enum::ENUM, var_name);
            // just return, we don't need to update g_llvm_value,
            // it will be updated in . op.
            return;
        }

        if (current_func_->has_var(var_name))
        {
            auto var = current_func_->get_var(var_name);
            g_type_ = *var.type;
        }

        // get llvm_value of var_name
        auto var_llvm_value = get_var_llvm_value(var_name);
        if (var_llvm_value == "")
        {
            // error
            throw JLCError(
                "Undefined llvm value of var:" + var_name);
        }

        set_global_llvm_value(var_llvm_value);
        if (!left_value_)
        {
            auto loaded_value = llvm_context_.gen_name(var_name);
            // gen load instruction
            llvm_context_.gen_load_inst(
                var_llvm_value,
                loaded_value,
                jlc_type2llvm_type(g_type_));
            set_global_llvm_value(loaded_value);
            return;
        }
    }

    void LLVMGenerator::
        visitEpropety(Epropety *epropety)
    {

        if (epropety->expr_)
            epropety->expr_->accept(this);

        auto obj_type = g_type_;

        auto prop_name = epropety->ident_;

        // length property for array
        if (obj_type.type == JLC::TYPE::type_enum::ARRAY &&
            prop_name == "length")
        {
            if (left_value_)
            {
                throw JLC::TC::JLCTCError(
                    "Array length property is read-only.");
            }

            // gen load instruction
            auto loaded_value = llvm_context_.gen_name("len");
            llvm_context_.gen_load_inst(
                g_llvm_value_,
                loaded_value,
                MLLVM::LLVM_i32);
            set_global_llvm_value(loaded_value);
            g_type_ = JLC::TYPE::JLCType(JLC::TYPE::type_enum::INT);
            return;
        }

        // enum
        if (obj_type.type == JLC::TYPE::type_enum::ENUM)
        {
            if (left_value_)
            {
                throw JLC::TC::JLCTCError(
                    "Enum property is read-only.");
            }

            auto type_name = obj_type.obj_name;
            auto enum_obj = context_->get_enum(type_name);

            // return the const value
            auto enum_ptr = "@" +
                            enum_obj->obj_name + "_" + prop_name;

            auto enum_v = llvm_context_.gen_name("v_" +
                                                 enum_obj->obj_name +
                                                 "_" + prop_name);
            llvm_context_.gen_load_inst(
                enum_ptr,
                enum_v,
                MLLVM::LLVM_i32);

            set_global_llvm_value(enum_v);

            // do not set the type of the property
            g_type_ = obj_type;
            return;
        }

        /*
         * struct does not support dot operator
         * instead, we use -> operator to access the member
         */

        // struct
        if (obj_type.type == JLC::TYPE::type_enum::STRUCT)
        {
            // error
            throw JLC::TC::JLCTCError(
                "Struct pointer does not support . operator, use -> operator instead.");
        }

        // class
        if (obj_type.type == JLC::TYPE::type_enum::CLASS)
        {
            auto type_name = obj_type.obj_name;
            auto class_obj = context_->get_class(type_name);
            auto member_type = class_obj->get_member_type(prop_name);
            auto member_idx = class_obj->get_member_index(prop_name);
            g_type_ = *member_type;

            auto addr_llvm_value = g_llvm_value_;
            if (left_value_)
            {
                // load the address of the obj
                addr_llvm_value = llvm_context_.gen_name("addr");
                llvm_context_.gen_load_inst(
                    g_llvm_value_,
                    addr_llvm_value,
                    MLLVM::LLVM_ptr);
            }

            // gen offset
            auto llvm_offset = llvm_context_.gen_name("a_" + prop_name);
            llvm_context_.gen_offset_field_in_type(
                llvm_offset,
                "%class." + type_name,
                addr_llvm_value,
                member_idx);

            if (left_value_)
            {
                // g_llvm_value_ = llvm_offset;
                set_global_llvm_value(llvm_offset);
            }
            else
            {
                // gen load
                auto loaded_value = llvm_context_.gen_name("v_" + prop_name);
                llvm_context_.gen_load_inst(
                    llvm_offset,
                    loaded_value,
                    jlc_type2llvm_type(*member_type));

                // g_llvm_value_ = loaded_value;
                set_global_llvm_value(loaded_value);
            }
            return;
        }
        // show not reach here
        throw JLC::TC::JLCTCError(
            "Property " + prop_name +
            " is not defined for type " + obj_type.str());
    }

    void LLVMGenerator::
        visitEArrow(EArrow *e_arrow)
    {

        if (e_arrow->expr_)
            e_arrow->expr_->accept(this);

        auto obj_type = g_type_;
        auto prop_name = e_arrow->ident_;

        if (obj_type.type == JLC::TYPE::type_enum::STRUCT)
        {
            auto type_name = obj_type.obj_name;
            auto struct_obj = context_->get_struct(type_name);

            auto member = struct_obj->get_member_type(prop_name);
            g_type_ = *member;

            int member_idx = struct_obj->get_member_index(prop_name);

            auto addr_llvm_value = g_llvm_value_;
            if (left_value_)
            {
                // gen load instruction
                auto loaded_value = llvm_context_.gen_name("a_" + obj_type.obj_name);
                llvm_context_.gen_load_inst(
                    addr_llvm_value,
                    loaded_value,
                    MLLVM::LLVM_ptr);
                addr_llvm_value = loaded_value;
            }
            // gen offset
            auto llvm_offset = llvm_context_.gen_name("a_" + obj_type.obj_name + "_" + prop_name);
            llvm_context_.gen_offset_field_in_type(
                llvm_offset,
                "%struct." + type_name,
                addr_llvm_value,
                member_idx);

            if (left_value_)
            {
                // g_llvm_value_ = llvm_offset;
                set_global_llvm_value(llvm_offset);
                return;
            }
            // gen load
            auto loaded_value = llvm_context_.gen_name("v_" + obj_type.obj_name + "_" + prop_name);
            llvm_context_.gen_load_inst(
                llvm_offset,
                loaded_value,
                jlc_type2llvm_type(*member));

            // g_llvm_value_ = loaded_value;
            set_global_llvm_value(loaded_value);
            return;
        }
        // error
        throw JLC::TC::JLCTCError(
            "Type " + obj_type.str() + " does not support -> operator.");
    }

    void LLVMGenerator::
        visitEAcc(EAcc *e_acc)
    {
        if (e_acc->expr_)
            e_acc->expr_->accept(this);
        auto obj_type = g_type_;

        auto obj_addr = g_llvm_value_;
        if (left_value_)
        {
            auto loaded_value = llvm_context_.gen_name("a_arr");
            llvm_context_.gen_load_inst(
                obj_addr,
                loaded_value,
                MLLVM::LLVM_ptr);
            obj_addr = loaded_value;
        }

        auto list_dim_expr = e_acc->listdimexpr_;
        int accessed_dim = list_dim_expr->size();

        // get the type of N - accessed_dim dimension array
        auto base_type = obj_type;
        for (int i = 0; i < accessed_dim; i++)
        {
            base_type = *base_type.base_type;
        }

        std::string len_llvm_value = "";
        for (ListDimExpr::iterator i = list_dim_expr->begin(); i != list_dim_expr->end(); ++i)
        {
            (*i)->accept(this);
            auto dim_llvm_value = g_llvm_value_;
            // gen offset + 4;
            llvm_context_.gen_comment("+4 (length filed)");
            auto offset_llvm_value = llvm_context_.gen_name("offset");
            llvm_context_.gen_offset_field_in_type(
                offset_llvm_value,
                "[ 0 x " + str(MLLVM::LLVM_i32) + "]",
                obj_addr,
                1);
            obj_addr = offset_llvm_value;
            // gen offset N-th element
            auto e_type = str(MLLVM::LLVM_ptr);
            if (i == list_dim_expr->end() - 1)
            {
                e_type = str(jlc_type2llvm_type(base_type));
            }

            auto llvm_offset = llvm_context_.gen_name("a_elem");
            llvm_context_.gen_offset_field_in_type(
                llvm_offset,
                "[ 0 x " + e_type + "]",
                obj_addr,
                dim_llvm_value);
            obj_addr = llvm_offset;

            // if not the last dimension, load the address
            if (i < list_dim_expr->end() - 1)
            {
                // gen load
                auto loaded_value = llvm_context_.gen_name("v_elem");
                llvm_context_.gen_load_inst(
                    obj_addr,
                    loaded_value,
                    MLLVM::LLVM_ptr);
                obj_addr = loaded_value;
            }
        }
        if (left_value_)
        {
            // g_llvm_value_ = obj_addr;
            set_global_llvm_value(obj_addr);
        }
        else
        {
            // gen load
            auto loaded_value = llvm_context_.gen_name("v_elem");
            llvm_context_.gen_load_inst(
                obj_addr,
                loaded_value,
                jlc_type2llvm_type(base_type));
            // g_llvm_value_ = loaded_value;
            set_global_llvm_value(loaded_value);
        }

        g_type_ = base_type;
    }

    /**************  math operation ***************/
    // ++
    void LLVMGenerator::
        visitEInc(EInc *e_inc)
    {
        left_value_ = true;
        if (e_inc->expr_)
            e_inc->expr_->accept(this);
        left_value_ = false;
        auto llvm_var_addr = g_llvm_value_;

        // load the value
        auto llvm_load_value = llvm_context_.gen_name("t");
        llvm_context_.gen_load_inst(
            llvm_var_addr,
            llvm_load_value,
            jlc_type2llvm_type(g_type_));

        // gen add 1
        auto llvm_return_value = llvm_context_.gen_name("t");
        llvm_context_.gen_add_inst(
            llvm_return_value,
            llvm_load_value,
            "1",
            jlc_type2llvm_type(g_type_));
        // store the value
        llvm_context_.gen_store_inst(
            llvm_return_value,
            llvm_var_addr,
            jlc_type2llvm_type(g_type_));
        // g_llvm_value_ = llvm_return_value;
        set_global_llvm_value(llvm_return_value);
    }

    // --
    void LLVMGenerator::
        visitEDecr(EDecr *e_decr)
    {
        left_value_ = true;
        if (e_decr->expr_)
            e_decr->expr_->accept(this);
        left_value_ = false;
        auto llvm_var_addr = g_llvm_value_;
        // load the value
        auto llvm_load_value = llvm_context_.gen_name("t");
        llvm_context_.gen_load_inst(
            llvm_var_addr,
            llvm_load_value,
            jlc_type2llvm_type(g_type_));

        // gen sub 1
        auto llvm_return_value = llvm_context_.gen_name("tmp");
        llvm_context_.gen_sub_inst(
            llvm_return_value,
            llvm_load_value,
            "1",
            jlc_type2llvm_type(g_type_));

        // store the value
        llvm_context_.gen_store_inst(
            llvm_return_value,
            llvm_var_addr,
            jlc_type2llvm_type(g_type_));

        // g_llvm_value_ = llvm_return_value;
        set_global_llvm_value(llvm_return_value);
    }

    // -
    void LLVMGenerator::
        visitENeg(ENeg *e_neg)
    {
        if (e_neg->expr_)
            e_neg->expr_->accept(this);
        auto type = g_type_;
        auto llvm_return_value = llvm_context_.gen_name("tmp");
        // gen sub 1
        llvm_context_.gen_sub_inst(
            llvm_return_value,
            type.type == JLC::TYPE::type_enum::INT ? "0" : "0.0",
            g_llvm_value_,
            jlc_type2llvm_type(type));
        // g_llvm_value_ = llvm_return_value;
        set_global_llvm_value(llvm_return_value);
    }

    // x / mod
    void LLVMGenerator::
        visitEMul(EMul *e_mul)
    {
        if (e_mul->expr_1)
            e_mul->expr_1->accept(this);
        auto type_left = g_type_;
        auto llvm_left_value = g_llvm_value_;

        if (e_mul->mulop_)
            e_mul->mulop_->accept(this);
        auto mul_op = g_mul_op_;

        if (e_mul->expr_2)
            e_mul->expr_2->accept(this);
        auto type_right = g_type_;
        auto llvm_right_value = g_llvm_value_;

        auto llvm_ret = llvm_context_.gen_name("tmp");
        switch (mul_op)
        {
        case JLC::OP::MulOp::MUL:
            // gen mul
            llvm_context_.gen_mul_inst(
                llvm_ret,
                llvm_left_value,
                llvm_right_value,
                jlc_type2llvm_type(type_left));
            break;

        case JLC::OP::MulOp::DIV:
            llvm_context_.gen_div_inst(
                llvm_ret,
                llvm_left_value,
                llvm_right_value,
                jlc_type2llvm_type(type_left));
            break;

        case JLC::OP::MulOp::MOD:
            llvm_context_.gen_mod_inst(
                llvm_ret,
                llvm_left_value,
                llvm_right_value,
                jlc_type2llvm_type(type_left));
            break;

        default:
            // error
            throw JLCError(
                "Unknown mulop: " + std::to_string(mul_op));
            break;
        }
        // g_llvm_value_ = llvm_ret;
        set_global_llvm_value(llvm_ret);
    }

    // + -
    void LLVMGenerator::
        visitEAdd(EAdd *e_add)
    {
        if (e_add->expr_1)
            e_add->expr_1->accept(this);
        auto type_left = g_type_;
        auto llvm_left_value = g_llvm_value_;

        if (e_add->addop_)
            e_add->addop_->accept(this);
        auto add_op = g_add_op_;

        if (e_add->expr_2)
            e_add->expr_2->accept(this);
        auto type_right = g_type_;
        auto llvm_right_value = g_llvm_value_;

        auto llvm_ret = llvm_context_.gen_name("tmp");
        switch (add_op)
        {
        case JLC::OP::AddOp::ADD:
            // gen add
            llvm_context_.gen_add_inst(
                llvm_ret,
                llvm_left_value,
                llvm_right_value,
                jlc_type2llvm_type(type_left));
            break;

        case JLC::OP::AddOp::SUB:
            // gen sub
            llvm_context_.gen_sub_inst(
                llvm_ret,
                llvm_left_value,
                llvm_right_value,
                jlc_type2llvm_type(type_left));
            break;

        default:
            // error
            throw JLCError(
                "Unknown addop: " + std::to_string(add_op));
            break;
        }
        // g_llvm_value_ = llvm_ret;
        set_global_llvm_value(llvm_ret);
    }

    // !
    void LLVMGenerator::
        visitENot(ENot *e_not)
    {
        if (e_not->expr_)
            e_not->expr_->accept(this);
        auto type = g_type_;
        auto llvm_return_value = llvm_context_.gen_name("tmp");
        // gen sub 1
        llvm_context_.gen_not_inst(
            llvm_return_value,
            g_llvm_value_,
            jlc_type2llvm_type(type));

        // g_llvm_value_ = llvm_return_value;
        set_global_llvm_value(llvm_return_value);
    }

    // > < <= == >= !=
    void LLVMGenerator::
        visitERel(ERel *e_rel)
    {
        if (e_rel->expr_1)
            e_rel->expr_1->accept(this);
        auto type_left = g_type_;
        auto llvm_left_value = g_llvm_value_;

        if (e_rel->relop_)
            e_rel->relop_->accept(this);
        auto relop = g_rel_op_;

        if (e_rel->expr_2)
            e_rel->expr_2->accept(this);
        auto type_right = g_type_;
        auto llvm_right_value = g_llvm_value_;

        auto llvm_ret = llvm_context_.gen_name("tmp");
        switch (relop)
        {
        case JLC::OP::RelOp::LTH:
            llvm_context_.gen_lth_inst(
                llvm_ret,
                llvm_left_value,
                llvm_right_value,
                jlc_type2llvm_type(type_left));
            break;

        case JLC::OP::RelOp::LE:
            llvm_context_.gen_le_inst(
                llvm_ret,
                llvm_left_value,
                llvm_right_value,
                jlc_type2llvm_type(type_left));
            break;

        case JLC::OP::RelOp::GTH:
            llvm_context_.gen_gth_inst(
                llvm_ret,
                llvm_left_value,
                llvm_right_value,
                jlc_type2llvm_type(type_left));
            break;

        case JLC::OP::RelOp::GE:
            llvm_context_.gen_ge_inst(
                llvm_ret,
                llvm_left_value,
                llvm_right_value,
                jlc_type2llvm_type(type_left));
            break;

        case JLC::OP::RelOp::EQU:
            llvm_context_.gen_equ_inst(
                llvm_ret,
                llvm_left_value,
                llvm_right_value,
                jlc_type2llvm_type(type_left));
            break;

        case JLC::OP::RelOp::NE:
            llvm_context_.gen_ne_inst(
                llvm_ret,
                llvm_left_value,
                llvm_right_value,
                jlc_type2llvm_type(type_left));
            break;

        default:
            // error
            throw JLCError(
                "Unknown relop: " + std::to_string(relop));
            break;
        }
        // g_llvm_value_ = llvm_ret;
        set_global_llvm_value(llvm_ret);
    }

    // &&
    void LLVMGenerator::
        visitEAnd(EAnd *e_and)
    {
        auto current_insert_point =
            llvm_context_.get_current_insert_point();

        auto current_insert_point_name =
            current_insert_point->label;
        if (current_insert_point_name == "")
        {
            current_insert_point_name = "entry";
        }

        auto and_true = llvm_context_.new_insert_point("and_true");
        auto and_end = llvm_context_.new_insert_point("and_end");

        if (e_and->expr_1)
            e_and->expr_1->accept(this);
        auto llvm_value_left = g_llvm_value_;

        // if first expression is true,
        // then we need to check the second expression
        llvm_context_.gen_cond_br_inst(
            llvm_value_left,
            and_true->label,
            and_end->label);

        llvm_context_.set_insert_point(and_true);
        if (e_and->expr_2)
            e_and->expr_2->accept(this);
        auto llvm_value_right = g_llvm_value_;
        auto llvm_ip_of_value = g_llvm_insert_point_;

        // then to the and-end  block
        llvm_context_.gen_br_inst(and_end->label);
        llvm_context_.set_insert_point(and_end);

        auto phi_name = llvm_context_.gen_name("and");

        llvm_context_.gen_phi_inst(
            phi_name,
            str(MLLVM::LLVM_i1),
            llvm_value_left,
            current_insert_point_name,
            llvm_value_right,
            llvm_ip_of_value);

        set_global_llvm_value(phi_name);
    }

    // ||
    void LLVMGenerator::
        visitEOr(EOr *e_or)
    {
        auto current_insert_point =
            llvm_context_.get_current_insert_point();

        auto current_insert_point_name =
            current_insert_point->label;
        if (current_insert_point_name == "")
        {
            current_insert_point_name = "entry";
        }

        auto or_fales = llvm_context_.new_insert_point("or_false");
        auto or_end = llvm_context_.new_insert_point("or_end");

        if (e_or->expr_1)
            e_or->expr_1->accept(this);
        auto llvm_value_left = g_llvm_value_;

        // if first expression is false,
        // then we need to check the second expression
        llvm_context_.gen_cond_br_inst(
            llvm_value_left,
            or_end->label,
            or_fales->label);
        llvm_context_.set_insert_point(or_fales);

        if (e_or->expr_2)
            e_or->expr_2->accept(this);
        auto llvm_value_right = g_llvm_value_;
        auto llvm_ip_of_value = g_llvm_insert_point_;

        // then to the or-end  block

        llvm_context_.gen_br_inst(or_end->label);
        llvm_context_.set_insert_point(or_end);

        auto phi_name = llvm_context_.gen_name("or");
        llvm_context_.gen_phi_inst(
            phi_name,
            str(MLLVM::LLVM_i1),
            llvm_value_left,
            current_insert_point_name,
            llvm_value_right,
            llvm_ip_of_value);

        set_global_llvm_value(phi_name);
    }

    /************** Control flow ***************/
    void LLVMGenerator::
        visitCond(Cond *cond)
    {

        auto cond_blk = llvm_context_.new_insert_point("cond");

        auto end_blk = llvm_context_.new_insert_point("end");

        llvm_context_.gen_comment("if(" + std::string(p->print(cond->expr_)) + "){");
        if (cond->expr_)
            cond->expr_->accept(this);
        auto llvm_cond_value = g_llvm_value_;

        // DEBUG_PRINT("cond value:" << llvm_cond_value);
        // gen cond branch
        llvm_context_.gen_cond_br_inst(
            llvm_cond_value,
            cond_blk->label,
            end_blk->label);

        // new block scope
        llvm_context_.set_insert_point(cond_blk);
        current_func_->push_blk();
        if (cond->stmt_)
            cond->stmt_->accept(this);
        // pop block scope
        current_func_->pop_blk();

        if (!llvm_context_.end_with_term_inst(cond_blk))
        {
            llvm_context_.gen_br_inst(end_blk->label);
        }
        llvm_context_.gen_comment("}");
        llvm_context_.set_insert_point(end_blk);
    }

    void LLVMGenerator::
        visitCondElse(CondElse *cond_else)
    {

        auto cond_blk = llvm_context_.new_insert_point("cond");
        auto else_blk = llvm_context_.new_insert_point("else");
        auto end_blk = llvm_context_.new_insert_point("end");

        llvm_context_.gen_comment("if(" + std::string(p->print(cond_else->expr_)) + "){");

        if (cond_else->expr_)
            cond_else->expr_->accept(this);
        auto llvm_cond_value = g_llvm_value_;

        llvm_context_.gen_cond_br_inst(
            llvm_cond_value,
            cond_blk->label,
            else_blk->label);

        llvm_context_.set_insert_point(cond_blk);
        // new block scope
        current_func_->push_blk();
        if (cond_else->stmt_1)
            cond_else->stmt_1->accept(this);
        // pop block scope
        current_func_->pop_blk();

        bool need_end_blk = false;
        if (!llvm_context_.end_with_term_inst(cond_blk))
        {
            need_end_blk = true;
            llvm_context_.gen_br_inst(end_blk->label);
        }
        llvm_context_.gen_comment("} else {");
        llvm_context_.set_insert_point(else_blk);
        // new block scope
        current_func_->push_blk();
        if (cond_else->stmt_2)
            cond_else->stmt_2->accept(this);

        // pop block scope
        current_func_->pop_blk();

        if (!llvm_context_.end_with_term_inst(else_blk))
        {
            need_end_blk = true;
            llvm_context_.gen_br_inst(end_blk->label);
        }
        llvm_context_.gen_comment("}");

        if (need_end_blk)
        {
            llvm_context_.set_insert_point(end_blk);
        }
    }

    void LLVMGenerator::
        visitWhile(While *while_)
    {
        auto cond_blk = llvm_context_.new_insert_point("wcond");
        auto body_blk = llvm_context_.new_insert_point("wbody");
        auto end_blk = llvm_context_.new_insert_point("wend");

        llvm_context_.gen_br_inst(cond_blk->label);
        llvm_context_.set_insert_point(cond_blk);

        if (while_->expr_)
            while_->expr_->accept(this);
        auto llvm_cond_value = g_llvm_value_;

        llvm_context_.gen_cond_br_inst(
            llvm_cond_value,
            body_blk->label,
            end_blk->label);

        llvm_context_.set_insert_point(body_blk);
        // new block scope
        current_func_->push_blk();
        if (while_->stmt_)
            while_->stmt_->accept(this);
        // pop block scope
        current_func_->pop_blk();

        llvm_context_.gen_br_inst(cond_blk->label);

        llvm_context_.set_insert_point(end_blk);
    }

    void LLVMGenerator::
        visitForLoop(ForLoop *for_loop)
    {
        /**
         * for (int x : arr) {
         *      for body
         * }
         * is equal to
         * {
         *  i = 0;
         *  s = arr.lenght
         *  while (i < s) {
         *     i = i +1
         *     x = arr[i]
         *    {
         *      for body
         *    }
         *  }
         * }
         *
         */

        auto code = "for (" + std::string(p->print(for_loop->type_)) +
                    " " + for_loop->ident_ + " : ";
        code += std::string(p->print(for_loop->expr_));
        code += " {";
        llvm_context_.gen_comment(code);

        // new block scope (virtual block)
        current_func_->push_blk();

        if (for_loop->type_)
            for_loop->type_->accept(this);
        auto elem_type = g_type_;

        auto var_name = for_loop->ident_;

        if (for_loop->expr_)
            for_loop->expr_->accept(this);
        auto array_type = g_type_;
        auto llvm_array_value = g_llvm_value_;

        // add the variable to the current scope
        current_func_->add_var(
            JLC::VAR::JLCVar(var_name, std::make_shared<JLC::TYPE::JLCType>(elem_type)));

        auto var_llvm_value = get_var_llvm_value(var_name);
        add_var_llvm_value(var_name, var_llvm_value);

        // get the base type of the array
        auto base_type = array_type.base_type;

        /*
         * {
         *  i = 0;
         *  s = arr.lenght
         *  while (i < s) {
         *     i = i +1
         *     x = arr[i]
         *    {
         *      for body
         *    }
         *  }
         * }
         */
        // allocate new variables, idex: i and length: s
        auto idx = llvm_context_.gen_name("i_");
        auto a_len = llvm_context_.gen_name("s_");
        // allocate i
        llvm_context_.gen_alloc_inst(
            idx,
            MLLVM::LLVM_i32);
        // initialize i = 0
        llvm_context_.gen_store_inst(
            "0",
            idx,
            MLLVM::LLVM_i32);
        // get the length of the array
        llvm_context_.gen_load_inst(
            llvm_array_value,
            a_len,
            MLLVM::LLVM_i32);

        // skip the length field
        auto arr_addr = llvm_context_.gen_name("a_arr_data");
        llvm_context_.gen_offset_field_in_type(
            arr_addr,
            "[ 0 x " + str(MLLVM::LLVM_i32) + "]",
            llvm_array_value,
            1);

        // generate a branch instruction to the condition block
        auto cond_blk = llvm_context_.new_insert_point("fcond");
        auto body_blk = llvm_context_.new_insert_point("fbody");
        auto end_blk = llvm_context_.new_insert_point("fend");

        // jump to the condition block
        llvm_context_.gen_br_inst(cond_blk->label);
        llvm_context_.set_insert_point(cond_blk);

        // load the value of i
        auto i_value = llvm_context_.gen_name("v_i_");
        llvm_context_.gen_load_inst(
            idx,
            i_value,
            MLLVM::LLVM_i32);

        // compare i < s
        auto cond_value = llvm_context_.gen_name("cond");
        llvm_context_.gen_lth_inst(
            cond_value,
            i_value,
            a_len,
            MLLVM::LLVM_i32);

        // jump to the body block or end block
        llvm_context_.gen_cond_br_inst(
            cond_value,
            body_blk->label,
            end_blk->label);

        // body block
        llvm_context_.set_insert_point(body_blk);

        // calculate the address of the element
        auto elem_addr = llvm_context_.gen_name("a_elem_");
        llvm_context_.gen_offset_field_in_type(
            elem_addr,
            "[ 0 x " + str(jlc_type2llvm_type(*base_type)) + "]",
            arr_addr,
            i_value);

        // update var x's llvm value, so that we can access it in the body
        add_var_llvm_value(var_name, elem_addr);

        // update the index i
        auto i_plus_1 = llvm_context_.gen_name("i_n_");
        llvm_context_.gen_add_inst(
            i_plus_1,
            i_value,
            "1",
            MLLVM::LLVM_i32);
        llvm_context_.gen_store_inst(
            i_plus_1,
            idx,
            MLLVM::LLVM_i32);

        // new block scope
        current_func_->push_blk();
        if (for_loop->stmt_)
            for_loop->stmt_->accept(this);
        // pop block scope
        current_func_->pop_blk();

        // jump to the condition block
        llvm_context_.gen_br_inst(cond_blk->label);

        // pop block scope
        current_func_->pop_blk();

        // end block
        llvm_context_.set_insert_point(end_blk);
        llvm_context_.gen_comment("}");
    }

    void LLVMGenerator::
        visitVRet(VRet *v_ret)
    {
        JLC_FUNC_DEF_Checker::visitVRet(v_ret);
        llvm_context_.gen_return_inst("", MLLVM::LLVM_void);
    }

    void LLVMGenerator::
        visitRet(Ret *ret)
    {
        JLC_FUNC_DEF_Checker::visitRet(ret);

        auto type = g_type_;

        llvm_context_.gen_return_inst(
            g_llvm_value_,
            jlc_type2llvm_type(type));
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

    void LLVMGenerator::
        visitSExp(SExp *s_exp)
    {
        auto code = std::string(p->print(s_exp));
        code.pop_back(); // remove the last '\n'
        llvm_context_.gen_comment(code);

        TypeVisitor::visitSExp(s_exp);
    }

} // namespace JLC::LLVM