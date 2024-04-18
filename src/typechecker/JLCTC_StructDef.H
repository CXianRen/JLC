#ifndef __JLC_TYPE_CHECHER_STRUCT_DEF_STAGE__
#define __JLC_TYPE_CHECHER_STRUCT_DEF_STAGE__

#include "context.H"

#include "Absyn.H"
#include "Skeleton.H"

class JLCTC_StructDef : public Skeleton
{
public:
    JLCTC_StructDef() {}
    JLCTC_StructDef(JLCContext context) : globalContext(context) {}
    ~JLCTC_StructDef() = default;

    // get the global context
    JLCContext getContext() const
    {
        return globalContext;
    }

public:
    // inherit from Skeleton
    void visitStructDef(StructDef *p);
    void visitMInner(MInner *p);
    void visitMArray(MArray *p);
    void visitMSArray(MSArray *p);
    void visitMStruct(MStruct *p);

    void visitInt(Int *p);
    void visitDoub(Doub *p);
    void visitBool(Bool *p);
    void visitVoid(Void *p);
    void visitArrayType(ArrayType *p);

private:
    JLCContext globalContext;
    JLCType temp_type;
    std::string current_struct_name;

};

#endif /* __JLC_TYPE_CHECHER_STRUCT_DEF_STAGE__ */