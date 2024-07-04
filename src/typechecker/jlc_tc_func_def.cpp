#include "typechecker/jlc_tc_func_def.h"
#include "typechecker/jlc_tc_error.h"

namespace JLC::TC
{
    void JLC_FUNC_DEF_Checker::
        visitFuncDef(FuncDef *func_def)
    {
        std::string func_name = func_def->ident_;
        auto func_name_with_scope =
            context_->get_scope_name(func_name,
                                     func_scope_);

        current_func_ =
            context_->get_func(func_name_with_scope);

        if (current_func_ == nullptr)
        {
            // error
            throw JLC::TC::JLCTCError(
                "Function " + func_name + " not found in the context");
        }

        // function body scope start
        current_func_->push_blk();
        JLC::TC::TypeVisitor::visitFuncDef(func_def);
        // function body scope end
        current_func_->pop_blk();
    }

    void JLC_FUNC_DEF_Checker::
        visitBStmt(BStmt *b_stmt)
    {
        // block scope start
        current_func_->push_blk();
        JLC::TC::TypeVisitor::visitBStmt(b_stmt);
        // block scope end
        current_func_->pop_blk();
    }

    void JLC_FUNC_DEF_Checker::
        visitNoInit(NoInit *no_init)
    {
        auto var_type =
            std::make_shared<JLC::TYPE::JLCType>(g_type_);

        // not void type
        if (var_type->type == JLC::TYPE::type_enum::VOID)
        {
            // error
            throw JLC::TC::JLCTCError(
                "Variable type cannot be void");
        }

        auto var_name = no_init->ident_;

        // check if the variable
        // is already defined in the current scope
        if (current_func_->blks.back().has_var(var_name))
        {
            // error
            throw JLC::TC::JLCTCError(
                "Variable " + var_name +
                " already defined in the current scope");
        }

        // DEBUG_PRINT("add variable: " << var_name << " type: " << var_type->str()
        //  << " to function: " << current_func_->name);

        // add the variable to the current scope
        current_func_->add_var(
            JLC::VAR::JLCVar(
                var_name,
                var_type));
    }

    void JLC_FUNC_DEF_Checker::
        visitInit(Init *init)
    {
        /* Code For Init Goes Here */

        auto var_type =
            std::make_shared<JLC::TYPE::JLCType>(g_type_);

        if (var_type->type == JLC::TYPE::type_enum::VOID)
        {
            // error
            throw JLC::TC::JLCTCError(
                "Variable type cannot be void");
        }

        auto var_name = init->ident_;
        // if the variable the name is same as custom type
        // then it is a illegal variable name

        // check if the variable
        // is already defined in the current scope
        if (current_func_->blks.back().has_var(var_name))
        {
            // error
            throw JLC::TC::JLCTCError(
                "Variable " + var_name +
                " already defined in the current scope");
        }

        if (init->expr_)
            init->expr_->accept(this);
        auto init_type =
            std::make_shared<JLC::TYPE::JLCType>(g_type_);

        // check if the variable type
        // is the same as the init type
        if ((*var_type) != (*init_type))
        {
            // error
            throw JLC::TC::JLCTCError(
                "Variable " + var_name + " type is " + var_type->str() +
                " type is not the same as the init type " + init_type->str());
        }

        // add the variable to the current scope
        current_func_->add_var(
            JLC::VAR::JLCVar(var_name, var_type));
    }

    void JLC_FUNC_DEF_Checker::
        visitAss(Ass *ass)
    {
        if (ass->expr_1)
            ass->expr_1->accept(this);
        auto type_left = g_type_;

        if (ass->expr_2)
            ass->expr_2->accept(this);
        auto type_right = g_type_;

        // check if type_left == type_right
        if (type_left != type_right)
        {
            // error
            throw JLC::TC::JLCTCError(
                "Can not assign var type: " + type_right.str() + " to var :" +
                type_left.str());
        }
    }

