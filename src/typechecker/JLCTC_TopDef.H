#ifndef __JLC_TYPE_CHECHER_TOP_DEF_STAGE__
#define __JLC_TYPE_CHECHER_TOP_DEF_STAGE__

#include "context.H"

#include "Absyn.H"
#include "Skeleton.H"

class JLCTC_TopDef : public Skeleton
{
public:
    JLCTC_TopDef() {}
    JLCTC_TopDef(JLCContext context) : globalContext(context) {}
    ~JLCTC_TopDef() = default;

    // get the global context
    JLCContext getContext() const
    {
        return globalContext;
    }

public:
    // inherit from Skeleton
    void visitProgram(Program *p);
    void visitTypeDef(TypeDef *p);
    void visitStructDef(StructDef *p);
    void visitFnDef(FnDef *p);
    void visitFnDefS(FnDefS *p);
    void visitArgument(Argument *p);
    void visitPtrgument(Ptrgument *p);

    void visitInt(Int *p);
    void visitDoub(Doub *p);
    void visitBool(Bool *p);
    void visitVoid(Void *p);
    void visitArrayType(ArrayType *p);
    void visitSArrayType(SArrayType *p);

private:
    JLCContext globalContext;
    JLCType temp_type;
    std::string temp_ident;

    std::vector<std::string> struct_list;
    std::map<std::string, std::string> defined_type_map;

    std::vector<std::string> defined_type_wait_to_check_list;
};

#endif /* __JLC_TYPE_CHECHER_TOP_DEF_STAGE__ */