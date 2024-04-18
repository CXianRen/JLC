#include "JLCTC_TopDef.H"
#include "util.h"

void JLCTC_TopDef::visitProgram(Program *program)
{
    /* Code For Program Goes Here */
    if (program->listtopdef_)
        program->listtopdef_->accept(this);

    // check defined type and struct match
    for (auto & p : defined_type_map)
    {   
        auto type_name = p.first;
        auto struct_name = p.second;
        // look for the struct in the struct list
        bool found = false;
        for (auto &s : struct_list)
        {
            if (s == struct_name)
            {
                found = true;
                break;
            }
        }
        if (!found)
        {
            ERROR_HANDLE("Type: " + struct_name + " is not defined");
        }
        // update to the global context
        globalContext.addDefinedType(struct_name, type_name);
    }

    // after all the types are defined, check if the wait list is empty
    for (auto &type : defined_type_wait_to_check_list)
    {
        if (defined_type_map.find(type) == defined_type_map.end())
        {
            ERROR_HANDLE("Type:" + type + " is not defined");
        }
    }
}

void JLCTC_TopDef::visitTypeDef(TypeDef *type_def)
{
    /* Code For TypeDef Goes Here */
    visitIdent(type_def->ident_1);
    visitIdent(type_def->ident_2);

    DEBUG_PRINT("TypeDef: " + type_def->ident_1 + " * " + type_def->ident_2);
    // add a new defined type
    // defined_type_map
    // check if the type is already defined
    if (defined_type_map.find(type_def->ident_2) != defined_type_map.end())
    {
        ERROR_HANDLE("Type " + type_def->ident_2 + " is already defined");
    }
    defined_type_map[type_def->ident_2] = type_def->ident_1;
}

void JLCTC_TopDef::visitStructDef(StructDef *struct_def)
{
    /* Code For StructDef Goes Here */
    visitIdent(struct_def->ident_);
    DEBUG_PRINT("StructDef: " + struct_def->ident_);
    // check if the struct is already defined
    for (auto &s : struct_list)
    {
        if (s == struct_def->ident_)
        {
            ERROR_HANDLE("Struct " + struct_def->ident_ + " is already defined");
        }
    }
    struct_list.push_back(struct_def->ident_);
    // if (struct_def->listsstmt_)
    //     struct_def->listsstmt_->accept(this);
}

void JLCTC_TopDef::visitFnDef(FnDef *fn_def)
{
    /* Code For FnDef Goes Here */

    if (fn_def->type_)
        fn_def->type_->accept(this);
    auto return_type = temp_type;

    auto func_name = fn_def->ident_;

    DEBUG_PRINT("FnDef: " + func_name + " -> " + to_string(return_type));
    // check if the function is already defined
    if (globalContext.isExistFunc(func_name))
    {
        ERROR_HANDLE("Function " + func_name + " is already defined");
    }

    // add the function to the global context
    globalContext.addFunc(func_name);
    globalContext.currentFuncName = func_name;

    // update the function return type
    auto &func = globalContext.getFunc(func_name);
    func.returnType = return_type;

    // if fuction is main, check if it has int type
    if (func_name == "main" && return_type != INT)
    {
        ERROR_HANDLE("Function main should have int type return");
    }

    // access function arguments
    if (fn_def->listarg_)
        fn_def->listarg_->accept(this);

    // if (fn_def->blk_)
    //     fn_def->blk_->accept(this);
}

void JLCTC_TopDef::visitFnDefS(FnDefS *fn_def_s)
{
    /* Code For FnDefS Goes Here */
    // return type is struct
    auto return_type = JLCType(STRUCT, fn_def_s->ident_1);

    // check if the struct is already defined
    if (defined_type_map.find(fn_def_s->ident_1) == defined_type_map.end())
    {
        // add to the wait list, and check when all the types are defined
        defined_type_wait_to_check_list.push_back(fn_def_s->ident_1);
    }

    // check if the function is already defined
    auto func_name = fn_def_s->ident_2;
    DEBUG_PRINT("FnDefS: " + func_name + " -> " + to_string(return_type));

    if (globalContext.isExistFunc(func_name))
    {
        ERROR_HANDLE("Function " + func_name + " is already defined");
    }

    // add the function to the global context
    globalContext.addFunc(func_name);
    globalContext.currentFuncName = func_name;

    // update the function return type
    auto &func = globalContext.getFunc(func_name);
    func.returnType = return_type;

    // if fuction is main, check if it has int type
    if (func_name == "main" && return_type != INT)
    {
        ERROR_HANDLE("Function main should have int type return");
    }

    if (fn_def_s->listarg_)
        fn_def_s->listarg_->accept(this);
}

void JLCTC_TopDef::visitArgument(Argument *argument)
{
    /* Code For Argument Goes Here */
    if (argument->type_)
        argument->type_->accept(this);
    DEBUG_PRINT("\tArgument name: " + argument->ident_ +
                "\tArgument type: " + to_string(temp_type));
    // check if the type is ok: case 072, void type
    if (temp_type == VOID)
    {
        ERROR_HANDLE("Argument " + argument->ident_ + " in function:" + globalContext.currentFuncName + " has void type");
    }

    auto &func = globalContext.getFunc(globalContext.currentFuncName);
    // check if the argument is already declared
    if (func.isExistArg(argument->ident_))
    {
        ERROR_HANDLE("Argument " + argument->ident_ + " in function:" + globalContext.currentFuncName + " is already declared");
    }
    // add the argument to the function
    func.addArg(argument->ident_, temp_type);
}

void JLCTC_TopDef::visitPtrgument(Ptrgument *ptrgument)
{
    /* Code For Ptrgument Goes Here */
    // check if the ident_1 is a defined type
    DEBUG_PRINT("\tPtrgument name: " + ptrgument->ident_2 +
                "\tPtrgument type: " + ptrgument->ident_1);
    if (defined_type_map.find(ptrgument->ident_1) == defined_type_map.end())
    {
        // add to the wait list, and check when all the types are defined
        defined_type_wait_to_check_list.push_back(ptrgument->ident_1);
    }
    auto &func = globalContext.getFunc(globalContext.currentFuncName);
    // check if the argument is already declared
    if (func.isExistArg(ptrgument->ident_2))
    {
        ERROR_HANDLE("Argument " + ptrgument->ident_2 + " in function:" + globalContext.currentFuncName + " is already declared");
    }
}

// type
void JLCTC_TopDef::visitInt(Int *int_)
{
    /* Code For Int Goes Here */
    temp_type = JLCType(INT);
}

void JLCTC_TopDef::visitDoub(Doub *doub)
{
    /* Code For Doub Goes Here */
    temp_type = JLCType(DOUB);
}

void JLCTC_TopDef::visitBool(Bool *bool_)
{
    /* Code For Bool Goes Here */
    temp_type = JLCType(BOOL);
}

void JLCTC_TopDef::visitVoid(Void *void_)
{
    /* Code For Void Goes Here */
    temp_type = JLCType(VOID);
}

void JLCTC_TopDef::visitArrayType(ArrayType *array_type)
{
    /* Code For ArrayType Goes Here */
    if (array_type->type_)
        array_type->type_->accept(this);
    // element type
    auto temp_array_type = temp_type;
    if (temp_array_type == VOID)
    {
        ERROR_HANDLE("cannot declare a array variable with void type");
    }

    // bracket number
    auto num = array_type->listbracketsopt_->size();
    temp_type = JLCType(ARRAY, temp_array_type.type, num);
}