    void JLC_FUNC_DEF_Checker::
        visitEVar(EVar *e_var)
    {
        auto var_name = e_var->ident_;
        // check if variable is defined

        /*
         * we regard enum as a virtual global variable
         * so that we can access the enum member by dot operator
         */
        if (context_->has_enum(var_name))
        {
            auto enum_obj = context_->get_enum(var_name);
            if (enum_obj == nullptr)
            {
                // error
                throw JLC::TC::JLCTCError(
                    "Enum " + var_name + " not found in the context");
            }
            g_type_ =
                JLC::TYPE::JLCType(
                    JLC::TYPE::type_enum::ENUM, var_name);
            return;
        }

        if (current_func_->has_var(var_name))
        {
            auto var = current_func_->get_var(var_name);

            // set the type of the variable
            g_type_ = *var.type;
            return;
        }

        // if it is a class member function

        if (func_scope_ != GLOBAL_SCOPE)
        {
            // check if the variable is a class member
            auto class_obj = context_->get_class(func_scope_);
            if (class_obj == nullptr)
            {
                DEBUG_PRINT("context:\n"
                            << context_->str());

                // throw error: cannot find the function
                throw JLC::TC::JLCTCError(
                    "Undefined class:" + func_scope_ + ".");
            }

            if (class_obj->has_member(var_name))
            {
                auto member = class_obj->get_member_type(var_name);
                if (member == nullptr)
                {
                    // error
                    throw JLC::TC::JLCTCError(
                        "Variable " + var_name +
                        " not defined in class " + class_obj->obj_name);
                }
                g_type_ = *member;
                return;
            }
        }

        // should not reach here
        throw JLC::TC::JLCTCError(
            "Variable " + var_name +
            " not defined in function " + current_func_->name);
    }

    void JLC_FUNC_DEF_Checker::
        visitEpropety(Epropety *epropety)
    {
        if (epropety->expr_)
            epropety->expr_->accept(this);
        auto obj_type = g_type_;

        auto prop_name = epropety->ident_;

        // length property for array
        if (prop_name == "length")
        {
            if (obj_type.type != JLC::TYPE::type_enum::ARRAY)
            {
                // error
                throw JLC::TC::JLCTCError(
                    "Property length is not defined for type " +
                    obj_type.str());
            }

            // set the type of the property
            g_type_ = JLC::TYPE::JLCType(JLC::TYPE::type_enum::INT);
            return;
        }
        // enum
        if (obj_type.type == JLC::TYPE::type_enum::ENUM)
        {
            auto type_name = obj_type.obj_name;
            auto enum_obj = context_->get_enum(type_name);
            if (enum_obj == nullptr)
            {
                // error
                throw JLC::TC::JLCTCError(
                    "Enum " + type_name + " not found in the context");
            }

            if (!enum_obj->has_member(prop_name))
            {
                // error
                throw JLC::TC::JLCTCError(
                    "Property " + prop_name +
                    " is not defined for enum " + type_name);
            }
            // do not set the type of the property
            g_type_ = g_type_;
            return;
        }

        /*
         * struct does not support dot operator
         * instead, we use -> operator to access the member
         */

        // struct
        if (obj_type.type == JLC::TYPE::type_enum::STRUCT)
        {
            auto type_name = obj_type.obj_name;
            auto struct_obj = context_->get_struct(type_name);
            if (struct_obj == nullptr)
            {
                // error
                throw JLC::TC::JLCTCError(
                    "Struct " + type_name + " not found in the context");
            }

            // if (!struct_obj->has_member(prop_name))
            // {
            //     // error
            //     throw JLC::TC::JLCTCError(
            //         "Property " + prop_name +
            //         " is not defined for struct " + type_name);
            // }

            // auto member = struct_obj->get_member_type(prop_name);
            // if (member == nullptr)
            // {
            //     // error
            //     throw JLC::TC::JLCTCError(
            //         "Property " + prop_name +
            //         " is not defined for struct " + type_name);
            // }
            // g_type_ = *member;
            // return;

            // error
            throw JLC::TC::JLCTCError(
                "Struct pointer does not support dot operator, use -> operator instead.");
        }

        // class
        if (obj_type.type == JLC::TYPE::type_enum::CLASS)
        {
            auto type_name = obj_type.obj_name;
            auto class_obj = context_->get_class(type_name);
            if (class_obj == nullptr)
            {
                // error
                throw JLC::TC::JLCTCError(
                    "Class " + type_name + " not found in the context");
            }

            if (!class_obj->has_member(prop_name))
            {
                // error
                throw JLC::TC::JLCTCError(
                    "Property " + prop_name +
                    " is not defined for class " + type_name);
            }

            auto member = class_obj->get_member_type(prop_name);
            if (member == nullptr)
            {
                // error
                throw JLC::TC::JLCTCError(
                    "Property " + prop_name +
                    " is not defined for class " + type_name);
            }
            g_type_ = *member;
            return;
        }

        // show not reach here
        throw JLC::TC::JLCTCError(
            "Property " + prop_name +
            " is not defined for type " + obj_type.str());
    }

