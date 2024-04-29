#include "JLCTC_StructDef.H"
#include "util.h"

void JLCTC_StructDef::visitStructDef(StructDef *struct_def)
{
    current_struct_name = struct_def->ident_;
    if (struct_def->listsstmt_)
        struct_def->listsstmt_->accept(this);
}

void JLCTC_StructDef::visitMInner(MInner *m_inner)
{
    auto &local_struct = globalContext.getStruct(current_struct_name);
    if (m_inner->type_)
        m_inner->type_->accept(this);
    auto member_type = temp_type;
    // @todo: can we define a void member in a struct?
    auto member_name = m_inner->ident_;

    // check if the member is already defined
    if (local_struct.isExistField(member_name))
    {
        ERROR_HANDLE("redefined member (" + member_name + ") in struct:" + current_struct_name);
    }
    // add the member to the struct
    DEBUG_PRINT("add member:" + to_string(member_type) + " " + member_name + " to struct " + current_struct_name);

    local_struct.addField(member_name, member_type);

}

void JLCTC_StructDef::visitMArray(MArray *m_array)
{
    auto &local_struct = globalContext.getStruct(current_struct_name);
    if (m_array->type_)
        m_array->type_->accept(this);
    auto member_type = temp_type;
    // check if the type is void
    if (member_type == VOID)
    {
        ERROR_HANDLE("cannot declare a array variable with void type");
    }

    int dimension = m_array->listbracketsopt_->size();
    // won't be 0 actually
    if (dimension == 0)
    {
        ERROR_HANDLE("array dimension should be greater than 0");
    }

    member_type = JLCType(ARRAY, member_type.type, dimension);

    auto member_name = m_array->ident_;
    // check if the member is already defined
    if (local_struct.isExistField(member_name))
    {
        ERROR_HANDLE("redefined member in struct");
    }

    // add the member to the struct
    DEBUG_PRINT("add member:" + to_string(member_type) + 
        " " + member_name + " to struct " + current_struct_name);

    local_struct.addField(member_name, member_type);
}

void JLCTC_StructDef::visitMSArray(MSArray *ms_array)
{
    visitIdent(ms_array->ident_1);
    auto defined_type = ms_array->ident_1;
    // check if the struct is defined
    if (!globalContext.isExistDefinedType(defined_type))
    {
        ERROR_HANDLE("Type " + defined_type + " is not defined");
    }

    int dimension = ms_array->listbracketsopt_->size();

    auto local_type = JLCType(ARRAY, STRUCT, dimension, defined_type);

    auto member_name = ms_array->ident_2;
    // check if the member is already defined
    auto &local_struct = globalContext.getStruct(current_struct_name);
    if (local_struct.isExistField(member_name))
    {
        ERROR_HANDLE("redefined member in struct");
    }

    // add the member to the struct
    DEBUG_PRINT("add member:" + to_string(local_type) + " " + member_name + " to struct " + current_struct_name);

    local_struct.addField(member_name, local_type);
}

void JLCTC_StructDef::visitMStruct(MStruct *m_struct)
{
    visitIdent(m_struct->ident_1);
    auto defined_type = m_struct->ident_1;
    // check if the struct is defined
    if (!globalContext.isExistDefinedType(defined_type))
    {
        ERROR_HANDLE("Type " + defined_type + " is not defined");
    }

    auto local_type = JLCType(STRUCT, defined_type);

    auto member_name = m_struct->ident_2;
    // check if the member is already defined
    auto &local_struct = globalContext.getStruct(current_struct_name);
    if (local_struct.isExistField(member_name))
    {
        ERROR_HANDLE("redefined member in struct");
    }
    // add the member to the struct
    DEBUG_PRINT("add member:" + to_string(local_type) + " " + member_name + " to struct " + current_struct_name);

    local_struct.addField(member_name, local_type);
}

// type
void JLCTC_StructDef::visitInt(Int *int_)
{
    /* Code For Int Goes Here */
    temp_type = JLCType(INT);
}

void JLCTC_StructDef::visitDoub(Doub *doub)
{
    /* Code For Doub Goes Here */
    temp_type = JLCType(DOUB);
}

void JLCTC_StructDef::visitBool(Bool *bool_)
{
    /* Code For Bool Goes Here */
    temp_type = JLCType(BOOL);
}

void JLCTC_StructDef::visitVoid(Void *void_)
{
    /* Code For Void Goes Here */
    temp_type = JLCType(VOID);
}

void JLCTC_StructDef::visitArrayType(ArrayType *array_type)
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