    void JLC_FUNC_DEF_Checker::
        visitEArrow(EArrow *e_arrow)
    {
        /* Code For EArrow Goes Here */

        if (e_arrow->expr_)
            e_arrow->expr_->accept(this);

        auto obj_type = g_type_;
        auto prop_name = e_arrow->ident_;

        if (obj_type.type == JLC::TYPE::type_enum::STRUCT)
        {
            auto type_name = obj_type.obj_name;
            auto struct_obj = context_->get_struct(type_name);
            if (struct_obj == nullptr)
            {
                // error
                throw JLC::TC::JLCTCError(
                    "Struct " + type_name + " not found in the context");
            }

            if (!struct_obj->has_member(prop_name))
            {
                // error
                throw JLC::TC::JLCTCError(
                    "Property " + prop_name +
                    " is not defined for struct " + type_name);
            }

            auto member = struct_obj->get_member_type(prop_name);
            if (member == nullptr)
            {
                // error
                throw JLC::TC::JLCTCError(
                    "Property " + prop_name +
                    " is not defined for struct " + type_name);
            }
            g_type_ = *member;
            return;
        }
        // error
        throw JLC::TC::JLCTCError(
            "Type " + obj_type.str() + " does not support -> operator.");
    }

    void JLC_FUNC_DEF_Checker::
        checkFuncParams(
            std::shared_ptr<JLC::FUNC::JLCFunc> &func_obj,
            ListExpr *list_expr)
    {
        auto func_name = func_obj->name;
        int idx = 0;
        for (; idx < list_expr->size(); idx++)
        {
            auto arg_expr = list_expr->at(idx);
            arg_expr->accept(this);
            auto arg_type = g_type_;

            if (idx >= func_obj->args.size())
            {
                // error
                throw JLC::TC::JLCTCError(
                    "Function " + func_name + " has more arguments than expected");
            }

            auto arg = func_obj->args.at(idx);
            if ((*arg.type) != arg_type)
            {
                // error
                throw JLC::TC::JLCTCError(
                    "Function " + func_name + " argument " + arg.name +
                    " type is not the same as the expected type " + arg.type->str());
            }
        }
        if (idx < func_obj->args.size())
        {
            // error
            throw JLC::TC::JLCTCError(
                "Function " + func_name + " has less arguments than expected");
        }

        // return type is the function type
        g_type_ = *func_obj->return_type;
    }

    void JLC_FUNC_DEF_Checker::
        visitEApp(EApp *e_app)
    {
        visitIdent(e_app->ident_);
        auto func_name = e_app->ident_;
        auto func_name_with_scope =
            context_->get_scope_name(func_name,
                                     GLOBAL_SCOPE);
        auto func_obj = context_->get_func(func_name_with_scope);

        if (func_obj == nullptr)
        {
            // error
            throw JLC::TC::JLCTCError(
                "Function " + func_name + " not found in the context");
        }

        // check parameters
        checkFuncParams(func_obj, e_app->listexpr_);
    }

    void JLC_FUNC_DEF_Checker::
        visitEFunc(EFunc *e_func)
    {
        if (e_func->expr_)
            e_func->expr_->accept(this);
        auto type = g_type_;

        // check if the type is a class
        if (type.type != JLC::TYPE::type_enum::CLASS)
        {
            // error
            throw JLC::TC::JLCTCError(
                "Type " + type.str() +
                " does not have a member function " +
                e_func->ident_);
        }

        auto scope = type.obj_name;
        auto func_name = e_func->ident_;
        auto func_name_with_scope =
            context_->get_scope_name(func_name,
                                     scope);
        // check if the function is defined
        auto func_obj = context_->get_func(func_name_with_scope);

        if (func_obj == nullptr)
        {
            // error
            throw JLC::TC::JLCTCError(
                "Function " + func_name +
                " not found in the context");
        }

        checkFuncParams(func_obj, e_func->listexpr_);
    }

    void JLC_FUNC_DEF_Checker::
        visitENewObj(ENewObj *e_new_obj)
    {
        auto type_name = e_new_obj->ident_;
        // check if the type is a class or struct
        if (context_->has_class(type_name))
        {
            g_type_ = JLC::TYPE::JLCType(JLC::TYPE::type_enum::CLASS, type_name);
            return;
        }
        if (context_->has_struct(type_name))
        {
            g_type_ = JLC::TYPE::JLCType(JLC::TYPE::type_enum::STRUCT, type_name);
            return;
        }

        // error
        throw JLC::TC::JLCTCError(
            "Type " + type_name + " not found.");
    }

    void JLC_FUNC_DEF_Checker::
        visitENewBArr(ENewBArr *e_new_b_arr)
    {
        if (e_new_b_arr->btype_)
            e_new_b_arr->btype_->accept(this);

        auto type = g_type_;
        // check if the type is INT, DOUBLE, BOOL
        if (type.type != JLC::TYPE::type_enum::INT &&
            type.type != JLC::TYPE::type_enum::DOUB &&
            type.type != JLC::TYPE::type_enum::BOOL)
        {
            // error
            throw JLC::TC::JLCTCError(
                "Type " + type.str() + " is not supported for barray.");
        }

        auto list_dim_expr = e_new_b_arr->listdimexpr_;
        for (ListDimExpr::iterator i = list_dim_expr->begin(); i != list_dim_expr->end(); ++i)
        {
            (*i)->accept(this);
            auto type = g_type_;
            // check if the type is INT
            if (type.type != JLC::TYPE::type_enum::INT)
            {
                // error
                throw JLC::TC::JLCTCError(
                    "[] operator only supports INT type, but got " + type.str());
            }
        }

        int dim = list_dim_expr->size();
        // dim should be at least 1
        if (dim == 0)
        {
            // error
            throw JLC::TC::JLCTCError(
                "[] operator should have at least one dimension.");
        }

        // generate N dim array type
        auto base_type = std::make_shared<JLC::TYPE::JLCType>(type);
        for (int i = 0; i < dim; i++)
        {
            base_type = std::make_shared<JLC::TYPE::JLCType>(
                JLC::TYPE::type_enum::ARRAY, base_type);
        }
        g_type_ = *base_type;
    }

    void JLC_FUNC_DEF_Checker::
        visitENewOArr(ENewOArr *e_new_o_arr)
    {

        if (e_new_o_arr->otype_)
            e_new_o_arr->otype_->accept(this);

        auto type = g_type_;
        // check if the type is struct or class
        if (type.type != JLC::TYPE::type_enum::STRUCT &&
            type.type != JLC::TYPE::type_enum::CLASS)
        {
            // error
            throw JLC::TC::JLCTCError(
                "Type " + type.str() + " is not supported for oarray.");
        }

        auto list_dim_expr = e_new_o_arr->listdimexpr_;
        for (ListDimExpr::iterator i = list_dim_expr->begin(); i != list_dim_expr->end(); ++i)
        {
            (*i)->accept(this);
            auto type = g_type_;
            // check if the type is INT
            if (type.type != JLC::TYPE::type_enum::INT)
            {
                // error
                throw JLC::TC::JLCTCError(
                    "[] operator only supports INT type, but got " + type.str());
            }
        }

        int dim = list_dim_expr->size();
        // dim should be at least 1
        if (dim == 0)
        {
            // error
            throw JLC::TC::JLCTCError(
                "[] operator should have at least one dimension.");
        }

        // generate N dim array type
        auto base_type = std::make_shared<JLC::TYPE::JLCType>(type);
        for (int i = 0; i < dim; i++)
        {
            base_type = std::make_shared<JLC::TYPE::JLCType>(
                JLC::TYPE::type_enum::ARRAY, base_type);
        }
        g_type_ = *base_type;
    }

    void JLC_FUNC_DEF_Checker::
        visitEAcc(EAcc *e_acc)
    {
        if (e_acc->expr_)
            e_acc->expr_->accept(this);
        auto obj_type = g_type_;
        // check if the type is an array
        if (obj_type.type != JLC::TYPE::type_enum::ARRAY)
        {
            // error
            throw JLC::TC::JLCTCError(
                "Type " + obj_type.str() + " does not support [] operator.");
        }

        // get the max dimension of the array
        int max_dim = 0;
        auto base_type = obj_type;
        while (base_type.type == JLC::TYPE::type_enum::ARRAY)
        {
            max_dim++;
            base_type = *base_type.base_type;
        }

        auto list_dim_expr = e_acc->listdimexpr_;
        int accessed_dim = list_dim_expr->size();

        // if the accessed dimension is larger than the max dimension
        if (accessed_dim > max_dim)
        {
            // error
            throw JLC::TC::JLCTCError(
                "Array accessed dimension " + std::to_string(accessed_dim) +
                " is larger than the max dimension " + std::to_string(max_dim));
        }

        for (ListDimExpr::iterator i = list_dim_expr->begin(); i != list_dim_expr->end(); ++i)
        {
            (*i)->accept(this);
            auto type = g_type_;
            // check if the type is INT
            if (type.type != JLC::TYPE::type_enum::INT)
            {
                // error
                throw JLC::TC::JLCTCError(
                    "[] operator only supports INT type, but got " + type.str());
            }
        }

        // get the type of N - accessed_dim dimension array
        base_type = obj_type;
        for (int i = 0; i < accessed_dim; i++)
        {
            base_type = *base_type.base_type;
        }
        g_type_ = base_type;
    }

    /************* operator ***************/
    void JLC_FUNC_DEF_Checker::
        visitEInc(EInc *e_inc)
    {
        if (e_inc->expr_)
            e_inc->expr_->accept(this);
        auto type = g_type_;
        // check if the type is INT
        if (type.type != JLC::TYPE::type_enum::INT)
        {
            // error
            throw JLC::TC::JLCTCError(
                "++ operator only supports INT type, but got " + type.str());
        }
    }

    void JLC_FUNC_DEF_Checker::
        visitEDecr(EDecr *e_decr)
    {
        if (e_decr->expr_)
            e_decr->expr_->accept(this);
        auto type = g_type_;
        // check if the type is INT
        if (type.type != JLC::TYPE::type_enum::INT)
        {
            // error
            throw JLC::TC::JLCTCError(
                "-- operator only supports INT type, but got " + type.str());
        }
    }

    void JLC_FUNC_DEF_Checker::
        visitENeg(ENeg *e_neg)
    {
        if (e_neg->expr_)
            e_neg->expr_->accept(this);
        auto type = g_type_;
        // check if the type is INT or DOUBLE
        if (type.type != JLC::TYPE::type_enum::INT &&
            type.type != JLC::TYPE::type_enum::DOUB)
        {
            // error
            throw JLC::TC::JLCTCError(
                "- operator only supports INT or DOUBLE type, but got " + type.str());
        }
    }

    void JLC_FUNC_DEF_Checker::
        visitENot(ENot *e_not)
    {
        if (e_not->expr_)
            e_not->expr_->accept(this);
        auto type = g_type_;
        // check if the type is BOOL
        if (type.type != JLC::TYPE::type_enum::BOOL)
        {
            // error
            throw JLC::TC::JLCTCError(
                "! operator only supports BOOL type, but got " + type.str());
        }
    }

    void JLC_FUNC_DEF_Checker::
        visitEMul(EMul *e_mul)
    {
        /* Code For EMul Goes Here */

        if (e_mul->expr_1)
            e_mul->expr_1->accept(this);
        auto type_left = g_type_;

        if (e_mul->mulop_)
            e_mul->mulop_->accept(this);
        auto mul_op = g_mul_op_;

        if (e_mul->expr_2)
            e_mul->expr_2->accept(this);
        auto type_right = g_type_;

        // DEBUG_PRINT(
        //     "type_left: " << type_left.str()
        //                   << " " << JLC::OP::str(mul_op)
        //                   << " type_right: " << type_right.str());

        // check if type is INT or DOUBLE
        if (type_left.type != JLC::TYPE::type_enum::INT &&
            type_left.type != JLC::TYPE::type_enum::DOUB)
        {
            // error
            throw JLC::TC::JLCTCError(
                "Can not perform " + JLC::OP::str(mul_op) +
                " operation on type: " + type_left.str());
        }

        // check if type_left == type_right
        if (type_left != type_right)
        {
            // error
            throw JLC::TC::JLCTCError(
                "Can not perform " + JLC::OP::str(mul_op) +
                " operation on type: " + type_right.str() + " and type: " + type_left.str());
        }

        // if op is MOD, then the type should be INT
        if (mul_op == JLC::OP::MOD)
        {
            if (type_left.type != JLC::TYPE::type_enum::INT)
            {
                // error
                throw JLC::TC::JLCTCError(
                    "Can not perform " + JLC::OP::str(mul_op) +
                    " operation on type: " + type_left.str());
            }
        }
    }

    void JLC_FUNC_DEF_Checker::
        visitEAdd(EAdd *e_add)
    {
        if (e_add->expr_1)
            e_add->expr_1->accept(this);
        auto type_left = g_type_;

        if (e_add->addop_)
            e_add->addop_->accept(this);
        if (e_add->expr_2)
            e_add->expr_2->accept(this);
        auto type_right = g_type_;

        // check if type is INT or DOUBLE
        if (type_left.type != JLC::TYPE::type_enum::INT &&
            type_left.type != JLC::TYPE::type_enum::DOUB)
        {
            // error
            throw JLC::TC::JLCTCError(
                "Can not perform " + JLC::OP::str(g_add_op_) +
                " operation on type: " + type_left.str());
        }

        // check if type_left == type_right
        if (type_left != type_right)
        {
            // error
            throw JLC::TC::JLCTCError(
                "Can not perform " + JLC::OP::str(g_add_op_) +
                " operation on type: " + type_right.str() + " and type: " + type_left.str());
        }
    }

    void JLC_FUNC_DEF_Checker::
        visitERel(ERel *e_rel)
    {
        if (e_rel->expr_1)
            e_rel->expr_1->accept(this);
        auto type_left = g_type_;

        if (e_rel->relop_)
            e_rel->relop_->accept(this);

        if (e_rel->expr_2)
            e_rel->expr_2->accept(this);
        auto type_right = g_type_;

        // check if rel op is == or !=
        if (g_rel_op_ == JLC::OP::EQU || g_rel_op_ == JLC::OP::NE)
        {
            // @todo, we now allow all types to compare by == and !=
        }
        else
        {
            // check if type is INT or DOUBLE
            if (type_left.type != JLC::TYPE::type_enum::INT &&
                type_left.type != JLC::TYPE::type_enum::DOUB)
            {
                // error
                throw JLC::TC::JLCTCError(
                    "Can not perform " + JLC::OP::str(g_rel_op_) +
                    " operation on type: " + type_left.str());
            }
        }

        // check if type_left == type_right
        if (type_left != type_right)
        {
            // error
            throw JLC::TC::JLCTCError(
                "Can not perform " + JLC::OP::str(g_rel_op_) +
                " operation on type: " + type_right.str() + " and type: " + type_left.str());
        }

        // set the type of the expression
        g_type_ = JLC::TYPE::JLCType(JLC::TYPE::type_enum::BOOL);
    }

    void JLC_FUNC_DEF_Checker::
        visitEAnd(EAnd *e_and)
    {
        if (e_and->expr_1)
            e_and->expr_1->accept(this);
        auto type_left = g_type_;
        if (e_and->expr_2)
            e_and->expr_2->accept(this);
        auto type_right = g_type_;

        // check if type is BOOL
        if (type_left.type != JLC::TYPE::type_enum::BOOL)
        {
            // error
            throw JLC::TC::JLCTCError(
                "Can not perform && operation on type: " + type_left.str());
        }

        // check if type_left == type_right
        if (type_left != type_right)
        {
            // error
            throw JLC::TC::JLCTCError(
                "Can not perform && operation on type: " + type_right.str() + " and type: " + type_left.str());
        }
    }

    void JLC_FUNC_DEF_Checker::
        visitEOr(EOr *e_or)
    {

        if (e_or->expr_1)
            e_or->expr_1->accept(this);
        auto type_left = g_type_;
        if (e_or->expr_2)
            e_or->expr_2->accept(this);
        auto type_right = g_type_;

        // check if type is BOOL
        if (type_left.type != JLC::TYPE::type_enum::BOOL)
        {
            // error
            throw JLC::TC::JLCTCError(
                "Can not perform || operation on type: " + type_left.str());
        }

        // check if type_left == type_right

        if (type_left != type_right)
        {
            // error
            throw JLC::TC::JLCTCError(
                "Can not perform || operation on type: " + type_right.str() + " and type: " + type_left.str());
        }
    }

    void JLC_FUNC_DEF_Checker::
        visitEcast(Ecast *ecast)
    {

        if (ecast->type_)
            ecast->type_->accept(this);
        auto cast_type = g_type_;

        if (ecast->expr_)
            ecast->expr_->accept(this);
        auto type = g_type_;

        g_type_ = cast_type;
    }

    /*************** control ***************/
    void JLC_FUNC_DEF_Checker::
        visitCond(Cond *cond)
    {
        if (cond->expr_)
            cond->expr_->accept(this);
        auto type = g_type_;

        // check if type is BOOL
        if (type.type != JLC::TYPE::type_enum::BOOL)
        {
            // error
            throw JLC::TC::JLCTCError(
                "Condition expression should be BOOL type, but got " + type.str());
        }

        // new block scope
        current_func_->push_blk();
        if (cond->stmt_)
            cond->stmt_->accept(this);
        // pop block scope
        current_func_->pop_blk();
    }

    void JLC_FUNC_DEF_Checker::
        visitCondElse(CondElse *cond_else)
    {
        if (cond_else->expr_)
            cond_else->expr_->accept(this);
        auto type = g_type_;

        // check if type is BOOL
        if (type.type != JLC::TYPE::type_enum::BOOL)
        {
            // error
            throw JLC::TC::JLCTCError(
                "Condition expression should be BOOL type, but got " + type.str());
        }
        // new block scope
        current_func_->push_blk();
        if (cond_else->stmt_1)
            cond_else->stmt_1->accept(this);
        // pop block scope
        current_func_->pop_blk();

        // new block scope
        current_func_->push_blk();
        if (cond_else->stmt_2)
            cond_else->stmt_2->accept(this);
        // pop block scope
        current_func_->pop_blk();
    }

    void JLC_FUNC_DEF_Checker::visitWhile(While *while_)
    {
        if (while_->expr_)
            while_->expr_->accept(this);
        auto type = g_type_;

        // check if type is BOOL
        if (type.type != JLC::TYPE::type_enum::BOOL)
        {
            // error
            throw JLC::TC::JLCTCError(
                "Condition expression should be BOOL type, but got " + type.str());
        }

        // new block scope
        current_func_->push_blk();
        if (while_->stmt_)
            while_->stmt_->accept(this);
        // pop block scope
        current_func_->pop_blk();
    }

    void JLC_FUNC_DEF_Checker::visitForLoop(ForLoop *for_loop)
    {
        // new block scope
        current_func_->push_blk();

        if (for_loop->type_)
            for_loop->type_->accept(this);
        auto elem_type = g_type_;

        visitIdent(for_loop->ident_);
        auto var_name = for_loop->ident_;

        // add the variable to the current scope
        current_func_->add_var(
            JLC::VAR::JLCVar(var_name, std::make_shared<JLC::TYPE::JLCType>(elem_type)));

        if (for_loop->expr_)
            for_loop->expr_->accept(this);
        auto array_type = g_type_;

        // check if the type is an array
        if (array_type.type != JLC::TYPE::type_enum::ARRAY)
        {
            // error
            throw JLC::TC::JLCTCError(
                "Type " + array_type.str() + " is not supported for for loop.");
        }

        // get the base type of the array
        auto base_type = array_type.base_type;
        // check if the base type is the same as the element type
        if ((*base_type) != elem_type)
        {
            // error
            throw JLC::TC::JLCTCError(
                "Array base type " + base_type->str() +
                " is not the same as the element type " + elem_type.str());
        }

        // new block scope
        current_func_->push_blk();
        if (for_loop->stmt_)
            for_loop->stmt_->accept(this);
        // pop block scope
        current_func_->pop_blk();

        // pop block scope
        current_func_->pop_blk();
    }

} // namespace JLC::TC